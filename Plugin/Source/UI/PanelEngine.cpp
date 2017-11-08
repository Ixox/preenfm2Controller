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
#include "png/AlgoPNG.h"
#include "SliderPfm2.h"
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
    //[Constructor_pre] You can add your own custom stuff here..
	envToCopy = -1;
	envSelected = 0;
    //[/Constructor_pre]

    addAndMakeVisible (operatorGroup = new GroupComponent ("operator group",
                                                           String()));
    operatorGroup->setTextLabelPosition (Justification::centredLeft);
    operatorGroup->setColour (GroupComponent::outlineColourId, Colour (0xff749fad));
    operatorGroup->setColour (GroupComponent::textColourId, Colour (0xff749fad));

    addAndMakeVisible (mixerGroup = new GroupComponent ("mixer group",
                                                        TRANS("Mixer")));
    mixerGroup->setTextLabelPosition (Justification::centredLeft);
    mixerGroup->setColour (GroupComponent::outlineColourId, Colour (0xff749fad));
    mixerGroup->setColour (GroupComponent::textColourId, Colour (0xff749fad));

    addAndMakeVisible (imGroup = new GroupComponent ("IM group",
                                                     TRANS("Modulation indexes")));
    imGroup->setTextLabelPosition (Justification::centredLeft);
    imGroup->setColour (GroupComponent::outlineColourId, Colour (0xff749fad));
    imGroup->setColour (GroupComponent::textColourId, Colour (0xff749fad));


    //[UserPreSize]
    for (int k=0; k<NUMBER_OF_MIX; k++) {
        addAndMakeVisible(volumeKnob[k] = new SliderPfm2("Volume " + String(k+1)));
        volumeKnob[k]->setRange (0, 1, .01f);
        volumeKnob[k]->setSliderStyle (Slider::RotaryVerticalDrag);
        volumeKnob[k]->setTextBoxStyle (Slider::NoTextBox, false, 0, 0);
        volumeKnob[k]->setDoubleClickReturnValue(true, 1.0f);
        volumeKnob[k]->setValue(1.0f, dontSendNotification);
        volumeKnob[k]->addListener (this);

        addAndMakeVisible(panKnob[k] = new SliderPfm2("Pan " + String(k+1)));
        panKnob[k]->setRange (-1, 1, .01f);
        panKnob[k]->setSliderStyle (Slider::LinearHorizontal);
        panKnob[k]->setTextBoxStyle (Slider::NoTextBox, false, 40, 20);
        panKnob[k]->setColour(Slider::thumbColourId, Colours::blue);
        panKnob[k]->setDoubleClickReturnValue(true, 0.0f);
        panKnob[k]->addListener (this);

        addAndMakeVisible(mixLabel[k] = new Label(String("mix label ")+ String(k+1), String("Mix ")+ String(k+1)));
		mixLabel[k]->setJustificationType(Justification::centred);
    }

    for (int k=0; k<NUMBER_OF_IM; k++) {
    	addAndMakeVisible(IMNumber[k] = new Label("IM Label" + String(k+1), String("IM") + String(k+1)));


        addAndMakeVisible(IMKnob[k] = new SliderPfm2("IM " + String(k+1)));
        IMKnob[k]->setRange (0, 16, .01f);
        IMKnob[k]->setSliderStyle (Slider::RotaryVerticalDrag);
        IMKnob[k]->setTextBoxStyle (Slider::TextBoxLeft, false, 40, 16);
        IMKnob[k]->setDoubleClickReturnValue(true, 1.0f);
        IMKnob[k]->setValue(1.0f, dontSendNotification);
        IMKnob[k]->addListener (this);

        addAndMakeVisible(IMVelocityKnob[k] = new SliderPfm2("IM Velocity " + String(k+1)));
        IMVelocityKnob[k]->setRange (0, 16, .01f);
        IMVelocityKnob[k]->setSliderStyle (Slider::RotaryVerticalDrag);
        IMVelocityKnob[k]->setTextBoxStyle (Slider::TextBoxLeft, false, 40, 16);
        IMVelocityKnob[k]->setDoubleClickReturnValue(true, 0.0f);
        IMVelocityKnob[k]->setValue(0.0f, dontSendNotification);
        IMVelocityKnob[k]->addListener (this);
    }
	addAndMakeVisible(IMLabel = new Label("IM Label", "Main"));
	IMLabel->setJustificationType(Justification::centredTop);
	addAndMakeVisible(IMVelocityLabel = new Label("IM Velocity Label", "Velocity"));
	IMVelocityLabel->setJustificationType(Justification::centredTop);

	addAndMakeVisible(envCopyButton = new TextButton("Copy"));
	envCopyButton->setColour(TextButton::buttonColourId, Colour::fromRGBA(150, 150, 150, 50));
	envCopyButton->setColour(TextButton::buttonOnColourId, Colour::fromRGBA(150, 150, 150, 150));
	envCopyButton->addListener(this);
	addAndMakeVisible(envPasteButton = new TextButton("Paste"));
	envPasteButton->setColour(TextButton::buttonColourId, Colour::fromRGBA(150, 150, 150, 50));
	envPasteButton->setColour(TextButton::buttonOnColourId, Colour::fromRGBA(150, 150, 150, 150));
	envPasteButton->addListener(this);


    for (int k=0; k<NUMBER_OF_OPERATORS; k++) {
        enveloppe[k] = new Enveloppe ();
        enveloppe[k]->setName ("Op"+String(k+1)+" Env");

        enveloppeButton[k] = new TextButton ("enveloppe button");
        enveloppeButton[k]->setButtonText ("Op" + String(k+1));

        enveloppeButton[k]->setClickingTogglesState(true);
        enveloppeButton[k]->setRadioGroupId(4242);
        enveloppeButton[k]->setConnectedEdges((k!=0 ? Button::ConnectedOnLeft : 0) | (k!= NUMBER_OF_OPERATORS-1 ? Button::ConnectedOnRight : 0 ));
        enveloppeButton[k]->addListener (this);
        addAndMakeVisible(enveloppeButton[k]);

        opShape[k] = new ComboBox("Op"+String(k+1)+" Shape");
        opShape[k]->setJustificationType (Justification::centred);
        opShape[k]->setColour (ComboBox::buttonColourId, Colours::blue);
		opShape[k]->addItem("Off", 8);
		opShape[k]->addItem("Sin", 1);
        opShape[k]->addItem("Saw", 2);
        opShape[k]->addItem("Square", 3);
        opShape[k]->addItem("Sin^2", 4);
        opShape[k]->addItem("SinZero", 5);
        opShape[k]->addItem("SinPos", 6);
        opShape[k]->addItem("Rand/Noise", 7);
		opShape[k]->addItem("User 1", 9);
		opShape[k]->addItem("User 2", 10);
		opShape[k]->addItem("User 3", 11);
		opShape[k]->addItem("User 4", 12);
		opShape[k]->addItem("User 5", 13);
		opShape[k]->addItem("User 6", 14);
		opShape[k]->setSelectedId(1);
		opShape[k]->setScrollWheelEnabled(true);
		opShape[k]->setEditableText (false);
        opShape[k]->addListener (this);

        opFrequencyType[k] = new ComboBox("Op"+ String(k+1) + " Freq Type");
        opFrequencyType[k]->setEditableText (false);
        opFrequencyType[k]->setJustificationType (Justification::centred);
        opFrequencyType[k]->setColour (ComboBox::buttonColourId, Colours::blue);
        opFrequencyType[k]->addItem("Keyboard", 1);
		opFrequencyType[k]->addItem("Fine tune Hertz", 3);
		opFrequencyType[k]->addItem("Fixed", 2);
		opFrequencyType[k]->setSelectedId(1);
        opFrequencyType[k]->addListener (this);

		opFrequency[k] = new SliderPfm2Always2Decimals("Op" + String(k+1) + " Frequency");
        opFrequency[k]->setRange (0, 16, 1.0f / 12.0f);
        opFrequency[k]->setSliderStyle (Slider::RotaryVerticalDrag);
        opFrequency[k]->setTextBoxStyle (Slider::TextBoxBelow, false, 60, 16);
        opFrequency[k]->setDoubleClickReturnValue(true, 1.0f);
        opFrequency[k]->addListener (this);

        opFrequencyFineTune[k] = new SliderPfm2("Op"+ String(k+1)+ " Fine Tune");
        opFrequencyFineTune[k]->setRange (-9.0f, 9.0f, .01f);
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

    addAndMakeVisible(algoChooser = new SliderPfm2("Algo"));
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

    addAndMakeVisible(velocity = new SliderPfm2("Velocity"));
    velocity->setRange (0, 16, 1);
    velocity->setSliderStyle (Slider::RotaryVerticalDrag);
    velocity->setTextBoxStyle (Slider::TextBoxAbove, false, 30, 16);
    velocity->setDoubleClickReturnValue(true, 1.0f);
    velocity->addListener (this);

	addAndMakeVisible(velocityLabel = new Label("velocity label", "Velocity"));
	velocityLabel->setJustificationType(Justification::centredTop);

    addAndMakeVisible(velocity = new SliderPfm2("Velocity"));
    velocity->setRange (0, 16, 1);
    velocity->setValue(12, dontSendNotification);
    velocity->setSliderStyle (Slider::RotaryVerticalDrag);
    velocity->setTextBoxStyle (Slider::TextBoxAbove, false, 30, 16);
    velocity->setDoubleClickReturnValue(true, 1.0f);
    velocity->addListener (this);

	addAndMakeVisible(voicesLabel = new Label("voices label", "Voices"));
	voicesLabel->setJustificationType(Justification::centredTop);

    addAndMakeVisible(voices = new SliderPfm2("Voices"));
    voices->setRange (0, 8, 1);
    voices->setSliderStyle (Slider::RotaryVerticalDrag);
    voices->setTextBoxStyle (Slider::TextBoxAbove, false, 30, 16);
    voices->setDoubleClickReturnValue(true, 3.0f);
    voices->addListener (this);

	addAndMakeVisible(glideLabel = new Label("glide label", "Glide"));
	glideLabel->setJustificationType(Justification::centredTop);

    addAndMakeVisible(glide = new SliderPfm2("Glide"));
    glide->setRange (0, 10, 1);
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



    //[Constructor] You can add your own custom stuff here..
    eventsToAdd = nullptr;
    voices->setValue(4.0f, sendNotification);
	sliderValueChanged(voices);
	sliderValueChanged(algoChooser);
	initialized = false;
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

    g.fillAll (Colour (0xff062934));

    {
        int x = 4, y = -4, width = getWidth() - 0, height = getHeight() - 0;
        Colour fillColour1 = Colour (0xff0b3f50), fillColour2 = Colour (0xff062934);
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setGradientFill (ColourGradient (fillColour1,
                                       static_cast<float> (proportionOfWidth (0.3016f)) - 4.0f + x,
                                       static_cast<float> (proportionOfHeight (0.1220f)) - static_cast<float> (-4) + y,
                                       fillColour2,
                                       static_cast<float> (proportionOfWidth (0.0340f)) - 4.0f + x,
                                       static_cast<float> (proportionOfHeight (0.9000f)) - static_cast<float> (-4) + y,
                                       true));
        g.fillRect (x, y, width, height);
    }

    {
        float x = static_cast<float> (proportionOfWidth (0.1412f)), y = static_cast<float> (proportionOfHeight (0.0065f)), width = static_cast<float> (proportionOfWidth (0.3400f)), height = static_cast<float> (proportionOfHeight (0.3094f));
        Colour fillColour1 = Colour (0xff1ca5cf), fillColour2 = Colour (0xff0b3d4d);
        Colour strokeColour = Colours::black;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setGradientFill (ColourGradient (fillColour1,
                                       static_cast<float> (proportionOfWidth (0.2961f)) - static_cast<float> (proportionOfWidth (0.1412f)) + x,
                                       static_cast<float> (proportionOfHeight (0.0610f)) - static_cast<float> (proportionOfHeight (0.0065f)) + y,
                                       fillColour2,
                                       static_cast<float> (proportionOfWidth (0.2961f)) - static_cast<float> (proportionOfWidth (0.1412f)) + x,
                                       static_cast<float> (proportionOfHeight (0.4444f)) - static_cast<float> (proportionOfHeight (0.0065f)) + y,
                                       true));
        g.fillRoundedRectangle (x, y, width, height, 10.000f);
        g.setColour (strokeColour);
        g.drawRoundedRectangle (x, y, width, height, 10.000f, 2.500f);
    }

    //[UserPaint] Add your own custom painting code here..
    //[/UserPaint]
}

