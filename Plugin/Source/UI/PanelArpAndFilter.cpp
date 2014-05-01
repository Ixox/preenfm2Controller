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
//[/Headers]

#include "PanelArpAndFilter.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
//[/MiscUserDefs]

//==============================================================================
PanelArpAndFilter::PanelArpAndFilter ()
{
    addAndMakeVisible (arpGroupComponent = new GroupComponent ("Arp group",
                                                               TRANS("Arpeggiator")));
    arpGroupComponent->setTextLabelPosition (Justification::centredLeft);

    addAndMakeVisible (arpOffButton = new ToggleButton ("Arp Clock"));
    arpOffButton->setButtonText (TRANS("Off"));
    arpOffButton->setRadioGroupId (5111);
    arpOffButton->addListener (this);
    arpOffButton->setToggleState (true, dontSendNotification);

    addAndMakeVisible (arpInternalButton = new ToggleButton ("Arp Clock"));
    arpInternalButton->setButtonText (TRANS("Internal clock"));
    arpInternalButton->setRadioGroupId (5111);
    arpInternalButton->addListener (this);

    addAndMakeVisible (arpExternalButton = new ToggleButton ("Arp Clock"));
    arpExternalButton->setButtonText (TRANS("External clock"));
    arpExternalButton->setRadioGroupId (5111);
    arpExternalButton->addListener (this);

    addAndMakeVisible (arpBPM = new Slider ("arp bpm slider"));
    arpBPM->setRange (10, 240, 1);
    arpBPM->setSliderStyle (Slider::RotaryVerticalDrag);
    arpBPM->setTextBoxStyle (Slider::TextBoxBelow, false, 40, 20);
    arpBPM->addListener (this);

    addAndMakeVisible (arpBPMLabel = new Label ("arp bpm label",
                                                TRANS("BPM")));
    arpBPMLabel->setFont (Font (15.00f, Font::plain));
    arpBPMLabel->setJustificationType (Justification::centredTop);
    arpBPMLabel->setEditable (false, false, false);
    arpBPMLabel->setColour (TextEditor::textColourId, Colours::black);
    arpBPMLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (arpDirectionLabel = new Label ("arp direction label",
                                                      TRANS("Direction")));
    arpDirectionLabel->setFont (Font (15.00f, Font::plain));
    arpDirectionLabel->setJustificationType (Justification::centredTop);
    arpDirectionLabel->setEditable (false, false, false);
    arpDirectionLabel->setColour (TextEditor::textColourId, Colours::black);
    arpDirectionLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (arpOctaveLabel = new Label ("arp octave label",
                                                   TRANS("Octave")));
    arpOctaveLabel->setFont (Font (15.00f, Font::plain));
    arpOctaveLabel->setJustificationType (Justification::centredTop);
    arpOctaveLabel->setEditable (false, false, false);
    arpOctaveLabel->setColour (TextEditor::textColourId, Colours::black);
    arpOctaveLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (arpPatternLabel = new Label ("arp pattern label",
                                                    TRANS("Pattern")));
    arpPatternLabel->setFont (Font (15.00f, Font::plain));
    arpPatternLabel->setJustificationType (Justification::centredTop);
    arpPatternLabel->setEditable (false, false, false);
    arpPatternLabel->setColour (TextEditor::textColourId, Colours::black);
    arpPatternLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (arpDivisionLabel = new Label ("arp division label",
                                                     TRANS("Division")));
    arpDivisionLabel->setFont (Font (15.00f, Font::plain));
    arpDivisionLabel->setJustificationType (Justification::centredTop);
    arpDivisionLabel->setEditable (false, false, false);
    arpDivisionLabel->setColour (TextEditor::textColourId, Colours::black);
    arpDivisionLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (arpDurationLabel = new Label ("arp Duration label",
                                                     TRANS("Duration")));
    arpDurationLabel->setFont (Font (15.00f, Font::plain));
    arpDurationLabel->setJustificationType (Justification::centredTop);
    arpDurationLabel->setEditable (false, false, false);
    arpDurationLabel->setColour (TextEditor::textColourId, Colours::black);
    arpDurationLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (arpLatchLabel = new Label ("arp Latch label",
                                                  TRANS("Latch")));
    arpLatchLabel->setFont (Font (15.00f, Font::plain));
    arpLatchLabel->setJustificationType (Justification::centredTop);
    arpLatchLabel->setEditable (false, false, false);
    arpLatchLabel->setColour (TextEditor::textColourId, Colours::black);
    arpLatchLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (arpDirectionCombo = new ComboBox ("arp dir combo box"));
    arpDirectionCombo->setEditableText (false);
    arpDirectionCombo->setJustificationType (Justification::centredLeft);
    arpDirectionCombo->setTextWhenNothingSelected (String::empty);
    arpDirectionCombo->setTextWhenNoChoicesAvailable (TRANS("(no choices)"));
    arpDirectionCombo->addItem (TRANS("Up"), 1);
    arpDirectionCombo->addItem (TRANS("Down"), 2);
    arpDirectionCombo->addItem (TRANS("Up & Down"), 3);
    arpDirectionCombo->addItem (TRANS("As played"), 4);
    arpDirectionCombo->addItem (TRANS("Random"), 5);
    arpDirectionCombo->addSeparator();
    arpDirectionCombo->addListener (this);

    addAndMakeVisible (arpOctavleSlider = new Slider ("arp octave slider"));
    arpOctavleSlider->setRange (1, 3, 1);
    arpOctavleSlider->setSliderStyle (Slider::RotaryVerticalDrag);
    arpOctavleSlider->setTextBoxStyle (Slider::TextBoxBelow, false, 40, 20);
    arpOctavleSlider->addListener (this);

    addAndMakeVisible (arpPatternCombo = new ComboBox ("arp pattern combo box"));
    arpPatternCombo->setEditableText (false);
    arpPatternCombo->setJustificationType (Justification::centredLeft);
    arpPatternCombo->setTextWhenNothingSelected (String::empty);
    arpPatternCombo->setTextWhenNoChoicesAvailable (TRANS("(no choices)"));
    arpPatternCombo->addItem (TRANS("1"), 1);
    arpPatternCombo->addItem (TRANS("2"), 2);
    arpPatternCombo->addItem (TRANS("3"), 3);
    arpPatternCombo->addItem (TRANS("4"), 4);
    arpPatternCombo->addItem (TRANS("5"), 5);
    arpPatternCombo->addItem (TRANS("6"), 6);
    arpPatternCombo->addItem (TRANS("7"), 7);
    arpPatternCombo->addItem (TRANS("8"), 8);
    arpPatternCombo->addItem (TRANS("9"), 9);
    arpPatternCombo->addItem (TRANS("10"), 10);
    arpPatternCombo->addItem (TRANS("11"), 11);
    arpPatternCombo->addItem (TRANS("12"), 12);
    arpPatternCombo->addItem (TRANS("13"), 13);
    arpPatternCombo->addItem (TRANS("14"), 14);
    arpPatternCombo->addItem (TRANS("15"), 15);
    arpPatternCombo->addItem (TRANS("16"), 16);
    arpPatternCombo->addItem (TRANS("17"), 17);
    arpPatternCombo->addItem (TRANS("18"), 18);
    arpPatternCombo->addItem (TRANS("19"), 19);
    arpPatternCombo->addItem (TRANS("20"), 20);
    arpPatternCombo->addItem (TRANS("21"), 21);
    arpPatternCombo->addItem (TRANS("22"), 22);
    arpPatternCombo->addItem (TRANS("User 1"), 23);
    arpPatternCombo->addItem (TRANS("User 2"), 24);
    arpPatternCombo->addItem (TRANS("User 3"), 25);
    arpPatternCombo->addItem (TRANS("User 4"), 26);
    arpPatternCombo->addSeparator();
    arpPatternCombo->addListener (this);

    addAndMakeVisible (arpDivisionCombo = new ComboBox ("arp division combo box"));
    arpDivisionCombo->setEditableText (false);
    arpDivisionCombo->setJustificationType (Justification::centredLeft);
    arpDivisionCombo->setTextWhenNothingSelected (String::empty);
    arpDivisionCombo->setTextWhenNoChoicesAvailable (TRANS("(no choices)"));
    arpDivisionCombo->addItem (TRANS("2/1"), 1);
    arpDivisionCombo->addItem (TRANS("3/2"), 2);
    arpDivisionCombo->addItem (TRANS("1/1"), 3);
    arpDivisionCombo->addItem (TRANS("3/4"), 4);
    arpDivisionCombo->addItem (TRANS("2/3"), 5);
    arpDivisionCombo->addItem (TRANS("1/2"), 6);
    arpDivisionCombo->addItem (TRANS("3/8"), 7);
    arpDivisionCombo->addItem (TRANS("1/3"), 8);
    arpDivisionCombo->addItem (TRANS("1/4"), 9);
    arpDivisionCombo->addItem (TRANS("1/6"), 10);
    arpDivisionCombo->addItem (TRANS("1/8"), 11);
    arpDivisionCombo->addItem (TRANS("1/12"), 12);
    arpDivisionCombo->addItem (TRANS("1/16"), 13);
    arpDivisionCombo->addItem (TRANS("1/24"), 14);
    arpDivisionCombo->addItem (TRANS("1/32"), 15);
    arpDivisionCombo->addItem (TRANS("1/48"), 16);
    arpDivisionCombo->addItem (TRANS("1/96"), 17);
    arpDivisionCombo->addListener (this);

    addAndMakeVisible (arpDurationCombo = new ComboBox ("arp duration combo box"));
    arpDurationCombo->setEditableText (false);
    arpDurationCombo->setJustificationType (Justification::centredLeft);
    arpDurationCombo->setTextWhenNothingSelected (String::empty);
    arpDurationCombo->setTextWhenNoChoicesAvailable (TRANS("(no choices)"));
    arpDurationCombo->addItem (TRANS("2/1"), 1);
    arpDurationCombo->addItem (TRANS("3/2"), 2);
    arpDurationCombo->addItem (TRANS("1/1"), 3);
    arpDurationCombo->addItem (TRANS("3/4"), 4);
    arpDurationCombo->addItem (TRANS("2/3"), 5);
    arpDurationCombo->addItem (TRANS("1/2"), 6);
    arpDurationCombo->addItem (TRANS("3/8"), 7);
    arpDurationCombo->addItem (TRANS("1/3"), 8);
    arpDurationCombo->addItem (TRANS("1/4"), 9);
    arpDurationCombo->addItem (TRANS("1/6"), 10);
    arpDurationCombo->addItem (TRANS("1/8"), 11);
    arpDurationCombo->addItem (TRANS("1/12"), 12);
    arpDurationCombo->addItem (TRANS("1/16"), 13);
    arpDurationCombo->addItem (TRANS("1/24"), 14);
    arpDurationCombo->addItem (TRANS("1/32"), 15);
    arpDurationCombo->addItem (TRANS("1/48"), 16);
    arpDurationCombo->addItem (TRANS("1/96"), 17);
    arpDurationCombo->addListener (this);

    addAndMakeVisible (arpLatchCombo = new ComboBox ("arp latch combo box"));
    arpLatchCombo->setEditableText (false);
    arpLatchCombo->setJustificationType (Justification::centredLeft);
    arpLatchCombo->setTextWhenNothingSelected (String::empty);
    arpLatchCombo->setTextWhenNoChoicesAvailable (TRANS("(no choices)"));
    arpLatchCombo->addItem (TRANS("Off"), 1);
    arpLatchCombo->addItem (TRANS("On"), 2);
    arpLatchCombo->addListener (this);

    addAndMakeVisible (filterGroupComponent = new GroupComponent ("Filter group",
                                                                  TRANS("Filter")));
    filterGroupComponent->setTextLabelPosition (Justification::centredLeft);

    addAndMakeVisible (filterOffButton = new ToggleButton ("filter off toggle button"));
    filterOffButton->setButtonText (TRANS("Off"));
    filterOffButton->setRadioGroupId (5112);
    filterOffButton->addListener (this);
    filterOffButton->setToggleState (true, dontSendNotification);

    addAndMakeVisible (filterMixButton = new ToggleButton ("filter mix toggle button"));
    filterMixButton->setButtonText (TRANS("Mix"));
    filterMixButton->setRadioGroupId (5112);
    filterMixButton->addListener (this);

    addAndMakeVisible (filterLPButton = new ToggleButton ("filter LP toggle button"));
    filterLPButton->setButtonText (TRANS("Low Pass"));
    filterLPButton->setRadioGroupId (5112);
    filterLPButton->addListener (this);

    addAndMakeVisible (filterHPButton = new ToggleButton ("filter HP toggle button"));
    filterHPButton->setButtonText (TRANS("High Pass"));
    filterHPButton->setRadioGroupId (5112);
    filterHPButton->addListener (this);

    addAndMakeVisible (filterBassButton = new ToggleButton ("filter Bass toggle button"));
    filterBassButton->setButtonText (TRANS("Bass"));
    filterBassButton->setRadioGroupId (5112);
    filterBassButton->addListener (this);

    addAndMakeVisible (filterParam1Label = new Label ("filter param1 label",
                                                      TRANS("Param1\n")));
    filterParam1Label->setFont (Font (15.00f, Font::plain));
    filterParam1Label->setJustificationType (Justification::centredTop);
    filterParam1Label->setEditable (false, false, false);
    filterParam1Label->setColour (TextEditor::textColourId, Colours::black);
    filterParam1Label->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (filterParam1Slider = new Slider ("filter param1 slider"));
    filterParam1Slider->setRange (0, 1, 0.01);
    filterParam1Slider->setSliderStyle (Slider::RotaryVerticalDrag);
    filterParam1Slider->setTextBoxStyle (Slider::TextBoxBelow, false, 40, 20);
    filterParam1Slider->addListener (this);

    addAndMakeVisible (filterParam2Label = new Label ("filter param2 label",
                                                      TRANS("Param2\n")));
    filterParam2Label->setFont (Font (15.00f, Font::plain));
    filterParam2Label->setJustificationType (Justification::centredTop);
    filterParam2Label->setEditable (false, false, false);
    filterParam2Label->setColour (TextEditor::textColourId, Colours::black);
    filterParam2Label->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (filterParam1Slider2 = new Slider ("filter param1 slider"));
    filterParam1Slider2->setRange (0, 1, 0.01);
    filterParam1Slider2->setSliderStyle (Slider::RotaryVerticalDrag);
    filterParam1Slider2->setTextBoxStyle (Slider::TextBoxBelow, false, 40, 20);
    filterParam1Slider2->addListener (this);

    addAndMakeVisible (filterGainLabel = new Label ("filter gain label",
                                                    TRANS("Gain")));
    filterGainLabel->setFont (Font (15.00f, Font::plain));
    filterGainLabel->setJustificationType (Justification::centredTop);
    filterGainLabel->setEditable (false, false, false);
    filterGainLabel->setColour (TextEditor::textColourId, Colours::black);
    filterGainLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (filterParam1Slider3 = new Slider ("filter param1 slider"));
    filterParam1Slider3->setRange (0, 2, 0.01);
    filterParam1Slider3->setSliderStyle (Slider::RotaryVerticalDrag);
    filterParam1Slider3->setTextBoxStyle (Slider::TextBoxBelow, false, 40, 20);
    filterParam1Slider3->addListener (this);


    //[UserPreSize]
    //[/UserPreSize]

    setSize (900, 700);


    //[Constructor] You can add your own custom stuff here..
    eventsToAdd = nullptr;

    arpDirectionCombo->setSelectedId(1);
    arpPatternCombo->setSelectedId(1);
    arpDivisionCombo->setSelectedId(1);
    arpDurationCombo->setSelectedId(1);
    arpLatchCombo->setSelectedId(1);

    arpDirectionCombo->setColour (ComboBox::buttonColourId, Colours::blue);
    arpPatternCombo->setColour (ComboBox::buttonColourId, Colours::blue);
    arpDivisionCombo->setColour (ComboBox::buttonColourId, Colours::blue);
    arpDurationCombo->setColour (ComboBox::buttonColourId, Colours::blue);
    arpLatchCombo->setColour (ComboBox::buttonColourId, Colours::blue);

    arpOffButton->setToggleState (false, dontSendNotification);
    arpOffButton->setToggleState (true, sendNotification);

    //[/Constructor]
}

