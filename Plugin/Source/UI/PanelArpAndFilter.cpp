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

#include "PanelArpAndFilter.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
//[/MiscUserDefs]

//==============================================================================
PanelArpAndFilter::PanelArpAndFilter ()
{
    addAndMakeVisible (arpGroupComponent = new GroupComponent ("Arp group",
                                                               TRANS("Arpeggiator")));
    arpGroupComponent->setTextLabelPosition (Justification::centredLeft);

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
    arpDirectionCombo->addItem (TRANS("Chord"), 6);
    arpDirectionCombo->addItem (TRANS("Rotate Up"), 7);
    arpDirectionCombo->addItem (TRANS("Rotate Down"), 8);
    arpDirectionCombo->addItem (TRANS("Rotate U&D"), 9);
    arpDirectionCombo->addItem (TRANS("Shift Up"), 10);
    arpDirectionCombo->addItem (TRANS("Shift Down"), 11);
    arpDirectionCombo->addItem (TRANS("Shift U&D"), 12);
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

    addAndMakeVisible (filterParam2Slider = new Slider ("filter param2 slider"));
    filterParam2Slider->setRange (0, 1, 0.01);
    filterParam2Slider->setSliderStyle (Slider::RotaryVerticalDrag);
    filterParam2Slider->setTextBoxStyle (Slider::TextBoxBelow, false, 40, 20);
    filterParam2Slider->addListener (this);

    addAndMakeVisible (filterGainLabel = new Label ("filter gain label",
                                                    TRANS("Gain")));
    filterGainLabel->setFont (Font (15.00f, Font::plain));
    filterGainLabel->setJustificationType (Justification::centredTop);
    filterGainLabel->setEditable (false, false, false);
    filterGainLabel->setColour (TextEditor::textColourId, Colours::black);
    filterGainLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (filterGainSlider = new Slider ("filter gain slider"));
    filterGainSlider->setRange (0, 2, 0.01);
    filterGainSlider->setSliderStyle (Slider::RotaryVerticalDrag);
    filterGainSlider->setTextBoxStyle (Slider::TextBoxBelow, false, 40, 20);
    filterGainSlider->addListener (this);

    addAndMakeVisible (arpClockComboBox = new ComboBox ("Clock Combo"));
    arpClockComboBox->setEditableText (false);
    arpClockComboBox->setJustificationType (Justification::centredLeft);
    arpClockComboBox->setTextWhenNothingSelected (TRANS("Off"));
    arpClockComboBox->setTextWhenNoChoicesAvailable (TRANS("Off"));
    arpClockComboBox->addItem (TRANS("Off"), 1);
    arpClockComboBox->addItem (TRANS("Internal"), 2);
    arpClockComboBox->addItem (TRANS("External"), 3);
    arpClockComboBox->addSeparator();
    arpClockComboBox->addListener (this);

    addAndMakeVisible (clockLabel = new Label ("clock label",
                                               TRANS("Clock:\n")));
    clockLabel->setFont (Font (15.00f, Font::plain));
    clockLabel->setJustificationType (Justification::centredLeft);
    clockLabel->setEditable (false, false, false);
    clockLabel->setColour (TextEditor::textColourId, Colours::black);
    clockLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (filterComboBox = new ComboBox ("Filter Combo"));
    filterComboBox->setEditableText (false);
    filterComboBox->setJustificationType (Justification::centredLeft);
    filterComboBox->setTextWhenNothingSelected (TRANS("Off"));
    filterComboBox->setTextWhenNoChoicesAvailable (TRANS("Off"));
    filterComboBox->addItem (TRANS("Off"), 1);
    filterComboBox->addItem (TRANS("Mix"), 2);
    filterComboBox->addItem (TRANS("Low Pass"), 3);
    filterComboBox->addItem (TRANS("High Pass"), 4);
    filterComboBox->addItem (TRANS("Bass Boost"), 5);
    filterComboBox->addListener (this);


    //[UserPreSize]
    //[/UserPreSize]

    setSize (900, 700);


    //[Constructor] You can add your own custom stuff here..
    eventsToAdd = nullptr;

    arpClockComboBox->setSelectedId(1);
    filterComboBox->setSelectedId(1);

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


    //[/Constructor]
}

