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

//[Headers] You can add your own extra header files here...
#include "JuceHeader.h"
#include "PanelEngine.h"
#include "PanelModulation.h"
#include "PanelArpAndFilter.h"
//[/Headers]

#include "MainTabs.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
//[/MiscUserDefs]

//==============================================================================
MainTabs::MainTabs ()
{
    //[Constructor_pre] You can add your own custom stuff here..
    //[/Constructor_pre]

    addAndMakeVisible (tabbedComponent = new TabbedComponent (TabbedButtonBar::TabsAtTop));
    tabbedComponent->setTabBarDepth (40);
    tabbedComponent->addTab (TRANS("Engine"), Colour (0xff062934), new PanelEngine(), true);
    tabbedComponent->addTab (TRANS("Modulation"), Colour (0xff062934), new PanelModulation(), true);
    tabbedComponent->addTab (TRANS("Arp & Filter"), Colour (0xff062934), new PanelArpAndFilter(), true);
    tabbedComponent->setCurrentTabIndex (0);

    addAndMakeVisible (pullButton = new TextButton ("pull button"));
    pullButton->setTooltip (TRANS("Pull all parameters from the preenfm2 to this plugin"));
    pullButton->setButtonText (TRANS("Pull"));
    pullButton->addListener (this);

    addAndMakeVisible (presetNameLabel = new Label ("preset name label",
                                                    TRANS("preset")));
    presetNameLabel->setTooltip (TRANS("Click to edit"));
    presetNameLabel->setFont (Font (25.90f, Font::plain).withTypefaceStyle ("Bold"));
    presetNameLabel->setJustificationType (Justification::centredLeft);
    presetNameLabel->setEditable (true, true, false);
    presetNameLabel->setColour (Label::textColourId, Colours::aliceblue);
    presetNameLabel->setColour (TextEditor::textColourId, Colours::aliceblue);
    presetNameLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));
    presetNameLabel->setColour (TextEditor::highlightColourId, Colours::coral);
    presetNameLabel->addListener (this);

    addAndMakeVisible (pushButton = new TextButton ("push button"));
    pushButton->setTooltip (TRANS("Push all parameters from plugin to preenfm2"));
    pushButton->setButtonText (TRANS("Push"));
    pushButton->addListener (this);

    addAndMakeVisible (midiChannelCombo = new ComboBox ("Midi Channel"));
    midiChannelCombo->setTooltip (TRANS("Midi Channel"));
    midiChannelCombo->setEditableText (false);
    midiChannelCombo->setJustificationType (Justification::centred);
    midiChannelCombo->setTextWhenNothingSelected (TRANS("1"));
    midiChannelCombo->setTextWhenNoChoicesAvailable (TRANS("1"));
    midiChannelCombo->addItem (TRANS("1"), 1);
    midiChannelCombo->addItem (TRANS("2"), 2);
    midiChannelCombo->addItem (TRANS("3"), 3);
    midiChannelCombo->addItem (TRANS("4"), 4);
    midiChannelCombo->addItem (TRANS("5"), 5);
    midiChannelCombo->addItem (TRANS("6"), 6);
    midiChannelCombo->addItem (TRANS("7"), 7);
    midiChannelCombo->addItem (TRANS("8"), 8);
    midiChannelCombo->addItem (TRANS("9"), 9);
    midiChannelCombo->addItem (TRANS("10"), 10);
    midiChannelCombo->addItem (TRANS("11"), 11);
    midiChannelCombo->addItem (TRANS("12"), 12);
    midiChannelCombo->addItem (TRANS("13"), 13);
    midiChannelCombo->addItem (TRANS("14"), 14);
    midiChannelCombo->addItem (TRANS("15"), 15);
    midiChannelCombo->addItem (TRANS("16"), 16);
    midiChannelCombo->addSeparator();
    midiChannelCombo->addListener (this);

    addAndMakeVisible (midiChannelLabel = new Label ("Midi Channel Label",
                                                     TRANS("Midi :")));
    midiChannelLabel->setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Regular"));
    midiChannelLabel->setJustificationType (Justification::centred);
    midiChannelLabel->setEditable (false, false, false);
    midiChannelLabel->setColour (Label::textColourId, Colours::aliceblue);
    midiChannelLabel->setColour (TextEditor::textColourId, Colours::black);
    midiChannelLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (versionLabel = new Label ("Version Label",
                                                 TRANS("v?.?\n")));
    versionLabel->setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Regular"));
    versionLabel->setJustificationType (Justification::centredLeft);
    versionLabel->setEditable (false, false, false);
    versionLabel->setColour (Label::textColourId, Colours::beige);
    versionLabel->setColour (TextEditor::textColourId, Colours::black);
    versionLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (midiInputLabel2 = new Label ("midi input label",
                                                    TRANS("0")));
    midiInputLabel2->setFont (Font (12.00f, Font::plain).withTypefaceStyle ("Regular"));
    midiInputLabel2->setJustificationType (Justification::centredLeft);
    midiInputLabel2->setEditable (false, false, false);
    midiInputLabel2->setColour (Label::textColourId, Colours::beige);
    midiInputLabel2->setColour (TextEditor::textColourId, Colours::black);
    midiInputLabel2->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (midiInputLabel = new Label ("midi input label",
                                                   TRANS("0")));
    midiInputLabel->setFont (Font (12.00f, Font::plain).withTypefaceStyle ("Regular"));
    midiInputLabel->setJustificationType (Justification::centredLeft);
    midiInputLabel->setEditable (false, false, false);
    midiInputLabel->setColour (Label::textColourId, Colours::beige);
    midiInputLabel->setColour (TextEditor::textColourId, Colours::black);
    midiInputLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));


    //[UserPreSize]
    midiChannelCombo->setSelectedId(1);
    versionLabel->setText(String("v") + ProjectInfo::versionString, dontSendNotification);
    //[/UserPreSize]

    setSize (900, 710);


    //[Constructor] You can add your own custom stuff here..
	panelEngine = ((PanelEngine*)tabbedComponent->getTabContentComponent(0));
	panelModulation = ((PanelModulation*)tabbedComponent->getTabContentComponent(1));
	panelArpAndFilter = ((PanelArpAndFilter*)tabbedComponent->getTabContentComponent(2));
	pullButtonValue = 0;
    currentMidiChannel = 1;
    // SET null !
    //[/Constructor]
}

