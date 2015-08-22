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

#include "SliderPfm2.h"

//[/Headers]

#include "PanelModulation.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
const char* matrixSourceNames [] = { "None", "lfo 1", "lfo 2", "lfo 3", "Free Env 1", "Free Env 2", "Step Seq 1", "Step Seq 2",
        "Mod Wheel", "Pit Bend", "After touch",  "Velocity", "Note1", "Note2", "Performance 1  ", "Performance 2", "Performance 3", "Performance 4",
        nullptr
} ;

const int matrixSourceIds[] = { 0, 1, 2, 3, 4 , 5, 6, 7, 8, 9, 10, 11, 12, 17, 13, 14, 15, 16 };


const char* matrixDestNames [] = {
        "None", "Gate", "Modulation Index 1", "Modulation Index 2", "Modulation Index 3", "Modulation index 4", "All Mod. Indexes",
        "Mix 1", "Pan 1", "Mix 2", "Pan 2", "Mix 3", "Pan 3", "Mix 4", "Pan 4", "All Mixes", "All Pans",
        "Op1 Frequency", "Op2 Frequency", "Op3 Frequency", "Op4 Frequency", "Op5 Frequency", "Op6 Frequency", "All Op Frequencies",
//         "Op1 Attack", "Op2 Attack", "Op3 Attack", "Op4 Attack", "Op5 Attack", "Op6 Attack", "All Op Attack", "All Op Release",
        "Mtx Multiplier 1", "Mtx Multiplier 2", "Mtx Multiplier 3", "Mtx Multiplier 4",
        "lfo 1 Frequency", "lfo 2 Frequency", "lfo 3 Frequency", "Free Env2 Silence", "Step Seq 1 gate", "Step Seq 2 gate",
        "Filter frequency", nullptr
} ;

const int matrixDestIds [] = { 0, 1, 2, 3, 4, 5, 6,
	7, 8, 9, 10, 11, 12, 13, 14, 15, 16,
	17, 18, 19, 20, 21, 22, 23,
	32, 33, 34, 35,
	36, 37, 38, 39, 40, 41, 42
};

//[/MiscUserDefs]

