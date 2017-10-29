/*
  ==============================================================================

  This is an automatically generated GUI class created by the Projucer!

  Be careful when adding custom code to these files, as only the code within
  the "//[xyz]" and "//[/xyz]" sections will be retained when the file is loaded
  and re-saved.

  Created with Projucer version: 5.1.2

  ------------------------------------------------------------------------------

  The Projucer is part of the JUCE library - "Jules' Utility Class Extensions"
  Copyright (c) 2015 - ROLI Ltd.

  ==============================================================================
*/

#pragma once

//[Headers]     -- You can add your own extra header files here --
#include "../PluginParameters/include/PluginParameters.h"

#include <unordered_set>

class PanelEngine;
class PanelModulation;
class PanelArpAndFilter;

//[/Headers]



//==============================================================================
/**
                                                                    //[Comments]
    An auto-generated component, created by the Introjucer.

    Describe your class and how it works here!
                                                                    //[/Comments]
*/
class MainTabs  : public Component,
                  public Button::Listener,
                  public Label::Listener,
                  public ComboBox::Listener
{
public:
    //==============================================================================
    MainTabs ();
    ~MainTabs();

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.
    void handleIncomingMidiBuffer(MidiBuffer &buffer, int numberOfSamples);
    void buildParameters(teragon::ConcurrentParameterSet& parameterSet);
	void updateUI(std::unordered_set<const char*> &paramSet);
	void newNrpnParam(int nrpn, int value);
	void setPresetName(const char* presetName);
	void setPresetNamePtr(char* presetNamePtr);
    void setMidiMessageCollector(MidiMessageCollector &midiMessageCollector);
	void setMidiChannel(int newMidiChannel);
    //[/UserMethods]

    void paint (Graphics& g) override;
    void resized() override;
    void buttonClicked (Button* buttonThatWasClicked) override;
    void labelTextChanged (Label* labelThatHasChanged) override;
    void comboBoxChanged (ComboBox* comboBoxThatHasChanged) override;



private:
    //[UserVariables]   -- You can add your own custom variables in this section.
    int midiInfo;
    PanelEngine* panelEngine;
    PanelModulation* panelModulation;
    PanelArpAndFilter* panelArpAndFilter;
    teragon::ConcurrentParameterSet* parameterSet;
    teragon::ParameterValue pullButtonValue;
    teragon::ParameterValue pushButtonValue;
    int currentMidiChannel;
    MidiMessageCollector *midiMessageCollector;
	char *presetNamePtr;
    //[/UserVariables]

    //==============================================================================
    ScopedPointer<TabbedComponent> tabbedComponent;
    ScopedPointer<TextButton> pullButton;
    ScopedPointer<Label> presetNameLabel;
    ScopedPointer<TextButton> pushButton;
    ScopedPointer<ComboBox> midiChannelCombo;
    ScopedPointer<Label> midiChannelLabel;
    ScopedPointer<Label> versionLabel;
    ScopedPointer<Label> midiInputLabel2;
    ScopedPointer<Label> midiInputLabel;


    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainTabs)
};

//[EndFile] You can add extra defines here...
//[/EndFile]
