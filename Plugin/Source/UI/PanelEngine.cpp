/*
  ==============================================================================

  This is an automatically generated GUI class created by the Projucer!

  Be careful when adding custom code to these files, as only the code within
  the "//[xyz]" and "//[/xyz]" sections will be retained when the file is loaded
  and re-saved.

  Created with Projucer version: 6.0.7

  ------------------------------------------------------------------------------

  The Projucer is part of the JUCE library.
  Copyright (c) 2020 - Raw Material Software Limited.

  ==============================================================================
*/

//[Headers] You can add your own extra header files here...

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

int algoOpInformation[][NUMBER_OF_OPERATORS] = {
		{1,2,2,0,0,0}, // ALGO1
		{1,1,2,0,0,0}, // ALGO2
		{1,2,2,2,0,0}, // ALGO3
		{1,1,2,2,0,0}, // ALGO4
		{1,2,2,2,0,0}, // ALGO5
		{1,1,1,2,0,0}, // ALGO6
		{1,2,1,2,1,2}, // ALGO7
		{1,2,2,2,1,2}, // ALGO8
		{1,2,2,1,2,2}, // ALGO9
		{1,2,1,2,2,2}, // ALGO10
		{1,2,2,1,2,2}, // ALGO11
		{1,2,1,2,1,2}, // ALGO12
		{1,2,1,2,2,2}, // ALGO13
		{1,2,2,1,2,2}, // ALGO14
		{1,2,1,2,2,2}, // ALGO15
		{1,2,1,2,2,2}, // ALGO16
		{1,2,2,2,2,2}, // ALGO17
		{1,2,2,2,2,2}, // ALGO18
		{1,2,2,1,1,2}, // ALGO19
		{1,1,2,1,2,2}, // ALGO20
		{1,1,2,1,1,2}, // ALGO21
		{1,2,1,1,1,2}, // ALGO22
		{1,1,1,1,1,2}, // ALGO23
		{1,2,1,2,2,1}, // ALGO24
		{1,1,1,2,1,2}, // ALGO25
		{1,1,1,2,2,1}, // ALGO26
		{1,1,1,1,1,1}, // ALGO27
		{1,1,1,1,1,2}, // ALGO28
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
	pfmType = TYPE_PREENFM2;
    //[/Constructor_pre]

    operatorGroup.reset (new juce::GroupComponent ("operator group",
                                                   juce::String()));
    addAndMakeVisible (operatorGroup.get());
    operatorGroup->setTextLabelPosition (juce::Justification::centredLeft);
    operatorGroup->setColour (juce::GroupComponent::outlineColourId, juce::Colour (0xff749fad));
    operatorGroup->setColour (juce::GroupComponent::textColourId, juce::Colour (0xff749fad));

    mixerGroup.reset (new juce::GroupComponent ("mixer group",
                                                TRANS("Mixer")));
    addAndMakeVisible (mixerGroup.get());
    mixerGroup->setTextLabelPosition (juce::Justification::centredLeft);
    mixerGroup->setColour (juce::GroupComponent::outlineColourId, juce::Colour (0xff749fad));
    mixerGroup->setColour (juce::GroupComponent::textColourId, juce::Colour (0xff749fad));

    imGroup.reset (new juce::GroupComponent ("IM group",
                                             TRANS("Modulation indexes")));
    addAndMakeVisible (imGroup.get());
    imGroup->setTextLabelPosition (juce::Justification::centredLeft);
    imGroup->setColour (juce::GroupComponent::outlineColourId, juce::Colour (0xff749fad));
    imGroup->setColour (juce::GroupComponent::textColourId, juce::Colour (0xff749fad));


    //[UserPreSize]
	for (int k = 0; k < NUMBER_OF_MIX; k++) {
		addAndMakeVisible(mixKnob[k] = new SliderPfm2("Mix " + String(k + 1)));
		mixKnob[k]->setRange(0, 1, .01f);
		mixKnob[k]->setSliderStyle(Slider::RotaryVerticalDrag);
		mixKnob[k]->setTextBoxStyle(Slider::TextBoxBelow, false, 40, 16);
		mixKnob[k]->setDoubleClickReturnValue(true, 1.0f);
		mixKnob[k]->setValue(1.0f, dontSendNotification);
		mixKnob[k]->addListener(this);

		addAndMakeVisible(panKnob[k] = new SliderPfm2("Pan " + String(k + 1)));
		panKnob[k]->setRange(-1, 1, .01f);
		panKnob[k]->setSliderStyle(Slider::LinearHorizontal);
		panKnob[k]->setTextBoxStyle(Slider::NoTextBox, false, 40, 20);
		panKnob[k]->setColour(Slider::thumbColourId, Colours::blue);
		panKnob[k]->setDoubleClickReturnValue(true, 0.0f);
		panKnob[k]->addListener(this);

		addAndMakeVisible(mixLabel[k] = new Label(String("mix label ") + String(k + 1), String("Mix ") + String(k + 1)));
		mixLabel[k]->setJustificationType(Justification::centred);
	}

	for (int k = 0; k < NUMBER_OF_IM; k++) {
		if (k < (NUMBER_OF_IM - 1)) {
			addAndMakeVisible(IMNumber[k] = new Label("IM Label" + String(k + 1), String("IM") + String(k + 1)));
		} else {
			addAndMakeVisible(IMNumber[k] = new Label("IM Label" + String(k + 1), String("Feedback")));
		}

		addAndMakeVisible(IMKnob[k] = new SliderPfm2("IM " + String(k + 1)));
		IMKnob[k]->setRange(0, k < (NUMBER_OF_IM - 1) ? 16 : 1, .01f);
		IMKnob[k]->setSliderStyle(Slider::RotaryVerticalDrag);
		IMKnob[k]->setTextBoxStyle(Slider::TextBoxLeft, false, 40, 16);
		IMKnob[k]->setDoubleClickReturnValue(true, 1.0f);
		IMKnob[k]->setValue(1.0f, dontSendNotification);
		IMKnob[k]->addListener(this);

		addAndMakeVisible(IMVelocityKnob[k] = new SliderPfm2("IM Velocity " + String(k + 1)));
		IMVelocityKnob[k]->setRange(0, k < (NUMBER_OF_IM - 1) ? 16 : 1, .01f);
		IMVelocityKnob[k]->setSliderStyle(Slider::RotaryVerticalDrag);
		IMVelocityKnob[k]->setTextBoxStyle(Slider::TextBoxLeft, false, 40, 16);
		IMVelocityKnob[k]->setDoubleClickReturnValue(true, 0.0f);
		IMVelocityKnob[k]->setValue(0.0f, dontSendNotification);
		IMVelocityKnob[k]->addListener(this);
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


	for (int k = 0; k < NUMBER_OF_OPERATORS; k++) {
		enveloppe[k] = new Enveloppe();
		enveloppe[k]->setName("Op" + String(k + 1) + " Env");

		enveloppeButton[k] = new TextButton("enveloppe button");
		enveloppeButton[k]->setButtonText("Op" + String(k + 1));

		enveloppeButton[k]->setClickingTogglesState(true);
		enveloppeButton[k]->setRadioGroupId(4242);
		enveloppeButton[k]->setConnectedEdges((k != 0 ? Button::ConnectedOnLeft : 0) | (k != NUMBER_OF_OPERATORS - 1 ? Button::ConnectedOnRight : 0));
		enveloppeButton[k]->addListener(this);
		addAndMakeVisible(enveloppeButton[k]);

		opShape[k] = new ComboBox("Op" + String(k + 1) + " Shape");
		opShape[k]->setJustificationType(Justification::centred);
		opShape[k]->setColour(ComboBox::buttonColourId, Colours::blue);
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
		opShape[k]->setEditableText(false);
		opShape[k]->addListener(this);

		opFrequencyType[k] = new ComboBox("Op" + String(k + 1) + " Freq Type");
		opFrequencyType[k]->setEditableText(false);
		opFrequencyType[k]->setJustificationType(Justification::centred);
		opFrequencyType[k]->setColour(ComboBox::buttonColourId, Colours::blue);
		opFrequencyType[k]->addItem("Keyboard", 1);
		opFrequencyType[k]->addItem("Fine tune Hertz", 3);
		opFrequencyType[k]->addItem("Fixed", 2);
		opFrequencyType[k]->setScrollWheelEnabled(true);
		opFrequencyType[k]->setSelectedId(1);
		opFrequencyType[k]->addListener(this);

		opFrequency[k] = new SliderPfm2Always2Decimals("Op" + String(k + 1) + " Frequency");
		opFrequency[k]->setRange(0, 16, 1.0f / 12.0f);
		opFrequency[k]->setSliderStyle(Slider::RotaryVerticalDrag);
		opFrequency[k]->setTextBoxStyle(Slider::TextBoxBelow, false, 60, 16);
		opFrequency[k]->setDoubleClickReturnValue(true, 1.0f);
		opFrequency[k]->addListener(this);

		opFrequencyFineTune[k] = new SliderPfm2("Op" + String(k + 1) + " Fine Tune");
		opFrequencyFineTune[k]->setRange(-9.0f, 9.0f, .01f);
		opFrequencyFineTune[k]->setSliderStyle(Slider::RotaryVerticalDrag);
		opFrequencyFineTune[k]->setTextBoxStyle(Slider::TextBoxBelow, false, 40, 16);
		opFrequencyFineTune[k]->setDoubleClickReturnValue(true, 0.0f);
		opFrequencyFineTune[k]->addListener(this);

		if (k == 0) {
			addAndMakeVisible(enveloppe[k]);
			addAndMakeVisible(opShape[k]);
			addAndMakeVisible(opFrequencyType[k]);
			addAndMakeVisible(opFrequency[k]);
			addAndMakeVisible(opFrequencyFineTune[k]);
		}
		else {
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
	algoChooser->setRange(1, NUMBER_OF_ALGO, 1);
	algoChooser->setTextBoxIsEditable(true);
	algoChooser->setSliderStyle(Slider::IncDecButtons);
	algoChooser->setTextBoxStyle(Slider::TextBoxAbove, false, 30, 16);
	algoChooser->setDoubleClickReturnValue(true, 1.0f);
	algoChooser->addListener(this);

	for (int a = 0; a < NUMBER_OF_ALGO; a++) {
		algoImages[a] = ImageFileFormat::loadFrom(algo4_pngs[a], algo4_png_sizes[a]);
	}
	addAndMakeVisible(algoDrawableImage = new DrawableImage());
	algoDrawableImage->setImage(algoImages[0]);

	addAndMakeVisible(algoChooserLabel = new Label("algo label", "Algo"));
	algoChooserLabel->setJustificationType(Justification::centredTop);

	addAndMakeVisible(velocityLabel = new Label("velocity label", "Velocity"));
	velocityLabel->setJustificationType(Justification::centredTop);

	addAndMakeVisible(velocity = new SliderPfm2("Velocity"));
	velocity->setRange(0, 16, 1);
	velocity->setSliderStyle(Slider::RotaryVerticalDrag);
	velocity->setTextBoxStyle(Slider::TextBoxAbove, false, 30, 16);
	velocity->setDoubleClickReturnValue(true, 1.0f);
	velocity->addListener(this);

	addAndMakeVisible(velocityLabel = new Label("velocity label", "Velocity"));
	velocityLabel->setJustificationType(Justification::centredTop);

	addAndMakeVisible(velocity = new SliderPfm2("Velocity"));
	velocity->setRange(0, 16, 1);
	velocity->setValue(12, dontSendNotification);
	velocity->setSliderStyle(Slider::RotaryVerticalDrag);
	velocity->setTextBoxStyle(Slider::TextBoxAbove, false, 30, 16);
	velocity->setDoubleClickReturnValue(true, 1.0f);
	velocity->addListener(this);

	addAndMakeVisible(voicesLabel = new Label("voices label", "Voices"));
	voicesLabel->setJustificationType(Justification::centredTop);

	addAndMakeVisible(voices = new SliderPfm2("Voices"));
	voices->setRange(0, 8, 1);
	voices->setSliderStyle(Slider::RotaryVerticalDrag);
	voices->setTextBoxStyle(Slider::TextBoxAbove, false, 30, 16);
	voices->setDoubleClickReturnValue(true, 3.0f);
	voices->addListener(this);

	playModePfm3 = new ComboBox("Play Mode pfm3");
	playModePfm3->setJustificationType(Justification::centred);
	playModePfm3->setColour(ComboBox::buttonColourId, Colours::blue);
	playModePfm3->addItem("Mono", 1);
	playModePfm3->addItem("Poly", 2);
	playModePfm3->addItem("Unison", 3);
	playModePfm3->setSelectedId(2);
	playModePfm3->setScrollWheelEnabled(true);
	playModePfm3->setEditableText(false);
	playModePfm3->addListener(this);
	addAndMakeVisible(playModePfm3);

	playModePfm2 = new ComboBox("Play Mode pfm2");
	playModePfm2->setJustificationType(Justification::centred);
	playModePfm2->setColour(ComboBox::buttonColourId, Colours::blue);
	playModePfm2->addItem("Poly", 1);
	playModePfm2->addItem("Unison", 2);
	playModePfm2->setSelectedId(1);
	playModePfm2->setScrollWheelEnabled(true);
	playModePfm2->setEditableText(false);
	playModePfm2->addListener(this);
	addAndMakeVisible(playModePfm2);


	addAndMakeVisible(glideLabel = new Label("glide label", "Glide"));
	glideLabel->setJustificationType(Justification::centredTop);

	addAndMakeVisible(glide = new SliderPfm2("Glide"));
	glide->setRange(0, 12, 1);
	glide->setSliderStyle(Slider::RotaryVerticalDrag);
	glide->setTextBoxStyle(Slider::TextBoxAbove, false, 30, 16);
	glide->setDoubleClickReturnValue(true, 3.0f);
	glide->setAlwaysOnTop(true);
	glide->addListener(this);

	addAndMakeVisible(glideTypeLabel = new Label("glide type label", "Glide Type"));
	glideTypeLabel->setJustificationType(Justification::centredTop);

	glideType = new ComboBox("Glide Type");
	glideType->setJustificationType(Justification::centred);
	glideType->setColour(ComboBox::buttonColourId, Colours::blue);
	glideType->addItem("Off", 1);
	glideType->addItem("Overlap", 2);
	glideType->addItem("Always", 3);
	glideType->setSelectedId(1);
	glideType->setScrollWheelEnabled(true);
	glideType->setEditableText(false);
	glideType->addListener(this);
	addAndMakeVisible(glideType);

	addAndMakeVisible(unisonSpreadLabel = new Label("unison spread label", "Spread"));
	unisonSpreadLabel->setJustificationType(Justification::centredTop);

	addAndMakeVisible(unisonSpread = new SliderPfm2("Unison Spread"));
	unisonSpread->setRange(0.0, 1.0, .01);
	unisonSpread->setSliderStyle(Slider::RotaryVerticalDrag);
	unisonSpread->setTextBoxStyle(Slider::TextBoxAbove, false, 50, 16);
	unisonSpread->setDoubleClickReturnValue(true, 3.0f);
	unisonSpread->addListener(this);

	addAndMakeVisible(unisonDetuneLabel = new Label("Unison Detune label", "Detune"));
	unisonDetuneLabel->setJustificationType(Justification::centredTop);

	addAndMakeVisible(unisonDetune = new SliderPfm2("Unison Detune"));
	unisonDetune->setRange(-1.0, 1.0, .01);
	unisonDetune->setSliderStyle(Slider::RotaryVerticalDrag);
	unisonDetune->setTextBoxStyle(Slider::TextBoxAbove, false, 50, 16);
	unisonDetune->setDoubleClickReturnValue(true, 3.0f);
	unisonDetune->addListener(this);


    //[/UserPreSize]

    setSize (900, 700);


    //[Constructor] You can add your own custom stuff here..
	eventsToAdd = nullptr;
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
void PanelEngine::paint (juce::Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..

    //[/UserPrePaint]

    {
        int x = proportionOfWidth (0.5000f), y = proportionOfHeight (0.0100f), width = proportionOfWidth (0.5000f), height = proportionOfHeight (0.6000f);
        juce::Colour fillColour1 = juce::Colour (0xff125368), fillColour2 = juce::Colour (0xff083543);
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setGradientFill (juce::ColourGradient (fillColour1,
                                             static_cast<float> (proportionOfWidth (0.8000f)) - static_cast<float> (proportionOfWidth (0.5000f)) + x,
                                             static_cast<float> (proportionOfHeight (0.0500f)) - static_cast<float> (proportionOfHeight (0.0100f)) + y,
                                             fillColour2,
                                             static_cast<float> (proportionOfWidth (0.5100f)) - static_cast<float> (proportionOfWidth (0.5000f)) + x,
                                             static_cast<float> (proportionOfHeight (0.0500f)) - static_cast<float> (proportionOfHeight (0.0100f)) + y,
                                             true));
        g.fillRect (x, y, width, height);
    }

    {
        float x = static_cast<float> (proportionOfWidth (0.1412f)), y = static_cast<float> (proportionOfHeight (0.0065f)), width = static_cast<float> (proportionOfWidth (0.2720f)), height = static_cast<float> (proportionOfHeight (0.3094f));
        juce::Colour fillColour = juce::Colour (0xff125468);
        juce::Colour strokeColour = juce::Colour (0xff749fad);
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.fillRoundedRectangle (x, y, width, height, 10.000f);
        g.setColour (strokeColour);
        g.drawRoundedRectangle (x, y, width, height, 10.000f, 1.500f);
    }

    //[UserPaint] Add your own custom painting code here..
    //[/UserPaint]
}

void PanelEngine::resized()
{
    //[UserPreResize] Add your own custom resize code here..
    //[/UserPreResize]

    operatorGroup->setBounds (proportionOfWidth (0.0103f), proportionOfHeight (0.5008f), proportionOfWidth (0.9803f), proportionOfHeight (0.4900f));
    mixerGroup->setBounds (proportionOfWidth (0.0103f), proportionOfHeight (0.3122f), proportionOfWidth (0.5906f), proportionOfHeight (0.1853f));
    imGroup->setBounds (proportionOfWidth (0.6103f), proportionOfHeight (0.0000f), proportionOfWidth (0.3794f), proportionOfHeight (0.4958f));
    //[UserResized] Add your own custom resize handling here..

	envCopyButton->setBounds(proportionOfWidth(0.023f), proportionOfHeight(0.645f), proportionOfWidth(0.06f), proportionOfHeight(0.03f));
	envPasteButton->setBounds(proportionOfWidth(0.09f), proportionOfHeight(0.645f), proportionOfWidth(0.06f), proportionOfHeight(0.03f));

	// OPERATORS !
	for (int k = 0; k < NUMBER_OF_OPERATORS; k++) {
		enveloppe[k]->setBounds(proportionOfWidth(0.0200f), proportionOfHeight(0.67f), proportionOfWidth(0.9600f), proportionOfHeight(0.30f));
		enveloppeButton[k]->setBounds(proportionOfWidth(0.0100f) + 2 + 50 * k, proportionOfHeight(0.50f) + 9, 50, 26);
	}

	opShapeLabel->setBounds(proportionOfWidth(0.4f), proportionOfHeight(.53f), proportionOfWidth(0.12f), 20);
	opFrequencyTypeLabel->setBounds(proportionOfWidth(0.55f), proportionOfHeight(.53f), proportionOfWidth(0.12f), 20);
	opFrequencyLabel->setBounds(proportionOfWidth(0.7f), proportionOfHeight(.52f), proportionOfWidth(0.08f), 20);
	opFrequencyFineTuneLabel->setBounds(proportionOfWidth(0.83f), proportionOfHeight(.52f), proportionOfWidth(0.08f), 20);
	for (int k = 0; k < NUMBER_OF_OPERATORS; k++) {
		opShape[k]->setBounds(proportionOfWidth(0.4f), proportionOfHeight(.58f), proportionOfWidth(0.12f), 20);
		opFrequencyType[k]->setBounds(proportionOfWidth(0.55f), proportionOfHeight(.58f), proportionOfWidth(0.12f), 20);
		opFrequency[k]->setBounds(proportionOfWidth(0.70f), proportionOfHeight(.55f), proportionOfWidth(0.08f), proportionOfHeight(0.11f));
		opFrequencyFineTune[k]->setBounds(proportionOfWidth(0.83f), proportionOfHeight(.55f), proportionOfWidth(0.08f), proportionOfHeight(0.11f));
	}

	// MIX !
	for (int k = 0; k < NUMBER_OF_MIX; k++) {
		mixKnob[k]->setBounds(proportionOfWidth(0.09f * k + .04f), proportionOfHeight(0.34f), proportionOfWidth(0.08f), proportionOfHeight(0.09f));
		mixLabel[k]->setBounds(proportionOfWidth(0.09f * k + .04f), proportionOfHeight(0.435f), proportionOfWidth(0.08f), proportionOfHeight(0.025f));
		panKnob[k]->setBounds(proportionOfWidth(0.09f * k + .04f), proportionOfHeight(0.45f), proportionOfWidth(0.08f), proportionOfHeight(.043f));
	}

	int numberOfIMs = pfmType == TYPE_PREENFM2 ? 5 : 6;
	float imHeight = .32f / (numberOfIMs - 1);
	float imYSpace = .352f / (numberOfIMs - 1);
	for (int k = 0; k < numberOfIMs; k++) {
		IMNumber[k]->setBounds(proportionOfWidth(0.63f), proportionOfHeight(.055f + imYSpace * k), proportionOfWidth(0.055f), proportionOfHeight(imHeight));
		IMKnob[k]->setBounds(proportionOfWidth(0.69f), proportionOfHeight(.055f + imYSpace * k), proportionOfWidth(0.11f), proportionOfHeight(imHeight));
		IMVelocityKnob[k]->setBounds(proportionOfWidth(0.84f), proportionOfHeight(.055f + imYSpace * k), proportionOfWidth(0.11f), proportionOfHeight(imHeight));
	}

	IMLabel->setBounds(proportionOfWidth(0.69f), proportionOfHeight(.02f), proportionOfWidth(0.11f), proportionOfHeight(0.05f));
	IMVelocityLabel->setBounds(proportionOfWidth(0.84f), proportionOfHeight(.02f), proportionOfWidth(0.11f), proportionOfHeight(0.05f));

	algoChooser->setBounds(proportionOfWidth(0.03f), proportionOfHeight(.05f), proportionOfWidth(0.08f), proportionOfHeight(0.08f));
	algoChooserLabel->setBounds(proportionOfWidth(0.03f), proportionOfHeight(.02f), proportionOfWidth(0.08f), 40);

	if (pfmType == TYPE_PREENFM2) {

		voicesLabel->setBounds(proportionOfWidth(0.42f), proportionOfHeight(.01f), proportionOfWidth(0.08f), proportionOfHeight(0.09f));
		voices->setBounds(proportionOfWidth(0.42f), proportionOfHeight(.01f) + 22, proportionOfWidth(0.10f), proportionOfHeight(0.09f));

		glideLabel->setText("Glide", NotificationType::dontSendNotification);
		glideLabel->setBounds(proportionOfWidth(0.51f), proportionOfHeight(.01f), proportionOfWidth(0.08f), proportionOfHeight(0.09f));
		glide->setBounds(proportionOfWidth(0.51f), proportionOfHeight(.01f) + 22, proportionOfWidth(0.10f), proportionOfHeight(0.09f));


		playModePfm2->setBounds(proportionOfWidth(0.45f), proportionOfHeight(.15f), proportionOfWidth(0.12f), 22);

		unisonSpreadLabel->setBounds(proportionOfWidth(0.42f), proportionOfHeight(.2f), proportionOfWidth(0.10f), 40);
		unisonSpread->setBounds(proportionOfWidth(0.42f), proportionOfHeight(.2f) + 22, proportionOfWidth(0.10f), proportionOfHeight(0.09f));

		unisonDetuneLabel->setBounds(proportionOfWidth(0.51f), proportionOfHeight(.2f), proportionOfWidth(0.10f), 40);
		unisonDetune->setBounds(proportionOfWidth(0.51f), proportionOfHeight(.2f) + 22, proportionOfWidth(0.10f), proportionOfHeight(0.09f));


	}
	else {
		voicesLabel->setBounds(proportionOfWidth(0.45f), proportionOfHeight(.01f), proportionOfWidth(0.12f), 22);
		playModePfm3->setBounds(proportionOfWidth(0.45f), proportionOfHeight(.01f) + 22, proportionOfWidth(0.12f), 22);

		//

		glideTypeLabel->setBounds(proportionOfWidth(0.43f), proportionOfHeight(.08f), proportionOfWidth(0.08f), 22);
		glideType->setBounds(proportionOfWidth(0.43f), proportionOfHeight(.1f) + 22, proportionOfWidth(0.08f), 22);

		glideLabel->setText("Glide Speed", NotificationType::dontSendNotification);
		glideLabel->setBounds(proportionOfWidth(0.51f), proportionOfHeight(.08f), proportionOfWidth(0.10f), 40);
		glide->setBounds(proportionOfWidth(0.51f), proportionOfHeight(.08f) + 22, proportionOfWidth(0.10f), proportionOfHeight(0.09f));


		unisonSpreadLabel->setBounds(proportionOfWidth(0.42f), proportionOfHeight(.2f), proportionOfWidth(0.10f), 40);
		unisonSpread->setBounds(proportionOfWidth(0.42f), proportionOfHeight(.2f) + 22, proportionOfWidth(0.10f), proportionOfHeight(0.09f));

		unisonDetuneLabel->setBounds(proportionOfWidth(0.51f), proportionOfHeight(.2f), proportionOfWidth(0.10f), 40);
		unisonDetune->setBounds(proportionOfWidth(0.51f), proportionOfHeight(.2f) + 22, proportionOfWidth(0.10f), proportionOfHeight(0.09f));

	}

	velocity->setBounds(proportionOfWidth(0.03f), proportionOfHeight(.20f), proportionOfWidth(0.08f), proportionOfHeight(0.11f));
	velocityLabel->setBounds(proportionOfWidth(0.03f), proportionOfHeight(.17f), proportionOfWidth(0.08f), 40);


	resizeAlgoDrawableImage();

    //[/UserResized]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...


void PanelEngine::resizeAlgoDrawableImage() {
	float left = (float)proportionOfWidth(0.12f);
	float top = (float)proportionOfHeight(0.007f);
	float width = (float)proportionOfWidth(0.32f);
	float height = (float)proportionOfHeight(0.31f);

	juce::Rectangle<float> rect = juce::Rectangle<float>(left, top, width, height);
	algoDrawableImage->setTransformToFit(rect, RectanglePlacement::centred | RectanglePlacement::onlyReduceInSize);

}

void PanelEngine::newAlgo(int algoNumber) {
	int numberOfMixer = algoInformation[algoNumber].mix;
	for (int m = 0; m < 6; m++) {
		bool enable = m < numberOfMixer;
		enableComponent(mixKnob[m].get(), enable);
		enableComponent(panKnob[m].get(), enable);
		enableComponent(mixLabel[m].get(), enable);
	}

	int numberOfIM = algoInformation[algoNumber].im;
	for (int im = 0; im < 5; im++) {
		bool enable = im < numberOfIM;
		enableComponent(IMKnob[im].get(), enable);
		enableComponent(IMVelocityKnob[im].get(), enable);
		enableComponent(IMNumber[im].get(), enable);
	}
	int numberOfOp = algoInformation[algoNumber].osc;
	for (int o = 0; o < 6; o++) {
		if (o < numberOfOp) {
			enveloppeButton[o]->setEnabled(true);
		}
		else {
			enveloppeButton[o]->setEnabled(false);
			if (enveloppeButton[o]->getToggleState()) {
				enveloppeButton[0]->setToggleState(true, sendNotification);
			}
		}
		// Only carrier operators have loop
		enveloppe[o]->setOperatorType(algoOpInformation[algoNumber][o]);
	}
	algoDrawableImage->setImage(algoImages[algoNumber]);
	resizeAlgoDrawableImage();
}

void PanelEngine::sliderValueChanged(Slider* sliderThatWasMoved)
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
			float value = (float)sliderThatWasMoved->getValue();
			((MidifiedFloatParameter*)parameterReady)->setRealValue(value);
		}
	}
	if (sliderThatWasMoved == algoChooser) {
		newAlgo((int)(algoChooser->getValue() - 1));
	} else if (sliderThatWasMoved == voices) {

		enableComponent(playModePfm2.get(), voices->getValue() > 1);

		bool unison = playModePfm2->getSelectedId() == 2;
		enableComponent(unisonSpreadLabel.get(), voices->getValue() > 1 && unison);
		enableComponent(unisonSpread.get(), voices->getValue() > 1 && unison);
		enableComponent(unisonDetuneLabel.get(), voices->getValue() > 1 && unison);
		enableComponent(unisonDetune.get(), voices->getValue() > 1 && unison);

		enableComponent(glideLabel.get(), voices->getValue() == 1 || unison);
		enableComponent(glide.get(), voices->getValue() == 1 || unison);
	}
}

void PanelEngine::comboBoxChanged(ComboBox* comboBoxThatHasChanged) {
	comboBoxChanged(comboBoxThatHasChanged, true);
}

void PanelEngine::comboBoxChanged(ComboBox* comboBoxThatHasChanged, bool fromPluginUI) {

	if (comboBoxThatHasChanged == playModePfm3) {
		bool glideEnable = playModePfm3->getSelectedId() != 2;

		enableComponent(glideTypeLabel.get(), glideEnable);
		enableComponent(glideType.get(), glideEnable);

		if (pfmType == TYPE_PREENFM3) {
			comboBoxChanged(glideType, false);
		}
		else {
			sliderValueChanged(voices, false);
		}

		bool spreadEnable = playModePfm3->getSelectedId() >= 3;

		enableComponent(unisonSpreadLabel.get(), spreadEnable);
		enableComponent(unisonSpread.get(), spreadEnable);

		enableComponent(unisonDetuneLabel.get(), spreadEnable);
		enableComponent(unisonDetune.get(), spreadEnable);

	}
	else if (comboBoxThatHasChanged == playModePfm2) {

		bool unison = playModePfm2->getSelectedId()== 2;

		enableComponent(unisonSpreadLabel.get(), unison);
		enableComponent(unisonSpread.get(), unison);

		enableComponent(unisonDetuneLabel.get(), unison);
		enableComponent(unisonDetune.get(), unison);

		enableComponent(glideLabel.get(), voices->getValue() == 1 || unison);
		enableComponent(glide.get(), voices->getValue() == 1 || unison);
	}
	else if (comboBoxThatHasChanged == glideType) {
		bool glideEnable = (glideType->getSelectedId() != 1) && (playModePfm3->getSelectedId() != 2);
		enableComponent(glideLabel.get(), glideEnable);
		enableComponent(glide.get(), glideEnable);
	}


	// Update the value if the change comes from the UI
	if (fromPluginUI) {
		AudioProcessorParameter * parameterReady = parameterMap[comboBoxThatHasChanged->getName()];
		if (parameterReady != nullptr) {
			float value = (float)comboBoxThatHasChanged->getSelectedId();
			((MidifiedFloatParameter*)parameterReady)->setRealValue(value);
		}
	}
}

void PanelEngine::buttonClicked(Button* buttonThatWasClicked)
{
	//[UserbuttonClicked_Pre]
	bool enveloppeButtonClicked = false;
	for (int k = 0; k < NUMBER_OF_OPERATORS; k++) {
		if (buttonThatWasClicked == enveloppeButton[k]) {
			enveloppeButtonClicked = true;
		}
	}
	if (enveloppeButtonClicked) {
		for (int k = 0; k < NUMBER_OF_OPERATORS; k++) {
			if (buttonThatWasClicked == enveloppeButton[k]) {
				envSelected = k;
				enveloppe[k]->setVisible(true);
				opShape[k]->setVisible(true);
				opFrequencyType[k]->setVisible(true);
				opFrequency[k]->setVisible(true);
				opFrequencyFineTune[k]->setVisible(true);
			}
			else {
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
	}
	else if (buttonThatWasClicked == envCopyButton) {
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

	// pfm3
	updateComboFromParameter(playModePfm3);
	updateComboFromParameter(glideType);
	updateSliderFromParameter(unisonDetune);
	updateSliderFromParameter(unisonSpread);

	// pfm2
	updateComboFromParameter(playModePfm2);

	for (int k = 0; k < NUMBER_OF_MIX; k++) {
		updateSliderFromParameter(mixKnob[k]);
		updateSliderFromParameter(panKnob[k]);
	}
	for (int k = 0; k < NUMBER_OF_IM; k++) {
		updateSliderFromParameter(IMKnob[k]);
		updateSliderFromParameter(IMVelocityKnob[k]);
	}
	for (int k = 0; k < NUMBER_OF_OPERATORS; k++) {
		updateComboFromParameter(opShape[k]);
		updateComboFromParameter(opFrequencyType[k]);
		updateSliderFromParameter(opFrequency[k]);
		updateSliderFromParameter(opFrequencyFineTune[k]);
	}

	// To fill map with all points
	updateUIEnveloppe("");

	for (int k = 0; k < NUMBER_OF_OPERATORS; k++) {
		// Let listen to enveloppe
		enveloppe[k]->addListener((EnveloppeListener*)this);
	}

}

void PanelEngine::updateUIEnveloppe(String paramName) {
	const char** pointName = enveloppe[0]->getPointSuffix();
	for (int k = 0; k < NUMBER_OF_OPERATORS; k++) {
		String pString = enveloppe[k]->getName();

		for (int p = 2; p < enveloppe[k]->getNumberOfPoints() * 2; p++) {
			String name = pString + String(pointName[p - 2]);

			MidifiedFloatParameter* param = checkParamExistence(name);

			if (paramName.length() > 0 && (param == nullptr || name != String(paramName))) {
				continue;
			}

			// And let's update the value and update the UI Without sending modification !!!
			// No modification : we dont want sliderValueChanged to be called in the different panels

			if ((p & 0x1) == 0) {
				if (param->getRealValue() != enveloppe[k]->getX(p / 2)) {
					enveloppe[k]->setX(p / 2, param->getRealValue());
					enveloppe[k]->repaint();

				}
			}
			else {
				if (param->getRealValue() != enveloppe[k]->getY(p / 2)) {
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


void PanelEngine::updateComboFromParameter_hook(ComboBox* combo) {
	comboBoxChanged(combo, false);
}

void PanelEngine::updateSliderFromParameter_hook(Slider* slider) {
	sliderValueChanged(slider, false);
}

void PanelEngine::sliderDragStarted(Slider* slider) {
	AudioProcessorParameter * param = parameterMap[slider->getName()];
	if (param != nullptr) {
		param->beginChangeGesture();
	}
}
void PanelEngine::sliderDragEnded(Slider* slider) {
	AudioProcessorParameter * param = parameterMap[slider->getName()];
	if (param != nullptr) {
		param->endChangeGesture();
	}
}


 void PanelEngine::setPfmType(int type) {
	pfmType = type;

	bool isPreenfm2 = pfmType == TYPE_PREENFM2;
	hideComponent(IMKnob[5].get(), isPreenfm2);
	hideComponent(IMNumber[5].get(), isPreenfm2);
	hideComponent(IMVelocityKnob[5].get(), isPreenfm2);

	hideComponent(glideTypeLabel.get(), isPreenfm2);
	hideComponent(glideType.get(), isPreenfm2);

	hideComponent(voices.get(), !isPreenfm2);

	hideComponent(playModePfm2, !isPreenfm2);
	hideComponent(playModePfm3, isPreenfm2);



	if (isPreenfm2) {
		voicesLabel->setText("Voices", NotificationType::dontSendNotification);
		sliderValueChanged(voices, false);

	} else 	{
		voicesLabel->setText("Play mode", NotificationType::dontSendNotification);
		comboBoxChanged(playModePfm3, false);
	}

	newAlgo((int)(algoChooser->getValue() - 1));
 }


 void PanelEngine::enableComponent(Component* comp, bool enable) {
	 comp->setEnabled(enable);
	 comp->setAlpha(enable ? 1.0f : 0.4f);
}

 void PanelEngine::hideComponent(Component* comp, bool enable) {
	 comp->setEnabled(!enable);
	 comp->setAlpha(enable ? 0.0f : 1.0f);
 }


//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Projucer information section --

    This is where the Projucer stores the metadata that describe this GUI layout, so
    make changes in here at your peril!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="PanelEngine" componentName=""
                 parentClasses="public Component, public Slider::Listener, public Button::Listener, public ComboBox::Listener, public PanelOfComponents"
                 constructorParams="" variableInitialisers="" snapPixels="8" snapActive="1"
                 snapShown="1" overlayOpacity="0.330" fixedSize="0" initialWidth="900"
                 initialHeight="700">
  <BACKGROUND backgroundColour="62934">
    <RECT pos="50% 1% 50% 60%" fill=" radial: 80% 5%, 51% 5%, 0=ff125368, 1=ff083543"
          hasStroke="0"/>
    <ROUNDRECT pos="14.119% 0.654% 27.2% 30.937%" cornerSize="10.0" fill="solid: ff125468"
               hasStroke="1" stroke="1.5, mitered, butt" strokeColour="solid: ff749fad"/>
  </BACKGROUND>
  <GROUPCOMPONENT name="operator group" id="3a99a017e94aaaf5" memberName="operatorGroup"
                  virtualName="" explicitFocusOrder="0" pos="1.03% 50.083% 98.026% 48.998%"
                  outlinecol="ff749fad" textcol="ff749fad" title="" textpos="33"/>
  <GROUPCOMPONENT name="mixer group" id="a41fc3891a2af464" memberName="mixerGroup"
                  virtualName="" explicitFocusOrder="0" pos="1.03% 31.219% 59.056% 18.531%"
                  outlinecol="ff749fad" textcol="ff749fad" title="Mixer" textpos="33"/>
  <GROUPCOMPONENT name="IM group" id="249d6ec6feb3696f" memberName="imGroup" virtualName=""
                  explicitFocusOrder="0" pos="61.03% 0% 37.94% 49.583%" outlinecol="ff749fad"
                  textcol="ff749fad" title="Modulation indexes" textpos="33"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]