PanelArpAndFilter::~PanelArpAndFilter()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    //[/Destructor_pre]

    arpGroupComponent = nullptr;
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
    filterParam1Label = nullptr;
    filterParam1Slider = nullptr;
    filterParam2Label = nullptr;
    filterParam2Slider = nullptr;
    filterGainLabel = nullptr;
    filterGainSlider = nullptr;
    arpClockComboBox = nullptr;
    clockLabel = nullptr;
    filterComboBox = nullptr;


    //[Destructor]. You can add your own custom destruction code here..
    //[/Destructor]
}

//==============================================================================
void PanelArpAndFilter::paint (Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    g.fillAll (Colour (0xfffffcc4));

    //[UserPaint] Add your own custom painting code here..
    //[/UserPaint]
}

void PanelArpAndFilter::resized()
{
    arpGroupComponent->setBounds (proportionOfWidth (0.0567f), proportionOfHeight (0.0216f), proportionOfWidth (0.8741f), proportionOfHeight (0.4849f));
    arpBPM->setBounds (proportionOfWidth (0.0761f), proportionOfHeight (0.1871f), proportionOfWidth (0.0857f), proportionOfHeight (0.1122f));
    arpBPMLabel->setBounds (proportionOfWidth (0.0954f), proportionOfHeight (0.1496f), 40, 20);
    arpDirectionLabel->setBounds (proportionOfWidth (0.1895f), proportionOfHeight (0.1496f), 60, 20);
    arpOctaveLabel->setBounds (proportionOfWidth (0.3140f), proportionOfHeight (0.1496f), 60, 20);
    arpPatternLabel->setBounds (proportionOfWidth (0.4274f), proportionOfHeight (0.1496f), 60, 20);
    arpDivisionLabel->setBounds (proportionOfWidth (0.5505f), proportionOfHeight (0.1496f), 60, 20);
    arpDurationLabel->setBounds (proportionOfWidth (0.6847f), proportionOfHeight (0.1496f), 60, 20);
    arpLatchLabel->setBounds (proportionOfWidth (0.8078f), proportionOfHeight (0.1496f), 60, 20);
    arpDirectionCombo->setBounds (proportionOfWidth (0.1812f), proportionOfHeight (0.2115f), 80, 20);
    arpOctavleSlider->setBounds (proportionOfWidth (0.3043f), proportionOfHeight (0.1871f), proportionOfWidth (0.0857f), proportionOfHeight (0.1122f));
    arpPatternCombo->setBounds (proportionOfWidth (0.4274f), proportionOfHeight (0.2115f), 60, 20);
    arpDivisionCombo->setBounds (proportionOfWidth (0.5505f), proportionOfHeight (0.2115f), 60, 20);
    arpDurationCombo->setBounds (proportionOfWidth (0.6847f), proportionOfHeight (0.2115f), 60, 20);
    arpLatchCombo->setBounds (proportionOfWidth (0.8174f), proportionOfHeight (0.2115f), 52, 20);
    filterGroupComponent->setBounds (proportionOfWidth (0.2559f), proportionOfHeight (0.5597f), proportionOfWidth (0.5228f), proportionOfHeight (0.2978f));
    filterParam1Label->setBounds (proportionOfWidth (0.3555f), proportionOfHeight (0.6676f), 60, 20);
    filterParam1Slider->setBounds (proportionOfWidth (0.3389f), proportionOfHeight (0.7036f), proportionOfWidth (0.0857f), proportionOfHeight (0.1122f));
    filterParam2Label->setBounds (proportionOfWidth (0.4869f), proportionOfHeight (0.6676f), 60, 20);
    filterParam2Slider->setBounds (proportionOfWidth (0.4703f), proportionOfHeight (0.7050f), proportionOfWidth (0.0857f), proportionOfHeight (0.1122f));
    filterGainLabel->setBounds (proportionOfWidth (0.6183f), proportionOfHeight (0.6676f), 60, 20);
    filterGainSlider->setBounds (proportionOfWidth (0.5989f), proportionOfHeight (0.7036f), proportionOfWidth (0.0857f), proportionOfHeight (0.1122f));
    arpClockComboBox->setBounds (proportionOfWidth (0.1439f), proportionOfHeight (0.0820f), 120, 24);
    clockLabel->setBounds (proportionOfWidth (0.0968f), proportionOfHeight (0.0820f), 64, 24);
    filterComboBox->setBounds (proportionOfWidth (0.3043f), proportionOfHeight (0.5942f), 120, 24);
    //[UserResized] Add your own custom resize handling here..
    //[/UserResized]
}

