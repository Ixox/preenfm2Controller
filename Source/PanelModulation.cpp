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
#include "PreenNrpn.h"
#include "MidifiedComponent.h"

//[/Headers]

#include "PanelModulation.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
const char* matrixSourceNames [] = { "None", "lfo 1", "lfo 2", "lfo 3", "Free Env 1", "Free Env 2", "Step Seq 1", "Step Seq 2",
        "Mod Wheel", "Pit Bend", "After touch",  "Key Velocity", "Key number", "Performance 1  ", "Performance 2", "Performance 3", "Performance 4",
        nullptr
} ;


const char* matrixDestNames [] = {
        "None", "Gate", "Modulation Index 1", "Modulation Index 2", "Modulation Index 3", "Modulation index 4", "All Mod. Indexes",
        "Mix 1", "Pan 1", "Mix 2", "Pan 2", "Mix 3", "Pan 3", "Mix 4", "Pan 4", "All Mixes", "All Pans",
        "Op1 Frequency", "Op2 Frequency", "Op3 Frequency", "Op4 Frequency", "Op5 Frequency", "Op6 Frequency", "All Op Frequencies",
        "Op1 Attack", "Op2 Attack", "Op3 Attack", "Op4 Attack", "Op5 Attack", "Op6 Attack", "All Op Attack", "All Op Release",
        "Mtx Multiplier 1", "Mtx Multiplier 2", "Mtx Multiplier 3", "Mtx Multiplier 4",
        "lfo 1 Frequency", "lfo 2 Frequency", "lfo 3 Frequency", "Free Env2 Silence", "Step Seq 1 gate", "Step Seq 2 gate",
        "Filter frequency", nullptr
} ;
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
        lfoButton[k]->setButtonText (TRANS("LFO " + String(k+1)));
        lfoButton[k]->addListener (this);
        lfoButton[k]->setColour (TextButton::buttonColourId, Colour (0xffcff0e5));
        lfoButton[k]->setColour (TextButton::buttonOnColourId, Colours::aliceblue);
        lfoButton[k]->setClickingTogglesState(true);
        lfoButton[k]->setRadioGroupId(4243);
        lfoButton[k]->setConnectedEdges((k!=0 ? Button::ConnectedOnLeft : 0) | (k!= NUMBER_OF_LFO-1 ? Button::ConnectedOnRight : 0 ));

        addAndMakeVisible(lfoShape[k] = new MidifiedComboBox(TRANS("LFO Shape "+ String(k)), PREENFM2_NRPN_LFO1_SHAPE + 4 * k, 1, 1));
        lfoShape[k]->setEditableText (false);
        lfoShape[k]->setJustificationType (Justification::left);
        lfoShape[k]->setColour (ComboBox::buttonColourId, Colours::blue);
        lfoShape[k]->addItem("Sin", 1);
        lfoShape[k]->addItem("Ramp", 2);
        lfoShape[k]->addItem("Saw", 3);
        lfoShape[k]->addItem("Square", 4);
        lfoShape[k]->addItem("Random", 5);
        lfoShape[k]->setSelectedId(1);
        lfoShape[k]->addListener (this);

        addAndMakeVisible(lfoExtMidiSync[k] = new MidifiedComboBox(TRANS("LFO Ext Sync "+ String(k)), PREENFM2_NRPN_LFO1_FREQUENCY+ 4 * k, -239, 10));
        lfoExtMidiSync[k]->setEditableText (false);
        lfoExtMidiSync[k]->setJustificationType (Justification::left);
        lfoExtMidiSync[k]->setColour (ComboBox::buttonColourId, Colours::blue);
        lfoExtMidiSync[k]->addItem("Internal", 1);
        lfoExtMidiSync[k]->addItem("MC/16", 2);
        lfoExtMidiSync[k]->addItem("MC/8", 3);
        lfoExtMidiSync[k]->addItem("MC/4", 4);
        lfoExtMidiSync[k]->addItem("MC/2", 5);
        lfoExtMidiSync[k]->addItem("MC", 6);
        lfoExtMidiSync[k]->addItem("MC*2", 7);
        lfoExtMidiSync[k]->addItem("MC*3", 8);
        lfoExtMidiSync[k]->addItem("MC*4", 9);
        lfoExtMidiSync[k]->addItem("MC*8", 10);
        lfoExtMidiSync[k]->setSelectedId(1);
        lfoExtMidiSync[k]->addListener (this);

        addAndMakeVisible(lfoFrequency[k] = new MidifiedSlider(TRANS("LFO frequency" + String(k+1)), PREENFM2_NRPN_LFO1_FREQUENCY + 4 * k, 0.0f));
        lfoFrequency[k]->setRange (0, 24.0f, .01f);
        lfoFrequency[k]->setSliderStyle (Slider::RotaryVerticalDrag);
        lfoFrequency[k]->setTextBoxStyle (Slider::TextBoxBelow, false, 35, 16);
        lfoFrequency[k]->setDoubleClickReturnValue(true, 3.0f);
        lfoFrequency[k]->setValue(3.0f, dontSendNotification);
        lfoFrequency[k]->addListener (this);

        addAndMakeVisible(lfoBias[k] = new MidifiedSlider(TRANS("LFO Bias " + String(k+1)), PREENFM2_NRPN_LFO1_BIAS+ 4 * k, -1.0f));
        lfoBias[k]->setRange (-1.0f, 1.0f, .01f);
        lfoBias[k]->setSliderStyle (Slider::LinearVertical);
        lfoBias[k]->setTextBoxStyle (Slider::TextBoxBelow, false, 35, 16);
        lfoBias[k]->setDoubleClickReturnValue(true, 0.0f);
        lfoBias[k]->setValue(0.0f, dontSendNotification);
        lfoBias[k]->addListener (this);

        addAndMakeVisible(lfoKSync[k] = new MidifiedSlider(TRANS("LFO KSyn " + String(k+1)), PREENFM2_NRPN_LFO1_KSYN+ 4 * k, -0.01f));
        lfoKSync[k]->setRange (0.0f, 16.0f, .01f);
        lfoKSync[k]->setSliderStyle (Slider::RotaryVerticalDrag);
        lfoKSync[k]->setTextBoxStyle (Slider::TextBoxBelow, false, 35, 16);
        lfoKSync[k]->setDoubleClickReturnValue(true, 0.0f);
        lfoKSync[k]->setValue(0.0f, dontSendNotification);
        lfoKSync[k]->addListener (this);

        addAndMakeVisible(lfoKsynOnOff[k] = new MidifiedComboBox(TRANS("Combo KSync "+ String(k)), PREENFM2_NRPN_LFO1_KSYN+ 4 * k, 1.01f, 1));
        lfoKsynOnOff[k]->setEditableText (false);
        lfoKsynOnOff[k]->setJustificationType (Justification::left);
        lfoKsynOnOff[k]->setColour (ComboBox::buttonColourId, Colours::blue);
        lfoKsynOnOff[k]->addItem("Off", 1);
        lfoKsynOnOff[k]->addItem("On", 2);
        lfoKsynOnOff[k]->setSelectedId(2);
        lfoKsynOnOff[k]->addListener (this);

    }
    lfoButton[0]->setToggleState(true, sendNotification);

    addAndMakeVisible(lfoFrequencyLabel = new Label("LFO freq labe", "Frequency"));
    lfoFrequencyLabel->setJustificationType(Justification::centredTop);

    addAndMakeVisible(lfoBiasLabel = new Label("LFO buas labe", "Bias"));
    lfoBiasLabel->setJustificationType(Justification::centredTop);

    addAndMakeVisible(lfoKSynLabel = new Label("LFO ksyn labe", "Note Sync"));
    lfoKSynLabel->setJustificationType(Justification::centredTop);


    int nrpnStepSeq[] = { PREENFM2_NRPN_STEPSEQ1_STEP1, PREENFM2_NRPN_STEPSEQ2_STEP1};
    for (int k=0; k<NUMBER_OF_STEP_SEQ; k++) {
        addAndMakeVisible(stepSeqExtMidiSync[k] = new MidifiedComboBox(TRANS("BPM Ext Sync "+ String(k)), PREENFM2_NRPN_STEPSEQ1_BPM + 4 * k, -239, 1));
        stepSeqExtMidiSync[k]->setEditableText (false);
        stepSeqExtMidiSync[k]->setColour (ComboBox::buttonColourId, Colours::blue);
        stepSeqExtMidiSync[k]->setJustificationType (Justification::left);
        stepSeqExtMidiSync[k]->addItem("Internal", 1);
        stepSeqExtMidiSync[k]->addItem("MC/4", 2);
        stepSeqExtMidiSync[k]->addItem("MC/2", 3);
        stepSeqExtMidiSync[k]->addItem("MC", 4);
        stepSeqExtMidiSync[k]->addItem("MC*2", 5);
        stepSeqExtMidiSync[k]->addItem("MC*4", 6);
        stepSeqExtMidiSync[k]->setSelectedId(1);
        stepSeqExtMidiSync[k]->addListener (this);

        addAndMakeVisible(stepSeqBPM[k] = new MidifiedSlider(TRANS("stepSeq BPM" + String(k+1)), PREENFM2_NRPN_STEPSEQ1_BPM + 4 * k, 0.0f, 1.0f));
        stepSeqBPM[k]->setRange (10, 240.0f, 1.0f);
        stepSeqBPM[k]->setSliderStyle (Slider::RotaryVerticalDrag);
        stepSeqBPM[k]->setTextBoxStyle (Slider::TextBoxLeft, false, 35, 16);
        stepSeqBPM[k]->setDoubleClickReturnValue(true, 3.0f);
        stepSeqBPM[k]->setValue(3.0f, dontSendNotification);
        stepSeqBPM[k]->addListener (this);

        addAndMakeVisible(stepSeqGate[k] = new MidifiedSlider(TRANS("stepSeq Gate " + String(k+1)), PREENFM2_NRPN_STEPSEQ1_GATE + 4 * k, 0.0f, 100.0f));
        stepSeqGate[k]->setRange (0.0f, 1.0f, 0.01f);
        stepSeqGate[k]->setSliderStyle (Slider::LinearHorizontal);
        stepSeqGate[k]->setTextBoxStyle (Slider::TextBoxBelow, false, 35, 16);
        stepSeqGate[k]->setDoubleClickReturnValue(true, 0.5f);
        stepSeqGate[k]->setValue(0.5f, dontSendNotification);
        stepSeqGate[k]->addListener (this);

        stepSequencer[k] = new StepSequencer (16, 16, nrpnStepSeq[k]);
        stepSequencer[k]->setBounds(16, 368, 500, 120);
        stepSequencer[k]->setName (TRANS("step sequencer" + String(k+1)));
        addAndMakeVisible(stepSequencer[k]);

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

        addAndMakeVisible(matrixMultipler[r] = new MidifiedSlider(TRANS("matrix multiplier" + String(r+1)), PREENFM2_NRPN_MTX1_MULTIPLIER + 4*r, -10));
        matrixMultipler[r]->setRange (-10.0f, 10.0f, .01f);
        matrixMultipler[r]->setSliderStyle (Slider::RotaryVerticalDrag);
        matrixMultipler[r]->setTextBoxStyle (Slider::TextBoxLeft, false, 35, 16);
        matrixMultipler[r]->setDoubleClickReturnValue(true, 0.0f);
        matrixMultipler[r]->setValue(0.0f, dontSendNotification);
        matrixMultipler[r]->addListener (this);

        addAndMakeVisible(matrixSource[r] = new MidifiedComboBox(TRANS("matrix source "+ String(r)), PREENFM2_NRPN_MTX1_SOURCE + 4 * r, 1, 1));
        matrixSource[r]->setEditableText (false);
        matrixSource[r]->setJustificationType (Justification::centred);
        matrixSource[r]->setColour (ComboBox::buttonColourId, Colours::blue);
        for (int i = 0; matrixSourceNames[i] != nullptr; i++) {
            matrixSource[r]->addItem(matrixSourceNames[i], i+1);
        }
        matrixSource[r]->setSelectedId(1);
        matrixSource[r]->addListener(this);

        addAndMakeVisible(matrixDestination[r] = new MidifiedComboBox(TRANS("matrix destination"+ String(r)), PREENFM2_NRPN_MTX1_DESTINATION + 4 * r, 1, 1));
        matrixDestination[r]->setEditableText (false);
        matrixDestination[r]->setJustificationType (Justification::centred);
        matrixDestination[r]->setColour (ComboBox::buttonColourId, Colours::blue);
        for (int i = 0; matrixDestNames[i] != nullptr; i++) {
            matrixDestination[r]->addItem(matrixDestNames[i], i+1);
        }
        matrixDestination[r]->setSelectedId(1);
        matrixDestination[r]->addListener(this);
    }

    addAndMakeVisible(enveloppeFree1 = new EnveloppeFree1 (PREENFM2_NRPN_FREE_ENV1_ATTK));
    enveloppeFree1->setName (TRANS("Free Env 1"));

    addAndMakeVisible(enveloppeFree2 = new EnveloppeFree2 (PREENFM2_NRPN_FREE_ENV2_SILENCE));
    enveloppeFree2->setName (TRANS("Free Env 2"));
    //[/UserPreSize]

    setSize (900, 700);


    //[Constructor] You can add your own custom stuff here..
    midiOutput = nullptr;
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
    matrixGroup->setBounds (proportionOfWidth (0.6017f), proportionOfHeight (0.0074f), proportionOfWidth (0.3954f), proportionOfHeight (0.9870f));
    lfoGroup->setBounds (proportionOfWidth (0.0000f), proportionOfHeight (0.0074f), proportionOfWidth (0.5903f), proportionOfHeight (0.2301f));
    env1Group->setBounds (proportionOfWidth (0.0000f), proportionOfHeight (0.2449f), proportionOfWidth (0.5903f), proportionOfHeight (0.1846f));
    env2Group->setBounds (proportionOfWidth (0.0000f), proportionOfHeight (0.4304f), proportionOfWidth (0.5903f), proportionOfHeight (0.1855f));
    stepSeqGroup->setBounds (proportionOfWidth (0.0000f), proportionOfHeight (0.6234f), proportionOfWidth (0.5903f), proportionOfHeight (0.3711f));
    //[UserResized] Add your own custom resize handling here..
    lfoFrequencyLabel->setBounds(proportionOfWidth (0.22f),  proportionOfHeight (0.04f) , 80, 20);
    lfoBiasLabel->setBounds(proportionOfWidth (0.35f),  proportionOfHeight (0.04f) , 80, 20);
    lfoKSynLabel->setBounds(proportionOfWidth (0.48f),  proportionOfHeight (0.04f) , 80, 20);
    for (int k=0; k<NUMBER_OF_LFO; k++) {
        lfoButton[k]      ->setBounds(proportionOfWidth (0.02f) + 50*k, proportionOfHeight (0.035f) , 50, 20);
        lfoShape[k]       ->setBounds(proportionOfWidth (0.05f),        proportionOfHeight (0.12f) , 80, 20);
        lfoExtMidiSync[k] ->setBounds(proportionOfWidth (0.22f) + 10,        proportionOfHeight (0.08f) , 60, 20);
        lfoFrequency[k]   ->setBounds(proportionOfWidth (0.22f),        proportionOfHeight (0.12f) , 80, 60);
        lfoBias[k]        ->setBounds(proportionOfWidth (0.35f),        proportionOfHeight (0.06f) , 80, proportionOfHeight (0.16f));
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

    //[/UserResized]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...
void PanelModulation::handleIncomingNrpn(int param, int value) {
    // enveloppe1->handleIncomingNrpn(param, value);
    static int index;
    switch (param) {
    case PREENFM2_NRPN_MTX1_MULTIPLIER:
    case PREENFM2_NRPN_MTX2_MULTIPLIER:
    case PREENFM2_NRPN_MTX3_MULTIPLIER:
    case PREENFM2_NRPN_MTX4_MULTIPLIER:
    case PREENFM2_NRPN_MTX5_MULTIPLIER:
    case PREENFM2_NRPN_MTX6_MULTIPLIER:
    case PREENFM2_NRPN_MTX7_MULTIPLIER:
    case PREENFM2_NRPN_MTX8_MULTIPLIER:
    case PREENFM2_NRPN_MTX9_MULTIPLIER:
    case PREENFM2_NRPN_MTX10_MULTIPLIER:
    case PREENFM2_NRPN_MTX11_MULTIPLIER:
    case PREENFM2_NRPN_MTX12_MULTIPLIER:
        index = (param - PREENFM2_NRPN_MTX1_MULTIPLIER) / 4;
        matrixMultipler[index]->setValue((float)value / 100.0f - 10.0f, dontSendNotification);
        break;
    case PREENFM2_NRPN_MTX1_SOURCE:
    case PREENFM2_NRPN_MTX2_SOURCE:
    case PREENFM2_NRPN_MTX3_SOURCE:
    case PREENFM2_NRPN_MTX4_SOURCE:
    case PREENFM2_NRPN_MTX5_SOURCE:
    case PREENFM2_NRPN_MTX6_SOURCE:
    case PREENFM2_NRPN_MTX7_SOURCE:
    case PREENFM2_NRPN_MTX8_SOURCE:
    case PREENFM2_NRPN_MTX9_SOURCE:
    case PREENFM2_NRPN_MTX10_SOURCE:
    case PREENFM2_NRPN_MTX11_SOURCE:
    case PREENFM2_NRPN_MTX12_SOURCE:
        index = (param - PREENFM2_NRPN_MTX1_SOURCE) / 4;
        matrixSource[index]->setSelectedId(value + 1, dontSendNotification);
        break;
    case PREENFM2_NRPN_MTX1_DESTINATION:
    case PREENFM2_NRPN_MTX2_DESTINATION:
    case PREENFM2_NRPN_MTX3_DESTINATION:
    case PREENFM2_NRPN_MTX4_DESTINATION:
    case PREENFM2_NRPN_MTX5_DESTINATION:
    case PREENFM2_NRPN_MTX6_DESTINATION:
    case PREENFM2_NRPN_MTX7_DESTINATION:
    case PREENFM2_NRPN_MTX8_DESTINATION:
    case PREENFM2_NRPN_MTX9_DESTINATION:
    case PREENFM2_NRPN_MTX10_DESTINATION:
    case PREENFM2_NRPN_MTX11_DESTINATION:
    case PREENFM2_NRPN_MTX12_DESTINATION:
        index = (param - PREENFM2_NRPN_MTX1_DESTINATION) / 4;
        matrixDestination[index]->setSelectedId(value + 1, dontSendNotification);
        break;
    case PREENFM2_NRPN_FREE_ENV1_ATTK:
    case PREENFM2_NRPN_FREE_ENV1_DECAY:
    case PREENFM2_NRPN_FREE_ENV1_RELEASE:
    case PREENFM2_NRPN_FREE_ENV1_SUSTAIN:
        enveloppeFree1->handleIncomingNrpn(param, value);
        break;
    case PREENFM2_NRPN_FREE_ENV2_SILENCE:
    case PREENFM2_NRPN_FREE_ENV2_ATTK:
    case PREENFM2_NRPN_FREE_ENV2_DECAY:
    case PREENFM2_NRPN_FREE_ENV2_LOOP:
        enveloppeFree2->handleIncomingNrpn(param, value);
        break;
    case PREENFM2_NRPN_LFO1_SHAPE:
    case PREENFM2_NRPN_LFO2_SHAPE:
    case PREENFM2_NRPN_LFO3_SHAPE:
        lfoShape[(param - PREENFM2_NRPN_LFO1_SHAPE) / 4]->setSelectedId(value + 1, dontSendNotification);
        break;
    case PREENFM2_NRPN_LFO1_FREQUENCY:
    case PREENFM2_NRPN_LFO2_FREQUENCY:
    case PREENFM2_NRPN_LFO3_FREQUENCY:
        if (value <= 2400) {
            if (lfoExtMidiSync[(param - PREENFM2_NRPN_LFO1_FREQUENCY) / 4]->getSelectedId() != 1) {
                lfoExtMidiSync[(param - PREENFM2_NRPN_LFO1_FREQUENCY) / 4]->setSelectedId(1, dontSendNotification);
                lfoFrequency[(param - PREENFM2_NRPN_LFO1_FREQUENCY) / 4]->setEnabled(true);
            }
            lfoFrequency[(param - PREENFM2_NRPN_LFO1_FREQUENCY) / 4]->setValue(value / 100.0f, dontSendNotification);
        } else {
            lfoExtMidiSync[(param - PREENFM2_NRPN_LFO1_FREQUENCY) / 4]->setSelectedId((value - 2400) / 10 + 1, dontSendNotification);
            lfoFrequency[(param - PREENFM2_NRPN_LFO1_FREQUENCY) / 4]->setEnabled(false);
        }
        break;
    case PREENFM2_NRPN_LFO1_BIAS:
    case PREENFM2_NRPN_LFO2_BIAS:
    case PREENFM2_NRPN_LFO3_BIAS:
        lfoBias[(param - PREENFM2_NRPN_LFO1_BIAS) / 4]->setValue(value / 100.0f - 1.0f);
        break;
    case PREENFM2_NRPN_LFO1_KSYN:
    case PREENFM2_NRPN_LFO2_KSYN:
    case PREENFM2_NRPN_LFO3_KSYN:
        if (value == 0) {
            lfoKsynOnOff[(param - PREENFM2_NRPN_LFO1_KSYN) / 4]->setSelectedId(1, dontSendNotification);
            lfoKSync[(param - PREENFM2_NRPN_LFO1_KSYN) / 4]->setEnabled(false);
        } else {
            if (lfoKsynOnOff[(param - PREENFM2_NRPN_LFO1_KSYN) / 4]->getSelectedId() == 1) {
                lfoKsynOnOff[(param - PREENFM2_NRPN_LFO1_KSYN) / 4]->setSelectedId(2, dontSendNotification);
                lfoKSync[(param - PREENFM2_NRPN_LFO1_KSYN) / 4]->setEnabled(true);
            }
            lfoKSync[(param - PREENFM2_NRPN_LFO1_KSYN) / 4]->setValue(value / 100.0f - 0.01f, dontSendNotification);
        }
        break;
    case PREENFM2_NRPN_STEPSEQ1_BPM:
    case PREENFM2_NRPN_STEPSEQ2_BPM:
        if (value <= 240) {
            if (stepSeqExtMidiSync[(param - PREENFM2_NRPN_STEPSEQ1_BPM) / 4]->getSelectedId() != 1) {
                stepSeqExtMidiSync[(param - PREENFM2_NRPN_STEPSEQ1_BPM) / 4]->setSelectedId(1, dontSendNotification);
                stepSeqBPM[(param - PREENFM2_NRPN_STEPSEQ1_BPM) / 4]->setEnabled(true);
            }
            stepSeqBPM[(param - PREENFM2_NRPN_STEPSEQ1_BPM) / 4]->setValue(value , dontSendNotification);
        } else if (value <= 245) {
            stepSeqExtMidiSync[(param - PREENFM2_NRPN_STEPSEQ1_BPM) / 4]->setSelectedId((value - 239) , dontSendNotification);
            stepSeqBPM[(param - PREENFM2_NRPN_STEPSEQ1_BPM) / 4]->setEnabled(false);
        }
        break;
    case PREENFM2_NRPN_STEPSEQ1_GATE:
    case PREENFM2_NRPN_STEPSEQ2_GATE:
        stepSeqGate[(param - PREENFM2_NRPN_STEPSEQ1_GATE) / 4]->setValue(value / 100.0f);
        break;
    case PREENFM2_NRPN_STEPSEQ1_STEP1:
    case PREENFM2_NRPN_STEPSEQ1_STEP2:
    case PREENFM2_NRPN_STEPSEQ1_STEP3:
    case PREENFM2_NRPN_STEPSEQ1_STEP4:
    case PREENFM2_NRPN_STEPSEQ1_STEP5:
    case PREENFM2_NRPN_STEPSEQ1_STEP6:
    case PREENFM2_NRPN_STEPSEQ1_STEP7:
    case PREENFM2_NRPN_STEPSEQ1_STEP8:
    case PREENFM2_NRPN_STEPSEQ1_STEP9:
    case PREENFM2_NRPN_STEPSEQ1_STEP10:
    case PREENFM2_NRPN_STEPSEQ1_STEP11:
    case PREENFM2_NRPN_STEPSEQ1_STEP12:
    case PREENFM2_NRPN_STEPSEQ1_STEP13:
    case PREENFM2_NRPN_STEPSEQ1_STEP14:
    case PREENFM2_NRPN_STEPSEQ1_STEP15:
    case PREENFM2_NRPN_STEPSEQ1_STEP16:
        stepSequencer[0]->handleIncomingNrpn(param, value);
        break;
    case PREENFM2_NRPN_STEPSEQ2_STEP1:
    case PREENFM2_NRPN_STEPSEQ2_STEP2:
    case PREENFM2_NRPN_STEPSEQ2_STEP3:
    case PREENFM2_NRPN_STEPSEQ2_STEP4:
    case PREENFM2_NRPN_STEPSEQ2_STEP5:
    case PREENFM2_NRPN_STEPSEQ2_STEP6:
    case PREENFM2_NRPN_STEPSEQ2_STEP7:
    case PREENFM2_NRPN_STEPSEQ2_STEP8:
    case PREENFM2_NRPN_STEPSEQ2_STEP9:
    case PREENFM2_NRPN_STEPSEQ2_STEP10:
    case PREENFM2_NRPN_STEPSEQ2_STEP11:
    case PREENFM2_NRPN_STEPSEQ2_STEP12:
    case PREENFM2_NRPN_STEPSEQ2_STEP13:
    case PREENFM2_NRPN_STEPSEQ2_STEP14:
    case PREENFM2_NRPN_STEPSEQ2_STEP15:
    case PREENFM2_NRPN_STEPSEQ2_STEP16:
        stepSequencer[1]->handleIncomingNrpn(param, value);
        break;
    }
}

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
                lfoExtMidiSync[k]->setVisible(true);
                lfoFrequency[k]->setVisible(true);
                lfoBias[k]->setVisible(true);
                lfoKSync[k]->setVisible(true);
                lfoKsynOnOff[k]->setVisible(true);

            } else {
                lfoShape[k]->setVisible(false);
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

    if (midiOutput == nullptr) return;
    //[UsersliderValueChanged_Pre]
    MidifiedSlider* midifiedSlider = dynamic_cast<MidifiedSlider*>(sliderThatWasMoved);
    if(midifiedSlider != 0) {
        // old was safely casted to NewType
        midifiedSlider->sendNrpn(midiOutput, midifiedSlider->getValue());
    }


}