PanelArpAndFilter::~PanelArpAndFilter()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    //[/Destructor_pre]

    arpGroupComponent = nullptr;
    arpOffButton = nullptr;
    arpInternalButton = nullptr;
    arpExternalButton = nullptr;
    arpBPM = nullptr;
    arpBPMLabel = nullptr;
    arpDirectionLabel = nullptr;
    arpOctaveLabel = nullptr;
    arpPatternLabel = nullptr;
    arpDivisionLabel = nullptr;
    arpDurationLabel = nullptr;
    arpLatchLabel = nullptr;
    arpDirectionCombo = nullptr;
    arpOctavleSlider = nullptr;
    arpPatternCombo = nullptr;
    arpDivisionCombo = nullptr;
    arpDurationCombo = nullptr;
    arpLatchCombo = nullptr;
    filterGroupComponent = nullptr;
    filterOffButton = nullptr;
    filterMixButton = nullptr;
    filterLPButton = nullptr;
    filterHPButton = nullptr;
    filterBassButton = nullptr;
    filterParam1Label = nullptr;
    filterParam1Slider = nullptr;
    filterParam2Label = nullptr;
    filterParam1Slider2 = nullptr;
    filterGainLabel = nullptr;
    filterParam1Slider3 = nullptr;


    //[Destructor]. You can add your own custom destruction code here..
    //[/Destructor]
}

