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
/*
* Copyright 2014 Xavier Hosxe
*
* Author: Xavier Hosxe (xavier <dot> hosxe
*                      (at) g m a i l <dot> com)
*
* This program is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
* You should have received a copy of the GNU General Public License
* along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/
#include "JuceHeader.h"
#include "../PluginProcessor.h"
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
    tabbedComponent->addTab (TRANS("Engine"), Colour (0xff083543), new PanelEngine(), true);
    tabbedComponent->addTab (TRANS("Modulation"), Colour (0xff083543), new PanelModulation(), true);
    tabbedComponent->addTab (TRANS("Arp & Filter"), Colour (0xff083543), new PanelArpAndFilter(), true);
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

    addAndMakeVisible (versionLabel = new Label ("Version Label",
                                                 TRANS("v?.?\n")));
    versionLabel->setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Regular"));
    versionLabel->setJustificationType (Justification::centredLeft);
    versionLabel->setEditable (false, false, false);
    versionLabel->setColour (Label::textColourId, Colours::beige);
    versionLabel->setColour (TextEditor::textColourId, Colours::black);
    versionLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (deviceButton = new TextButton ("Device Button"));
    deviceButton->setButtonText (TRANS("Midi"));
    deviceButton->addListener (this);
    deviceButton->setColour (TextButton::buttonColourId, Colour (0x005c5da4));
    deviceButton->setColour (TextButton::buttonOnColourId, Colours::aliceblue);


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
	pullButtonValue = 0;
	pushButtonValue = 0;
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
    versionLabel = nullptr;
    deviceButton = nullptr;


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
    versionLabel->setBounds (getWidth() - 58, 8, 55, 24);
    deviceButton->setBounds (getWidth() - 340, 8, 60, 24);
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
		pullButtonValue = (pullButtonValue == 1.0f ? 0.0f : 1.0f);
		param->setRealValue(pullButtonValue);

        //[/UserButtonCode_pullButton]
    }
    else if (buttonThatWasClicked == pushButton)
    {
        //[UserButtonCode_pushButton] -- add your button handler code here..

		MidifiedFloatParameter* param = getParameterFromName("push button");
		pushButtonValue = (pushButtonValue == 1.0f ? 0.0f : 1.0f);
		param->setRealValue(pushButtonValue);

        //[/UserButtonCode_pushButton]
    }
    else if (buttonThatWasClicked == deviceButton)
    {
        //[UserButtonCode_deviceButton] -- add your button handler code here..
		Pfm2AudioProcessor* pfm2Processor = dynamic_cast<Pfm2AudioProcessor*>(audioProcessor);
		if (pfm2Processor) {
			pfm2Processor->choseNewMidiDevice();
		}
        //[/UserButtonCode_deviceButton]
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
		Pfm2AudioProcessor* pfm2Processor = dynamic_cast<Pfm2AudioProcessor*>(audioProcessor);
		if (pfm2Processor) {
			pfm2Processor->setPresetName(presetNameLabel->getText());
			pfm2Processor->sendNrpnPresetName();
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
			param->setRealValue((float)currentMidiChannel);
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
		MidifiedFloatParameter* midiFP = (MidifiedFloatParameter*)parameters[p];
		if (midiFP->getName() == componentName) {
			return midiFP;
		}
	}
	return nullptr;
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

	std::unordered_set<String>::const_iterator midiChannel = paramSet.find("Midi Channel");
	if (midiChannel != paramSet.end()) {
		MidifiedFloatParameter* param = getParameterFromName("Midi Channel");
		midiChannelCombo->setSelectedId((int)param->getRealValue());
	}

	panelEngine->updateUI(paramSet);
	panelModulation->updateUI(paramSet);
	panelArpAndFilter->updateUI(paramSet);
}


void MainTabs::setPresetName(String presetName) {
	presetNameLabel->setText(presetName, dontSendNotification);
}

void MainTabs::setPresetNamePtr(char* presetNamePtr) {
	this->presetNamePtr = presetNamePtr;
}

void MainTabs::setMidiOutBuffer(MidiBuffer *midiOutBuffer) {
	this->midiOutBuffer = midiOutBuffer;
}


void MainTabs::setMidiChannel(int newMidiChannel) {
	midiChannelCombo->setSelectedId(newMidiChannel);
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
    <TAB name="Engine" colour="ff083543" useJucerComp="0" contentClassName="PanelEngine"
         constructorParams="" jucerComponentFile=""/>
    <TAB name="Modulation" colour="ff083543" useJucerComp="0" contentClassName="PanelModulation"
         constructorParams="" jucerComponentFile=""/>
    <TAB name="Arp &amp; Filter" colour="ff083543" useJucerComp="0" contentClassName="PanelArpAndFilter"
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
  <LABEL name="Version Label" id="c8880c204a60b679" memberName="versionLabel"
         virtualName="" explicitFocusOrder="0" pos="58R 8 55 24" textCol="fff5f5dc"
         edTextCol="ff000000" edBkgCol="0" labelText="v?.?&#10;" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15" kerning="0" bold="0" italic="0" justification="33"/>
  <TEXTBUTTON name="Device Button" id="69cb4ea6d744571b" memberName="deviceButton"
              virtualName="" explicitFocusOrder="0" pos="340R 8 60 24" bgColOff="5c5da4"
              bgColOn="fff0f8ff" buttonText="Midi" connectedEdges="0" needsCallback="1"
              radioGroupId="0"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]