MainTabs::~MainTabs()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    //[/Destructor_pre]

    tabbedComponent = nullptr;
    pullButton = nullptr;
    presetNameLabel = nullptr;
    pushButton = nullptr;
    midiChannelCombo = nullptr;
    midiChannelLabel = nullptr;
    versionLabel = nullptr;
    midiInputLabel2 = nullptr;
    midiInputLabel = nullptr;


    //[Destructor]. You can add your own custom destruction code here..
    //[/Destructor]
}

//==============================================================================
void MainTabs::paint (Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    g.fillAll (Colour (0xff0b232a));

    //[UserPaint] Add your own custom painting code here..
    //[/UserPaint]
}

void MainTabs::resized()
{
    //[UserPreResize] Add your own custom resize code here..
    //[/UserPreResize]

    tabbedComponent->setBounds (0, 0, getWidth() - 0, getHeight() - 0);
    pullButton->setBounds (getWidth() - 116, 8, 55, 24);
    presetNameLabel->setBounds (proportionOfWidth (0.4003f), proportionOfHeight (0.0033f), 200, 32);
    pushButton->setBounds (getWidth() - 184, 8, 55, 24);
    midiChannelCombo->setBounds (getWidth() - 268, 8, 55, 24);
    midiChannelLabel->setBounds (getWidth() - 364, 8, 103, 24);
    versionLabel->setBounds (getWidth() - 58, 8, 55, 24);
    midiInputLabel2->setBounds (proportionOfWidth (0.3557f), 21, 48, 12);
    midiInputLabel->setBounds (proportionOfWidth (0.3557f), 5, 36, 12);
    //[UserResized] Add your own custom resize handling here..
    //[/UserResized]
}

void MainTabs::buttonClicked (Button* buttonThatWasClicked)
{
    //[UserbuttonClicked_Pre]
    //[/UserbuttonClicked_Pre]

    if (buttonThatWasClicked == pullButton)
    {
        //[UserButtonCode_pullButton] -- add your button handler code here..

		MidifiedFloatParameter* param = getParameterFromName("pull button");
        pullButtonValue = (pullButtonValue == 0 ? 1 : 0) ;
		param->setRealValue(pullButtonValue);

        //[/UserButtonCode_pullButton]
    }
    else if (buttonThatWasClicked == pushButton)
    {
        //[UserButtonCode_pushButton] -- add your button handler code here..

		 MidifiedFloatParameter* param = getParameterFromName("push button");
		 pushButtonValue = (pushButtonValue == 0 ? 1 : 0);
		 param->setRealValue(pushButtonValue);

        //[/UserButtonCode_pushButton]
    }

    //[UserbuttonClicked_Post]
    //[/UserbuttonClicked_Post]
}

