/*
  ==============================================================================

   This file is part of the JUCE library.
   Copyright (c) 2013 - Raw Material Software Ltd.

   Permission is granted to use this software under the terms of either:
   a) the GPL v2 (or any later version)
   b) the Affero GPL v3

   Details of these licenses can be found at: www.gnu.org/licenses

   JUCE is distributed in the hope that it will be useful, but WITHOUT ANY
   WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR
   A PARTICULAR PURPOSE.  See the GNU General Public License for more details.

   ------------------------------------------------------------------------------

   To release a closed-source product which uses JUCE, commercial licenses are
   available: visit www.juce.com for more information.
  ==============================================================================


  April 26 2014 : Adapted by Xavier Hosxe to fit PreenfM2 conroller requirement
*/

#ifndef PFM2_WINDOW_H_INCLUDED
#define PFM2_WINDOW_H_INCLUDED

#define JUCE_NO_DEPRECATION_WARNINGS 1


#if JUCE_MODULE_AVAILABLE_juce_audio_plugin_client
extern juce::AudioProcessor* JUCE_API JUCE_CALLTYPE createPluginFilterOfType(juce::AudioProcessor::WrapperType type);
#else
extern juce::AudioProcessor* JUCE_API JUCE_CALLTYPE createPluginFilter();

#endif

namespace juce
{