void PanelEngine::resized()
{
    //[UserPreResize] Add your own custom resize code here..
    //[/UserPreResize]

    operatorGroup->setBounds (proportionOfWidth (0.0103f), proportionOfHeight (0.5000f), proportionOfWidth (0.9801f), proportionOfHeight (0.4804f));
    mixerGroup->setBounds (proportionOfWidth (0.0117f), proportionOfHeight (0.3116f), proportionOfWidth (0.5963f), proportionOfHeight (0.1852f));
    imGroup->setBounds (proportionOfWidth (0.6121f), proportionOfHeight (0.0000f), proportionOfWidth (0.3729f), proportionOfHeight (0.4967f));
    //[UserResized] Add your own custom resize handling here..

	envCopyButton->setBounds(proportionOfWidth(0.023f), proportionOfHeight(0.645f), proportionOfWidth(0.06f), proportionOfHeight(0.03f));
	envPasteButton->setBounds(proportionOfWidth(0.09f), proportionOfHeight(0.645f), proportionOfWidth(0.06f), proportionOfHeight(0.03f));

    // OPERATORS !
    for (int k=0; k<NUMBER_OF_OPERATORS; k++) {
        enveloppe[k]->setBounds (proportionOfWidth (0.0200f), proportionOfHeight (0.67f), proportionOfWidth (0.9600f), proportionOfHeight (0.30f));
        enveloppeButton[k]->setBounds(proportionOfWidth (0.0100f) + 2 + 50*k, proportionOfHeight (0.50f) + 9, 50, 26);
	}

	opShapeLabel->setBounds(proportionOfWidth(0.4), proportionOfHeight(.53f), proportionOfWidth(0.12f), 20);
	opFrequencyTypeLabel->setBounds(proportionOfWidth(0.55f), proportionOfHeight(.53f), proportionOfWidth(0.12f), 20);
	opFrequencyLabel->setBounds(proportionOfWidth(0.7f), proportionOfHeight(.52f), proportionOfWidth(0.08f), 20);
	opFrequencyFineTuneLabel->setBounds(proportionOfWidth(0.83f), proportionOfHeight(.52f), proportionOfWidth(0.08f), 20);
	for (int k = 0; k<NUMBER_OF_OPERATORS; k++) {
		opShape[k]->setBounds(proportionOfWidth (0.4f)   ,            proportionOfHeight (.58f), proportionOfWidth(0.12f), 20);
    	opFrequencyType[k]->setBounds(    proportionOfWidth (0.55f)  , proportionOfHeight (.58f), proportionOfWidth(0.12f), 20);
    	opFrequency[k]->setBounds(        proportionOfWidth (0.70f)  , proportionOfHeight (.55f), proportionOfWidth(0.08f), proportionOfHeight(0.11f));
    	opFrequencyFineTune[k]->setBounds(proportionOfWidth (0.83f)  , proportionOfHeight (.55f), proportionOfWidth(0.08f), proportionOfHeight(0.11f));
    }

    // MIX !
	for (int k = 0; k<NUMBER_OF_MIX; k++) {
        volumeKnob[k]->setBounds(proportionOfWidth (0.09f * k + .04f)   ,proportionOfHeight (0.34f) , proportionOfWidth(0.08f), proportionOfHeight(0.08f));
        mixLabel[k]->setBounds(proportionOfWidth (0.09f * k + .04f)   ,proportionOfHeight (0.42f) , proportionOfWidth(0.08f), proportionOfHeight(0.025f));
        panKnob[k]->setBounds(proportionOfWidth (0.09f * k + .04f)   ,proportionOfHeight (0.44f) , proportionOfWidth(0.08f), proportionOfHeight(.043f));
    }

    for (int k = 0; k<NUMBER_OF_IM; k++) {
    	IMNumber[k]->setBounds(proportionOfWidth (0.63f)        , proportionOfHeight (.055f + .088f * k), proportionOfWidth(0.055f), proportionOfHeight(0.08f));
    	IMKnob[k]->setBounds(proportionOfWidth (0.69f)          , proportionOfHeight (.055f + .088f * k), proportionOfWidth(0.11f), proportionOfHeight(0.08f));
    	IMVelocityKnob[k]->setBounds(proportionOfWidth (0.84f)  , proportionOfHeight (.055f + .088f * k), proportionOfWidth(0.11f), proportionOfHeight(0.08f));
    }

    IMLabel->setBounds(proportionOfWidth (0.69f)   , proportionOfHeight (.02f), proportionOfWidth(0.11f), proportionOfHeight(0.05f));
	IMVelocityLabel->setBounds(proportionOfWidth (0.84f) , proportionOfHeight (.02f), proportionOfWidth(0.11f), proportionOfHeight(0.05f));

	algoChooser->setBounds(proportionOfWidth (0.03f)  , proportionOfHeight (.05f), proportionOfWidth(0.08f), proportionOfHeight(0.08f));
	algoChooserLabel->setBounds(proportionOfWidth (0.03f)  , proportionOfHeight (.02f), proportionOfWidth(0.08f), 40);


	voices->setBounds(proportionOfWidth (0.50f)  , proportionOfHeight (.05f), proportionOfWidth(0.08f), proportionOfHeight(0.11f));
	voicesLabel->setBounds(proportionOfWidth (0.50f)  , proportionOfHeight (.02f), proportionOfWidth(0.08f), 40);

	velocity->setBounds(proportionOfWidth(0.03f), proportionOfHeight(.20f), proportionOfWidth(0.08f), proportionOfHeight(0.11f));
	velocityLabel->setBounds(proportionOfWidth(0.03f), proportionOfHeight(.17f), proportionOfWidth(0.08f), 40);

	glide->setBounds(proportionOfWidth (0.50f)  , proportionOfHeight (.20f), proportionOfWidth(0.08f), proportionOfHeight(0.11f));
	glideLabel->setBounds(proportionOfWidth (0.50f)  , proportionOfHeight (.17f), proportionOfWidth(0.08f), 40);

	resizeAlgoDrawableImage();

    //[/UserResized]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...


void PanelEngine::resizeAlgoDrawableImage() {
	float left = proportionOfWidth (0.15f);
	float top = proportionOfHeight (0.007f);
	float width = proportionOfWidth (0.32f);
	float height = proportionOfHeight(0.31f);
	juce::Rectangle<float> rect = juce::Rectangle<float>(left, top, width, height);
	algoDrawableImage->setTransformToFit(rect, RectanglePlacement::centred | RectanglePlacement::onlyReduceInSize);

}

void PanelEngine::newAlgo(int algoNumber) {
	int numberOfMixer = algoInformation[algoNumber].mix;
	for (int m=0; m<6; m++) {
		if (m < numberOfMixer) {
			volumeKnob[m]->setEnabled(true);
			panKnob[m]->setEnabled(true);
			mixLabel[m]->setEnabled(true);
			volumeKnob[m]->setAlpha(1.0f);
			panKnob[m]->setAlpha(1.0f);
			mixLabel[m]->setAlpha(1.0f);
		} else {
			volumeKnob[m]->setEnabled(false);
			panKnob[m]->setEnabled(false);
			mixLabel[m]->setEnabled(false);
			volumeKnob[m]->setAlpha(.2f);
			panKnob[m]->setAlpha(.2f);
			mixLabel[m]->setAlpha(.2f);
		}
	}
	int numberOfIM = algoInformation[algoNumber].im;
	for (int im = 0; im < 5; im++) {
		if (im < numberOfIM) {
			IMKnob[im]->setEnabled(true);
			IMVelocityKnob[im]->setEnabled(true);
			IMNumber[im]->setEnabled(true);
			IMKnob[im]->setAlpha(1.0f);
			IMVelocityKnob[im]->setAlpha(1.0f);
			IMNumber[im]->setAlpha(1.0f);
		} else {
			IMKnob[im]->setEnabled(false);
			IMVelocityKnob[im]->setEnabled(false);
			IMNumber[im]->setEnabled(false);
			IMKnob[im]->setAlpha(0.2f);
			IMVelocityKnob[im]->setAlpha(0.2f);
			IMNumber[im]->setAlpha(0.2f);
		}
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
    sliderValueChanged(sliderThatWasMoved, true);
    //[/UsersliderValueChanged_Pre]

    //[UsersliderValueChanged_Post]
    //[/UsersliderValueChanged_Post]
}

void PanelEngine::sliderValueChanged(Slider* sliderThatWasMoved, bool fromPluginUI)
{
    // Update the value if the change comes from the UI
    if (fromPluginUI) {
		AudioProcessorParameter* parameterReady = parameterMap[sliderThatWasMoved->getName()];
        if (parameterReady != nullptr) {
            double value = sliderThatWasMoved->getValue();
			((MidifiedFloatParameter*) parameterReady)->setRealValue(value);
        }
    }
	if (sliderThatWasMoved == algoChooser) {
		newAlgo(algoChooser->getValue()-1);
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
}

void PanelEngine::comboBoxChanged (ComboBox* comboBoxThatHasChanged) {
    comboBoxChanged(comboBoxThatHasChanged, true);
}

void PanelEngine::comboBoxChanged (ComboBox* comboBoxThatHasChanged, bool fromPluginUI) {
    // Update the value if the change comes from the UI
    if (fromPluginUI) {
        AudioProcessorParameter * parameterReady = parameterMap[comboBoxThatHasChanged->getName()];
        if (parameterReady != nullptr) {
            double value = comboBoxThatHasChanged->getSelectedId();
			((MidifiedFloatParameter*)parameterReady)->setRealValue(value);
        }
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
				envSelected = k;
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

	if (buttonThatWasClicked == envPasteButton) {
		if (envToCopy >= 0) {
			for (int k = 0; k < enveloppe[envToCopy]->getNumberOfPoints(); k++) {
				enveloppe[envSelected]->setX(k, enveloppe[envToCopy]->getX(k));
				enveloppe[envSelected]->setY(k, enveloppe[envToCopy]->getY(k));
			}
			// Point 0 is not a real point. 
			for (int k = 1; k < enveloppe[envToCopy]->getNumberOfPoints(); k++) {
				enveloppe[envSelected]->notifyObservers(k, true);
				enveloppe[envSelected]->notifyObservers(k, false);
			}
			enveloppe[envSelected]->repaint();
		}
	} else if (buttonThatWasClicked == envCopyButton)  {
		envToCopy = envSelected;
		envPasteButton->setButtonText("Paste " + String(envToCopy + 1));
	}

    //[/UserbuttonClicked_Pre]


    //[UserbuttonClicked_Post]
    //[/UserbuttonClicked_Post]
}



void PanelEngine::buildParameters() {
    updateSliderFromParameter(algoChooser);
    updateSliderFromParameter(velocity);
    updateSliderFromParameter(voices);
    updateSliderFromParameter(glide);

    for (int k=0; k<NUMBER_OF_MIX; k++) {
        updateSliderFromParameter(volumeKnob[k]);
        updateSliderFromParameter(panKnob[k]);
    }
    for (int k=0; k<NUMBER_OF_IM; k++) {
        updateSliderFromParameter(IMKnob[k]);
        updateSliderFromParameter(IMVelocityKnob[k]);
    }
    for (int k=0; k<NUMBER_OF_OPERATORS; k++) {
        updateComboFromParameter(opShape[k]);
        updateComboFromParameter(opFrequencyType[k]);
        updateSliderFromParameter(opFrequency[k]);
        updateSliderFromParameter(opFrequencyFineTune[k]);
    }

	// To fill map with all points
	updateUIEnveloppe("");

    for (int k=0; k<NUMBER_OF_OPERATORS; k++) {
        // Let listen to enveloppe
        if (!initialized) {
            enveloppe[k]->addListener((EnveloppeListener*)this);
        }
    }


	/*
    for (int k=0; k<NUMBER_OF_OPERATORS; k++) {
        addComboBoxParameter(opShape[k]);
    }*/
    initialized = true;
}

void PanelEngine::updateUIEnveloppe(String paramName) {
    const char** pointName = enveloppe[0]->getPointSuffix();
    for (int k=0; k<NUMBER_OF_OPERATORS; k++) {
        String pString = enveloppe[k]->getName();

        for (int p=2; p < enveloppe[k]->getNumberOfPoints() * 2; p++) {
            String name = pString + String(pointName[p - 2]);

			MidifiedFloatParameter* param = checkParamExistence(name);
			
			if (paramName.length() > 0 && (param == nullptr || name != String(paramName))) {
				continue;
			}

            // And let's update the value and update the UI Without sending modification !!!
            // No modification : we dont want sliderValueChanged to be called in the different panels

            if ((p & 0x1) == 0) {
                if (param->getValue() != enveloppe[k]->getX(p / 2)) {
                    enveloppe[k]->setX(p / 2, param->getRealValue());
                    enveloppe[k]->repaint();

                }
            } else {
                if (param->getValue() != enveloppe[k]->getY(p / 2)) {
                    enveloppe[k]->setY(p / 2, param->getRealValue());
                    enveloppe[k]->repaint();
                }
            }
        }
    }
}

bool PanelEngine::containsThisParameterAsEnveloppe(String name) {
	return (name.startsWith("Op") && name.indexOf(" Env") == 3);
}



void PanelEngine::updateSliderFromParameter_hook(Slider* slider) {
	sliderValueChanged(slider, false);
}



//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Projucer information section --

    This is where the Projucer stores the metadata that describe this GUI layout, so
    make changes in here at your peril!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="PanelEngine" componentName=""
                 parentClasses="public Component, public Slider::Listener, public Button::Listener, public ComboBox::Listener, public PanelOfParameters"
                 constructorParams="" variableInitialisers="" snapPixels="8" snapActive="1"
                 snapShown="1" overlayOpacity="0.330" fixedSize="0" initialWidth="900"
                 initialHeight="700">
  <BACKGROUND backgroundColour="ff062934">
    <RECT pos="4 -4 0M 0M" fill=" radial: 30.158% 12.2%, 3.4% 90%, 0=ff0b3f50, 1=ff062934"
          hasStroke="0"/>
    <ROUNDRECT pos="14.119% 0.654% 34% 30.937%" cornerSize="10" fill=" radial: 29.609% 6.1%, 29.609% 44.444%, 0=ff1ca5cf, 1=ff0b3d4d"
               hasStroke="1" stroke="2.5, mitered, butt" strokeColour="solid: ff000000"/>
  </BACKGROUND>
  <GROUPCOMPONENT name="operator group" id="3a99a017e94aaaf5" memberName="operatorGroup"
                  virtualName="" explicitFocusOrder="0" pos="1.028% 50% 98.012% 48.039%"
                  outlinecol="ff749fad" textcol="ff749fad" title="" textpos="33"/>
  <GROUPCOMPONENT name="mixer group" id="a41fc3891a2af464" memberName="mixerGroup"
                  virtualName="" explicitFocusOrder="0" pos="1.165% 31.155% 59.63% 18.519%"
                  outlinecol="ff749fad" textcol="ff749fad" title="Mixer" textpos="33"/>
  <GROUPCOMPONENT name="IM group" id="249d6ec6feb3696f" memberName="imGroup" virtualName=""
                  explicitFocusOrder="0" pos="61.206% 0% 37.286% 49.673%" outlinecol="ff749fad"
                  textcol="ff749fad" title="Modulation indexes" textpos="33"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]