void MainTabs::labelTextChanged (Label* labelThatHasChanged)
{
    //[UserlabelTextChanged_Pre]
    //[/UserlabelTextChanged_Pre]

    if (labelThatHasChanged == presetNameLabel)
    {
        //[UserLabelCode_presetNameLabel] -- add your label text handling code here..
        for (int k=0; k<12; k++) {
            int timeNow = Time::getMillisecondCounter();
            MidiMessage byte1 = MidiMessage::controllerEvent(currentMidiChannel, 99, 1);
            byte1.setTimeStamp(timeNow);
            midiMessageCollector->addMessageToQueue(byte1);

            MidiMessage byte2 = MidiMessage::controllerEvent(currentMidiChannel, 98, 100 + k);
            byte2.setTimeStamp(timeNow);
            midiMessageCollector->addMessageToQueue(byte2);

            int letter = presetNameLabel->getText().toRawUTF8()[k];
			this->presetNamePtr[k] = (char)letter;

            MidiMessage byte3 = MidiMessage::controllerEvent(currentMidiChannel, 6, letter >> 7);
            byte3.setTimeStamp(timeNow);
            midiMessageCollector->addMessageToQueue(byte3);

            MidiMessage byte4 = MidiMessage::controllerEvent(currentMidiChannel, 38, letter & 0xff);
            byte4.setTimeStamp(timeNow);
            midiMessageCollector->addMessageToQueue(byte4);
        }
        //[/UserLabelCode_presetNameLabel]
    }

    //[UserlabelTextChanged_Post]
    //[/UserlabelTextChanged_Post]
}

