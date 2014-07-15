/*
  ==============================================================================

  This is an automatically generated GUI class created by the Introjucer!

  Be careful when adding custom code to these files, as only the code within
  the "//[xyz]" and "//[/xyz]" sections will be retained when the file is loaded
  and re-saved.

  Created with Introjucer version: 3.1.0

  ------------------------------------------------------------------------------

  The Introjucer is part of the JUCE library - "Jules' Utility Class Extensions"
  Copyright 2004-13 by Raw Material Software Ltd.

  ==============================================================================
*/

//[Headers] You can add your own extra header files here...
#include "JuceHeader.h"
#include "../PluginParameters/include/PluginParameters.h"
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
    addAndMakeVisible (tabbedComponent = new TabbedComponent (TabbedButtonBar::TabsAtTop));
    tabbedComponent->setTabBarDepth (30);
    tabbedComponent->addTab (TRANS("Engine"), Colour (0xffe5f9ff), new PanelEngine(), true);
    tabbedComponent->addTab (TRANS("Modulation"), Colour (0xffdeffe4), new PanelModulation(), true);
    tabbedComponent->addTab (TRANS("Arp & Filter"), Colours::bisque, new PanelArpAndFilter(), true);
    tabbedComponent->setCurrentTabIndex (0);

    addAndMakeVisible (midiInputLabel = new Label ("midi input label",
                                                   TRANS("0")));
    midiInputLabel->setFont (Font (15.00f, Font::plain));
    midiInputLabel->setJustificationType (Justification::centredLeft);
    midiInputLabel->setEditable (false, false, false);
    midiInputLabel->setColour (Label::textColourId, Colours::blue);
    midiInputLabel->setColour (TextEditor::textColourId, Colours::black);
    midiInputLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (midiInputLabel2 = new Label ("midi input label",
                                                    TRANS("0")));
    midiInputLabel2->setFont (Font (15.00f, Font::plain));
    midiInputLabel2->setJustificationType (Justification::centredLeft);
    midiInputLabel2->setEditable (false, false, false);
    midiInputLabel2->setColour (Label::textColourId, Colours::blue);
    midiInputLabel2->setColour (TextEditor::textColourId, Colours::black);
    midiInputLabel2->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (pullButton = new TextButton ("pull button"));
    pullButton->setTooltip (TRANS("Pull all parameters from the preenfm2 to this plugin"));
    pullButton->setButtonText (TRANS("Pull"));
    pullButton->addListener (this);

    addAndMakeVisible (presetNameLabel = new Label ("preset name label",
                                                    TRANS("preset")));
    presetNameLabel->setTooltip (TRANS("Click to edit"));
    presetNameLabel->setFont (Font (25.90f, Font::bold));
    presetNameLabel->setJustificationType (Justification::centredLeft);
    presetNameLabel->setEditable (true, true, false);
    presetNameLabel->setColour (TextEditor::textColourId, Colours::black);
    presetNameLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));
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
                                                     TRANS("Midi Channel:")));
    midiChannelLabel->setFont (Font (15.00f, Font::plain));
    midiChannelLabel->setJustificationType (Justification::centred);
    midiChannelLabel->setEditable (false, false, false);
    midiChannelLabel->setColour (TextEditor::textColourId, Colours::black);
    midiChannelLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));


    //[UserPreSize]
    midiChannelCombo->setSelectedId(1);
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
    midiInputLabel = nullptr;
    midiInputLabel2 = nullptr;
    pullButton = nullptr;
    presetNameLabel = nullptr;
    pushButton = nullptr;
    midiChannelCombo = nullptr;
    midiChannelLabel = nullptr;


    //[Destructor]. You can add your own custom destruction code here..
    //[/Destructor]
}

//==============================================================================
void MainTabs::paint (Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    g.fillAll (Colours::aliceblue);

    //[UserPaint] Add your own custom painting code here..
    //[/UserPaint]
}

void MainTabs::resized()
{
    tabbedComponent->setBounds (proportionOfWidth (0.0092f), proportionOfHeight (0.0241f), proportionOfWidth (0.9782f), proportionOfHeight (0.9699f));
    midiInputLabel->setBounds (16, 0, 48, 16);
    midiInputLabel2->setBounds (72, 0, 48, 16);
    pullButton->setBounds (getWidth() - 67, 8, 55, 24);
    presetNameLabel->setBounds (288, 8, 168, 32);
    pushButton->setBounds (getWidth() - 283, 8, 55, 24);
    midiChannelCombo->setBounds (getWidth() - 131, 8, 55, 24);
    midiChannelLabel->setBounds (getWidth() - 227, 8, 103, 24);
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

        teragon::Parameter* param =  parameterSet->get("pull button");
        pullButtonValue = (pullButtonValue == 0 ? 1 : 0) ;
        parameterSet->set(param, pullButtonValue, nullptr);

        //[/UserButtonCode_pullButton]
    }
    else if (buttonThatWasClicked == pushButton)
    {
        //[UserButtonCode_pushButton] -- add your button handler code here..
        teragon::Parameter* param =  parameterSet->get("push button");
        pushButtonValue = (pushButtonValue == 0 ? 1 : 0) ;
        parameterSet->set(param, pushButtonValue, nullptr);

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
        teragon::Parameter* param =  parameterSet->get("Midi Channel");
        if (currentMidiChannel != midiChannelCombo->getSelectedId()) {
            currentMidiChannel = midiChannelCombo->getSelectedId();
            parameterSet->set(param, currentMidiChannel, nullptr);
        }

        //[/UserComboBoxCode_midiChannelCombo]
    }

    //[UsercomboBoxChanged_Post]
    //[/UsercomboBoxChanged_Post]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...


