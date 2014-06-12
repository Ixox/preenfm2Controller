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
    tabbedComponent->addTab (TRANS("Engine"), Colour (0xffdef8ff), new PanelEngine(), true);
    tabbedComponent->addTab (TRANS("Moldulation"), Colour (0xffdeffe4), new PanelModulation(), true);
    tabbedComponent->addTab (TRANS("Arp & Filter"), Colour (0xfffffade), new PanelArpAndFilter(), true);
    tabbedComponent->addTab (TRANS("Settings"), Colour (0xfff6ffc7), 0, false);
    tabbedComponent->setCurrentTabIndex (0);

    addAndMakeVisible (midiInputLabel = new Label ("midi input label",
                                                   TRANS("0")));
    midiInputLabel->setFont (Font (15.00f, Font::plain));
    midiInputLabel->setJustificationType (Justification::centredLeft);
    midiInputLabel->setEditable (false, false, false);
    midiInputLabel->setColour (Label::textColourId, Colours::blue);
    midiInputLabel->setColour (TextEditor::textColourId, Colours::black);
    midiInputLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (midiInputLabel2 = new Label ("midi input label", TRANS("0")));
    midiInputLabel2->setFont (Font (15.00f, Font::plain));
    midiInputLabel2->setJustificationType (Justification::centredLeft);
    midiInputLabel2->setEditable (false, false, false);
    midiInputLabel2->setColour (Label::textColourId, Colours::blue);
    midiInputLabel2->setColour (TextEditor::textColourId, Colours::black);
    midiInputLabel2->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (titleLabel = new Label ("Title label", "Preset"));
    titleLabel->setFont (Font (24.00f, Font::plain));
    titleLabel->setJustificationType (Justification::centredLeft);
    titleLabel->setEditable (true, true, false);

    addAndMakeVisible (pullButton = new TextButton ("pull button"));
    pullButton->setButtonText (TRANS("Pull"));
    pullButton->addListener (this);

    addAndMakeVisible (pushButton = new TextButton ("push button"));
    pushButton->setButtonText (TRANS("push"));
    pushButton->addListener (this);


    //[UserPreSize]
    //[/UserPreSize]

    setSize (900, 710);


    //[Constructor] You can add your own custom stuff here..
	panelEngine = ((PanelEngine*)tabbedComponent->getTabContentComponent(0));
	panelModulation = ((PanelModulation*)tabbedComponent->getTabContentComponent(1));
	panelArpAndFilter = ((PanelArpAndFilter*)tabbedComponent->getTabContentComponent(2));
	pullButtonValue = 0;
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
    pushButton = nullptr;


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
    tabbedComponent->setBounds (proportionOfWidth (0.0095f), proportionOfHeight (0.0248f), proportionOfWidth (0.9786f), proportionOfHeight (0.9689f));
    midiInputLabel->setBounds (600, 8, 48, 16);
    midiInputLabel2->setBounds (650, 8, 48, 16);
    pullButton->setBounds (getWidth() - 74, 8, 55, 24);
    pushButton->setBounds (getWidth() - 146, 8, 55, 24);
    titleLabel->setBounds (getWidth() / 2.5, 10, 200, 30);
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

        teragon::Parameter* param =  parameterSet->get("Pull button");
        // Will remove that later but dont' BUG for the moment if that doesn't fit
        if (param == nullptr) {
            printf("PULL BUTTON does not exist...\r\n");
            return;
        }

        pullButtonValue = (pullButtonValue == 0 ? 1 : 0) ;
        printf("MainTabs::PULL BUTTON PRESSED");
        parameterSet->set(param, pullButtonValue, nullptr);

        //[/UserButtonCode_pullButton]
    }
    else if (buttonThatWasClicked == pushButton)
    {
        //[UserButtonCode_pushButton] -- add your button handler code here..
        //[/UserButtonCode_pushButton]
    }

    //[UserbuttonClicked_Post]
    //[/UserbuttonClicked_Post]
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
    panelEngine->updateUI(paramSet);
    panelModulation->updateUI(paramSet);
    panelArpAndFilter->updateUI(paramSet);
}


void MainTabs::newNrpnParam(int nrpn, int value) {
    midiInputLabel->setText(String(nrpn), dontSendNotification);
    midiInputLabel2->setText(String(value), dontSendNotification);
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
                   virtualName="TabbedComponent" explicitFocusOrder="0" pos="0.95% 2.484% 97.862% 96.894%"
                   orientation="top" tabBarDepth="30" initialTab="0">
    <TAB name="Engine" colour="ffdef8ff" useJucerComp="0" contentClassName="PanelEngine"
         constructorParams="" jucerComponentFile=""/>
    <TAB name="Moldulation" colour="ffdeffe4" useJucerComp="0" contentClassName="PanelModulation"
         constructorParams="" jucerComponentFile=""/>
    <TAB name="Arp &amp; Filter" colour="fffffade" useJucerComp="0" contentClassName="PanelArpAndFilter"
         constructorParams="" jucerComponentFile=""/>
    <TAB name="Settings" colour="fff6ffc7" useJucerComp="0" contentClassName=""
         constructorParams="" jucerComponentFile=""/>
  </TABBEDCOMPONENT>
  <LABEL name="midi input label" id="f77b232960a175fb" memberName="midiInputLabel"
         virtualName="" explicitFocusOrder="0" pos="552 8 48 16" textCol="ff0000ff"
         edTextCol="ff000000" edBkgCol="0" labelText="0" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15" bold="0" italic="0" justification="33"/>
  <LABEL name="midi input label" id="f5bde9938974ba9f" memberName="midiInputLabel2"
         virtualName="" explicitFocusOrder="0" pos="616 8 48 16" textCol="ff0000ff"
         edTextCol="ff000000" edBkgCol="0" labelText="0" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15" bold="0" italic="0" justification="33"/>
  <TEXTBUTTON name="pull button" id="9da85c0691256028" memberName="pullButton"
              virtualName="" explicitFocusOrder="0" pos="74R 8 55 24" buttonText="Pull"
              connectedEdges="0" needsCallback="1" radioGroupId="0"/>
  <TEXTBUTTON name="push button" id="cd85e35be3968a4b" memberName="pushButton"
              virtualName="" explicitFocusOrder="0" pos="146R 8 55 24" buttonText="push"
              connectedEdges="0" needsCallback="1" radioGroupId="0"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]