void MainTabs::comboBoxChanged (ComboBox* comboBoxThatHasChanged)
{
    //[UsercomboBoxChanged_Pre]
    //[/UsercomboBoxChanged_Pre]

    if (comboBoxThatHasChanged == midiChannelCombo)
    {
        //[UserComboBoxCode_midiChannelCombo] -- add your combo box handling code here..

		MidifiedFloatParameter* param = getParameterFromName("Midi Channel");
		
        if (currentMidiChannel != midiChannelCombo->getSelectedId()) {
            currentMidiChannel = midiChannelCombo->getSelectedId();
			param->setRealValue(currentMidiChannel);
        }

        //[/UserComboBoxCode_midiChannelCombo]
    }

    //[UsercomboBoxChanged_Post]
    //[/UsercomboBoxChanged_Post]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...

MidifiedFloatParameter* MainTabs::getParameterFromName(String componentName) {
	const OwnedArray<AudioProcessorParameter>& parameters = audioProcessor->getParameters();
	for (int p = 0; p < parameters.size(); p++) {
		if (parameters[p]->getName(256) == componentName) {
			return (MidifiedFloatParameter*) parameters[p];		
		}
	}
	
}


void MainTabs::buildParameters(AudioProcessor *audioProcessor) {
    this->audioProcessor = audioProcessor;

    panelEngine->setParameterSet(audioProcessor);
    panelEngine->buildParameters();

    panelModulation->setParameterSet(audioProcessor);
    panelModulation->buildParameters();

    panelArpAndFilter->setParameterSet(audioProcessor);
    panelArpAndFilter->buildParameters();
}

void MainTabs::updateUI(std::unordered_set<String> &paramSet) {
    /*
    printf("====================================================\r\n");
    printf("====> %d\r\n", paramSet.size());
    for(std::unordered_set<const char*>::iterator it = paramSet.begin(); it != paramSet.end(); ++it) {
        printf("'%s'\r\n", (*it));
    }
    printf("====================================================\r\n");
    */

    for(std::unordered_set<String>::iterator it = paramSet.begin(); it != paramSet.end(); ++it) {
        if (*it == "Midi Channel") {
			MidifiedFloatParameter* param = getParameterFromName("Midi Channel");
			midiChannelCombo->setSelectedId(param->getRealValue());
        }
    }
    panelEngine->updateUI(paramSet);
    panelModulation->updateUI(paramSet);
    panelArpAndFilter->updateUI(paramSet);

}


void MainTabs::newNrpnParam(int nrpn, int value) {
    midiInputLabel->setText(String(nrpn), dontSendNotification);
    midiInputLabel2->setText(String(value), dontSendNotification);
}


void MainTabs::setPresetName(const char* presetName) {
    presetNameLabel->setText(String(presetName), dontSendNotification);
}

void MainTabs::setPresetNamePtr(char* presetNamePtr) {
	this->presetNamePtr = presetNamePtr;
}

void MainTabs::setMidiMessageCollector(MidiMessageCollector &midiMessageCollector) {
    this->midiMessageCollector = &midiMessageCollector;
}


void MainTabs::setMidiChannel(int newMidiChannel) {
	midiChannelCombo->setSelectedId(newMidiChannel);
}


void MainTabs::setPushButtonEnabled(bool enabled) {
	pushButton->setEnabled(enabled);

}

//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Projucer information section --

    This is where the Projucer stores the metadata that describe this GUI layout, so
    make changes in here at your peril!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="MainTabs" componentName=""
                 parentClasses="public Component" constructorParams="" variableInitialisers=""
                 snapPixels="8" snapActive="0" snapShown="1" overlayOpacity="0.330"
                 fixedSize="0" initialWidth="900" initialHeight="710">
  <BACKGROUND backgroundColour="ff0b232a"/>
  <TABBEDCOMPONENT name="new tabbed component" id="f175981f6c34a740" memberName="tabbedComponent"
                   virtualName="TabbedComponent" explicitFocusOrder="0" pos="0 0 0M 0M"
                   orientation="top" tabBarDepth="40" initialTab="0">
    <TAB name="Engine" colour="ff062934" useJucerComp="0" contentClassName="PanelEngine"
         constructorParams="" jucerComponentFile=""/>
    <TAB name="Modulation" colour="ff062934" useJucerComp="0" contentClassName="PanelModulation"
         constructorParams="" jucerComponentFile=""/>
    <TAB name="Arp &amp; Filter" colour="ff062934" useJucerComp="0" contentClassName="PanelArpAndFilter"
         constructorParams="" jucerComponentFile=""/>
  </TABBEDCOMPONENT>
  <TEXTBUTTON name="pull button" id="9da85c0691256028" memberName="pullButton"
              virtualName="" explicitFocusOrder="0" pos="116R 8 55 24" tooltip="Pull all parameters from the preenfm2 to this plugin"
              buttonText="Pull" connectedEdges="0" needsCallback="1" radioGroupId="0"/>
  <LABEL name="preset name label" id="4201f054ae2edbe" memberName="presetNameLabel"
         virtualName="" explicitFocusOrder="0" pos="40.027% 0.327% 200 32"
         tooltip="Click to edit" textCol="fff0f8ff" edTextCol="fff0f8ff"
         edBkgCol="0" hiliteCol="ffff7f50" labelText="preset" editableSingleClick="1"
         editableDoubleClick="1" focusDiscardsChanges="0" fontname="Default font"
         fontsize="25.899999999999998579" kerning="0" bold="1" italic="0"
         justification="33" typefaceStyle="Bold"/>
  <TEXTBUTTON name="push button" id="52c3034a926a2609" memberName="pushButton"
              virtualName="" explicitFocusOrder="0" pos="184R 8 55 24" tooltip="Push all parameters from plugin to preenfm2"
              buttonText="Push" connectedEdges="0" needsCallback="1" radioGroupId="0"/>
  <COMBOBOX name="Midi Channel" id="a2c1c2de24e3a5a3" memberName="midiChannelCombo"
            virtualName="" explicitFocusOrder="0" pos="268R 8 55 24" tooltip="Midi Channel"
            editable="0" layout="36" items="1&#10;2&#10;3&#10;4&#10;5&#10;6&#10;7&#10;8&#10;9&#10;10&#10;11&#10;12&#10;13&#10;14&#10;15&#10;16&#10;"
            textWhenNonSelected="1" textWhenNoItems="1"/>
  <LABEL name="Midi Channel Label" id="6b9a0088a5f5afa" memberName="midiChannelLabel"
         virtualName="" explicitFocusOrder="0" pos="364R 8 103 24" textCol="fff0f8ff"
         edTextCol="ff000000" edBkgCol="0" labelText="Midi :" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15" kerning="0" bold="0" italic="0" justification="36"/>
  <LABEL name="Version Label" id="c8880c204a60b679" memberName="versionLabel"
         virtualName="" explicitFocusOrder="0" pos="58R 8 55 24" textCol="fff5f5dc"
         edTextCol="ff000000" edBkgCol="0" labelText="v?.?&#10;" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15" kerning="0" bold="0" italic="0" justification="33"/>
  <LABEL name="midi input label" id="f5bde9938974ba9f" memberName="midiInputLabel2"
         virtualName="" explicitFocusOrder="0" pos="35.572% 21 48 12"
         textCol="fff5f5dc" edTextCol="ff000000" edBkgCol="0" labelText="0"
         editableSingleClick="0" editableDoubleClick="0" focusDiscardsChanges="0"
         fontname="Default font" fontsize="12" kerning="0" bold="0" italic="0"
         justification="33"/>
  <LABEL name="midi input label" id="f77b232960a175fb" memberName="midiInputLabel"
         virtualName="" explicitFocusOrder="0" pos="35.572% 5 36 12" textCol="fff5f5dc"
         edTextCol="ff000000" edBkgCol="0" labelText="0" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="12" kerning="0" bold="0" italic="0" justification="33"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]