void PanelArpAndFilter::sliderValueChanged (Slider* sliderThatWasMoved)
{
    //[UsersliderValueChanged_Pre]
    sliderValueChanged(sliderThatWasMoved, true);
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
    else if (sliderThatWasMoved == filterParam2Slider)
    {
        //[UserSliderCode_filterParam2Slider] -- add your slider handling code here..
        //[/UserSliderCode_filterParam2Slider]
    }
    else if (sliderThatWasMoved == filterGainSlider)
    {
        //[UserSliderCode_filterGainSlider] -- add your slider handling code here..
        //[/UserSliderCode_filterGainSlider]
    }

    //[UsersliderValueChanged_Post]
    //[/UsersliderValueChanged_Post]
}

void PanelArpAndFilter::comboBoxChanged (ComboBox* comboBoxThatHasChanged)
{
    //[UsercomboBoxChanged_Pre]
    comboBoxChanged(comboBoxThatHasChanged, true);
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
    else if (comboBoxThatHasChanged == arpClockComboBox)
    {
        //[UserComboBoxCode_arpClockComboBox] -- add your combo box handling code here..
        //[/UserComboBoxCode_arpClockComboBox]
    }
    else if (comboBoxThatHasChanged == filterComboBox)
    {
        //[UserComboBoxCode_filterComboBox] -- add your combo box handling code here..
        //[/UserComboBoxCode_filterComboBox]
    }

    //[UsercomboBoxChanged_Post]
    //[/UsercomboBoxChanged_Post]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...



void PanelArpAndFilter::comboBoxChanged (ComboBox* comboBoxThatHasChanged, bool fromPluginUI) {
    // Update the value if the change comes from the UI
    if (fromPluginUI) {
        teragon::Parameter * parameterReady = panelParameterMap[comboBoxThatHasChanged->getName()];
        if (parameterReady != nullptr) {
            teragon::ParameterValue value = comboBoxThatHasChanged->getSelectedId();
            parameterSet->set(parameterReady, value, nullptr);
        }
    }

    if (comboBoxThatHasChanged == arpClockComboBox) {
        if (arpClockComboBox->getSelectedId() == 1) {
            arpIsNow(false, false);
        } else if (arpClockComboBox->getSelectedId() == 2) {
            arpIsNow(true, true);
        } else if (arpClockComboBox->getSelectedId() == 3) {
            arpIsNow(true, false);
        }
    } else if (comboBoxThatHasChanged == filterComboBox) {
        if (filterComboBox->getSelectedId() == 1) {
            filterIsNow(false, false);
        } else if (filterComboBox->getSelectedId() == 2) {
            filterIsNow(true, false);
        } else if (filterComboBox->getSelectedId() == 3) {
            filterIsNow(true, true);
        } else if (filterComboBox->getSelectedId() == 4) {
            filterIsNow(true, true);
        } else if (filterComboBox->getSelectedId() == 5) {
            filterIsNow(true, true);
        }
    }
}

void PanelArpAndFilter::sliderValueChanged(Slider* sliderThatWasMoved, bool fromPluginUI)
{
    // Update the value if the change comes from the UI
    if (fromPluginUI) {
        teragon::Parameter * parameterReady = panelParameterMap[sliderThatWasMoved->getName()];
        if (parameterReady != nullptr) {
            teragon::ParameterValue value = sliderThatWasMoved->getValue();
            parameterSet->set(parameterReady, value, nullptr);
        }
    }
}

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

void PanelArpAndFilter::filterIsNow(bool paramOn1, bool paramOn2) {
    filterParam1Label->setEnabled(paramOn1);
    filterParam1Slider->setEnabled(paramOn1);
    filterParam2Label->setEnabled(paramOn2);
    filterParam2Slider->setEnabled(paramOn2);
}

void PanelArpAndFilter::buildParameters() {
//    arpClockComboBox->setSelectedId(1);
//    filterComboBox->setSelectedId(1);
//
//    arpDirectionCombo->setSelectedId(1);
//    arpPatternCombo->setSelectedId(1);
//    arpDivisionCombo->setSelectedId(1);
//    arpDurationCombo->setSelectedId(1);
//    arpLatchCombo->setSelectedId(1);

    updateComboParameter(arpClockComboBox);
    updateComboParameter(filterComboBox);

    updateComboParameter(arpDirectionCombo);
    updateComboParameter(arpPatternCombo);
    updateComboParameter(arpDivisionCombo);
    updateComboParameter(arpDurationCombo);
    updateComboParameter(arpLatchCombo);

    updateSliderParameter(arpBPM);
    updateSliderParameter(arpOctavleSlider);

    updateComboParameter(filterComboBox);
    updateSliderParameter(filterParam1Slider);
    updateSliderParameter(filterParam2Slider);
    updateSliderParameter(filterGainSlider);

}

void PanelArpAndFilter::onParameterUpdated(const teragon::Parameter *parameter) {
}

void PanelArpAndFilter::updateComboParameter_hook(ComboBox* combo) {
    comboBoxChanged(combo, false);
}

void PanelArpAndFilter::updateSliderParameter_hook(Slider* slider) {
    sliderValueChanged(slider, false);
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
  <BACKGROUND backgroundColour="fffffcc4"/>
  <GROUPCOMPONENT name="Arp group" id="13e5d1a66afb37f8" memberName="arpGroupComponent"
                  virtualName="GroupComponent" explicitFocusOrder="0" pos="5.677% 2.118% 87.445% 48.471%"
                  title="Arpeggiator" textpos="33"/>
  <SLIDER name="arp bpm slider" id="834b58daf5daacae" memberName="arpBPM"
          virtualName="Slider" explicitFocusOrder="0" pos="7.642% 18.706% 8.624% 11.176%"
          min="10" max="240" int="1" style="RotaryVerticalDrag" textBoxPos="TextBoxBelow"
          textBoxEditable="1" textBoxWidth="40" textBoxHeight="20" skewFactor="1"/>
  <LABEL name="arp bpm label" id="ae9087ef378fcc73" memberName="arpBPMLabel"
         virtualName="" explicitFocusOrder="0" pos="9.498% 14.941% 40 20"
         edTextCol="ff000000" edBkgCol="0" labelText="BPM" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15" bold="0" italic="0" justification="12"/>
  <LABEL name="arp direction label" id="dd08708728c535e1" memberName="arpDirectionLabel"
         virtualName="" explicitFocusOrder="0" pos="18.996% 14.941% 60 20"
         edTextCol="ff000000" edBkgCol="0" labelText="Direction" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15" bold="0" italic="0" justification="12"/>
  <LABEL name="arp octave label" id="a1efff324e6fc45a" memberName="arpOctaveLabel"
         virtualName="" explicitFocusOrder="0" pos="31.441% 14.941% 60 20"
         edTextCol="ff000000" edBkgCol="0" labelText="Octave" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15" bold="0" italic="0" justification="12"/>
  <LABEL name="arp pattern label" id="81abe99d3c3b9cb" memberName="arpPatternLabel"
         virtualName="" explicitFocusOrder="0" pos="42.686% 14.941% 60 20"
         edTextCol="ff000000" edBkgCol="0" labelText="Pattern" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15" bold="0" italic="0" justification="12"/>
  <LABEL name="arp division label" id="bc6d9b8d07143332" memberName="arpDivisionLabel"
         virtualName="" explicitFocusOrder="0" pos="55.022% 14.941% 60 20"
         edTextCol="ff000000" edBkgCol="0" labelText="Division" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15" bold="0" italic="0" justification="12"/>
  <LABEL name="arp Duration label" id="6e39565df396e160" memberName="arpDurationLabel"
         virtualName="" explicitFocusOrder="0" pos="68.45% 14.941% 60 20"
         edTextCol="ff000000" edBkgCol="0" labelText="Duration" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15" bold="0" italic="0" justification="12"/>
  <LABEL name="arp Latch label" id="4bba356716a40a00" memberName="arpLatchLabel"
         virtualName="" explicitFocusOrder="0" pos="80.786% 14.941% 60 20"
         edTextCol="ff000000" edBkgCol="0" labelText="Latch" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15" bold="0" italic="0" justification="12"/>
  <COMBOBOX name="arp dir combo box" id="5403f05ff830eb2e" memberName="arpDirectionCombo"
            virtualName="ComboBox" explicitFocusOrder="0" pos="18.122% 21.176% 80 20"
            editable="0" layout="33" items="Up&#10;Down&#10;Up &amp; Down&#10;As played&#10;Random&#10;Chord&#10;Rotate Up&#10;Rotate Down&#10;Rotate U&amp;D&#10;Shift Up&#10;Shift Down&#10;Shift U&amp;D&#10;"
            textWhenNonSelected="" textWhenNoItems="(no choices)"/>
  <SLIDER name="arp octave slider" id="1cb995267258f0bb" memberName="arpOctavleSlider"
          virtualName="Slider" explicitFocusOrder="0" pos="30.459% 18.706% 8.624% 11.176%"
          min="1" max="3" int="1" style="RotaryVerticalDrag" textBoxPos="TextBoxBelow"
          textBoxEditable="1" textBoxWidth="40" textBoxHeight="20" skewFactor="1"/>
  <COMBOBOX name="arp pattern combo box" id="4ab8dec3ec103766" memberName="arpPatternCombo"
            virtualName="ComboBox" explicitFocusOrder="0" pos="42.686% 21.176% 60 20"
            editable="0" layout="33" items="1&#10;2&#10;3&#10;4&#10;5&#10;6&#10;7&#10;8&#10;9&#10;10&#10;11&#10;12&#10;13&#10;14&#10;15&#10;16&#10;17&#10;18&#10;19&#10;20&#10;21&#10;22&#10;User 1&#10;User 2&#10;User 3&#10;User 4&#10;"
            textWhenNonSelected="" textWhenNoItems="(no choices)"/>
  <COMBOBOX name="arp division combo box" id="40d9cbf865d21a6d" memberName="arpDivisionCombo"
            virtualName="ComboBox" explicitFocusOrder="0" pos="55.022% 21.176% 60 20"
            editable="0" layout="33" items="2/1&#10;3/2&#10;1/1&#10;3/4&#10;2/3&#10;1/2&#10;3/8&#10;1/3&#10;1/4&#10;1/6&#10;1/8&#10;1/12&#10;1/16&#10;1/24&#10;1/32&#10;1/48&#10;1/96"
            textWhenNonSelected="" textWhenNoItems="(no choices)"/>
  <COMBOBOX name="arp duration combo box" id="40f06b2b6126c25d" memberName="arpDurationCombo"
            virtualName="ComboBox" explicitFocusOrder="0" pos="68.45% 21.176% 60 20"
            editable="0" layout="33" items="2/1&#10;3/2&#10;1/1&#10;3/4&#10;2/3&#10;1/2&#10;3/8&#10;1/3&#10;1/4&#10;1/6&#10;1/8&#10;1/12&#10;1/16&#10;1/24&#10;1/32&#10;1/48&#10;1/96"
            textWhenNonSelected="" textWhenNoItems="(no choices)"/>
  <COMBOBOX name="arp latch combo box" id="3072fb2928d8c8f4" memberName="arpLatchCombo"
            virtualName="ComboBox" explicitFocusOrder="0" pos="81.769% 21.176% 52 20"
            editable="0" layout="33" items="Off&#10;On" textWhenNonSelected=""
            textWhenNoItems="(no choices)"/>
  <GROUPCOMPONENT name="Filter group" id="ef53faceed268e04" memberName="filterGroupComponent"
                  virtualName="" explicitFocusOrder="0" pos="25.546% 56% 52.293% 29.765%"
                  title="Filter" textpos="33"/>
  <LABEL name="filter param1 label" id="ad964c1a500045d4" memberName="filterParam1Label"
         virtualName="" explicitFocusOrder="0" pos="35.59% 66.706% 60 20"
         edTextCol="ff000000" edBkgCol="0" labelText="Param1&#10;" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15" bold="0" italic="0" justification="12"/>
  <SLIDER name="filter param1 slider" id="c05a5ec6435b8dba" memberName="filterParam1Slider"
          virtualName="Slider" explicitFocusOrder="0" pos="33.843% 70.353% 8.624% 11.176%"
          min="0" max="1" int="0.010000000000000000208" style="RotaryVerticalDrag"
          textBoxPos="TextBoxBelow" textBoxEditable="1" textBoxWidth="40"
          textBoxHeight="20" skewFactor="1"/>
  <LABEL name="filter param2 label" id="8e05a7e79e0d078c" memberName="filterParam2Label"
         virtualName="" explicitFocusOrder="0" pos="48.69% 66.706% 60 20"
         edTextCol="ff000000" edBkgCol="0" labelText="Param2&#10;" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15" bold="0" italic="0" justification="12"/>
  <SLIDER name="filter param2 slider" id="d542ada05f27098e" memberName="filterParam2Slider"
          virtualName="Slider" explicitFocusOrder="0" pos="47.052% 70.471% 8.624% 11.176%"
          min="0" max="1" int="0.010000000000000000208" style="RotaryVerticalDrag"
          textBoxPos="TextBoxBelow" textBoxEditable="1" textBoxWidth="40"
          textBoxHeight="20" skewFactor="1"/>
  <LABEL name="filter gain label" id="1739e718e2bf97c" memberName="filterGainLabel"
         virtualName="" explicitFocusOrder="0" pos="61.79% 66.706% 60 20"
         edTextCol="ff000000" edBkgCol="0" labelText="Gain" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15" bold="0" italic="0" justification="12"/>
  <SLIDER name="filter gain slider" id="4d28a9c9b11da6ce" memberName="filterGainSlider"
          virtualName="Slider" explicitFocusOrder="0" pos="59.934% 70.353% 8.624% 11.176%"
          min="0" max="2" int="0.010000000000000000208" style="RotaryVerticalDrag"
          textBoxPos="TextBoxBelow" textBoxEditable="1" textBoxWidth="40"
          textBoxHeight="20" skewFactor="1"/>
  <COMBOBOX name="Clock Combo" id="1b23d19ebc4cb655" memberName="arpClockComboBox"
            virtualName="" explicitFocusOrder="0" pos="14.41% 8.235% 120 24"
            editable="0" layout="33" items="Off&#10;Internal&#10;External&#10;"
            textWhenNonSelected="Off" textWhenNoItems="Off"/>
  <LABEL name="clock label" id="6a7e1148cc077687" memberName="clockLabel"
         virtualName="" explicitFocusOrder="0" pos="9.716% 8.235% 64 24"
         edTextCol="ff000000" edBkgCol="0" labelText="Clock:&#10;" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15" bold="0" italic="0" justification="33"/>
  <COMBOBOX name="Filter Combo" id="599ad67e6f27bfd7" memberName="filterComboBox"
            virtualName="" explicitFocusOrder="0" pos="30.459% 59.412% 120 24"
            editable="0" layout="33" items="Off&#10;Mix&#10;Low Pass&#10;High Pass&#10;Bass Boost"
            textWhenNonSelected="Off" textWhenNoItems="Off"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]
