/*
* Copyright 2017 Xavier Hosxe
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
//[Headers] You can add your own extra header files here...
#include "JuceHeader.h"
#include "SliderPfm2.h"
#include "../MidifiedFloatParameter.h"
//[/Headers]

#include "PanelModulation.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
const char* matrixSourceNames [] = { "None", "lfo 1", "lfo 2", "lfo 3", "Free Env 1", "Free Env 2", "Step Seq 1", "Step Seq 2",
        "Mod Wheel", "Pit Bend", "After touch",  "Velocity", "Note1", "Note2", "Breath CC2",  "Performance 1  ", "Performance 2", "Performance 3", "Performance 4",
		
        nullptr
} ;

const int matrixSourceIds[] = { 0, 1, 2, 3, 4 , 5, 6, 7, 8, 9, 10, 11, 12, 17, 18, 13, 14, 15, 16 };


const char* matrixDestNames [] = {
	        "None", "Gate", "Modulation Index 1", "Modulation Index 2", "Modulation Index 3", "Modulation index 4", "All Mod. Indexes",
/*7*/        "Mix 1", "Pan 1", "Mix 2", "Pan 2", "Mix 3", "Pan 3", "Mix 4", "Pan 4", "All Mixes", "All Pans",
/*17*/       "Op1 Frequency", "Op2 Frequency", "Op3 Frequency", "Op4 Frequency", "Op5 Frequency", "Op6 Frequency", "All Op Frequencies", "All Op Freq Harmonic",
/*24*/       "Op1 Attack", "Op2 Attack", "Op3 Attack", "Op4 Attack", "Op5 Attack", "Op6 Attack", 
/*30*/		 "Carrier Attacks", "Carrier Decays", "Carrier Releases", "Modulator Attacks", "Modulator Decays", "Modulator Releases",
/*32*/        "Mtx Multiplier 1", "Mtx Multiplier 2", "Mtx Multiplier 3", "Mtx Multiplier 4",
/*36*/        "lfo 1 Frequency", "lfo 2 Frequency", "lfo 3 Frequency", "Free Env2 Silence", "Step Seq 1 gate", "Step Seq 2 gate",
/*42*/        "Filter frequency", 
		
		nullptr
} ;

const int matrixDestIds [] = { 0, 1, 2, 3, 4, 5, 6,
	7, 8, 9, 10, 11, 12, 13, 14, 15, 16,
	17, 18, 19, 20, 21, 22, 23, 43,
	24, 25, 26, 27, 28, 29,
	30, 44, 31, 45, 46, 47,
	32, 33, 34, 35,
	36, 37, 38, 39, 40, 41,
	42

};


//[/MiscUserDefs]