void PanelModulation::comboBoxChanged (ComboBox* comboBoxThatHasChanged) {
    int lfoExteralMidiComboChanged = -1;
    int lfoKSyncOnOffChanged = -1;
    int stepSeqMidiComboChanged = -1;

    for (int k = 0 ; k< NUMBER_OF_LFO; k++) {
        if (comboBoxThatHasChanged == lfoExtMidiSync[k]) {
            lfoFrequency[k]->setEnabled(comboBoxThatHasChanged->getSelectedId() == 1);
            lfoExteralMidiComboChanged = k;

        }
        if (comboBoxThatHasChanged == lfoKsynOnOff[k]) {
            lfoKSync[k]->setEnabled(lfoKsynOnOff[k]->getSelectedId() == 2);
            lfoKSyncOnOffChanged = k;
        }
    }
    for (int k = 0 ; k< NUMBER_OF_STEP_SEQ; k++) {
        if (comboBoxThatHasChanged == stepSeqExtMidiSync[k]) {
            stepSeqBPM[k]->setEnabled(comboBoxThatHasChanged->getSelectedId() == 1);
            stepSeqMidiComboChanged = k;
        }
    }

    if (midiOutput == nullptr) return;
    MidifiedComboBox* midifiedComboBox = dynamic_cast<MidifiedComboBox*>(comboBoxThatHasChanged);
    if (midifiedComboBox != 0) {
        // If new combo is internal frequency, we must send the nrpn of the slider value
        if (lfoExteralMidiComboChanged >= 0 && comboBoxThatHasChanged->getSelectedId() == 1) {
            Slider *lfoSlider = lfoFrequency[lfoExteralMidiComboChanged];
            MidifiedSlider* midifiedSlider = dynamic_cast<MidifiedSlider*>(lfoSlider);
            if (midifiedSlider) {
                midifiedSlider->sendNrpn(midiOutput, midifiedSlider->getValue());
            }
        } else if (lfoKSyncOnOffChanged >= 0 && comboBoxThatHasChanged->getSelectedId() == 2) {
            Slider *ksynSlider = lfoKSync[lfoKSyncOnOffChanged];
            MidifiedSlider* midifiedSlider = dynamic_cast<MidifiedSlider*>(ksynSlider);
            if (midifiedSlider) {
                midifiedSlider->sendNrpn(midiOutput, midifiedSlider->getValue());
            }
        } else if (stepSeqMidiComboChanged >= 0 && comboBoxThatHasChanged->getSelectedId() == 1) {
            Slider *bpmSlider = stepSeqBPM[stepSeqMidiComboChanged];
            MidifiedSlider* midifiedSlider = dynamic_cast<MidifiedSlider*>(bpmSlider);
            if (midifiedSlider) {
                midifiedSlider->sendNrpn(midiOutput, midifiedSlider->getValue());
            }
        } else {
            midifiedComboBox->sendNrpn(midiOutput, midifiedComboBox->getSelectedId());
        }
    }
}