//==============================================================================
PanelModulation::PanelModulation ()
{
    addAndMakeVisible (matrixGroup = new GroupComponent ("matrix group",
                                                         TRANS("Matrix")));
    matrixGroup->setColour (GroupComponent::outlineColourId, Colour (0x604f4f4f));
    matrixGroup->setColour (GroupComponent::textColourId, Colour (0xff4f4f4f));

    addAndMakeVisible (lfoGroup = new GroupComponent ("lfo group",
                                                      TRANS("LFO")));
    lfoGroup->setColour (GroupComponent::outlineColourId, Colour (0x604f4f4f));
    lfoGroup->setColour (GroupComponent::textColourId, Colour (0xff4f4f4f));

    addAndMakeVisible (env1Group = new GroupComponent ("env 1 group",
                                                       TRANS("Free Enveloppe 1")));
    env1Group->setColour (GroupComponent::outlineColourId, Colour (0x60808080));
    env1Group->setColour (GroupComponent::textColourId, Colour (0xff4f4f4f));

    addAndMakeVisible (env2Group = new GroupComponent ("env 2 group",
                                                       TRANS("Free Enveloppe 2")));
    env2Group->setColour (GroupComponent::outlineColourId, Colour (0x60808080));
    env2Group->setColour (GroupComponent::textColourId, Colour (0xff4f4f4f));

    addAndMakeVisible (stepSeqGroup = new GroupComponent ("step sequencer group",
                                                          TRANS("Step Sequencers")));
    stepSeqGroup->setColour (GroupComponent::outlineColourId, Colour (0x60808080));
    stepSeqGroup->setColour (GroupComponent::textColourId, Colour (0xff4f4f4f));


    //[UserPreSize]

    // LFO
    for (int k = 0; k < NUMBER_OF_LFO; k++) {
        addAndMakeVisible(lfoButton[k] = new TextButton ("lfo button"));
        lfoButton[k]->setButtonText ("LFO " + String(k+1));
        lfoButton[k]->addListener (this);
        lfoButton[k]->setColour (TextButton::buttonColourId, Colour (0xffcff0e5));
        lfoButton[k]->setColour (TextButton::buttonOnColourId, Colours::aliceblue);
        lfoButton[k]->setClickingTogglesState(true);
        lfoButton[k]->setRadioGroupId(4243);
        lfoButton[k]->setConnectedEdges((k!=0 ? Button::ConnectedOnLeft : 0) | (k!= NUMBER_OF_LFO-1 ? Button::ConnectedOnRight : 0 ));

        addAndMakeVisible(lfoShape[k] = new ComboBox("LFO"+ String(k+1)+ " Shape"));
        lfoShape[k]->setEditableText (false);
        lfoShape[k]->setJustificationType (Justification::left);
        lfoShape[k]->setColour (ComboBox::buttonColourId, Colours::blue);
        lfoShape[k]->addItem("Sin", 1);
        lfoShape[k]->addItem("Saw", 2);
        lfoShape[k]->addItem("Triangle", 3);
        lfoShape[k]->addItem("Square", 4);
        lfoShape[k]->addItem("Random", 5);
        lfoShape[k]->setSelectedId(1);
        lfoShape[k]->addListener (this);

        addAndMakeVisible(lfoPhase[k] = new SliderPfm2("LFO"+ String(k+1) + " Phase"));
        lfoPhase[k]->setRange (0, 1.0f, .01f);
        lfoPhase[k]->setSliderStyle (Slider::RotaryVerticalDrag);
        lfoPhase[k]->setTextBoxStyle (Slider::TextBoxBelow, false, 35, 16);
        lfoPhase[k]->setDoubleClickReturnValue(true, 0.0f);
        lfoPhase[k]->setValue(0, dontSendNotification);
        lfoPhase[k]->addListener (this);


        addAndMakeVisible(lfoExtMidiSync[k] = new ComboBox("LFO"+ String(k+1) + " External Sync"));
        lfoExtMidiSync[k]->setEditableText (false);
        lfoExtMidiSync[k]->setJustificationType (Justification::left);
        lfoExtMidiSync[k]->setColour (ComboBox::buttonColourId, Colours::blue);
        lfoExtMidiSync[k]->addItem("Internal", 2400);
        lfoExtMidiSync[k]->addItem("MC/16", 2410);
        lfoExtMidiSync[k]->addItem("MC/8", 2420);
        lfoExtMidiSync[k]->addItem("MC/4", 2430);
        lfoExtMidiSync[k]->addItem("MC/2", 2440);
        lfoExtMidiSync[k]->addItem("MC", 2450);
        lfoExtMidiSync[k]->addItem("MC*2", 2460);
        lfoExtMidiSync[k]->addItem("MC*3", 2470);
        lfoExtMidiSync[k]->addItem("MC*4", 2480);
        lfoExtMidiSync[k]->addItem("MC*8", 2490);
        lfoExtMidiSync[k]->setSelectedId(2400);
        lfoExtMidiSync[k]->addListener (this);

        addAndMakeVisible(lfoFrequency[k] = new SliderPfm2("LFO"+ String(k+1) + " Frequency"));
        lfoFrequency[k]->setRange (0, 24.0f, .01f);
        lfoFrequency[k]->setSliderStyle (Slider::RotaryVerticalDrag);
        lfoFrequency[k]->setTextBoxStyle (Slider::TextBoxBelow, false, 35, 16);
        lfoFrequency[k]->setDoubleClickReturnValue(true, 3.0f);
        lfoFrequency[k]->setValue(3.0f, dontSendNotification);
        lfoFrequency[k]->addListener (this);

        addAndMakeVisible(lfoBias[k] = new SliderPfm2("LFO"+ String(k+1) + " Bias"));
        lfoBias[k]->setRange (-1.0f, 1.0f, .01f);
        lfoBias[k]->setSliderStyle (Slider::LinearVertical);
        lfoBias[k]->setTextBoxStyle (Slider::TextBoxBelow, false, 35, 16);
        lfoBias[k]->setDoubleClickReturnValue(true, 0.0f);
        lfoBias[k]->setValue(0.0f, dontSendNotification);
        lfoBias[k]->addListener (this);

        addAndMakeVisible(lfoKSync[k] = new SliderPfm2("LFO"+ String(k+1) + " KeySync time"));
        lfoKSync[k]->setRange (0.0f, 16.0f, .01f);
        lfoKSync[k]->setSliderStyle (Slider::RotaryVerticalDrag);
        lfoKSync[k]->setTextBoxStyle (Slider::TextBoxBelow, false, 35, 16);
        lfoKSync[k]->setDoubleClickReturnValue(true, 0.0f);
        lfoKSync[k]->setValue(0.0f, dontSendNotification);
        lfoKSync[k]->addListener (this);

        addAndMakeVisible(lfoKsynOnOff[k] = new ComboBox("LFO"+ String(k+1) + " KeySync"));
        lfoKsynOnOff[k]->setEditableText (false);
        lfoKsynOnOff[k]->setJustificationType (Justification::left);
        lfoKsynOnOff[k]->setColour (ComboBox::buttonColourId, Colours::blue);
        lfoKsynOnOff[k]->addItem("Off", 1);
        lfoKsynOnOff[k]->addItem("On", 2);
        lfoKsynOnOff[k]->setSelectedId(2);
        lfoKsynOnOff[k]->addListener (this);

    }
    lfoButton[0]->setToggleState(true, sendNotification);

    addAndMakeVisible(lfoPhaseLabel = new Label("LFO phase label", "Phase"));
    lfoPhaseLabel->setJustificationType(Justification::centredTop);

    addAndMakeVisible(lfoFrequencyLabel = new Label("LFO freq label", "Frequency"));
    lfoFrequencyLabel->setJustificationType(Justification::centredTop);

    addAndMakeVisible(lfoBiasLabel = new Label("LFO bias label", "Bias"));
    lfoBiasLabel->setJustificationType(Justification::centredTop);

    addAndMakeVisible(lfoKSynLabel = new Label("LFO ksyn label", "Note Sync"));
    lfoKSynLabel->setJustificationType(Justification::centredTop);


    for (int k=0; k<NUMBER_OF_STEP_SEQ; k++) {
        addAndMakeVisible(stepSeqExtMidiSync[k] = new ComboBox("Step Seq " + String(k+1) + " External Sync"));
        stepSeqExtMidiSync[k]->setEditableText (false);
        stepSeqExtMidiSync[k]->setColour (ComboBox::buttonColourId, Colours::blue);
        stepSeqExtMidiSync[k]->setJustificationType (Justification::left);
        stepSeqExtMidiSync[k]->addItem("Internal", 240);
        stepSeqExtMidiSync[k]->addItem("MC/4", 241);
        stepSeqExtMidiSync[k]->addItem("MC/2", 242);
        stepSeqExtMidiSync[k]->addItem("MC", 243);
        stepSeqExtMidiSync[k]->addItem("MC*2", 244);
        stepSeqExtMidiSync[k]->addItem("MC*4", 245);
        stepSeqExtMidiSync[k]->setSelectedId(1);
        stepSeqExtMidiSync[k]->addListener (this);

        addAndMakeVisible(stepSeqBPM[k] = new SliderPfm2("Step Seq " + String(k+1) +  " BPM"));
        stepSeqBPM[k]->setRange (10, 240.0f, 1.0f);
        stepSeqBPM[k]->setSliderStyle (Slider::RotaryVerticalDrag);
        stepSeqBPM[k]->setTextBoxStyle (Slider::TextBoxLeft, false, 35, 16);
        stepSeqBPM[k]->setDoubleClickReturnValue(true, 3.0f);
        stepSeqBPM[k]->setValue(3.0f, dontSendNotification);
        stepSeqBPM[k]->addListener (this);

        addAndMakeVisible(stepSeqGate[k] = new SliderPfm2("Step Seq " + String(k+1) +  " Gate"));
        stepSeqGate[k]->setRange (0.0f, 1.0f, 0.01f);
        stepSeqGate[k]->setSliderStyle (Slider::LinearHorizontal);
        stepSeqGate[k]->setTextBoxStyle (Slider::TextBoxBelow, false, 35, 16);
        stepSeqGate[k]->setDoubleClickReturnValue(true, 0.5f);
        stepSeqGate[k]->setValue(0.5f, dontSendNotification);
        stepSeqGate[k]->addListener (this);

        addAndMakeVisible(stepSequencer[k] = new StepSequencer (16, 16, 100 /* TOC CHANGE !!!!!*/ ));
        stepSequencer[k]->setBounds(16, 368, 500, 120);
        stepSequencer[k]->setName ("Step Seq " + String(k+1));
        stepSequencer[k]->addListener(this);

        stepSeqButton[k] = new TextButton ("step sequencer button");
        stepSeqButton[k]->setBounds(16 + 80*k,336, 80, 20);
        stepSeqButton[k]->setButtonText (TRANS("Sequencer " + String(k+1)));
        stepSeqButton[k]->addListener (this);
        stepSeqButton[k]->setColour (TextButton::buttonColourId, Colour (0xffcff0e5));
        stepSeqButton[k]->setColour (TextButton::buttonOnColourId, Colours::aliceblue);
        stepSeqButton[k]->setClickingTogglesState(true);
        stepSeqButton[k]->setRadioGroupId(4242);
        stepSeqButton[k]->setConnectedEdges((k!=0 ? Button::ConnectedOnLeft : 0) | (k!= NUMBER_OF_STEP_SEQ-1 ? Button::ConnectedOnRight : 0 ));
        addAndMakeVisible(stepSeqButton[k]);
    }
    stepSeqButton[0]->setToggleState(true, sendNotification);

    addAndMakeVisible(stepSeqBPMLabel = new Label("step seq label", "BPM"));
    stepSeqBPMLabel->setJustificationType(Justification::centred);

    addAndMakeVisible(stepSeqGateLabel = new Label("step seq get label", "Gate"));
    stepSeqBPMLabel->setJustificationType(Justification::centred);


    for (int r = 0; r < NUMBER_OF_MATRIX_ROW; r++) {
        addAndMakeVisible(matrixRowLabel[r] = new Label(String("matrix label ")+ String(r+1), String(r+1)));

        addAndMakeVisible(matrixMultipler[r] = new SliderPfm2("Mtx"+ String (r+1) + " Multiplier"));
        matrixMultipler[r]->setRange (-10.0f, 10.0f, .01f);
        matrixMultipler[r]->setSliderStyle (Slider::RotaryVerticalDrag);
        matrixMultipler[r]->setTextBoxStyle (Slider::TextBoxLeft, false, 35, 16);
        matrixMultipler[r]->setDoubleClickReturnValue(true, 0.0f);
        matrixMultipler[r]->setValue(0.0f, dontSendNotification);
        matrixMultipler[r]->addListener (this);

        addAndMakeVisible(matrixSource[r] = new ComboBox("Mtx"+ String (r+1) + " Source"));
        matrixSource[r]->setEditableText (false);
        matrixSource[r]->setJustificationType (Justification::centred);
        matrixSource[r]->setColour (ComboBox::buttonColourId, Colours::blue);
        for (int i = 0; matrixSourceNames[i] != nullptr; i++) {
            matrixSource[r]->addItem(matrixSourceNames[i], matrixSourceIds[i] + 1);
        }
        matrixSource[r]->setSelectedId(1);
        matrixSource[r]->addListener(this);

        addAndMakeVisible(matrixDestination[r] = new ComboBox("Mtx"+ String (r+1) + " Destination"));
        matrixDestination[r]->setEditableText (false);
        matrixDestination[r]->setJustificationType (Justification::centred);
        matrixDestination[r]->setColour (ComboBox::buttonColourId, Colours::blue);
        for (int i = 0; matrixDestNames[i] != nullptr; i++) {
            matrixDestination[r]->addItem(matrixDestNames[i], matrixDestIds[i] + 1);
        }
        matrixDestination[r]->setSelectedId(1);
        matrixDestination[r]->addListener(this);
    }

    addAndMakeVisible(enveloppeFree1 = new EnveloppeFree1 (127 /* 
															   !!!!!!!!!!!!!!!! */));
    enveloppeFree1->setName (TRANS("Free Env 1"));

    addAndMakeVisible(enveloppeFree2 = new EnveloppeFree2 (127));
    enveloppeFree2->setName (TRANS("Free Env 2"));

    addAndMakeVisible(enveloppeFree2LoopLabel = new Label("Freen Env 2 Loop label", "Loop"));

    addAndMakeVisible(enveloppeFree2Loop = new ComboBox("Free Env 2 Loop"));
    enveloppeFree2Loop->setEditableText (false);
    enveloppeFree2Loop->setJustificationType (Justification::centred);
    enveloppeFree2Loop->addItem("None", 1);
    enveloppeFree2Loop->addItem("Silence", 2);
    enveloppeFree2Loop->addItem("Attack", 3);
    enveloppeFree2Loop->setSelectedId(1);
    enveloppeFree2Loop->addListener (this);
    //[/UserPreSize]



    setSize (900, 700);


    //[Constructor] You can add your own custom stuff here..
    eventsToAdd = nullptr;
    initialized = false;
    //[/Constructor]
}

