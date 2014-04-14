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
#include "png/AlgoPNG.h"
//[/Headers]

#include "PanelEngine.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
struct AlgoInformation  algoInformation[] = {
        { 3, 3, 1}, // ALGO1
        { 3, 2, 2}, // ALGO2
        { 4, 4, 1}, // ALGO3
        { 4, 4, 2}, // ALGO4
        { 4, 4, 1}, // ALGO5
        { 4, 3, 3}, // ALGO6
        { 6, 4, 3},  // ALGO7
        { 6, 4, 2},  // ALGO8
        { 6, 4, 2},  // ALGO9
        { 6, 4, 2},   // ALG10
        { 6, 4, 2},   // ALG11
        { 6, 3, 3},   // ALG12
        { 6, 4, 2},   // ALG13
        { 6, 4, 2},   // ALG14
        { 6, 4, 2},   // ALG15
        { 6, 4, 2},   // ALG16
        { 6, 5, 1},   // ALG17
        { 6, 5, 1},   // ALG18
        { 6, 4, 3},   // ALG19
        { 6, 4, 3},   // ALG20
        { 6, 4, 4},   // ALG21
        { 6, 4, 4},   // ALG22
        { 6, 3, 5},   // ALG23
        { 6, 3, 3},   // ALG24
        { 6, 2, 4},   // ALG25
        { 6, 2, 4},   // ALG26
        { 6, 0, 6},   // ALG27
        { 6, 1, 5},   // ALG28
};

const char* algo4_pngs[] = {
		 AlgoPNG::algo1_png, AlgoPNG::algo2_png, AlgoPNG::algo3_png, AlgoPNG::algo4_png, AlgoPNG::algo5_png, AlgoPNG::algo6_png,
		 AlgoPNG::algo7_png, AlgoPNG::algo8_png, AlgoPNG::algo9_png, AlgoPNG::algo10_png, AlgoPNG::algo11_png, AlgoPNG::algo12_png,
		 AlgoPNG::algo13_png, AlgoPNG::algo14_png, AlgoPNG::algo15_png, AlgoPNG::algo16_png, AlgoPNG::algo17_png, AlgoPNG::algo18_png,
		 AlgoPNG::algo19_png, AlgoPNG::algo20_png, AlgoPNG::algo21_png, AlgoPNG::algo22_png, AlgoPNG::algo23_png, AlgoPNG::algo24_png,
		 AlgoPNG::algo25_png, AlgoPNG::algo26_png, AlgoPNG::algo27_png, AlgoPNG::algo28_png };

const int algo4_png_sizes[] = {
		 AlgoPNG::algo1_pngSize, AlgoPNG::algo2_pngSize, AlgoPNG::algo3_pngSize, AlgoPNG::algo4_pngSize, AlgoPNG::algo5_pngSize, AlgoPNG::algo6_pngSize,
		 AlgoPNG::algo7_pngSize, AlgoPNG::algo8_pngSize, AlgoPNG::algo9_pngSize, AlgoPNG::algo10_pngSize, AlgoPNG::algo11_pngSize, AlgoPNG::algo12_pngSize,
		 AlgoPNG::algo13_pngSize, AlgoPNG::algo14_pngSize, AlgoPNG::algo15_pngSize, AlgoPNG::algo16_pngSize, AlgoPNG::algo17_pngSize, AlgoPNG::algo18_pngSize,
		 AlgoPNG::algo19_pngSize, AlgoPNG::algo20_pngSize, AlgoPNG::algo21_pngSize, AlgoPNG::algo22_pngSize, AlgoPNG::algo23_pngSize, AlgoPNG::algo24_pngSize,
		 AlgoPNG::algo25_pngSize, AlgoPNG::algo26_pngSize, AlgoPNG::algo27_pngSize, AlgoPNG::algo28_pngSize };
//[/MiscUserDefs]