//==============================================================================
void PanelArpAndFilter::paint (Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    g.fillAll (Colour (0xfffffade));

    //[UserPaint] Add your own custom painting code here..
    //[/UserPaint]
}

void PanelArpAndFilter::resized()
{
    arpGroupComponent->setBounds (proportionOfWidth (0.0570f), proportionOfHeight (0.0248f), proportionOfWidth (0.8741f), proportionOfHeight (0.4845f));
    arpOffButton->setBounds (proportionOfWidth (0.0950f), proportionOfHeight (0.0745f), 48, 24);
    arpInternalButton->setBounds (proportionOfWidth (0.1615f), proportionOfHeight (0.0745f), 104, 24);
    arpExternalButton->setBounds (proportionOfWidth (0.2945f), proportionOfHeight (0.0745f), 112, 24);
    arpBPM->setBounds (proportionOfWidth (0.0760f), proportionOfHeight (0.1863f), proportionOfWidth (0.0855f), proportionOfHeight (0.1118f));
    arpBPMLabel->setBounds (proportionOfWidth (0.0950f), proportionOfHeight (0.1491f), 40, 20);
    arpDirectionLabel->setBounds (proportionOfWidth (0.1900f), proportionOfHeight (0.1491f), 60, 20);
    arpOctaveLabel->setBounds (proportionOfWidth (0.3135f), proportionOfHeight (0.1491f), 60, 20);
    arpPatternLabel->setBounds (proportionOfWidth (0.4276f), proportionOfHeight (0.1491f), 60, 20);
    arpDivisionLabel->setBounds (proportionOfWidth (0.5511f), proportionOfHeight (0.1491f), 60, 20);
    arpDurationLabel->setBounds (proportionOfWidth (0.6841f), proportionOfHeight (0.1491f), 60, 20);
    arpLatchLabel->setBounds (proportionOfWidth (0.8076f), proportionOfHeight (0.1491f), 60, 20);
    arpDirectionCombo->setBounds (proportionOfWidth (0.1805f), proportionOfHeight (0.2112f), 80, 20);
    arpOctavleSlider->setBounds (proportionOfWidth (0.3040f), proportionOfHeight (0.1863f), proportionOfWidth (0.0855f), proportionOfHeight (0.1118f));
    arpPatternCombo->setBounds (proportionOfWidth (0.4276f), proportionOfHeight (0.2112f), 60, 20);
    arpDivisionCombo->setBounds (proportionOfWidth (0.5511f), proportionOfHeight (0.2112f), 60, 20);
    arpDurationCombo->setBounds (proportionOfWidth (0.6841f), proportionOfHeight (0.2112f), 60, 20);
    arpLatchCombo->setBounds (proportionOfWidth (0.8171f), proportionOfHeight (0.2112f), 52, 20);
    filterGroupComponent->setBounds (proportionOfWidth (0.2565f), proportionOfHeight (0.5590f), proportionOfWidth (0.5226f), proportionOfHeight (0.2981f));
    filterOffButton->setBounds (proportionOfWidth (0.2922f), proportionOfHeight (0.6071f), 48, 24);
    filterMixButton->setBounds (proportionOfWidth (0.3611f), proportionOfHeight (0.6087f), 48, 24);
    filterLPButton->setBounds (proportionOfWidth (0.4276f), proportionOfHeight (0.6087f), 96, 24);
    filterHPButton->setBounds (proportionOfWidth (0.5321f), proportionOfHeight (0.6087f), 96, 24);
    filterBassButton->setBounds (proportionOfWidth (0.6461f), proportionOfHeight (0.6087f), 96, 24);
    filterParam1Label->setBounds (proportionOfWidth (0.3492f), proportionOfHeight (0.6661f), 60, 20);
    filterParam1Slider->setBounds (proportionOfWidth (0.3397f), proportionOfHeight (0.7034f), proportionOfWidth (0.0855f), proportionOfHeight (0.1118f));
    filterParam2Label->setBounds (proportionOfWidth (0.4751f), proportionOfHeight (0.6661f), 60, 20);
    filterParam1Slider2->setBounds (proportionOfWidth (0.4703f), proportionOfHeight (0.7034f), proportionOfWidth (0.0855f), proportionOfHeight (0.1118f));
    filterGainLabel->setBounds (proportionOfWidth (0.6081f), proportionOfHeight (0.6661f), 60, 20);
    filterParam1Slider3->setBounds (proportionOfWidth (0.5986f), proportionOfHeight (0.7034f), proportionOfWidth (0.0855f), proportionOfHeight (0.1118f));
    //[UserResized] Add your own custom resize handling here..
    //[/UserResized]
}