//==============================================================================
PanelModulation::PanelModulation ()
{
    //[Constructor_pre] You can add your own custom stuff here..
    //[/Constructor_pre]

    addAndMakeVisible (matrixGroup = new GroupComponent ("matrix group",
                                                         TRANS("Matrix")));
    matrixGroup->setColour (GroupComponent::outlineColourId, Colour (0xff749fad));
    matrixGroup->setColour (GroupComponent::textColourId, Colour (0xff749fad));

    addAndMakeVisible (lfoGroup = new GroupComponent ("lfo group",
                                                      String()));
    lfoGroup->setColour (GroupComponent::outlineColourId, Colour (0xff749fad));
    lfoGroup->setColour (GroupComponent::textColourId, Colour (0xff749fad));

    addAndMakeVisible (env1Group = new GroupComponent ("env 1 group",
                                                       TRANS("Free Enveloppe 1")));
    env1Group->setColour (GroupComponent::outlineColourId, Colour (0xff749fad));
    env1Group->setColour (GroupComponent::textColourId, Colour (0xff749fad));

    addAndMakeVisible (env2Group = new GroupComponent ("env 2 group",
                                                       TRANS("Free Enveloppe 2")));
    env2Group->setColour (GroupComponent::outlineColourId, Colour (0xff749fad));
    env2Group->setColour (GroupComponent::textColourId, Colour (0xff749fad));

    addAndMakeVisible (stepSeqGroup = new GroupComponent ("step sequencer group",
                                                          String()));
    stepSeqGroup->setColour (GroupComponent::outlineColourId, Colour (0xff749fad));
    stepSeqGroup->setColour (GroupComponent::textColourId, Colour (0xff749fad));


    //[UserPreSize]

    // LFO
    for (int k = 0; k < NUMBER_OF_LFO; k++) {
        addAndMakeVisible(lfoButton[k] = new TextButton ("lfo button"));
        lfoButton[k]->setButtonText ("LFO " + String(k+1));
        lfoButton[k]->addListener (this);
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
        lfoExtMidiSync[k]->addItem("Internal", 9990);
        lfoExtMidiSync[k]->addItem("MC/16", 10000);
        lfoExtMidiSync[k]->addItem("MC/8", 10010);
        lfoExtMidiSync[k]->addItem("MC/4", 10020);
        lfoExtMidiSync[k]->addItem("MC/2", 10030);
        lfoExtMidiSync[k]->addItem("MC", 10040);
        lfoExtMidiSync[k]->addItem("MC*2", 10050);
        lfoExtMidiSync[k]->addItem("MC*3", 10060);
        lfoExtMidiSync[k]->addItem("MC*4", 10070);
        lfoExtMidiSync[k]->addItem("MC*8", 10080);
        lfoExtMidiSync[k]->setSelectedId(9990);
        lfoExtMidiSync[k]->addListener (this);

        addAndMakeVisible(lfoFrequency[k] = new SliderPfm2("LFO"+ String(k+1) + " Frequency"));
        lfoFrequency[k]->setRange (0, 99.9f, .1f);
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
		matrixRowLabel[r]->setJustificationType(Justification::centred);

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
		matrixSource[r]->setScrollWheelEnabled(true);
        matrixSource[r]->addListener(this);

        addAndMakeVisible(matrixDestination[r] = new ComboBox("Mtx"+ String (r+1) + " Destination"));
        matrixDestination[r]->setEditableText (false);
        matrixDestination[r]->setJustificationType (Justification::centred);
        matrixDestination[r]->setColour (ComboBox::buttonColourId, Colours::blue);
        for (int i = 0; matrixDestNames[i] != nullptr; i++) {
            matrixDestination[r]->addItem(matrixDestNames[i], matrixDestIds[i] + 1);
        }
        matrixDestination[r]->setSelectedId(1);
		matrixDestination[r]->setScrollWheelEnabled(true);
        matrixDestination[r]->addListener(this);
    }

    addAndMakeVisible(enveloppeFree1 = new EnveloppeFree1 (127 ));
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

    {
        int x = 0, y = 0, width = getWidth() - 0, height = getHeight() - 0;
        Colour fillColour1 = Colour (0xff0b3e4e), fillColour2 = Colour (0xff061e26);
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setGradientFill (ColourGradient (fillColour1,
                                       static_cast<float> (proportionOfWidth (0.7622f)) - 0.0f + x,
                                       static_cast<float> (proportionOfHeight (0.4532f)) - 0.0f + y,
                                       fillColour2,
                                       static_cast<float> (proportionOfWidth (0.1590f)) - 0.0f + x,
                                       static_cast<float> (proportionOfHeight (0.8976f)) - 0.0f + y,
                                       true));
        g.fillRect (x, y, width, height);
    }

    //[UserPaint] Add your own custom painting code here..
    //[/UserPaint]
}