void PanelModulation::setMidiOutput(MidiOutput* midiOutput) {
    this->midiOutput = midiOutput;
    enveloppeFree1->setMidiOutput(midiOutput);
    enveloppeFree2->setMidiOutput(midiOutput);
    for (int s=0; s<NUMBER_OF_STEP_SEQ; s++) {
        stepSequencer[s]->setMidiOutput(midiOutput);
    }
}


//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Introjucer information section --

    This is where the Introjucer stores the metadata that describe this GUI layout, so
    make changes in here at your peril!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="PanelModulation" componentName=""
                 parentClasses="public Component, public Slider::Listener, public Button::Listener, public ComboBox::Listener"
                 constructorParams="" variableInitialisers="" snapPixels="8" snapActive="1"
                 snapShown="1" overlayOpacity="0.330" fixedSize="0" initialWidth="900"
                 initialHeight="700">
  <BACKGROUND backgroundColour="cff0e5"/>
  <GROUPCOMPONENT name="matrix group" id="f5fd2d041b369fc" memberName="matrixGroup"
                  virtualName="" explicitFocusOrder="0" pos="60.214% 0.776% 39.549% 98.758%"
                  outlinecol="604f4f4f" textcol="ff4f4f4f" title="Matrix"/>
  <GROUPCOMPONENT name="lfo group" id="25551a3d7e81232d" memberName="lfoGroup"
                  virtualName="" explicitFocusOrder="0" pos="0% 0.776% 59.026% 22.981%"
                  outlinecol="604f4f4f" textcol="ff4f4f4f" title="LFO"/>
  <GROUPCOMPONENT name="env 1 group" id="dc02178fe3e4a3e1" memberName="env1Group"
                  virtualName="" explicitFocusOrder="0" pos="0% 24.534% 59.026% 18.478%"
                  outlinecol="60808080" textcol="ff4f4f4f" title="Free Enveloppe 1"/>
  <GROUPCOMPONENT name="env 2 group" id="c35474bb62378ab6" memberName="env2Group"
                  virtualName="" explicitFocusOrder="0" pos="0% 43.012% 59.026% 18.478%"
                  outlinecol="60808080" textcol="ff4f4f4f" title="Free Enveloppe 2"/>
  <GROUPCOMPONENT name="step sequencer group" id="edf809d50c7eeefc" memberName="stepSeqGroup"
                  virtualName="" explicitFocusOrder="0" pos="0% 62.267% 59.026% 37.112%"
                  outlinecol="60808080" textcol="ff4f4f4f" title="Step Sequencers"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]