void PanelArpAndFilter::buttonClicked (Button* buttonThatWasClicked)
{
    //[UserbuttonClicked_Pre]
    //[/UserbuttonClicked_Pre]

    if (buttonThatWasClicked == arpOffButton)
    {
        //[UserButtonCode_arpOffButton] -- add your button handler code here..
        arpIsNow(false, false);
        //[/UserButtonCode_arpOffButton]
    }
    else if (buttonThatWasClicked == arpInternalButton)
    {
        //[UserButtonCode_arpInternalButton] -- add your button handler code here..
        arpIsNow(true, true);
        //[/UserButtonCode_arpInternalButton]
    }
    else if (buttonThatWasClicked == arpExternalButton)
    {
        //[UserButtonCode_arpExternalButton] -- add your button handler code here..
        arpIsNow(true, false);
        //[/UserButtonCode_arpExternalButton]
    }
    else if (buttonThatWasClicked == filterOffButton)
    {
        //[UserButtonCode_filterOffButton] -- add your button handler code here..
        //[/UserButtonCode_filterOffButton]
    }
    else if (buttonThatWasClicked == filterMixButton)
    {
        //[UserButtonCode_filterMixButton] -- add your button handler code here..
        //[/UserButtonCode_filterMixButton]
    }
    else if (buttonThatWasClicked == filterLPButton)
    {
        //[UserButtonCode_filterLPButton] -- add your button handler code here..
        //[/UserButtonCode_filterLPButton]
    }
    else if (buttonThatWasClicked == filterHPButton)
    {
        //[UserButtonCode_filterHPButton] -- add your button handler code here..
        //[/UserButtonCode_filterHPButton]
    }
    else if (buttonThatWasClicked == filterBassButton)
    {
        //[UserButtonCode_filterBassButton] -- add your button handler code here..
        //[/UserButtonCode_filterBassButton]
    }

    //[UserbuttonClicked_Post]
    //[/UserbuttonClicked_Post]
}