void PanelModulation::resized()
{
    //[UserPreResize] Add your own custom resize code here..
    //[/UserPreResize]

    matrixGroup->setBounds (proportionOfWidth (0.5977f), proportionOfHeight (0.0087f), proportionOfWidth (0.3948f), proportionOfHeight (0.9869f));
    lfoGroup->setBounds (proportionOfWidth (0.0000f), proportionOfHeight (0.0098f), proportionOfWidth (0.5901f), proportionOfHeight (0.2299f));
    env1Group->setBounds (proportionOfWidth (0.0000f), proportionOfHeight (0.2440f), proportionOfWidth (0.5901f), proportionOfHeight (0.1852f));
    env2Group->setBounds (proportionOfWidth (0.0000f), proportionOfHeight (0.4292f), proportionOfWidth (0.5901f), proportionOfHeight (0.1852f));
    stepSeqGroup->setBounds (proportionOfWidth (0.0000f), proportionOfHeight (0.6100f), proportionOfWidth (0.5901f), proportionOfHeight (0.3834f));
    //[UserResized] Add your own custom resize handling here..

	lfoPhaseLabel->setBounds(proportionOfWidth (0.48f),      proportionOfHeight (0.04f) , proportionOfWidth(0.080f), 20);
    lfoFrequencyLabel->setBounds(proportionOfWidth (0.21f),  proportionOfHeight (0.04f) , proportionOfWidth(0.080f), 20);
    lfoBiasLabel->setBounds(proportionOfWidth (0.30f),       proportionOfHeight (0.04f) , proportionOfWidth(0.080f), 20);
    lfoKSynLabel->setBounds(proportionOfWidth (0.39f),       proportionOfHeight (0.04f) , proportionOfWidth(0.080f), 20);
	for (int k=0; k<NUMBER_OF_LFO; k++) {
        lfoButton[k]      ->setBounds(2 + 60*k, proportionOfHeight (0.01f) + 9 , 60, 26);
        lfoShape[k]       ->setBounds(proportionOfWidth (0.07f),        proportionOfHeight (0.12f) , proportionOfWidth(0.08f), 20);
        lfoPhase[k]       ->setBounds(proportionOfWidth (0.48f),        proportionOfHeight (0.10f) , proportionOfWidth(0.08f), proportionOfHeight(0.1f));
        lfoExtMidiSync[k] ->setBounds(proportionOfWidth (0.21f),        proportionOfHeight (0.08f) , proportionOfWidth(0.08f), 20);
        lfoFrequency[k]   ->setBounds(proportionOfWidth (0.21f),        proportionOfHeight (0.12f) , proportionOfWidth(0.08f), proportionOfHeight(0.1f));
        lfoBias[k]        ->setBounds(proportionOfWidth (0.30f),        proportionOfHeight (0.06f) , proportionOfWidth(0.08f), proportionOfHeight (0.16f));
        lfoKsynOnOff[k]   ->setBounds(proportionOfWidth (0.39f),        proportionOfHeight (0.08f) , proportionOfWidth(0.08f), 20);
        lfoKSync[k]       ->setBounds(proportionOfWidth (0.39f),        proportionOfHeight (0.12f) , proportionOfWidth(0.08f), proportionOfHeight(0.1f));
    }

    stepSeqBPMLabel->setBounds(proportionOfWidth (0.25f),  proportionOfHeight (0.66) , 40, 20);
    stepSeqGateLabel->setBounds(proportionOfWidth (0.46f),  proportionOfHeight (0.66) , 60, 20);
    for (int k=0; k<NUMBER_OF_STEP_SEQ; k++) {
        stepSeqButton[k]->setBounds(2 + 100 * k, proportionOfHeight (0.61f) + 9, 100, 26);
        stepSequencer[k]->setBounds(proportionOfWidth (0.02f), proportionOfHeight (0.78f), proportionOfWidth (0.55f), proportionOfHeight (0.20f));
        stepSeqExtMidiSync[k] ->setBounds(proportionOfWidth (0.29f) + 10,        proportionOfHeight (0.66f) , 80, 20);
        stepSeqBPM[k]   ->setBounds(proportionOfWidth (0.27f),        proportionOfHeight (0.69f) , 80, 60);
        stepSeqGate[k]   ->setBounds(proportionOfWidth (0.46f) + 20 - proportionOfWidth(0.08),        proportionOfHeight (0.70f) , proportionOfWidth(0.16), 40);
    }

    for (int r =0; r<NUMBER_OF_MATRIX_ROW; r++) {
        matrixRowLabel[r]   ->setBounds(proportionOfWidth (0.60f)  , proportionOfHeight (.06f + .08f * r), proportionOfWidth(0.03f), 20);
        matrixSource[r]     ->setBounds(proportionOfWidth (0.63f)  , proportionOfHeight (.06f + .08f * r), proportionOfWidth(0.10f), 20);
        matrixMultipler[r]  ->setBounds(proportionOfWidth (0.74f)  , proportionOfHeight (.034f + .08f * r), proportionOfWidth(0.12f), proportionOfHeight(0.088f));
        matrixDestination[r]->setBounds(proportionOfWidth (0.86f)  , proportionOfHeight (.06f + .08f * r), proportionOfWidth(0.12f), 20);
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
    if (fromPluginUI) {
		AudioProcessorParameter * parameterReady = parameterMap[sliderThatWasMoved->getName()];
        if (parameterReady != nullptr) {
            double value = sliderThatWasMoved->getValue();
			((MidifiedFloatParameter*)parameterReady)->setRealValue(value);
        }
    }
    for (int k=0; k < NUMBER_OF_LFO; k++) {
    	if (sliderThatWasMoved == lfoFrequency[k] && lfoExtMidiSync[k]->getSelectedId() != 9990) {
    		lfoFrequency[k]->setEnabled(true);
    		lfoExtMidiSync[k]->setSelectedId(9990, dontSendNotification);
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
		AudioProcessorParameter * parameterReady = parameterMap[comboBoxThatHasChanged->getName()];
        if (parameterReady != nullptr) {
            double value = comboBoxThatHasChanged->getSelectedId();
			((MidifiedFloatParameter*)parameterReady)->setRealValue(value);
		}
    }

    for (int k = 0 ; k< NUMBER_OF_LFO; k++) {
        if (comboBoxThatHasChanged == lfoExtMidiSync[k]) {
            // Refresh Ksyn frequency on pfm2
            if (comboBoxThatHasChanged->getSelectedId() == 9990) {
                lfoFrequency[k]->setEnabled(true);
                // Force sending new value
                float value = lfoFrequency[k]->getValue();
                lfoFrequency[k]->setValue(99.9);
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
        updateComboFromParameter(matrixSource[k]);
        updateSliderFromParameter(matrixMultipler[k]);
        updateComboFromParameter(matrixDestination[k]);
    }
    for (int k = 0; k < NUMBER_OF_LFO; k++) {
        updateComboFromParameter(lfoShape[k]);
        updateComboFromParameter(lfoExtMidiSync[k]);
        updateSliderFromParameter(lfoPhase[k]);
        updateSliderFromParameter(lfoFrequency[k]);
        updateSliderFromParameter(lfoBias[k]);
        updateComboFromParameter(lfoKsynOnOff[k]);
        updateSliderFromParameter(lfoKSync[k]);
    }

    updateComboFromParameter(enveloppeFree2Loop);

    for (int k=0; k < NUMBER_OF_STEP_SEQ; k++) {
        updateStepSeqParameter(stepSequencer[k]);
        updateComboFromParameter(stepSeqExtMidiSync[k]);
        updateSliderFromParameter(stepSeqBPM[k]);
        updateSliderFromParameter(stepSeqGate[k]);
    }
	updateUIEnveloppe("#INITIALIZE#");

    // Let listen to enveloppe
    if (!initialized) {
        enveloppeFree1->addListener((EnveloppeListener*)this);
        enveloppeFree2->addListener((EnveloppeListener*)this);
    }

    initialized = true;
}


void PanelModulation::updateUIEnveloppe(String paramName) {
    const char** pointName = enveloppeFree1->getPointSuffix();
    String pString = enveloppeFree1->getName();

    for (int p=1; p < enveloppeFree1->getNumberOfPoints() ; p++) {
        String name = pString + String(pointName[p-1]);

		MidifiedFloatParameter* param = checkParamExistence(name);
		// Will remove that later but dont' BUG for the moment if that doesn't fit
		// Will remove that later but dont' BUG for the moment if that doesn't fit
		if (param == nullptr) {
			return;
		}

		if (name != String(paramName)) {
			continue;
		}

        // And let's update the value and update the UI Without sending modification !!!
        // No modification : we dont want sliderValueChanged to be called in the different panels
		
        if (p  == 3) {
            if (param->getValue() != enveloppeFree1->getY(p)) {
                enveloppeFree1->setY(p, param->getRealValue());
                enveloppeFree1->repaint();
            }
        } else {
            if (param->getValue() != enveloppeFree1->getX(p)) {
                enveloppeFree1->setX(p, param->getRealValue());
                enveloppeFree1->repaint();
            }
        }
    }

    pointName = enveloppeFree2->getPointSuffix();
    pString = enveloppeFree2->getName();

    for (int p=1; p < enveloppeFree2->getNumberOfPoints() ; p++) {
        String name = String(pString) + String(pointName[p-1]);

		MidifiedFloatParameter* param = checkParamExistence(name);

		// Will remove that later but dont' BUG for the moment if that doesn't fit
		if (param == nullptr) {
			return;
		}

		if (name != String(paramName)) {
			continue;
		}
		
		// And let's update the value and update the UI Without sending modification !!!
        // No modification : we dont want sliderValueChanged to be called in the different panels
        if (param->getValue() != enveloppeFree2->getX(p)) {
            enveloppeFree2->setX(p, param->getRealValue());
            enveloppeFree2->repaint();
        }
    }
}

void PanelModulation::updateUIStepSequencer(String paramName) {
    if (paramName.startsWith("Step Seq 1")) {
        updateStepSeqParameter(stepSequencer[0]);
    } else  {
        updateStepSeqParameter(stepSequencer[1]);
    }
}



void PanelModulation::updateSliderFromParameter_hook(Slider* slider) {
	sliderValueChanged(slider, false);
}

void PanelModulation::updateComboFromParameter_hook(ComboBox* combo) {
	comboBoxChanged(combo, false);
}

//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Projucer information section --

    This is where the Projucer stores the metadata that describe this GUI layout, so
    make changes in here at your peril!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="PanelModulation" componentName=""
                 parentClasses="public Component, public Slider::Listener, public Button::Listener, public ComboBox::Listener, public PanelOfParameters"
                 constructorParams="" variableInitialisers="" snapPixels="8" snapActive="1"
                 snapShown="1" overlayOpacity="0.330" fixedSize="0" initialWidth="900"
                 initialHeight="700">
  <BACKGROUND backgroundColour="62934">
    <RECT pos="0 0 0M 0M" fill=" radial: 76.217% 45.316%, 15.901% 89.76%, 0=ff0b3e4e, 1=ff061e26"
          hasStroke="0"/>
  </BACKGROUND>
  <GROUPCOMPONENT name="matrix group" id="f5fd2d041b369fc" memberName="matrixGroup"
                  virtualName="" explicitFocusOrder="0" pos="59.767% 0.871% 39.479% 98.693%"
                  outlinecol="ff749fad" textcol="ff749fad" title="Matrix"/>
  <GROUPCOMPONENT name="lfo group" id="25551a3d7e81232d" memberName="lfoGroup"
                  virtualName="" explicitFocusOrder="0" pos="0% 0.98% 59.013% 22.985%"
                  outlinecol="ff749fad" textcol="ff749fad" title=""/>
  <GROUPCOMPONENT name="env 1 group" id="dc02178fe3e4a3e1" memberName="env1Group"
                  virtualName="" explicitFocusOrder="0" pos="0% 24.401% 59.013% 18.519%"
                  outlinecol="ff749fad" textcol="ff749fad" title="Free Enveloppe 1"/>
  <GROUPCOMPONENT name="env 2 group" id="c35474bb62378ab6" memberName="env2Group"
                  virtualName="" explicitFocusOrder="0" pos="0% 42.919% 59.013% 18.519%"
                  outlinecol="ff749fad" textcol="ff749fad" title="Free Enveloppe 2"/>
  <GROUPCOMPONENT name="step sequencer group" id="edf809d50c7eeefc" memberName="stepSeqGroup"
                  virtualName="" explicitFocusOrder="0" pos="0% 61.002% 59.013% 38.344%"
                  outlinecol="ff749fad" textcol="ff749fad" title=""/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]