//==============================================================================
PanelEngine::PanelEngine ()
{
    addAndMakeVisible (operatorGroup = new GroupComponent ("operator group",
                                                           TRANS("Operators")));
    operatorGroup->setTextLabelPosition (Justification::centredLeft);
    operatorGroup->setColour (GroupComponent::outlineColourId, Colour (0x60808080));
    operatorGroup->setColour (GroupComponent::textColourId, Colour (0xff4f4f4f));

    addAndMakeVisible (mixerGroup = new GroupComponent ("mixer group",
                                                        TRANS("Mixer")));
    mixerGroup->setTextLabelPosition (Justification::centredLeft);
    mixerGroup->setColour (GroupComponent::outlineColourId, Colour (0x60808080));
    mixerGroup->setColour (GroupComponent::textColourId, Colour (0xff4f4f4f));

    addAndMakeVisible (imGroup = new GroupComponent ("IM group",
                                                     TRANS("Modulation indexes")));
    imGroup->setTextLabelPosition (Justification::centredLeft);
    imGroup->setColour (GroupComponent::outlineColourId, Colour (0x60808080));
    imGroup->setColour (GroupComponent::textColourId, Colour (0xff4f4f4f));


    //[UserPreSize]
    for (int k=0; k<NUMBER_OF_MIX; k++) {
        addAndMakeVisible(volumeKnob[k] = new MidifiedSlider(TRANS("volume" + String(k+1)), PREENFM2_NRPN_MIX1 + 2*k, 0));
        volumeKnob[k]->setRange (0, 1, .01f);
        volumeKnob[k]->setSliderStyle (Slider::RotaryVerticalDrag);
        volumeKnob[k]->setTextBoxStyle (Slider::NoTextBox, false, 20, 20);
        volumeKnob[k]->setDoubleClickReturnValue(true, 1.0f);
        volumeKnob[k]->setValue(1.0f, dontSendNotification);
        volumeKnob[k]->addListener (this);

        addAndMakeVisible(panKnob[k] = new MidifiedSlider(TRANS("pan" + String(k+1)), PREENFM2_NRPN_PAN1 + 2*k, -1.0f));
        panKnob[k]->setRange (-1, 1, .01f);
        panKnob[k]->setSliderStyle (Slider::LinearHorizontal);
        panKnob[k]->setTextBoxStyle (Slider::NoTextBox, false, 40, 20);
        panKnob[k]->setColour(Slider::thumbColourId, Colours::blue);
        panKnob[k]->setDoubleClickReturnValue(true, 0.0f);
        panKnob[k]->addListener (this);

        addAndMakeVisible(mixLabel[k] = new Label(String("mix label ")+ String(k+1), String("Mix ")+ String(k+1)));
    }

    for (int k=0; k<NUMBER_OF_IM; k++) {
    	addAndMakeVisible(IMNumber[k] = new Label("IM Label" + String(k+1), String("IM") + String(k+1)));


        addAndMakeVisible(IMKnob[k] = new MidifiedSlider(TRANS("IM knob" + String(k+1)), PREENFM2_NRPN_IM1 + 2*k, 0));
        IMKnob[k]->setRange (0, 16, .01f);
        IMKnob[k]->setSliderStyle (Slider::RotaryVerticalDrag);
        IMKnob[k]->setTextBoxStyle (Slider::TextBoxLeft, false, 30, 16);
        IMKnob[k]->setDoubleClickReturnValue(true, 1.0f);
        IMKnob[k]->setValue(1.0f, dontSendNotification);
        IMKnob[k]->addListener (this);

        addAndMakeVisible(IMVelocityKnob[k] = new MidifiedSlider(TRANS("IM velo knob" + String(k+1)), PREENFM2_NRPN_IM1_VELOCITY + 2*k, 0));
        IMVelocityKnob[k]->setRange (0, 16, .01f);
        IMVelocityKnob[k]->setSliderStyle (Slider::RotaryVerticalDrag);
        IMVelocityKnob[k]->setTextBoxStyle (Slider::TextBoxLeft, false, 30, 16);
        IMVelocityKnob[k]->setDoubleClickReturnValue(true, 0.0f);
        IMVelocityKnob[k]->setValue(0.0f, dontSendNotification);
        IMVelocityKnob[k]->addListener (this);
    }
	addAndMakeVisible(IMLabel = new Label("IM Label", "Main"));
	IMLabel->setJustificationType(Justification::centredTop);
	addAndMakeVisible(IMVelocityLabel = new Label("IM Velocity Label", "Velocity"));
	IMVelocityLabel->setJustificationType(Justification::centredTop);

    for (int k=0; k<NUMBER_OF_OPERATORS; k++) {
        enveloppe[k] = new Enveloppe (PREENFM2_NRPN_ENV1_ATTK + 8*k);
        enveloppe[k]->setName (TRANS("enveloppe " + String(k+1)));

        enveloppeButton[k] = new TextButton ("enveloppe button");
        enveloppeButton[k]->setButtonText (TRANS("OP" + String(k+1)));

        enveloppeButton[k]->setColour (TextButton::buttonColourId, Colour (0xffa4c9e9));
        enveloppeButton[k]->setColour (TextButton::buttonOnColourId, Colours::aliceblue);

        enveloppeButton[k]->setClickingTogglesState(true);
        enveloppeButton[k]->setRadioGroupId(4242);
        enveloppeButton[k]->setConnectedEdges((k!=0 ? Button::ConnectedOnLeft : 0) | (k!= NUMBER_OF_OPERATORS-1 ? Button::ConnectedOnRight : 0 ));
        enveloppeButton[k]->addListener (this);
        addAndMakeVisible(enveloppeButton[k]);

        opShape[k] = new MidifiedComboBox(TRANS("Op shape"+ String(k)), PREENFM2_NRPN_OPERATOR1_SHAPE + 4 * k, 1, 1);
        opShape[k]->setEditableText (false);
        opShape[k]->setJustificationType (Justification::centred);
        opShape[k]->addItem("Sin", 1);
        opShape[k]->addItem("Saw", 2);
        opShape[k]->addItem("Square", 3);
        opShape[k]->addItem("Sin^2", 4);
        opShape[k]->addItem("SinZero", 5);
        opShape[k]->addItem("SinPos", 6);
        opShape[k]->addItem("Noise", 7);
        opShape[k]->addItem("Off", 8);
        opShape[k]->setSelectedId(1);
        opShape[k]->addListener (this);

        opFrequencyType[k] = new MidifiedComboBox(TRANS("Op frequency type "+ String(k)), PREENFM2_NRPN_OPERATOR1_FREQUENCY_TYPE + 4 * k, 1, 1);
        opFrequencyType[k]->setEditableText (false);
        opFrequencyType[k]->setJustificationType (Justification::centred);
        opFrequencyType[k]->addItem("Keyboard", 1);
        opFrequencyType[k]->addItem("Fixed", 2);
        opFrequencyType[k]->setSelectedId(1);
        opFrequencyType[k]->addListener (this);

        opFrequency[k] = new MidifiedSlider(TRANS("op Frequency" + String(k+1)), PREENFM2_NRPN_OPERATOR1_FREQUENCY + 4*k, 0);
        opFrequency[k]->setRange (0, 16, 1.0f / 12.0f);
        opFrequency[k]->setSliderStyle (Slider::RotaryVerticalDrag);
        opFrequency[k]->setTextBoxStyle (Slider::TextBoxBelow, false, 60, 16);
        opFrequency[k]->setDoubleClickReturnValue(true, 1.0f);
        opFrequency[k]->addListener (this);

        opFrequencyFineTune[k] = new MidifiedSlider(TRANS("op Frequency FT " + String(k+1)), PREENFM2_NRPN_OPERATOR1_FREQUENCY_FINE_TUNE + 4*k, -1);
        opFrequencyFineTune[k]->setRange (-1.0f, 1.0f, .01f);
        opFrequencyFineTune[k]->setSliderStyle (Slider::RotaryVerticalDrag);
        opFrequencyFineTune[k]->setTextBoxStyle (Slider::TextBoxBelow, false, 40, 16);
        opFrequencyFineTune[k]->setDoubleClickReturnValue(true, 0.0f);
        opFrequencyFineTune[k]->addListener (this);

        if (k == 0) {
            addAndMakeVisible(enveloppe[k]);
            addAndMakeVisible(opShape[k]);
            addAndMakeVisible(opFrequencyType[k]);
            addAndMakeVisible(opFrequency[k]);
            addAndMakeVisible(opFrequencyFineTune[k]);
        } else {
            addChildComponent(enveloppe[k]);
            addChildComponent(opShape[k]);
            addChildComponent(opFrequencyType[k]);
            addChildComponent(opFrequency[k]);
            addChildComponent(opFrequencyFineTune[k]);
        }
    }
    enveloppeButton[0]->setToggleState(true, sendNotification);

    addAndMakeVisible(opShapeLabel = new Label("op shapelabel", "Shape"));
	opShapeLabel->setJustificationType(Justification::centredTop);

    addAndMakeVisible(opFrequencyTypeLabel = new Label("op frequency type", "Follows"));
    opFrequencyTypeLabel->setJustificationType(Justification::centredTop);

    addAndMakeVisible(opFrequencyLabel = new Label("op frequency label", "Frequency"));
    opFrequencyLabel->setJustificationType(Justification::centredTop);

    addAndMakeVisible(opFrequencyFineTuneLabel = new Label("op frequency FT label", "Fine Tune"));
    opFrequencyFineTuneLabel->setJustificationType(Justification::centredTop);

    addAndMakeVisible(algoChooser = new MidifiedSlider(TRANS("Algo"), PREENFM2_NRPN_ALGO, 1, 1));
    algoChooser->setRange (1, NUMBER_OF_ALGO, 1);
    algoChooser->setTextBoxIsEditable(true);
    algoChooser->setSliderStyle (Slider::IncDecButtons);
    algoChooser->setTextBoxStyle (Slider::TextBoxAbove, false, 30, 16);
    algoChooser->setDoubleClickReturnValue(true, 1.0f);
    algoChooser->addListener (this);

    for (int a=0; a<NUMBER_OF_ALGO; a++) {
    	algoImages[a] = ImageFileFormat::loadFrom(algo4_pngs[a], algo4_png_sizes[a]);
    }
    addAndMakeVisible(algoDrawableImage = new DrawableImage());
    algoDrawableImage->setImage(algoImages[0]);

	addAndMakeVisible(algoChooserLabel = new Label("algo label", "Algo"));
	algoChooserLabel->setJustificationType(Justification::centredTop);

	addAndMakeVisible(velocityLabel = new Label("velocity label", "Velocity"));
	velocityLabel->setJustificationType(Justification::centredTop);

    addAndMakeVisible(velocity = new MidifiedSlider(TRANS("Algo"), PREENFM2_NRPN_VELOCITY, 1, 1));
    velocity->setRange (0, 16, 1);
    velocity->setSliderStyle (Slider::RotaryVerticalDrag);
    velocity->setTextBoxStyle (Slider::TextBoxAbove, false, 30, 16);
    velocity->setDoubleClickReturnValue(true, 1.0f);
    velocity->addListener (this);

	addAndMakeVisible(velocityLabel = new Label("velocity label", "Velocity"));
	velocityLabel->setJustificationType(Justification::centredTop);

    addAndMakeVisible(velocity = new MidifiedSlider(TRANS("Algo"), PREENFM2_NRPN_VELOCITY, 0, 1));
    velocity->setRange (0, 16, 1);
    velocity->setValue(12, dontSendNotification);
    velocity->setSliderStyle (Slider::RotaryVerticalDrag);
    velocity->setTextBoxStyle (Slider::TextBoxAbove, false, 30, 16);
    velocity->setDoubleClickReturnValue(true, 1.0f);
    velocity->addListener (this);

	addAndMakeVisible(voicesLabel = new Label("voices label", "Voices"));
	voicesLabel->setJustificationType(Justification::centredTop);

    addAndMakeVisible(voices = new MidifiedSlider(TRANS("Voices"), PREENFM2_NRPN_VOICE, 0, 1));
    voices->setRange (0, 8, 1);
    voices->setSliderStyle (Slider::RotaryVerticalDrag);
    voices->setTextBoxStyle (Slider::TextBoxAbove, false, 30, 16);
    voices->setDoubleClickReturnValue(true, 3.0f);
    voices->addListener (this);

	addAndMakeVisible(glideLabel = new Label("glide label", "Glide"));
	glideLabel->setJustificationType(Justification::centredTop);

    addAndMakeVisible(glide = new MidifiedSlider(TRANS("Glide"), PREENFM2_NRPN_GLIDE, 0, 1));
    glide->setRange (0, 8, 1);
    glide->setSliderStyle (Slider::RotaryVerticalDrag);
    glide->setTextBoxStyle (Slider::TextBoxAbove, false, 30, 16);
    glide->setDoubleClickReturnValue(true, 3.0f);
    glide->addListener (this);


//    addAndMakeVisible (comboBox);
//    comboBox.setBounds (10, 85, 200, 24);
//    comboBox.setEditableText (true);
//    comboBox.setJustificationType (Justification::centred);
//
//    for (int i = 1; i < 100; ++i)
//        comboBox.addItem ("combo box item " + String (i), i);
//	}
//    comboBox.setSelectedId (1);

    //[/UserPreSize]

    setSize (900, 700);


    //[Constructor] You can add your own custom stuff here..
    midiOutput = nullptr;
    voices->setValue(4.0f, sendNotification);
	sliderValueChanged(voices);
	sliderValueChanged(algoChooser);
    //[/Constructor]
}