void MainTabs::buildParameters(teragon::ConcurrentParameterSet& parameterSet) {
    this->parameterSet = &parameterSet;

    panelEngine->setParameterSet(parameterSet);
    panelEngine->buildParameters();

    panelModulation->setParameterSet(parameterSet);
    panelModulation->buildParameters();

    panelArpAndFilter->setParameterSet(parameterSet);
    panelArpAndFilter->buildParameters();
}

void MainTabs::updateUI(std::unordered_set<const char*> &paramSet) {
    /*
    printf("====================================================\r\n");
    printf("====> %d\r\n", paramSet.size());
    for(std::unordered_set<const char*>::iterator it = paramSet.begin(); it != paramSet.end(); ++it) {
        printf("'%s'\r\n", (*it));
    }
    printf("====================================================\r\n");
    */

    for(std::unordered_set<const char*>::iterator it = paramSet.begin(); it != paramSet.end(); ++it) {
        if (strcmp((*it), "Midi Channel") == 0) {
            midiChannelCombo->setSelectedId(this->parameterSet->get("Midi Channel")->getValue());
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

void MainTabs::setMidiMessageCollector(MidiMessageCollector &midiMessageCollector) {
    this->midiMessageCollector = &midiMessageCollector;
}


void MainTabs::setMidiChannel(int newMidiChannel) {
	midiChannelCombo->setSelectedId(newMidiChannel);
}
//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Introjucer information section --

    This is where the Introjucer stores the metadata that describe this GUI layout, so
    make changes in here at your peril!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="MainTabs" componentName=""
                 parentClasses="public Component" constructorParams="" variableInitialisers=""
                 snapPixels="8" snapActive="1" snapShown="1" overlayOpacity="0.330"
                 fixedSize="0" initialWidth="900" initialHeight="710">
  <BACKGROUND backgroundColour="fff0f8ff"/>
  <TABBEDCOMPONENT name="new tabbed component" id="f175981f6c34a740" memberName="tabbedComponent"
                   virtualName="TabbedComponent" explicitFocusOrder="0" pos="0.931% 2.421% 97.851% 97.02%"
                   orientation="top" tabBarDepth="30" initialTab="0">
    <TAB name="Engine" colour="ffe5f9ff" useJucerComp="0" contentClassName="PanelEngine"
         constructorParams="" jucerComponentFile=""/>
    <TAB name="Modulation" colour="ffdeffe4" useJucerComp="0" contentClassName="PanelModulation"
         constructorParams="" jucerComponentFile=""/>
    <TAB name="Arp &amp; Filter" colour="ffffe4c4" useJucerComp="0" contentClassName="PanelArpAndFilter"
         constructorParams="" jucerComponentFile=""/>
  </TABBEDCOMPONENT>
  <LABEL name="midi input label" id="f77b232960a175fb" memberName="midiInputLabel"
         virtualName="" explicitFocusOrder="0" pos="16 0 48 16" textCol="ff0000ff"
         edTextCol="ff000000" edBkgCol="0" labelText="0" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15" bold="0" italic="0" justification="33"/>
  <LABEL name="midi input label" id="f5bde9938974ba9f" memberName="midiInputLabel2"
         virtualName="" explicitFocusOrder="0" pos="72 0 48 16" textCol="ff0000ff"
         edTextCol="ff000000" edBkgCol="0" labelText="0" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15" bold="0" italic="0" justification="33"/>
  <TEXTBUTTON name="pull button" id="9da85c0691256028" memberName="pullButton"
              virtualName="" explicitFocusOrder="0" pos="67R 8 55 24" tooltip="Pull all parameters from the preenfm2 to this plugin"
              buttonText="Pull" connectedEdges="0" needsCallback="1" radioGroupId="0"/>
  <LABEL name="preset name label" id="4201f054ae2edbe" memberName="presetNameLabel"
         virtualName="" explicitFocusOrder="0" pos="288 8 168 32" tooltip="Click to edit"
         edTextCol="ff000000" edBkgCol="0" labelText="preset" editableSingleClick="1"
         editableDoubleClick="1" focusDiscardsChanges="0" fontname="Default font"
         fontsize="25.899999999999999" bold="1" italic="0" justification="33"/>
  <TEXTBUTTON name="push button" id="52c3034a926a2609" memberName="pushButton"
              virtualName="" explicitFocusOrder="0" pos="283R 8 55 24" tooltip="Push all parameters from plugin to preenfm2"
              buttonText="Push" connectedEdges="0" needsCallback="1" radioGroupId="0"/>
  <COMBOBOX name="Midi Channel" id="a2c1c2de24e3a5a3" memberName="midiChannelCombo"
            virtualName="" explicitFocusOrder="0" pos="131R 8 55 24" tooltip="Midi Channel"
            editable="0" layout="36" items="1&#10;2&#10;3&#10;4&#10;5&#10;6&#10;7&#10;8&#10;9&#10;10&#10;11&#10;12&#10;13&#10;14&#10;15&#10;16&#10;"
            textWhenNonSelected="1" textWhenNoItems="1"/>
  <LABEL name="Midi Channel Label" id="6b9a0088a5f5afa" memberName="midiChannelLabel"
         virtualName="" explicitFocusOrder="0" pos="227R 8 103 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Midi Channel:" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15" bold="0" italic="0" justification="36"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]