void PanelArpAndFilter::sliderValueChanged (Slider* sliderThatWasMoved)
{
    //[UsersliderValueChanged_Pre]
    //[/UsersliderValueChanged_Pre]

    if (sliderThatWasMoved == arpBPM)
    {
        //[UserSliderCode_arpBPM] -- add your slider handling code here..
        //[/UserSliderCode_arpBPM]
    }
    else if (sliderThatWasMoved == arpOctavleSlider)
    {
        //[UserSliderCode_arpOctavleSlider] -- add your slider handling code here..
        //[/UserSliderCode_arpOctavleSlider]
    }
    else if (sliderThatWasMoved == filterParam1Slider)
    {
        //[UserSliderCode_filterParam1Slider] -- add your slider handling code here..
        //[/UserSliderCode_filterParam1Slider]
    }
    else if (sliderThatWasMoved == filterParam1Slider2)
    {
        //[UserSliderCode_filterParam1Slider2] -- add your slider handling code here..
        //[/UserSliderCode_filterParam1Slider2]
    }
    else if (sliderThatWasMoved == filterParam1Slider3)
    {
        //[UserSliderCode_filterParam1Slider3] -- add your slider handling code here..
        //[/UserSliderCode_filterParam1Slider3]
    }

    //[UsersliderValueChanged_Post]
    //[/UsersliderValueChanged_Post]
}