	//==============================================================================
	/**
		An object that creates and plays a standalone instance of an AudioProcessor.
		The object will create your processor using the same createPluginFilter()
		function that the other plugin wrappers use, and will run it through the
		computer's audio/MIDI devices using AudioDeviceManager and AudioProcessorPlayer.
		@tags{Audio}
	*/
	class StandalonePluginHolder : private AudioIODeviceCallback,
		private Timer,
		private Value::Listener
	{
public:
	//==============================================================================
	/** Structure used for the number of inputs and outputs. */
	struct PluginInOuts { short numIns, numOuts; };

	//==============================================================================
	/** Creates an instance of the default plugin.
		The settings object can be a PropertySet that the class should use to store its
		settings - the takeOwnershipOfSettings indicates whether this object will delete
		the settings automatically when no longer needed. The settings can also be nullptr.
		A default device name can be passed in.
		Preferably a complete setup options object can be used, which takes precedence over
		the preferredDefaultDeviceName and allows you to select the input & output device names,
		sample rate, buffer size etc.
		In all instances, the settingsToUse will take precedence over the "preferred" options if not null.
	*/
	StandalonePluginHolder(PropertySet* settingsToUse,
		bool takeOwnershipOfSettings = true,
		const String& preferredDefaultDeviceName = String(),
		const AudioDeviceManager::AudioDeviceSetup* preferredSetupOptions = nullptr,
		const Array<PluginInOuts>& channels = Array<PluginInOuts>(),
#if JUCE_ANDROID || JUCE_IOS
		bool shouldAutoOpenMidiDevices = true
#else
		bool shouldAutoOpenMidiDevices = false
#endif
	)

		: settings(settingsToUse, takeOwnershipOfSettings),
		channelConfiguration(channels),
		autoOpenMidiDevices(shouldAutoOpenMidiDevices)
	{
		shouldMuteInput.addListener(this);
		shouldMuteInput = !isInterAppAudioConnected();

		createPlugin();

		auto inChannels = (channelConfiguration.size() > 0 ? channelConfiguration[0].numIns
			: processor->getMainBusNumInputChannels());

		if (preferredSetupOptions != nullptr)
			options.reset(new AudioDeviceManager::AudioDeviceSetup(*preferredSetupOptions));

		auto audioInputRequired = (inChannels > 0);

		if (audioInputRequired && RuntimePermissions::isRequired(RuntimePermissions::recordAudio)
			&& !RuntimePermissions::isGranted(RuntimePermissions::recordAudio))
			RuntimePermissions::request(RuntimePermissions::recordAudio,
				[this, preferredDefaultDeviceName](bool granted) { init(granted, preferredDefaultDeviceName); });
		else
			init(audioInputRequired, preferredDefaultDeviceName);
	}

	void init(bool enableAudioInput, const String& preferredDefaultDeviceName)
	{
		setupAudioDevices(enableAudioInput, preferredDefaultDeviceName, options.get());
		reloadPluginState();
		startPlaying();

		if (autoOpenMidiDevices)
			startTimer(500);
	}

	virtual ~StandalonePluginHolder() override
	{
		stopTimer();

		deletePlugin();
		shutDownAudioDevices();
	}

	//==============================================================================
	virtual void createPlugin()
	{
#if JUCE_MODULE_AVAILABLE_juce_audio_plugin_client
		processor.reset(::createPluginFilterOfType(AudioProcessor::wrapperType_Standalone));
#else
		AudioProcessor::setTypeOfNextNewPlugin(AudioProcessor::wrapperType_Standalone);
		processor.reset(createPluginFilter());
		AudioProcessor::setTypeOfNextNewPlugin(AudioProcessor::wrapperType_Undefined);
#endif
		jassert(processor != nullptr); // Your createPluginFilter() function must return a valid object!

		processor->disableNonMainBuses();
		processor->setRateAndBufferSizeDetails(44100, 512);

		int inChannels = (channelConfiguration.size() > 0 ? channelConfiguration[0].numIns
			: processor->getMainBusNumInputChannels());

		int outChannels = (channelConfiguration.size() > 0 ? channelConfiguration[0].numOuts
			: processor->getMainBusNumOutputChannels());

		processorHasPotentialFeedbackLoop = (inChannels > 0 && outChannels > 0);
	}

	virtual void deletePlugin()
	{
		stopPlaying();
		processor = nullptr;
	}


	//==============================================================================
	Value& getMuteInputValue() { return shouldMuteInput; }
	bool getProcessorHasPotentialFeedbackLoop() const { return processorHasPotentialFeedbackLoop; }
	void valueChanged(Value& value) override { muteInput = (bool)value.getValue(); }
	//==============================================================================

	File getLastFile() const
	{
		File f;

		if (settings != nullptr)
			f = File(settings->getValue("lastStateFile"));

		if (f == File())
			f = File::getSpecialLocation(File::userDocumentsDirectory);

		return f;
	}

	void setLastFile(const FileChooser& fc)
	{
		if (settings != nullptr)
			settings->setValue("lastStateFile", fc.getResult().getFullPathName());
	}

	/** Pops up a dialog letting the user save the processor's state to a file. */
	void askUserToSaveState()
	{
#if JUCE_MODAL_LOOPS_PERMITTED
		FileChooser fc(TRANS("Save current preset"), getLastFile(), "*.pfm2;*");

		if (fc.browseForFileToSave(true))
		{
			setLastFile(fc);

			MemoryBlock data;
			processor->getStateInformation(data);

			if (!fc.getResult().replaceWithData(data.getData(), data.getSize()))
				AlertWindow::showMessageBoxAsync(AlertWindow::WarningIcon,
					TRANS("Error whilst saving"),
					TRANS("Couldn't write to the specified file!"));
		}
#else
		ignoreUnused(fileSuffix);
#endif
	}

	/** Pops up a dialog letting the user re-load the processor's state from a file. */
	void askUserToLoadState()
	{
#if JUCE_MODAL_LOOPS_PERMITTED
		FileChooser fc(TRANS("Load a saved preset"), getLastFile(), "*.pfm2;*");

		if (fc.browseForFileToOpen())
		{
			setLastFile(fc);

			MemoryBlock data;

			if (fc.getResult().loadFileAsData(data))
				processor->setStateInformation(data.getData(), (int)data.getSize());
			else
				AlertWindow::showMessageBoxAsync(AlertWindow::WarningIcon,
					TRANS("Error whilst loading"),
					TRANS("Couldn't read from the specified file!"));
		}
#else
		ignoreUnused(fileSuffix);
#endif
	}

	//==============================================================================
	void startPlaying()
	{
		player.setProcessor(processor.get());

#if JucePlugin_Enable_IAA && JUCE_IOS
		if (auto device = dynamic_cast<iOSAudioIODevice*> (deviceManager.getCurrentAudioDevice()))
		{
			processor->setPlayHead(device->getAudioPlayHead());
			device->setMidiMessageCollector(&player.getMidiMessageCollector());
		}
#endif
	}

	void stopPlaying()
	{
		player.setProcessor(nullptr);
	}

	//==============================================================================
	/** Shows an audio properties dialog box modally. */
	void showAudioSettingsDialog()
	{
		DialogWindow::LaunchOptions o;

		int minNumInputs = std::numeric_limits<int>::max(), maxNumInputs = 0,
			minNumOutputs = std::numeric_limits<int>::max(), maxNumOutputs = 0;

		auto updateMinAndMax = [](int newValue, int& minValue, int& maxValue)
		{
			minValue = jmin(minValue, newValue);
			maxValue = jmax(maxValue, newValue);
		};

		if (channelConfiguration.size() > 0)
		{
			auto defaultConfig = channelConfiguration.getReference(0);
			updateMinAndMax((int)defaultConfig.numIns, minNumInputs, maxNumInputs);
			updateMinAndMax((int)defaultConfig.numOuts, minNumOutputs, maxNumOutputs);
		}

		if (auto* bus = processor->getBus(true, 0))
			updateMinAndMax(bus->getDefaultLayout().size(), minNumInputs, maxNumInputs);

		if (auto* bus = processor->getBus(false, 0))
			updateMinAndMax(bus->getDefaultLayout().size(), minNumOutputs, maxNumOutputs);


		o.content.setOwned(new SettingsComponent(*this, deviceManager, 0, 0, 0, 0));
		o.content->setSize(500, 550);

		o.dialogTitle = TRANS("Midi Input");
		o.dialogBackgroundColour = o.content->getLookAndFeel().findColour(ResizableWindow::backgroundColourId);
		o.escapeKeyTriggersCloseButton = true;
		o.useNativeTitleBar = true;
		o.resizable = false;

		o.launchAsync();
	}

	void saveAudioDeviceState()
	{
		if (settings != nullptr)
		{
			auto xml = deviceManager.createStateXml();

			settings->setValue("audioSetup", xml.get());

#if ! (JUCE_IOS || JUCE_ANDROID)
			settings->setValue("shouldMuteInput", (bool)shouldMuteInput.getValue());
#endif
		}
	}

	void reloadAudioDeviceState(bool enableAudioInput,
		const String& preferredDefaultDeviceName,
		const AudioDeviceManager::AudioDeviceSetup* preferredSetupOptions)
	{
		std::unique_ptr<XmlElement> savedState;

		if (settings != nullptr)
		{
			savedState = settings->getXmlValue("audioSetup");

#if ! (JUCE_IOS || JUCE_ANDROID)
			shouldMuteInput.setValue(settings->getBoolValue("shouldMuteInput", true));
#endif
		}

		auto totalInChannels = processor->getMainBusNumInputChannels();
		auto totalOutChannels = processor->getMainBusNumOutputChannels();

		if (channelConfiguration.size() > 0)
		{
			auto defaultConfig = channelConfiguration.getReference(0);
			totalInChannels = defaultConfig.numIns;
			totalOutChannels = defaultConfig.numOuts;
		}

		deviceManager.initialise(enableAudioInput ? totalInChannels : 0,
			totalOutChannels,
			savedState.get(),
			true,
			preferredDefaultDeviceName,
			preferredSetupOptions);
	}

	//==============================================================================
	void savePluginState()
	{
		if (settings != nullptr && processor != nullptr)
		{
			MemoryBlock data;
			processor->getStateInformation(data);

			settings->setValue("filterState", data.toBase64Encoding());
		}
	}

	void reloadPluginState()
	{
		if (settings != nullptr)
		{
			MemoryBlock data;

			if (data.fromBase64Encoding(settings->getValue("filterState")) && data.getSize() > 0)
				processor->setStateInformation(data.getData(), (int)data.getSize());
		}
	}

	//==============================================================================
	void quickHelp()
	{
		AlertWindow helpWindow("Quick Configuration Help",
			"Check your preenfm2 settings : \r\n"
			"(Menu->Tools->Set)\r\n"
			". Midi channels 1, 2, 3 & 4\r\n"
			". Midi thru : No\r\n"
			". Receives : NRPN\r\n"
			". Send : NRPN\r\n\r\n"
			"In the main editor window :\r\n"
			". Click on 'Midi' button to select your midi device\r\n"
			". Select the midi channel (1-16) of the preenfm2 instrument               \r\n"
			"   you want to talk to. \r\n\r\n",
			AlertWindow::InfoIcon);

		helpWindow.addButton("OK", 1);
		helpWindow.runModalLoop();
	}

	//==============================================================================
	void switchToHostApplication()
	{
#if JUCE_IOS
		if (auto device = dynamic_cast<iOSAudioIODevice*> (deviceManager.getCurrentAudioDevice()))
			device->switchApplication();
#endif
	}

	bool isInterAppAudioConnected()
	{
#if JUCE_IOS
		if (auto device = dynamic_cast<iOSAudioIODevice*> (deviceManager.getCurrentAudioDevice()))
			return device->isInterAppAudioConnected();
#endif

		return false;
	}

#if JUCE_MODULE_AVAILABLE_juce_gui_basics
	Image getIAAHostIcon(int size)
	{
#if JUCE_IOS && JucePlugin_Enable_IAA
		if (auto device = dynamic_cast<iOSAudioIODevice*> (deviceManager.getCurrentAudioDevice()))
			return device->getIcon(size);
#else
		ignoreUnused(size);
#endif

		return {};
	}
#endif

	static StandalonePluginHolder* getInstance();

	//==============================================================================
	OptionalScopedPointer<PropertySet> settings;
	std::unique_ptr<AudioProcessor> processor;
	AudioDeviceManager deviceManager;
	AudioProcessorPlayer player;
	Array<PluginInOuts> channelConfiguration;

	// avoid feedback loop by default
	bool processorHasPotentialFeedbackLoop = true;
	std::atomic<bool> muteInput{ true };
	Value shouldMuteInput;
	AudioBuffer<float> emptyBuffer;
	bool autoOpenMidiDevices;

	std::unique_ptr<AudioDeviceManager::AudioDeviceSetup> options;
	Array<MidiDeviceInfo> lastMidiDevices;

private:
	//==============================================================================
	class SettingsComponent : public Component
	{
	public:
		SettingsComponent(StandalonePluginHolder& pluginHolder,
			AudioDeviceManager& deviceManagerToUse,
			int minAudioInputChannels,
			int maxAudioInputChannels,
			int minAudioOutputChannels,
			int maxAudioOutputChannels)
			: owner(pluginHolder),
			deviceSelector(deviceManagerToUse,
				minAudioInputChannels, maxAudioInputChannels,
				minAudioOutputChannels, maxAudioOutputChannels,
				true,
				(pluginHolder.processor.get() != nullptr && pluginHolder.processor->producesMidi()),
				true, false),
			shouldMuteLabel("Feedback Loop:", "Feedback Loop:"),
			shouldMuteButton("Mute audio input")
		{
			setOpaque(true);

			shouldMuteButton.setClickingTogglesState(true);
			shouldMuteButton.getToggleStateValue().referTo(owner.shouldMuteInput);

			addAndMakeVisible(deviceSelector);

			if (owner.getProcessorHasPotentialFeedbackLoop())
			{
				addAndMakeVisible(shouldMuteButton);
				addAndMakeVisible(shouldMuteLabel);

				shouldMuteLabel.attachToComponent(&shouldMuteButton, true);
			}
		}

		void paint(Graphics& g) override
		{
			g.fillAll(getLookAndFeel().findColour(ResizableWindow::backgroundColourId));
		}

		void resized() override
		{
			auto r = getLocalBounds();

			if (owner.getProcessorHasPotentialFeedbackLoop())
			{
				auto itemHeight = deviceSelector.getItemHeight();
				auto extra = r.removeFromTop(itemHeight);

				auto seperatorHeight = (itemHeight >> 1);
				shouldMuteButton.setBounds(Rectangle<int>(extra.proportionOfWidth(0.35f), seperatorHeight,
					extra.proportionOfWidth(0.60f), deviceSelector.getItemHeight()));

				r.removeFromTop(seperatorHeight);
			}

			deviceSelector.setBounds(r);
		}

	private:
		//==============================================================================
		StandalonePluginHolder& owner;
		AudioDeviceSelectorComponent deviceSelector;
		Label shouldMuteLabel;
		ToggleButton shouldMuteButton;

		//==============================================================================
		JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(SettingsComponent)
	};

	//==============================================================================
	void audioDeviceIOCallback(const float** inputChannelData,
		int numInputChannels,
		float** outputChannelData,
		int numOutputChannels,
		int numSamples) override
	{
		if (muteInput)
		{
			emptyBuffer.clear();
			inputChannelData = emptyBuffer.getArrayOfReadPointers();
		}

		player.audioDeviceIOCallback(inputChannelData, numInputChannels,
			outputChannelData, numOutputChannels, numSamples);
	}

	void audioDeviceAboutToStart(AudioIODevice* device) override
	{
		emptyBuffer.setSize(device->getActiveInputChannels().countNumberOfSetBits(), device->getCurrentBufferSizeSamples());
		emptyBuffer.clear();

		player.audioDeviceAboutToStart(device);
		player.setMidiOutput(deviceManager.getDefaultMidiOutput());
	}

	void audioDeviceStopped() override
	{
		player.setMidiOutput(nullptr);
		player.audioDeviceStopped();
		emptyBuffer.setSize(0, 0);
	}

	//==============================================================================
	void setupAudioDevices(bool enableAudioInput,
		const String& preferredDefaultDeviceName,
		const AudioDeviceManager::AudioDeviceSetup* preferredSetupOptions)
	{
		deviceManager.addAudioCallback(this);
		deviceManager.addMidiInputDeviceCallback({}, &player);

		reloadAudioDeviceState(enableAudioInput, preferredDefaultDeviceName, preferredSetupOptions);
	}

	void shutDownAudioDevices()
	{
		saveAudioDeviceState();

		deviceManager.removeMidiInputDeviceCallback({}, &player);
		deviceManager.removeAudioCallback(this);
	}

	void timerCallback() override
	{
		auto newMidiDevices = MidiInput::getAvailableDevices();

		if (newMidiDevices != lastMidiDevices)
		{
			for (auto& oldDevice : lastMidiDevices)
				if (!newMidiDevices.contains(oldDevice))
					deviceManager.setMidiInputDeviceEnabled(oldDevice.identifier, false);

			for (auto& newDevice : newMidiDevices)
				if (!lastMidiDevices.contains(newDevice))
					deviceManager.setMidiInputDeviceEnabled(newDevice.identifier, true);

			lastMidiDevices = newMidiDevices;
		}
	}

	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(StandalonePluginHolder)
};


//==============================================================================
/**
	A class that can be used to run a simple standalone application containing your filter.

	Just create one of these objects in your JUCEApplicationBase::initialise() method, and
	let it do its work. It will create your filter object using the same createPluginFilter() function
	that the other plugin wrappers use.
*/
class StandalonePFM2Window : public DocumentWindow,
	public Button::Listener   // (can't use Button::Listener due to VC2005 bug)
{
public:
	//==============================================================================
	/** Creates a window with a given title and colour.
		The settings object can be a PropertySet that the class should use to
		store its settings - the object that is passed-in will be owned by this
		class and deleted automatically when no longer needed. (It can also be null)
	*/
	StandalonePFM2Window(const String& title,
		Colour backgroundColour,
		PropertySet* settingsToUse)
		: DocumentWindow(title, backgroundColour, DocumentWindow::minimiseButton | DocumentWindow::closeButton),
		optionsButton("Options")
	{
		setTitleBarButtonsRequired(DocumentWindow::minimiseButton | DocumentWindow::closeButton | DocumentWindow::maximiseButton, false);

		Component::addAndMakeVisible(optionsButton);
		optionsButton.addListener(this);
		optionsButton.setTriggeredOnMouseDown(true);

		pluginHolder = new StandalonePluginHolder(settingsToUse);

		createEditorComp();

		if (PropertySet* props = pluginHolder->settings)
		{
			const int x = props->getIntValue("windowX", -100);
			const int y = props->getIntValue("windowY", -100);

			if (x != -100 && y != -100)
				setBoundsConstrained(juce::Rectangle<int>(x, y, getWidth(), getHeight()));
			else
				centreWithSize(getWidth(), getHeight());
		}
		else
		{
			centreWithSize(getWidth(), getHeight());
		}
	}

	~StandalonePFM2Window()
	{
		if (PropertySet* props = pluginHolder->settings)
		{
			props->setValue("windowX", getX());
			props->setValue("windowY", getY());
		}

		pluginHolder->stopPlaying();
		deleteEditorComp();
		pluginHolder = nullptr;
	}

	//==============================================================================
	AudioProcessor* getAudioProcessor() const noexcept { return pluginHolder->processor.get(); }
	AudioDeviceManager& getDeviceManager() const noexcept { return pluginHolder->deviceManager; }

	void createEditorComp()
	{
		setContentOwned(getAudioProcessor()->createEditorIfNeeded(), true);
	}

	void deleteEditorComp()
	{
		if (AudioProcessorEditor* ed = dynamic_cast<AudioProcessorEditor*> (getContentComponent()))
		{
			pluginHolder->processor->editorBeingDeleted(ed);
			clearContentComponent();
		}
	}

	/** Deletes and re-creates the plugin, resetting it to its default state. */
	void resetToDefaultState()
	{
		pluginHolder->stopPlaying();
		deleteEditorComp();
		pluginHolder->deletePlugin();

		if (PropertySet* props = pluginHolder->settings)
			props->removeValue("filterState");

		pluginHolder->createPlugin();
		createEditorComp();
		pluginHolder->startPlaying();
	}

	//==============================================================================
	void closeButtonPressed() override
	{
		JUCEApplicationBase::quit();
	}

	void buttonClicked(Button*) override
	{
		PopupMenu m;
		m.addItem(5, TRANS("Quick Help"));
		m.addSeparator();
		m.addItem(1, TRANS("Midi input"));
		m.addSeparator();
		m.addItem(2, TRANS("Save current preset"));
		m.addItem(3, TRANS("Load a saved preset"));
		m.addSeparator();
		m.addItem(4, TRANS("Reset to default preset"));

		switch (m.showAt(&optionsButton))
		{
		case 1:  pluginHolder->showAudioSettingsDialog(); break;
		case 2:  pluginHolder->askUserToSaveState(); break;
		case 3:  pluginHolder->askUserToLoadState(); break;
		case 4:  resetToDefaultState(); break;
		case 5:  pluginHolder->quickHelp(); break;
		default: break;
		}
	}

	void resized() override
	{
		DocumentWindow::resized();
		optionsButton.setBounds(8, 4, 60, getTitleBarHeight() - 8);
	}

	ScopedPointer<StandalonePluginHolder> pluginHolder;

private:
	//==============================================================================
	TextButton optionsButton;

	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(StandalonePFM2Window)
};

} // namespace juce

#endif   // PFM2_WINDOW_H_INCLUDED