PanelEngine::~PanelEngine()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    //[/Destructor_pre]

    operatorGroup = nullptr;
    mixerGroup = nullptr;
    imGroup = nullptr;


    //[Destructor]. You can add your own custom destruction code here..
    //[/Destructor]
}

//==============================================================================
void PanelEngine::paint (Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    g.fillAll (Colour (0xffa8c8e4));

    //[UserPaint] Add your own custom painting code here..
    //[/UserPaint]
}

void PanelEngine::resized()
{
    operatorGroup->setBounds (proportionOfWidth (0.0100f), proportionOfHeight (0.5009f), proportionOfWidth (0.9799f), proportionOfHeight (0.4805f));
    mixerGroup->setBounds (proportionOfWidth (0.0115f), proportionOfHeight (0.3117f), proportionOfWidth (0.5960f), proportionOfHeight (0.1855f));
    imGroup->setBounds (proportionOfWidth (0.6132f), proportionOfHeight (0.0000f), proportionOfWidth (0.3725f), proportionOfHeight (0.4972f));
    //[UserResized] Add your own custom resize handling here..

    // OPERATORS !
    for (int k=0; k<NUMBER_OF_OPERATORS; k++) {
        enveloppe[k]->setBounds (proportionOfWidth (0.0200f), proportionOfHeight (0.67f), proportionOfWidth (0.9600f), proportionOfHeight (0.30f));
        enveloppeButton[k]->setBounds(proportionOfWidth (0.0100f) + 10 + 50*k ,proportionOfHeight (0.50f) + 18, 50, 22);
    	opShape[k]->setBounds(proportionOfWidth (0.17f)   ,        proportionOfHeight (.61f), 80, 20);
    	opFrequencyType[k]->setBounds(    proportionOfWidth (0.47f)  , proportionOfHeight (.58f), 80, 20);
    	opFrequency[k]->setBounds(        proportionOfWidth (0.62f)  , proportionOfHeight (.56f), 80, 60);
    	opFrequencyFineTune[k]->setBounds(proportionOfWidth (0.77f)  , proportionOfHeight (.56f), 80, 60);
    }
	opShapeLabel->setBounds(proportionOfWidth (0.17)  , proportionOfHeight (.57f), 80, 20);

	opFrequencyTypeLabel->setBounds(    proportionOfWidth (0.47f)  , proportionOfHeight (.53f), 80, 20);
	opFrequencyLabel->setBounds(        proportionOfWidth (0.62f)  , proportionOfHeight (.53f), 80, 20);
	opFrequencyFineTuneLabel->setBounds(proportionOfWidth (0.77f)  , proportionOfHeight (.53f), 80, 20);

    // MIX !
	for (int k =0; k<NUMBER_OF_MIX; k++) {
        volumeKnob[k]->setBounds(proportionOfWidth (0.09f * k + .08) - 20  ,proportionOfHeight (0.35f) , 40, 40);
        mixLabel[k]->setBounds(proportionOfWidth (0.09f * k + .08) - 20  ,proportionOfHeight (0.42f) , 40, 16);
        panKnob[k]->setBounds(proportionOfWidth (0.09f * k + .08) - 40  ,proportionOfHeight (0.44f) , 80, 30);
    }

    for (int k =0; k<NUMBER_OF_IM; k++) {
    	IMNumber[k]->setBounds(proportionOfWidth (0.67f) - 20  , proportionOfHeight (.06f + .088f * k) + 10, 40, 20);
    	IMKnob[k]->setBounds(proportionOfWidth (0.77f) - 40  , proportionOfHeight (.06f + .088f * k), 80, 40);
    	IMVelocityKnob[k]->setBounds(proportionOfWidth (0.90f) - 40  , proportionOfHeight (.06f + .088f * k), 80, 40);
    }
    IMLabel->setBounds(proportionOfWidth (0.77f) - 40  , proportionOfHeight (.02f), 80, 40);
	IMVelocityLabel->setBounds(proportionOfWidth (0.90f) - 40  , proportionOfHeight (.02f), 80, 40);

	algoChooser->setBounds(proportionOfWidth (0.03f)  , proportionOfHeight (.05f), 80, 40);
	algoChooserLabel->setBounds(proportionOfWidth (0.03f)  , proportionOfHeight (.02f), 80, 40);

	velocity->setBounds(proportionOfWidth (0.03f)  , proportionOfHeight (.18f), 80, 60);
	velocityLabel->setBounds(proportionOfWidth (0.03f)  , proportionOfHeight (.15f), 80, 60);

	voices->setBounds(proportionOfWidth (0.50f)  , proportionOfHeight (.05f), 80, 60);
	voicesLabel->setBounds(proportionOfWidth (0.50f)  , proportionOfHeight (.02f), 80, 60);

	glide->setBounds(proportionOfWidth (0.50f)  , proportionOfHeight (.18f), 80, 60);
	glideLabel->setBounds(proportionOfWidth (0.50f)  , proportionOfHeight (.15f), 80, 60);

	resizeAlgoDrawableImage();

    //[/UserResized]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...
void PanelEngine::handleIncomingNrpn(int param, int value) {
	// enveloppe1->handleIncomingNrpn(param, value);
	static int index;
	switch (param) {
	case PREENFM2_NRPN_ALGO:
		algoChooser->setValue((float)value + 1, dontSendNotification);
		newAlgo(value + 1);
		break;
	case PREENFM2_NRPN_VELOCITY:
		velocity->setValue((float)value , dontSendNotification);
		break;
	case PREENFM2_NRPN_VOICE:
		voices->setValue((float)value , dontSendNotification);
		break;
	case PREENFM2_NRPN_GLIDE:
		glide->setValue((float)value , dontSendNotification);
		break;
	case PREENFM2_NRPN_IM1:
	case PREENFM2_NRPN_IM2:
	case PREENFM2_NRPN_IM3:
	case PREENFM2_NRPN_IM4:
	case PREENFM2_NRPN_IM5 :
		index = (param - PREENFM2_NRPN_IM1) / 2;
		IMKnob[index]->setValue((float)value * .01f, dontSendNotification);
		break;
	case PREENFM2_NRPN_IM1_VELOCITY:
	case PREENFM2_NRPN_IM2_VELOCITY:
	case PREENFM2_NRPN_IM3_VELOCITY:
	case PREENFM2_NRPN_IM4_VELOCITY:
	case PREENFM2_NRPN_IM5_VELOCITY:
		index = (param - PREENFM2_NRPN_IM1_VELOCITY) / 2;
		IMVelocityKnob[index]->setValue((float)value * .01f, dontSendNotification);
		break;

	case PREENFM2_NRPN_MIX1:
	case PREENFM2_NRPN_MIX2:
	case PREENFM2_NRPN_MIX3:
	case PREENFM2_NRPN_MIX4:
	case PREENFM2_NRPN_MIX5:
	case PREENFM2_NRPN_MIX6:
		index = (param - PREENFM2_NRPN_MIX1) / 2;
		volumeKnob[index]->setValue((float)value * .01f, dontSendNotification);
		break;
	case PREENFM2_NRPN_PAN1:
	case PREENFM2_NRPN_PAN2:
	case PREENFM2_NRPN_PAN3:
	case PREENFM2_NRPN_PAN4:
	case PREENFM2_NRPN_PAN5:
	case PREENFM2_NRPN_PAN6:
		index = (param - PREENFM2_NRPN_PAN1) / 2;
		panKnob[index]->setValue((float)value * .01f - 1.0f, dontSendNotification);
		break;
	case PREENFM2_NRPN_OPERATOR1_SHAPE:
	case PREENFM2_NRPN_OPERATOR2_SHAPE:
	case PREENFM2_NRPN_OPERATOR3_SHAPE:
	case PREENFM2_NRPN_OPERATOR4_SHAPE:
	case PREENFM2_NRPN_OPERATOR5_SHAPE:
	case PREENFM2_NRPN_OPERATOR6_SHAPE:
		index = (param - PREENFM2_NRPN_OPERATOR1_SHAPE) / 4;
		opShape[index]->setSelectedId(value + 1, dontSendNotification);
		break;
	case PREENFM2_NRPN_OPERATOR1_FREQUENCY_TYPE:
	case PREENFM2_NRPN_OPERATOR2_FREQUENCY_TYPE:
	case PREENFM2_NRPN_OPERATOR3_FREQUENCY_TYPE:
	case PREENFM2_NRPN_OPERATOR4_FREQUENCY_TYPE:
	case PREENFM2_NRPN_OPERATOR5_FREQUENCY_TYPE:
	case PREENFM2_NRPN_OPERATOR6_FREQUENCY_TYPE:
		index = (param - PREENFM2_NRPN_OPERATOR1_FREQUENCY_TYPE) / 4;
		opFrequencyType[index]->setSelectedId(value + 1, dontSendNotification);
		break;
	case PREENFM2_NRPN_OPERATOR1_FREQUENCY:
	case PREENFM2_NRPN_OPERATOR2_FREQUENCY:
	case PREENFM2_NRPN_OPERATOR3_FREQUENCY:
	case PREENFM2_NRPN_OPERATOR4_FREQUENCY:
	case PREENFM2_NRPN_OPERATOR5_FREQUENCY:
	case PREENFM2_NRPN_OPERATOR6_FREQUENCY:
		index = (param - PREENFM2_NRPN_OPERATOR1_FREQUENCY) / 4;
		opFrequency[index]->setValue(value * .01f, dontSendNotification);
		break;
	case PREENFM2_NRPN_OPERATOR1_FREQUENCY_FINE_TUNE:
	case PREENFM2_NRPN_OPERATOR2_FREQUENCY_FINE_TUNE:
	case PREENFM2_NRPN_OPERATOR3_FREQUENCY_FINE_TUNE:
	case PREENFM2_NRPN_OPERATOR4_FREQUENCY_FINE_TUNE:
	case PREENFM2_NRPN_OPERATOR5_FREQUENCY_FINE_TUNE:
	case PREENFM2_NRPN_OPERATOR6_FREQUENCY_FINE_TUNE:
		index = (param - PREENFM2_NRPN_OPERATOR1_FREQUENCY_FINE_TUNE) / 4;
		opFrequencyFineTune[index]->setValue(value * .01f - 1.0f, dontSendNotification);
		break;
	}
	if (param >= PREENFM2_NRPN_ENV1_ATTK && param <= PREENFM2_NRPN_ENV6_RELEASE_LEVEL) {
		int envIndex = (param - PREENFM2_NRPN_ENV1_ATTK) / 8;
		enveloppe[envIndex]->handleIncomingNrpn(param, value);
	}
}

void  PanelEngine::sendNrpn(MidiOutput* midiOutput, int param, int value) {
	if (midiOutput != nullptr) {
		midiOutput->sendMessageNow(MidiMessage::controllerEvent(1, 99, (param >> 7)));
		midiOutput->sendMessageNow(MidiMessage::controllerEvent(1, 98, (param & 0xff)));
		midiOutput->sendMessageNow(MidiMessage::controllerEvent(1, 6, (value >> 7)));
		midiOutput->sendMessageNow(MidiMessage::controllerEvent(1, 38, (value & 0xff)));
	}
}

void PanelEngine::resizeAlgoDrawableImage() {
	float left = proportionOfWidth (0.15f);
	float top = proportionOfHeight (0.007f);
	float width = proportionOfWidth (0.32f);
	float height = proportionOfHeight(0.31f);
	Rectangle<float> rect = Rectangle<float>(left, top, width, height);
	algoDrawableImage->setTransformToFit(rect, RectanglePlacement::centred | RectanglePlacement::onlyReduceInSize);
}

void PanelEngine::newAlgo(int algoNumber) {
	int numberOfMixer = algoInformation[algoNumber].mix;
	for (int m=0; m<6; m++) {
		volumeKnob[m]->setVisible(m < numberOfMixer);
		panKnob[m]->setVisible(m < numberOfMixer);
		mixLabel[m]->setEnabled(m < numberOfMixer);
	}
	int numberOfIM = algoInformation[algoNumber].im;
	for (int im = 0; im < 5; im++) {
		IMKnob[im]->setVisible(im < numberOfIM);
		IMVelocityKnob[im]->setVisible(im < numberOfIM);
		IMNumber[im]->setEnabled(im < numberOfIM);
	}
	int numberOfOp = algoInformation[algoNumber].osc;
	for (int o=0; o<6; o++) {
		if (o < numberOfOp) {
			enveloppeButton[o]->setEnabled(true);
		} else {
			enveloppeButton[o]->setEnabled(false);
			if (enveloppeButton[o]->getToggleState()) {
			    enveloppeButton[0]->setToggleState(true, sendNotification);
			}
		}
	}
	algoDrawableImage->setImage(algoImages[algoNumber]);
	resizeAlgoDrawableImage();
}

void PanelEngine::sliderValueChanged (Slider* sliderThatWasMoved)
{
    //[UsersliderValueChanged_Pre]
	MidifiedSlider* midifiedSlider = dynamic_cast<MidifiedSlider*>(sliderThatWasMoved);
	if(midifiedSlider != 0) {
	   // old was safely casted to NewType
		midifiedSlider->sendNrpn(midiOutput, midifiedSlider->getValue());
	}
	if (sliderThatWasMoved == algoChooser) {
		newAlgo((int)sliderThatWasMoved->getValue() - 1);
	}
	if (sliderThatWasMoved == voices) {
		if (voices->getValue() == 1) {
			if (!glide->isEnabled()) {
				glide->setEnabled(true);
			}
		} else {
			if (glide->isEnabled()) {
				glide->setEnabled(false);
			}
		}
	}
    //[/UsersliderValueChanged_Pre]

    //[UsersliderValueChanged_Post]
    //[/UsersliderValueChanged_Post]
}


void PanelEngine::comboBoxChanged (ComboBox* comboBoxThatHasChanged) {
	MidifiedComboBox* midifiedComboBox = dynamic_cast<MidifiedComboBox*>(comboBoxThatHasChanged);
	if(midifiedComboBox != 0) {
	   // old was safely casted to NewType
		midifiedComboBox->sendNrpn(midiOutput, midifiedComboBox->getSelectedId());
	}
}

void PanelEngine::buttonClicked (Button* buttonThatWasClicked)
{
    //[UserbuttonClicked_Pre]
    bool enveloppeButtonClicked = false;
    for (int k = 0 ; k< NUMBER_OF_OPERATORS; k++) {
        if (buttonThatWasClicked == enveloppeButton[k]) {
            enveloppeButtonClicked = true;
        }
    }
    if (enveloppeButtonClicked) {
        for (int k = 0 ; k< NUMBER_OF_OPERATORS; k++) {
            if (buttonThatWasClicked == enveloppeButton[k]) {
                enveloppe[k]->setVisible(true);
                opShape[k]->setVisible(true);
                opFrequencyType[k]->setVisible(true);
                opFrequency[k]->setVisible(true);
                opFrequencyFineTune[k]->setVisible(true);
            } else {
                enveloppe[k]->setVisible(false);
                opShape[k]->setVisible(false);
                opFrequencyType[k]->setVisible(false);
                opFrequency[k]->setVisible(false);
                opFrequencyFineTune[k]->setVisible(false);
            }
        }
    }

    //[/UserbuttonClicked_Pre]


    //[UserbuttonClicked_Post]
    //[/UserbuttonClicked_Post]
}



void PanelEngine::setMidiOutput(MidiOutput* midiOutput) {
	this->midiOutput = midiOutput;
    for (int k=0; k<NUMBER_OF_OPERATORS; k++) {
    	enveloppe[k]->setMidiOutput(midiOutput);
    }
}

//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Introjucer information section --

    This is where the Introjucer stores the metadata that describe this GUI layout, so
    make changes in here at your peril!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="PanelEngine" componentName=""
                 parentClasses="public Component, public Slider::Listener, public Button::Listener, public ComboBox::Listener"
                 constructorParams="" variableInitialisers="" snapPixels="8" snapActive="1"
                 snapShown="1" overlayOpacity="0.330" fixedSize="0" initialWidth="900"
                 initialHeight="700">
  <BACKGROUND backgroundColour="ffa8c8e4"/>
  <GROUPCOMPONENT name="operator group" id="3a99a017e94aaaf5" memberName="operatorGroup"
                  virtualName="" explicitFocusOrder="0" pos="1.003% 50.093% 97.994% 48.052%"
                  outlinecol="60808080" textcol="ff4f4f4f" title="Operators" textpos="33"/>
  <GROUPCOMPONENT name="mixer group" id="a41fc3891a2af464" memberName="mixerGroup"
                  virtualName="" explicitFocusOrder="0" pos="1.146% 31.169% 59.599% 18.553%"
                  outlinecol="60808080" textcol="ff4f4f4f" title="Mixer" textpos="33"/>
  <GROUPCOMPONENT name="IM group" id="249d6ec6feb3696f" memberName="imGroup" virtualName=""
                  explicitFocusOrder="0" pos="61.318% 0% 37.249% 49.722%" outlinecol="60808080"
                  textcol="ff4f4f4f" title="Modulation indexes" textpos="33"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]