void PanelArpAndFilter::comboBoxChanged (ComboBox* comboBoxThatHasChanged)
{
    //[UsercomboBoxChanged_Pre]
    //[/UsercomboBoxChanged_Pre]

    if (comboBoxThatHasChanged == arpDirectionCombo)
    {
        //[UserComboBoxCode_arpDirectionCombo] -- add your combo box handling code here..
        //[/UserComboBoxCode_arpDirectionCombo]
    }
    else if (comboBoxThatHasChanged == arpPatternCombo)
    {
        //[UserComboBoxCode_arpPatternCombo] -- add your combo box handling code here..
        //[/UserComboBoxCode_arpPatternCombo]
    }
    else if (comboBoxThatHasChanged == arpDivisionCombo)
    {
        //[UserComboBoxCode_arpDivisionCombo] -- add your combo box handling code here..
        //[/UserComboBoxCode_arpDivisionCombo]
    }
    else if (comboBoxThatHasChanged == arpDurationCombo)
    {
        //[UserComboBoxCode_arpDurationCombo] -- add your combo box handling code here..
        //[/UserComboBoxCode_arpDurationCombo]
    }
    else if (comboBoxThatHasChanged == arpLatchCombo)
    {
        //[UserComboBoxCode_arpLatchCombo] -- add your combo box handling code here..
        //[/UserComboBoxCode_arpLatchCombo]
    }

    //[UsercomboBoxChanged_Post]
    //[/UsercomboBoxChanged_Post]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...

void PanelArpAndFilter::arpIsNow(bool arpOn, bool enableBPM) {
    arpBPM->setEnabled(enableBPM);
    arpBPMLabel->setEnabled(enableBPM);
    arpDirectionLabel->setEnabled(arpOn);
    arpOctaveLabel->setEnabled(arpOn);
    arpDivisionLabel->setEnabled(arpOn);
    arpDurationLabel->setEnabled(arpOn);
    arpLatchLabel->setEnabled(arpOn);
    arpDirectionCombo->setEnabled(arpOn);
    arpOctavleSlider->setEnabled(arpOn);
    arpPatternCombo->setEnabled(arpOn);
    arpDivisionCombo->setEnabled(arpOn);
    arpDurationCombo->setEnabled(arpOn);
    arpLatchCombo->setEnabled(arpOn);
}


void PanelArpAndFilter::buildParameters() {
}

void PanelArpAndFilter::onParameterUpdated(const teragon::Parameter *parameter) {
}

//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Introjucer information section --

    This is where the Introjucer stores the metadata that describe this GUI layout, so
    make changes in here at your peril!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="PanelArpAndFilter" componentName=""
                 parentClasses="public Component, public PanelOfParameters" constructorParams=""
                 variableInitialisers="" snapPixels="8" snapActive="1" snapShown="1"
                 overlayOpacity="0.330" fixedSize="0" initialWidth="900" initialHeight="700">
  <BACKGROUND backgroundColour="fffffade"/>
  <GROUPCOMPONENT name="Arp group" id="13e5d1a66afb37f8" memberName="arpGroupComponent"
                  virtualName="" explicitFocusOrder="0" pos="5.701% 2.484% 87.411% 48.447%"
                  title="Arpeggiator" textpos="33"/>
  <TOGGLEBUTTON name="arp off toggle button" id="541a7783c4a10ff6" memberName="arpOffButton"
                virtualName="MidifiedToggleButton" explicitFocusOrder="0" pos="9.501% 7.453% 48 24"
                buttonText="Off" connectedEdges="0" needsCallback="1" radioGroupId="5111"
                state="1"/>
  <TOGGLEBUTTON name="arp int toggle button" id="8aea137f0870de41" memberName="arpInternalButton"
                virtualName="MidifiedToggleButton" explicitFocusOrder="0" pos="16.152% 7.453% 104 24"
                buttonText="Internal clock" connectedEdges="0" needsCallback="1"
                radioGroupId="5111" state="0"/>
  <TOGGLEBUTTON name="arp Ext toggle button" id="536036d94e481e69" memberName="arpExternalButton"
                virtualName="MidifiedToggleButton" explicitFocusOrder="0" pos="29.454% 7.453% 112 24"
                buttonText="External clock" connectedEdges="0" needsCallback="1"
                radioGroupId="5111" state="0"/>
  <SLIDER name="arp bpm slider" id="834b58daf5daacae" memberName="arpBPM"
          virtualName="MidifiedSlider" explicitFocusOrder="0" pos="7.601% 18.634% 8.551% 11.18%"
          min="10" max="240" int="1" style="RotaryVerticalDrag" textBoxPos="TextBoxBelow"
          textBoxEditable="1" textBoxWidth="40" textBoxHeight="20" skewFactor="1"/>
  <LABEL name="arp bpm label" id="ae9087ef378fcc73" memberName="arpBPMLabel"
         virtualName="" explicitFocusOrder="0" pos="9.501% 14.907% 40 20"
         edTextCol="ff000000" edBkgCol="0" labelText="BPM" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15" bold="0" italic="0" justification="12"/>
  <LABEL name="arp direction label" id="dd08708728c535e1" memberName="arpDirectionLabel"
         virtualName="" explicitFocusOrder="0" pos="19.002% 14.907% 60 20"
         edTextCol="ff000000" edBkgCol="0" labelText="Direction" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15" bold="0" italic="0" justification="12"/>
  <LABEL name="arp octave label" id="a1efff324e6fc45a" memberName="arpOctaveLabel"
         virtualName="" explicitFocusOrder="0" pos="31.354% 14.907% 60 20"
         edTextCol="ff000000" edBkgCol="0" labelText="Octave" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15" bold="0" italic="0" justification="12"/>
  <LABEL name="arp pattern label" id="81abe99d3c3b9cb" memberName="arpPatternLabel"
         virtualName="" explicitFocusOrder="0" pos="42.755% 14.907% 60 20"
         edTextCol="ff000000" edBkgCol="0" labelText="Pattern" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15" bold="0" italic="0" justification="12"/>
  <LABEL name="arp division label" id="bc6d9b8d07143332" memberName="arpDivisionLabel"
         virtualName="" explicitFocusOrder="0" pos="55.107% 14.907% 60 20"
         edTextCol="ff000000" edBkgCol="0" labelText="Division" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15" bold="0" italic="0" justification="12"/>
  <LABEL name="arp Duration label" id="6e39565df396e160" memberName="arpDurationLabel"
         virtualName="" explicitFocusOrder="0" pos="68.409% 14.907% 60 20"
         edTextCol="ff000000" edBkgCol="0" labelText="Duration" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15" bold="0" italic="0" justification="12"/>
  <LABEL name="arp Latch label" id="4bba356716a40a00" memberName="arpLatchLabel"
         virtualName="" explicitFocusOrder="0" pos="80.76% 14.907% 60 20"
         edTextCol="ff000000" edBkgCol="0" labelText="Latch" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15" bold="0" italic="0" justification="12"/>
  <COMBOBOX name="arp dir combo box" id="5403f05ff830eb2e" memberName="arpDirectionCombo"
            virtualName="MidifiedComboBox" explicitFocusOrder="0" pos="18.052% 21.118% 80 20"
            editable="0" layout="33" items="Up&#10;Down&#10;Up &amp; Down&#10;As played&#10;Random&#10;"
            textWhenNonSelected="" textWhenNoItems="(no choices)"/>
  <SLIDER name="arp octave slider" id="1cb995267258f0bb" memberName="arpOctavleSlider"
          virtualName="MidifiedSlider" explicitFocusOrder="0" pos="30.404% 18.634% 8.551% 11.18%"
          min="1" max="3" int="1" style="RotaryVerticalDrag" textBoxPos="TextBoxBelow"
          textBoxEditable="1" textBoxWidth="40" textBoxHeight="20" skewFactor="1"/>
  <COMBOBOX name="arp pattern combo box" id="4ab8dec3ec103766" memberName="arpPatternCombo"
            virtualName="MidifiedComboBox" explicitFocusOrder="0" pos="42.755% 21.118% 60 20"
            editable="0" layout="33" items="1&#10;2&#10;3&#10;4&#10;5&#10;6&#10;7&#10;8&#10;9&#10;10&#10;11&#10;12&#10;13&#10;14&#10;15&#10;16&#10;17&#10;18&#10;19&#10;20&#10;21&#10;22&#10;User 1&#10;User 2&#10;User 3&#10;User 4&#10;"
            textWhenNonSelected="" textWhenNoItems="(no choices)"/>
  <COMBOBOX name="arp division combo box" id="40d9cbf865d21a6d" memberName="arpDivisionCombo"
            virtualName="MidifiedComboBox" explicitFocusOrder="0" pos="55.107% 21.118% 60 20"
            editable="0" layout="33" items="2/1&#10;3/2&#10;1/1&#10;3/4&#10;2/3&#10;1/2&#10;3/8&#10;1/3&#10;1/4&#10;1/6&#10;1/8&#10;1/12&#10;1/16&#10;1/24&#10;1/32&#10;1/48&#10;1/96"
            textWhenNonSelected="" textWhenNoItems="(no choices)"/>
  <COMBOBOX name="arp duration combo box" id="40f06b2b6126c25d" memberName="arpDurationCombo"
            virtualName="MidifiedComboBox" explicitFocusOrder="0" pos="68.409% 21.118% 60 20"
            editable="0" layout="33" items="2/1&#10;3/2&#10;1/1&#10;3/4&#10;2/3&#10;1/2&#10;3/8&#10;1/3&#10;1/4&#10;1/6&#10;1/8&#10;1/12&#10;1/16&#10;1/24&#10;1/32&#10;1/48&#10;1/96"
            textWhenNonSelected="" textWhenNoItems="(no choices)"/>
  <COMBOBOX name="arp latch combo box" id="3072fb2928d8c8f4" memberName="arpLatchCombo"
            virtualName="MidifiedComboBox" explicitFocusOrder="0" pos="81.71% 21.118% 52 20"
            editable="0" layout="33" items="Off&#10;On" textWhenNonSelected=""
            textWhenNoItems="(no choices)"/>
  <GROUPCOMPONENT name="Filter group" id="ef53faceed268e04" memberName="filterGroupComponent"
                  virtualName="" explicitFocusOrder="0" pos="25.653% 55.901% 52.257% 29.814%"
                  title="Filter" textpos="33"/>
  <TOGGLEBUTTON name="filter off toggle button" id="f555890481d0a1f" memberName="filterOffButton"
                virtualName="MidifiedToggleButton" explicitFocusOrder="0" pos="29.216% 60.714% 48 24"
                buttonText="Off" connectedEdges="0" needsCallback="1" radioGroupId="5112"
                state="1"/>
  <TOGGLEBUTTON name="filter mix toggle button" id="172947188d32c0f8" memberName="filterMixButton"
                virtualName="MidifiedToggleButton" explicitFocusOrder="0" pos="36.105% 60.87% 48 24"
                buttonText="Mix" connectedEdges="0" needsCallback="1" radioGroupId="5112"
                state="0"/>
  <TOGGLEBUTTON name="filter LP toggle button" id="ec6deacb84b7389b" memberName="filterLPButton"
                virtualName="MidifiedToggleButton" explicitFocusOrder="0" pos="42.755% 60.87% 96 24"
                buttonText="Low Pass" connectedEdges="0" needsCallback="1" radioGroupId="5112"
                state="0"/>
  <TOGGLEBUTTON name="filter HP toggle button" id="541432d4f0649caf" memberName="filterHPButton"
                virtualName="MidifiedToggleButton" explicitFocusOrder="0" pos="53.207% 60.87% 96 24"
                buttonText="High Pass" connectedEdges="0" needsCallback="1" radioGroupId="5112"
                state="0"/>
  <TOGGLEBUTTON name="filter Bass toggle button" id="845c86de86519034" memberName="filterBassButton"
                virtualName="MidifiedToggleButton" explicitFocusOrder="0" pos="64.608% 60.87% 96 24"
                buttonText="Bass" connectedEdges="0" needsCallback="1" radioGroupId="5112"
                state="0"/>
  <LABEL name="filter param1 label" id="ad964c1a500045d4" memberName="filterParam1Label"
         virtualName="" explicitFocusOrder="0" pos="34.917% 66.615% 60 20"
         edTextCol="ff000000" edBkgCol="0" labelText="Param1&#10;" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15" bold="0" italic="0" justification="12"/>
  <SLIDER name="filter param1 slider" id="c05a5ec6435b8dba" memberName="filterParam1Slider"
          virtualName="MidifiedSlider" explicitFocusOrder="0" pos="33.967% 70.342% 8.551% 11.18%"
          min="0" max="1" int="0.010000000000000000208" style="RotaryVerticalDrag"
          textBoxPos="TextBoxBelow" textBoxEditable="1" textBoxWidth="40"
          textBoxHeight="20" skewFactor="1"/>
  <LABEL name="filter param2 label" id="8e05a7e79e0d078c" memberName="filterParam2Label"
         virtualName="" explicitFocusOrder="0" pos="47.506% 66.615% 60 20"
         edTextCol="ff000000" edBkgCol="0" labelText="Param2&#10;" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15" bold="0" italic="0" justification="12"/>
  <SLIDER name="filter param1 slider" id="d542ada05f27098e" memberName="filterParam1Slider2"
          virtualName="MidifiedSlider" explicitFocusOrder="0" pos="47.031% 70.342% 8.551% 11.18%"
          min="0" max="1" int="0.010000000000000000208" style="RotaryVerticalDrag"
          textBoxPos="TextBoxBelow" textBoxEditable="1" textBoxWidth="40"
          textBoxHeight="20" skewFactor="1"/>
  <LABEL name="filter gain label" id="1739e718e2bf97c" memberName="filterGainLabel"
         virtualName="" explicitFocusOrder="0" pos="60.808% 66.615% 60 20"
         edTextCol="ff000000" edBkgCol="0" labelText="Gain" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15" bold="0" italic="0" justification="12"/>
  <SLIDER name="filter param1 slider" id="4d28a9c9b11da6ce" memberName="filterParam1Slider3"
          virtualName="MidifiedSlider" explicitFocusOrder="0" pos="59.857% 70.342% 8.551% 11.18%"
          min="0" max="2" int="0.010000000000000000208" style="RotaryVerticalDrag"
          textBoxPos="TextBoxBelow" textBoxEditable="1" textBoxWidth="40"
          textBoxHeight="20" skewFactor="1"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]