PanelModulation::~PanelModulation()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    //[/Destructor_pre]

    matrixGroup = nullptr;
    lfoGroup = nullptr;
    env1Group = nullptr;
    env2Group = nullptr;
    stepSeqGroup = nullptr;


    //[Destructor]. You can add your own custom destruction code here..
    //[/Destructor]
}

//==============================================================================
void PanelModulation::paint (Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    //[UserPaint] Add your own custom painting code here..
    //[/UserPaint]
}

void PanelModulation::resized()
{
    matrixGroup->setBounds (proportionOfWidth (0.6021f), proportionOfHeight (0.0078f), proportionOfWidth (0.3955f), proportionOfHeight (0.9876f));
    lfoGroup->setBounds (proportionOfWidth (0.0000f), proportionOfHeight (0.0078f), proportionOfWidth (0.5903f), proportionOfHeight (0.2298f));
    env1Group->setBounds (proportionOfWidth (0.0000f), proportionOfHeight (0.2453f), proportionOfWidth (0.5903f), proportionOfHeight (0.1848f));
    env2Group->setBounds (proportionOfWidth (0.0000f), proportionOfHeight (0.4301f), proportionOfWidth (0.5903f), proportionOfHeight (0.1848f));
    stepSeqGroup->setBounds (proportionOfWidth (0.0000f), proportionOfHeight (0.6227f), proportionOfWidth (0.5903f), proportionOfHeight (0.3711f));
    //[UserResized] Add your own custom resize handling here..
    lfoPhaseLabel->setBounds(proportionOfWidth (0.21f),  proportionOfHeight (0.06f) , 80, 20);
    lfoFrequencyLabel->setBounds(proportionOfWidth (0.30f),  proportionOfHeight (0.04f) , 80, 20);
    lfoBiasLabel->setBounds(proportionOfWidth (0.39f),  proportionOfHeight (0.04f) , 80, 20);
    lfoKSynLabel->setBounds(proportionOfWidth (0.48f),  proportionOfHeight (0.04f) , 80, 20);
    for (int k=0; k<NUMBER_OF_LFO; k++) {
        lfoButton[k]      ->setBounds(proportionOfWidth (0.02f) + 50*k, proportionOfHeight (0.035f) , 50, 20);
        lfoShape[k]       ->setBounds(proportionOfWidth (0.07f),        proportionOfHeight (0.12f) , 80, 20);
        lfoPhase[k]       ->setBounds(proportionOfWidth (0.21f),        proportionOfHeight (0.10f) , 80, 60);
        lfoExtMidiSync[k] ->setBounds(proportionOfWidth (0.30f) + 10,   proportionOfHeight (0.08f) , 60, 20);
        lfoFrequency[k]   ->setBounds(proportionOfWidth (0.30f),        proportionOfHeight (0.12f) , 80, 60);
        lfoBias[k]        ->setBounds(proportionOfWidth (0.39f),        proportionOfHeight (0.06f) , 80, proportionOfHeight (0.16f));
        lfoKsynOnOff[k]   ->setBounds(proportionOfWidth (0.48f) + 15,   proportionOfHeight (0.08f) , 50, 20);
        lfoKSync[k]       ->setBounds(proportionOfWidth (0.48f),        proportionOfHeight (0.12f) , 80, 60);
    }

    stepSeqBPMLabel->setBounds(proportionOfWidth (0.25f),  proportionOfHeight (0.66) , 40, 20);
    stepSeqGateLabel->setBounds(proportionOfWidth (0.46f),  proportionOfHeight (0.66) , 60, 20);
    for (int k=0; k<NUMBER_OF_STEP_SEQ; k++) {
        stepSeqButton[k]->setBounds(proportionOfWidth (0.02f) + 80*k, proportionOfHeight (0.65f) , 80, 20);
        stepSequencer[k]->setBounds(proportionOfWidth (0.02f), proportionOfHeight (0.78f), proportionOfWidth (0.55f), proportionOfHeight (0.20f));
        stepSeqExtMidiSync[k] ->setBounds(proportionOfWidth (0.29f) + 10,        proportionOfHeight (0.66f) , 60, 20);
        stepSeqBPM[k]   ->setBounds(proportionOfWidth (0.27f),        proportionOfHeight (0.69f) , 80, 60);
        stepSeqGate[k]   ->setBounds(proportionOfWidth (0.46f) + 20 - proportionOfWidth(0.08),        proportionOfHeight (0.70f) , proportionOfWidth(0.16), 40);
    }

    for (int r =0; r<NUMBER_OF_MATRIX_ROW; r++) {
        matrixRowLabel[r]   ->setBounds(proportionOfWidth (0.61f)  , proportionOfHeight (.06f + .08f * r), 40, 20);
        matrixSource[r]     ->setBounds(proportionOfWidth (0.64f)  , proportionOfHeight (.06f + .08f * r), 90, 20);
        matrixMultipler[r]  ->setBounds(proportionOfWidth (0.76f)  , proportionOfHeight (.035f + .08f * r), 80, 50);
        matrixDestination[r]->setBounds(proportionOfWidth (0.86f)  , proportionOfHeight (.06f + .08f * r), 110, 20);
    }
    enveloppeFree1->setBounds(proportionOfWidth (0.02f), proportionOfHeight (0.27f), proportionOfWidth (0.55f), proportionOfHeight (0.14f));
    enveloppeFree2->setBounds(proportionOfWidth (0.02f), proportionOfHeight (0.46f), proportionOfWidth (0.55f), proportionOfHeight (0.14f));

    enveloppeFree2LoopLabel->setBounds(proportionOfWidth (0.42)  , proportionOfHeight (.55f), 60, 20);
    enveloppeFree2Loop->setBounds(proportionOfWidth (0.47) , proportionOfHeight (.55f), 80, 20);

    //[/UserResized]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...

void PanelModulation::buttonClicked (Button* buttonThatWasClicked) {
    bool lfoButtonClicked = false;
    for (int k = 0 ; k< NUMBER_OF_LFO; k++) {
        if (buttonThatWasClicked == lfoButton[k]) {
            lfoButtonClicked = true;
        }
    }
    if (lfoButtonClicked) {
        for (int k = 0 ; k< NUMBER_OF_LFO; k++) {
            if (buttonThatWasClicked == lfoButton[k]) {
                lfoShape[k]->setVisible(true);
                lfoPhase[k]->setVisible(true);
                lfoExtMidiSync[k]->setVisible(true);
                lfoFrequency[k]->setVisible(true);
                lfoBias[k]->setVisible(true);
                lfoKSync[k]->setVisible(true);
                lfoKsynOnOff[k]->setVisible(true);

            } else {
                lfoShape[k]->setVisible(false);
                lfoPhase[k]->setVisible(false);
                lfoExtMidiSync[k]->setVisible(false);
                lfoFrequency[k]->setVisible(false);
                lfoBias[k]->setVisible(false);
                lfoKSync[k]->setVisible(false);
                lfoKsynOnOff[k]->setVisible(false);
            }
        }
        return;
    }
    bool stepButtonClicked = false;
    for (int k = 0 ; k< NUMBER_OF_STEP_SEQ; k++) {
        if (buttonThatWasClicked == stepSeqButton[k]) {
            stepButtonClicked = true;
        }
    }
    if (stepButtonClicked) {
        for (int k = 0 ; k< NUMBER_OF_STEP_SEQ; k++) {
            if (buttonThatWasClicked == stepSeqButton[k]) {
                stepSequencer[k]->setVisible(true);
                stepSeqBPM[k]->setVisible(true);
                stepSeqExtMidiSync[k]->setVisible(true);
                stepSeqGate[k]->setVisible(true);
            } else {
                stepSequencer[k]->setVisible(false);
                stepSeqBPM[k]->setVisible(false);
                stepSeqExtMidiSync[k]->setVisible(false);
                stepSeqGate[k]->setVisible(false);
            }
        }
        return;
    }


}
void PanelModulation::sliderValueChanged (Slider* sliderThatWasMoved) {
	sliderValueChanged(sliderThatWasMoved, true);
}

void PanelModulation::sliderValueChanged(Slider* sliderThatWasMoved, bool fromPluginUI)
{
    // Update the value if the change comes from the UI
    //printf("PanelModulation::sliderValueChanged (%u) : %s\n", fromPluginUI ? 1:0, sliderThatWasMoved->getName().toRawUTF8() );
    if (fromPluginUI) {
		teragon::Parameter * parameterReady = panelParameterMap[sliderThatWasMoved->getName()];
        if (parameterReady != nullptr) {
            teragon::ParameterValue value = sliderThatWasMoved->getValue();
            parameterSet->set(parameterReady, value, nullptr);
        }
    }
    for (int k=0; k < NUMBER_OF_LFO; k++) {
    	if (sliderThatWasMoved == lfoFrequency[k] && lfoExtMidiSync[k]->getSelectedId() != 2400) {
    		lfoFrequency[k]->setEnabled(true);
    		lfoExtMidiSync[k]->setSelectedId(2400, dontSendNotification);
    	}

        if (sliderThatWasMoved == lfoKSync[k] && lfoKsynOnOff[k]->getSelectedId() != 2) {
            lfoKSync[k]->setEnabled(true);
            lfoKsynOnOff[k]->setSelectedId(2, dontSendNotification);
        }
    }

    for (int k=0; k < NUMBER_OF_STEP_SEQ; k++) {
        if (sliderThatWasMoved == stepSeqBPM[k] && stepSeqExtMidiSync[k]->getSelectedId() != 240) {
            stepSeqBPM[k]->setEnabled(true);
            stepSeqExtMidiSync[k]->setSelectedId(240, dontSendNotification);
        }
    }
}

void PanelModulation::comboBoxChanged (ComboBox* comboBoxThatHasChanged) {
    comboBoxChanged(comboBoxThatHasChanged, true);
}

void PanelModulation::comboBoxChanged (ComboBox* comboBoxThatHasChanged, bool fromPluginUI) {
    // Update the value if the change comes from the UI
    if (fromPluginUI) {
        teragon::Parameter * parameterReady = panelParameterMap[comboBoxThatHasChanged->getName()];
        if (parameterReady != nullptr) {
            teragon::ParameterValue value = comboBoxThatHasChanged->getSelectedId();
            parameterSet->set(parameterReady, value, nullptr);
        }
    }

    for (int k = 0 ; k< NUMBER_OF_LFO; k++) {
        if (comboBoxThatHasChanged == lfoExtMidiSync[k]) {
            // Refresh Ksyn frequency on pfm2
            if (comboBoxThatHasChanged->getSelectedId() == 2400) {
                lfoFrequency[k]->setEnabled(true);
                // Force sending new value
                float value = lfoFrequency[k]->getValue();
                lfoFrequency[k]->setValue(24.0);
                lfoFrequency[k]->setValue(value);
            } else {
                lfoFrequency[k]->setEnabled(false);
            }
        }
        if (comboBoxThatHasChanged == lfoKsynOnOff[k]) {
            if (lfoKsynOnOff[k]->getSelectedId() == 2) {
                lfoKSync[k]->setEnabled(true);
                // Refresh Ksyn frequency on pfm2
                float value = lfoKSync[k]->getValue();
                lfoKSync[k]->setValue(.0f);
                lfoKSync[k]->setValue(value);
            } else {
                lfoKSync[k]->setEnabled(false);
            }
        }
    }
    for (int k = 0 ; k< NUMBER_OF_STEP_SEQ; k++) {
        if (comboBoxThatHasChanged == stepSeqExtMidiSync[k]) {
            if (comboBoxThatHasChanged->getSelectedId() == 240) {
                stepSeqBPM[k]->setEnabled(true);
                float value = stepSeqBPM[k]->getValue();
                stepSeqBPM[k]->setValue(10);
                stepSeqBPM[k]->setValue(value);
            } else {
                stepSeqBPM[k]->setEnabled(false);
            }
        }
    }

}



void PanelModulation::buildParameters() {
    for (int k=0; k<NUMBER_OF_MATRIX_ROW; k++) {
        updateComboParameter(matrixSource[k]);
        updateSliderParameter(matrixMultipler[k]);
        updateComboParameter(matrixDestination[k]);
    }
    for (int k = 0; k < NUMBER_OF_LFO; k++) {
        updateComboParameter(lfoShape[k]);
        updateComboParameter(lfoExtMidiSync[k]);
        updateSliderParameter(lfoPhase[k]);
        updateSliderParameter(lfoFrequency[k]);
        updateSliderParameter(lfoBias[k]);
        updateComboParameter(lfoKsynOnOff[k]);
        updateSliderParameter(lfoKSync[k]);
    }

    updateComboParameter(enveloppeFree2Loop);

    for (int k=0; k < NUMBER_OF_STEP_SEQ; k++) {
        updateStepSeqParameter(stepSequencer[k]);
        updateComboParameter(stepSeqExtMidiSync[k]);
        updateSliderParameter(stepSeqBPM[k]);
        updateSliderParameter(stepSeqGate[k]);
    }
    updateUIEnveloppe();

    // Let listen to enveloppe
    if (!initialized) {
        enveloppeFree1->addListener((EnveloppeListener*)this);
        enveloppeFree2->addListener((EnveloppeListener*)this);
    }

    initialized = true;
}


void PanelModulation::updateUIEnveloppe(const char* paramName) {
    const char** pointName = enveloppeFree1->getPointSuffix();
    const char* pString = enveloppeFree1->getName().toRawUTF8();

    for (int p=1; p < enveloppeFree1->getNumberOfPoints() ; p++) {
        String name = String(pString) + String(pointName[p-1]);
        teragon::Parameter* paramToMap =  parameterSet->get(name.toRawUTF8());

        if (paramName != nullptr && name != String(paramName)) {
            continue;
        } else {
//            printf("Cool... It's %s\r\n", name.toRawUTF8());
        }

        // Will remove that later but dont' BUG for the moment if that doesn't fit
        if (paramToMap == nullptr) {
            printf("Enveloppe point %s does not exist...\r\n", name.toRawUTF8());
            return;
        }

        if (panelParameterMap[name] == nullptr) {
            panelParameterMap.set(name ,paramToMap);
        }
        // And let's update the value and update the UI Without sending modification !!!
        // No modification : we dont want sliderValueChanged to be called in the different panels
        if (p  == 3) {
            if (paramToMap->getValue() != enveloppeFree1->getY(p)) {
                enveloppeFree1->setY(p, paramToMap->getValue());
                enveloppeFree1->repaint();
            }
        } else {
            if (paramToMap->getValue() != enveloppeFree1->getX(p)) {
                enveloppeFree1->setX(p, paramToMap->getValue());
                enveloppeFree1->repaint();
            }
        }
    }

    pointName = enveloppeFree2->getPointSuffix();
    pString = enveloppeFree2->getName().toRawUTF8();

    for (int p=1; p < enveloppeFree2->getNumberOfPoints() ; p++) {
        String name = String(pString) + String(pointName[p-1]);
        teragon::Parameter* paramToMap =  parameterSet->get(name.toRawUTF8());

        if (paramName != nullptr && name != String(paramName)) {
            continue;
        } else {
//            printf("Cool... It's %s\r\n", name.toRawUTF8());
        }

        // Will remove that later but dont' BUG for the moment if that doesn't fit
        if (paramToMap == nullptr) {
            printf("Enveloppe point %s does not exist...\r\n", name.toRawUTF8());
            return;
        }

        if (panelParameterMap[name] == nullptr) {
            panelParameterMap.set(name ,paramToMap);
        }
        // And let's update the value and update the UI Without sending modification !!!
        // No modification : we dont want sliderValueChanged to be called in the different panels
        if (paramToMap->getValue() != enveloppeFree2->getX(p)) {
            enveloppeFree2->setX(p, paramToMap->getValue());
            enveloppeFree2->repaint();
        }
    }
}

void PanelModulation::updateUIStepSequencer(const char* paramName) {
    if (String(paramName).startsWith("Step Seq 1")) {
        updateStepSeqParameter(stepSequencer[0]);
    } else  {
        updateStepSeqParameter(stepSequencer[1]);
    }
}



void PanelModulation::updateSliderParameter_hook(Slider* slider) {
	sliderValueChanged(slider, false);
}

void PanelModulation::updateComboParameter_hook(ComboBox* combo) {
	comboBoxChanged(combo, false);
}

//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Introjucer information section --

    This is where the Introjucer stores the metadata that describe this GUI layout, so
    make changes in here at your peril!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="PanelModulation" componentName=""
                 parentClasses="public Component, public Slider::Listener, public Button::Listener, public ComboBox::Listener, public PanelOfParameters"
                 constructorParams="" variableInitialisers="" snapPixels="8" snapActive="1"
                 snapShown="1" overlayOpacity="0.330" fixedSize="0" initialWidth="900"
                 initialHeight="700">
  <BACKGROUND backgroundColour="cff0e5"/>
  <GROUPCOMPONENT name="matrix group" id="f5fd2d041b369fc" memberName="matrixGroup"
                  virtualName="" explicitFocusOrder="0" pos="60.249% 0.781% 39.531% 98.698%"
                  outlinecol="604f4f4f" textcol="ff4f4f4f" title="Matrix"/>
  <GROUPCOMPONENT name="lfo group" id="25551a3d7e81232d" memberName="lfoGroup"
                  virtualName="" explicitFocusOrder="0" pos="0% 0.781% 59.004% 22.917%"
                  outlinecol="604f4f4f" textcol="ff4f4f4f" title="LFO"/>
  <GROUPCOMPONENT name="env 1 group" id="dc02178fe3e4a3e1" memberName="env1Group"
                  virtualName="" explicitFocusOrder="0" pos="0% 24.479% 59.004% 18.49%"
                  outlinecol="60808080" textcol="ff4f4f4f" title="Free Enveloppe 1"/>
  <GROUPCOMPONENT name="env 2 group" id="c35474bb62378ab6" memberName="env2Group"
                  virtualName="" explicitFocusOrder="0" pos="0% 42.969% 59.004% 18.49%"
                  outlinecol="60808080" textcol="ff4f4f4f" title="Free Enveloppe 2"/>
  <GROUPCOMPONENT name="step sequencer group" id="edf809d50c7eeefc" memberName="stepSeqGroup"
                  virtualName="" explicitFocusOrder="0" pos="0% 62.24% 59.004% 37.109%"
                  outlinecol="60808080" textcol="ff4f4f4f" title="Step Sequencers"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]
