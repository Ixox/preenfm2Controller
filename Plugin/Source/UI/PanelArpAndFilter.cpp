/*
  ==============================================================================

  This is an automatically generated GUI class created by the Projucer!

  Be careful when adding custom code to these files, as only the code within
  the "//[xyz]" and "//[/xyz]" sections will be retained when the file is loaded
  and re-saved.

  Created with Projucer version: 5.4.5

  ------------------------------------------------------------------------------

  The Projucer is part of the JUCE library.
  Copyright (c) 2017 - ROLI Ltd.

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
#include "SliderPfm2.h"
#include "../MidifiedFloatParameter.h"
#include "../ListProperty.h"

//[/Headers]

#include "PanelArpAndFilter.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...


struct NameAndId effectNameInit[] = { { "Off",	1 },
    { "Mix simple mixer",	2 },
    { "LP low pass",	3 },
    { "HP high pass",	4 },
    { "Bass",	5 },
    { "BP band pass",	6 },
    { "Crush ",	7 },
    { "LP2 Low pass flavour 2",	8 },
    { "HP2 High pass flavour 2",	9 },
    { "BP2 Band pass flavour 2",	10 },
    { "Lp3 state variable Low pass",	11 },
    { "Hp3 state variable High pass",	12 },
    { "Bp3 state variable band pass",	13 },
    { "Peak state variable peak",	14 },
    { "Notc state variable notchmode",	15 },
    { "Bell state variable EQ",	16 },
    { "LowS state variable low shelf",	17 },
    { "HigS state variable high shelf",	18 },
    { "LpHp Distortion from LP to HP",	19 },
    { "BpDs saturated band pass",	20 },
    { "LPws distorted low pass and presence",	21 },
    { "Tilt frequency emphasis",	22 },
    { "Pann stereo placement tool",	23 },
    { "Sat guitare saturation",	24 },
    { "Sigm tanh waveshaper saturation",	25 },
    { "Fold amplifier and folder",	26 },
    { "Wrap amplifier and wrapper",	27 },
    { "Xor xored ober threshold",	28 },
    { "Txr1 bitmangling texture 1",	29 },
    { "Txr2 bitmangling texture 2",	30 },
    { "LPx1 xor low pass + fold",	31 },
    { "LPx2 xor low pass + fold",	32 },
    { "LpSn saturated low pass",	33 },
    { "HpSn saturated high pass",	34 },
    { "Not4 quad notch filter",	35 },
    { "Ap4 all pass quad filter",	36 },
    { "Ap4b resonant all pass quad filter",	37 },
    { "Ap4D diffusion all pass quad filter",	38 },
    { "Oryx 2 peaks format",	39 },
    { "Orx2 3 peaks formant",	40 },
    { "Orx3 3 peaks format and distortion",	41 },
    { "18db 3 pole soft low pass",	42 },
    { "La+d ladder 1",	43 },
    { "Lad+ ladder 2",	44 },
    { "Diod ladder 3",	45 },
    { "L+d+ ladder 4",	46 },
    { "h3o+ tb303 filter",	47 },
    { "Svh3 svf with hp in feedback loop",	48 },
    { "Alkx double sample rate reduction",	49 },
    { "", 50 }
};


//[/MiscUserDefs]

//==============================================================================
PanelArpAndFilter::PanelArpAndFilter ()
{
    //[Constructor_pre] You can add your own custom stuff here..

    ListProperty filterList("filters", ".filters.xml", effectNameInit);
    NameAndId* fxNames = filterList.getList();

    //[/Constructor_pre]

    arpGroupComponent.reset (new GroupComponent ("Arp group",
                                                 TRANS("Arpeggiator")));
    addAndMakeVisible (arpGroupComponent.get());
    arpGroupComponent->setTextLabelPosition (Justification::centredLeft);
    arpGroupComponent->setColour (GroupComponent::outlineColourId, Colours::cadetblue);
    arpGroupComponent->setColour (GroupComponent::textColourId, Colours::cadetblue);

    arpBPM.reset (new Slider ("Arp bpm"));
    addAndMakeVisible (arpBPM.get());
    arpBPM->setRange (10, 240, 1);
    arpBPM->setSliderStyle (Slider::RotaryVerticalDrag);
    arpBPM->setTextBoxStyle (Slider::TextBoxBelow, false, 40, 20);
    arpBPM->addListener (this);

    arpBPMLabel.reset (new Label ("arp bpm label",
                                  TRANS("BPM")));
    addAndMakeVisible (arpBPMLabel.get());
    arpBPMLabel->setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Regular"));
    arpBPMLabel->setJustificationType (Justification::centredTop);
    arpBPMLabel->setEditable (false, false, false);
    arpBPMLabel->setColour (TextEditor::textColourId, Colours::black);
    arpBPMLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    arpDirectionLabel.reset (new Label ("arp direction label",
                                        TRANS("Direction")));
    addAndMakeVisible (arpDirectionLabel.get());
    arpDirectionLabel->setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Regular"));
    arpDirectionLabel->setJustificationType (Justification::centredTop);
    arpDirectionLabel->setEditable (false, false, false);
    arpDirectionLabel->setColour (TextEditor::textColourId, Colours::black);
    arpDirectionLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    arpOctaveLabel.reset (new Label ("arp octave label",
                                     TRANS("Octave")));
    addAndMakeVisible (arpOctaveLabel.get());
    arpOctaveLabel->setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Regular"));
    arpOctaveLabel->setJustificationType (Justification::centredTop);
    arpOctaveLabel->setEditable (false, false, false);
    arpOctaveLabel->setColour (TextEditor::textColourId, Colours::black);
    arpOctaveLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    arpPatternLabel.reset (new Label ("arp pattern label",
                                      TRANS("Pattern")));
    addAndMakeVisible (arpPatternLabel.get());
    arpPatternLabel->setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Regular"));
    arpPatternLabel->setJustificationType (Justification::centredTop);
    arpPatternLabel->setEditable (false, false, false);
    arpPatternLabel->setColour (TextEditor::textColourId, Colours::black);
    arpPatternLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    arpDivisionLabel.reset (new Label ("arp division label",
                                       TRANS("Division")));
    addAndMakeVisible (arpDivisionLabel.get());
    arpDivisionLabel->setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Regular"));
    arpDivisionLabel->setJustificationType (Justification::centredTop);
    arpDivisionLabel->setEditable (false, false, false);
    arpDivisionLabel->setColour (TextEditor::textColourId, Colours::black);
    arpDivisionLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    arpDurationLabel.reset (new Label ("arp Duration label",
                                       TRANS("Duration")));
    addAndMakeVisible (arpDurationLabel.get());
    arpDurationLabel->setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Regular"));
    arpDurationLabel->setJustificationType (Justification::centredTop);
    arpDurationLabel->setEditable (false, false, false);
    arpDurationLabel->setColour (TextEditor::textColourId, Colours::black);
    arpDurationLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    arpLatchLabel.reset (new Label ("arp Latch label",
                                    TRANS("Latch")));
    addAndMakeVisible (arpLatchLabel.get());
    arpLatchLabel->setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Regular"));
    arpLatchLabel->setJustificationType (Justification::centredTop);
    arpLatchLabel->setEditable (false, false, false);
    arpLatchLabel->setColour (TextEditor::textColourId, Colours::black);
    arpLatchLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    arpDirectionCombo.reset (new ComboBox ("Arp direction"));
    addAndMakeVisible (arpDirectionCombo.get());
    arpDirectionCombo->setEditableText (false);
    arpDirectionCombo->setJustificationType (Justification::centredLeft);
    arpDirectionCombo->setTextWhenNothingSelected (String());
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

    arpOctavleSlider.reset (new Slider ("Arp octave"));
    addAndMakeVisible (arpOctavleSlider.get());
    arpOctavleSlider->setRange (1, 3, 1);
    arpOctavleSlider->setSliderStyle (Slider::RotaryVerticalDrag);
    arpOctavleSlider->setTextBoxStyle (Slider::TextBoxBelow, false, 40, 20);
    arpOctavleSlider->addListener (this);

    arpPatternCombo.reset (new ComboBox ("Arp pattern"));
    addAndMakeVisible (arpPatternCombo.get());
    arpPatternCombo->setEditableText (false);
    arpPatternCombo->setJustificationType (Justification::centredLeft);
    arpPatternCombo->setTextWhenNothingSelected (String());
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

    arpDivisionCombo.reset (new ComboBox ("Arp division"));
    addAndMakeVisible (arpDivisionCombo.get());
    arpDivisionCombo->setEditableText (false);
    arpDivisionCombo->setJustificationType (Justification::centredLeft);
    arpDivisionCombo->setTextWhenNothingSelected (String());
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

    arpDurationCombo.reset (new ComboBox ("Arp duration"));
    addAndMakeVisible (arpDurationCombo.get());
    arpDurationCombo->setEditableText (false);
    arpDurationCombo->setJustificationType (Justification::centredLeft);
    arpDurationCombo->setTextWhenNothingSelected (String());
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

    arpLatchCombo.reset (new ComboBox ("Arp latch"));
    addAndMakeVisible (arpLatchCombo.get());
    arpLatchCombo->setEditableText (false);
    arpLatchCombo->setJustificationType (Justification::centredLeft);
    arpLatchCombo->setTextWhenNothingSelected (String());
    arpLatchCombo->setTextWhenNoChoicesAvailable (TRANS("(no choices)"));
    arpLatchCombo->addItem (TRANS("Off"), 1);
    arpLatchCombo->addItem (TRANS("On"), 2);
    arpLatchCombo->addListener (this);

    filterGroupComponent.reset (new GroupComponent ("Filter group",
                                                    TRANS("Filter")));
    addAndMakeVisible (filterGroupComponent.get());
    filterGroupComponent->setTextLabelPosition (Justification::centredLeft);
    filterGroupComponent->setColour (GroupComponent::outlineColourId, Colour (0x00749fad));
    filterGroupComponent->setColour (GroupComponent::textColourId, Colours::beige);

    filterParam1Label.reset (new Label ("filter param1 label",
                                        TRANS("Param1")));
    addAndMakeVisible (filterParam1Label.get());
    filterParam1Label->setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Regular"));
    filterParam1Label->setJustificationType (Justification::centredTop);
    filterParam1Label->setEditable (false, false, false);
    filterParam1Label->setColour (TextEditor::textColourId, Colours::black);
    filterParam1Label->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    filterParam1Slider.reset (new Slider ("Filter param1"));
    addAndMakeVisible (filterParam1Slider.get());
    filterParam1Slider->setRange (0, 1, 0.01);
    filterParam1Slider->setSliderStyle (Slider::RotaryVerticalDrag);
    filterParam1Slider->setTextBoxStyle (Slider::TextBoxBelow, false, 40, 20);
    filterParam1Slider->addListener (this);

    filterParam2Label.reset (new Label ("filter param2 label",
                                        TRANS("Param2")));
    addAndMakeVisible (filterParam2Label.get());
    filterParam2Label->setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Regular"));
    filterParam2Label->setJustificationType (Justification::centredTop);
    filterParam2Label->setEditable (false, false, false);
    filterParam2Label->setColour (TextEditor::textColourId, Colours::black);
    filterParam2Label->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    filterParam2Slider.reset (new Slider ("Filter param2"));
    addAndMakeVisible (filterParam2Slider.get());
    filterParam2Slider->setRange (0, 1, 0.01);
    filterParam2Slider->setSliderStyle (Slider::RotaryVerticalDrag);
    filterParam2Slider->setTextBoxStyle (Slider::TextBoxBelow, false, 40, 20);
    filterParam2Slider->addListener (this);

    filterGainLabel.reset (new Label ("filter gain label",
                                      TRANS("Gain")));
    addAndMakeVisible (filterGainLabel.get());
    filterGainLabel->setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Regular"));
    filterGainLabel->setJustificationType (Justification::centredTop);
    filterGainLabel->setEditable (false, false, false);
    filterGainLabel->setColour (TextEditor::textColourId, Colours::black);
    filterGainLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    filterGainSlider.reset (new Slider ("Filter gain"));
    addAndMakeVisible (filterGainSlider.get());
    filterGainSlider->setRange (0, 2, 0.01);
    filterGainSlider->setSliderStyle (Slider::RotaryVerticalDrag);
    filterGainSlider->setTextBoxStyle (Slider::TextBoxBelow, false, 40, 20);
    filterGainSlider->addListener (this);

    arpClockComboBox.reset (new ComboBox ("Arp clock"));
    addAndMakeVisible (arpClockComboBox.get());
    arpClockComboBox->setEditableText (false);
    arpClockComboBox->setJustificationType (Justification::centredLeft);
    arpClockComboBox->setTextWhenNothingSelected (TRANS("Off"));
    arpClockComboBox->setTextWhenNoChoicesAvailable (TRANS("Off"));
    arpClockComboBox->addItem (TRANS("Off"), 1);
    arpClockComboBox->addItem (TRANS("Internal"), 2);
    arpClockComboBox->addItem (TRANS("External"), 3);
    arpClockComboBox->addSeparator();
    arpClockComboBox->addListener (this);

    clockLabel.reset (new Label ("clock label",
                                 TRANS("Clock:\n")));
    addAndMakeVisible (clockLabel.get());
    clockLabel->setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Regular"));
    clockLabel->setJustificationType (Justification::centredLeft);
    clockLabel->setEditable (false, false, false);
    clockLabel->setColour (TextEditor::textColourId, Colours::black);
    clockLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    filterComboBox.reset (new ComboBox ("Filter type"));
    addAndMakeVisible (filterComboBox.get());
    filterComboBox->setEditableText (false);
    filterComboBox->setJustificationType (Justification::centredLeft);
    filterComboBox->setTextWhenNothingSelected (TRANS("Off"));
    filterComboBox->setTextWhenNoChoicesAvailable (TRANS("Off"));
    filterComboBox->addListener (this);


    //[UserPreSize]

    for (int n = 0; fxNames[n].name != ""; n++) {
        filterComboBox->addItem(TRANS(fxNames[n].name), fxNames[n].id);
    }

    for (int n = 0; n < 2; n++) {
        addAndMakeVisible(noteGroupComponent[n] = new GroupComponent("Note group" + String(n + 1), TRANS("Note" + String(n + 1) + " Scaling")));
        noteGroupComponent[n]->setColour(GroupComponent::textColourId, Colour(0xff749FAD));
        noteGroupComponent[n]->setColour(GroupComponent::outlineColourId, Colour(0xff749FAD));
        noteGroupComponent[n]->setTextLabelPosition(Justification::centredLeft);

        addAndMakeVisible(noteBeforeLabel[n] = new Label("Note" + String(n + 1) + " before label ", "Before"));
        noteBeforeLabel[n]->setJustificationType(Justification::centredTop);
        addAndMakeVisible(noteBefore[n] = new ComboBox("Note" + String(n + 1) + " before"));
        noteBefore[n]->setEditableText(false);
        noteBefore[n]->setJustificationType(Justification::centred);
        noteBefore[n]->setColour(ComboBox::buttonColourId, Colours::blue);
        noteBefore[n]->addItem("Flat", 1);
        noteBefore[n]->addItem("+Linear", 2);
        noteBefore[n]->addItem("+Linear*8", 3);
        noteBefore[n]->addItem("+Exp", 4);
        noteBefore[n]->addItem("-Linear", 5);
        noteBefore[n]->addItem("-Linear*8", 6);
        noteBefore[n]->addItem("-Exp", 7);
        noteBefore[n]->setSelectedId(5);
        noteBefore[n]->setScrollWheelEnabled(true);
        noteBefore[n]->addListener(this);

        addAndMakeVisible(noteBreakLabel[n] = new Label("Note" + String(n + 1) + " break label ", "Break note"));
        noteBreakLabel[n]->setJustificationType(Justification::centredTop);
        addAndMakeVisible(noteBreak[n] = new SliderPfm2("Note" + String(n + 1) + " break"));
        noteBreak[n]->setRange(0, 127.0f, 1.0f);
        noteBreak[n]->setSliderStyle(Slider::RotaryVerticalDrag);
        noteBreak[n]->setTextBoxStyle(Slider::TextBoxBelow, false, 35, 16);
        noteBreak[n]->setDoubleClickReturnValue(true, 60.0f);
        noteBreak[n]->setValue(60.0f, dontSendNotification);
        noteBreak[n]->addListener(this);

        addAndMakeVisible(noteAfterLabel[n] = new Label("Note" + String(n + 1) + " after label ", "After"));
        noteAfterLabel[n]->setJustificationType(Justification::centred);
        addAndMakeVisible(noteAfter[n] = new ComboBox("Note" + String(n + 1) + " after"));
        noteAfter[n]->setEditableText(false);
        noteAfter[n]->setJustificationType(Justification::left);
        noteAfter[n]->setColour(ComboBox::buttonColourId, Colours::blue);
        noteAfter[n]->addItem("Flat", 1);
        noteAfter[n]->addItem("+Linear", 2);
        noteAfter[n]->addItem("+Linear*8", 3);
        noteAfter[n]->addItem("+Exp", 4);
        noteAfter[n]->addItem("-Linear", 5);
        noteAfter[n]->addItem("-Linear*8", 6);
        noteAfter[n]->addItem("-Exp", 7);
        noteAfter[n]->setSelectedId(1);
        noteAfter[n]->setScrollWheelEnabled(true);
        noteAfter[n]->addListener(this);
    }

    arpDirectionCombo->setScrollWheelEnabled(true);
    arpPatternCombo->setScrollWheelEnabled(true);
    arpDivisionCombo->setScrollWheelEnabled(true);
    arpDurationCombo->setScrollWheelEnabled(true);
    arpLatchCombo->setScrollWheelEnabled(true);
    arpClockComboBox->setScrollWheelEnabled(true);

    filterComboBox->setScrollWheelEnabled(true);
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

	arpDirectionCombo->setColour(ComboBox::buttonColourId, Colours::blue);
	arpPatternCombo->setColour(ComboBox::buttonColourId, Colours::blue);
	arpDivisionCombo->setColour(ComboBox::buttonColourId, Colours::blue);
	arpDurationCombo->setColour(ComboBox::buttonColourId, Colours::blue);
	arpLatchCombo->setColour(ComboBox::buttonColourId, Colours::blue);



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

    {
        int x = 2, y = proportionOfHeight (0.2000f), width = getWidth() - 4, height = proportionOfHeight (0.2000f);
        Colour fillColour1 = Colour (0xff14576c), fillColour2 = Colour (0xff083543);
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setGradientFill (ColourGradient (fillColour1,
                                       50.0f - 2.0f + x,
                                       static_cast<float> (proportionOfHeight (0.4000f)) - static_cast<float> (proportionOfHeight (0.2000f)) + y,
                                       fillColour2,
                                       50.0f - 2.0f + x,
                                       static_cast<float> (proportionOfHeight (0.2000f)) - static_cast<float> (proportionOfHeight (0.2000f)) + y,
                                       false));
        g.fillRect (x, y, width, height);
    }

    {
        int x = 2, y = proportionOfHeight (0.3900f), width = getWidth() - 4, height = proportionOfHeight (0.2100f);
        Colour fillColour1 = Colour (0xff14576c), fillColour2 = Colour (0xff083543);
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setGradientFill (ColourGradient (fillColour1,
                                       50.0f - 2.0f + x,
                                       static_cast<float> (proportionOfHeight (0.4000f)) - static_cast<float> (proportionOfHeight (0.3900f)) + y,
                                       fillColour2,
                                       50.0f - 2.0f + x,
                                       static_cast<float> (proportionOfHeight (0.6000f)) - static_cast<float> (proportionOfHeight (0.3900f)) + y,
                                       false));
        g.fillRect (x, y, width, height);
    }

    {
        float x = static_cast<float> (proportionOfWidth (0.0964f)), y = static_cast<float> (proportionOfHeight (0.3616f)), width = static_cast<float> (proportionOfWidth (0.8132f)), height = static_cast<float> (proportionOfHeight (0.2137f));
        Colour fillColour1 = Colour (0x8fa52a2a), fillColour2 = Colour (0xb6a5462a);
        Colour strokeColour = Colours::cadetblue;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setGradientFill (ColourGradient (fillColour1,
                                       static_cast<float> (proportionOfWidth (0.5878f)) - static_cast<float> (proportionOfWidth (0.0964f)) + x,
                                       static_cast<float> (proportionOfHeight (0.3566f)) - static_cast<float> (proportionOfHeight (0.3616f)) + y,
                                       fillColour2,
                                       static_cast<float> (proportionOfWidth (0.7123f)) - static_cast<float> (proportionOfWidth (0.0964f)) + x,
                                       static_cast<float> (proportionOfHeight (0.5736f)) - static_cast<float> (proportionOfHeight (0.3616f)) + y,
                                       false));
        g.fillRoundedRectangle (x, y, width, height, 10.000f);
        g.setColour (strokeColour);
        g.drawRoundedRectangle (x, y, width, height, 10.000f, 2.000f);
    }

    //[UserPaint] Add your own custom painting code here..
    //[/UserPaint]
}

void PanelArpAndFilter::resized()
{
    //[UserPreResize] Add your own custom resize code here..
    //[/UserPreResize]

    arpGroupComponent->setBounds (proportionOfWidth (0.0616f), proportionOfHeight (0.0233f), proportionOfWidth (0.8817f), proportionOfHeight (0.3023f));
    arpBPM->setBounds (proportionOfWidth (0.1003f), proportionOfHeight (0.1793f), proportionOfWidth (0.0903f), proportionOfHeight (0.1211f));
    arpBPMLabel->setBounds (proportionOfWidth (0.1003f), proportionOfHeight (0.1395f), proportionOfWidth (0.0903f), 20);
    arpDirectionLabel->setBounds (proportionOfWidth (0.2098f), proportionOfHeight (0.1395f), proportionOfWidth (0.0816f), 20);
    arpOctaveLabel->setBounds (proportionOfWidth (0.3101f), proportionOfHeight (0.1395f), proportionOfWidth (0.0903f), 20);
    arpPatternLabel->setBounds (proportionOfWidth (0.4303f), proportionOfHeight (0.1395f), proportionOfWidth (0.0697f), 20);
    arpDivisionLabel->setBounds (proportionOfWidth (0.5598f), proportionOfHeight (0.1395f), proportionOfWidth (0.0697f), 20);
    arpDurationLabel->setBounds (proportionOfWidth (0.6899f), proportionOfHeight (0.1395f), proportionOfWidth (0.0697f), 20);
    arpLatchLabel->setBounds (proportionOfWidth (0.8313f), proportionOfHeight (0.1395f), proportionOfWidth (0.0697f), 20);
    arpDirectionCombo->setBounds (proportionOfWidth (0.1999f), proportionOfHeight (0.2016f), proportionOfWidth (0.1003f), 20);
    arpOctavleSlider->setBounds (proportionOfWidth (0.3101f), proportionOfHeight (0.1793f), proportionOfWidth (0.0903f), proportionOfHeight (0.1211f));
    arpPatternCombo->setBounds (proportionOfWidth (0.4303f), proportionOfHeight (0.2016f), proportionOfWidth (0.0816f), 20);
    arpDivisionCombo->setBounds (proportionOfWidth (0.5598f), proportionOfHeight (0.2016f), proportionOfWidth (0.0816f), 20);
    arpDurationCombo->setBounds (proportionOfWidth (0.6899f), proportionOfHeight (0.2016f), proportionOfWidth (0.0816f), 20);
    arpLatchCombo->setBounds (proportionOfWidth (0.8313f), proportionOfHeight (0.2016f), proportionOfWidth (0.0816f), 20);
    filterGroupComponent->setBounds (proportionOfWidth (0.1027f), proportionOfHeight (0.3634f), proportionOfWidth (0.8088f), proportionOfHeight (0.2064f));
    filterParam1Label->setBounds (proportionOfWidth (0.4546f), proportionOfHeight (0.3808f), proportionOfWidth (0.0903f), 20);
    filterParam1Slider->setBounds (proportionOfWidth (0.4546f), proportionOfHeight (0.4147f), proportionOfWidth (0.0903f), proportionOfHeight (0.1211f));
    filterParam2Label->setBounds (proportionOfWidth (0.5841f), proportionOfHeight (0.3789f), proportionOfWidth (0.0903f), 20);
    filterParam2Slider->setBounds (proportionOfWidth (0.5841f), proportionOfHeight (0.4167f), proportionOfWidth (0.0903f), proportionOfHeight (0.1211f));
    filterGainLabel->setBounds (proportionOfWidth (0.7242f), proportionOfHeight (0.3789f), proportionOfWidth (0.0903f), 20);
    filterGainSlider->setBounds (proportionOfWidth (0.7242f), proportionOfHeight (0.4147f), proportionOfWidth (0.0903f), proportionOfHeight (0.1211f));
    arpClockComboBox->setBounds (proportionOfWidth (0.1644f), proportionOfHeight (0.0707f), proportionOfWidth (0.0816f), 20);
    clockLabel->setBounds (proportionOfWidth (0.0984f), proportionOfHeight (0.0707f), 64, 24);
    filterComboBox->setBounds (proportionOfWidth (0.1600f), proportionOfHeight (0.4516f), proportionOfWidth (0.2198f), 20);
    //[UserResized] Add your own custom resize handling here..

	float h = 0.7f;
	for (int k = 0; k < 2; k++) {
		// 0.05 0.65 0.47 0.25
		noteGroupComponent[k]->setBounds(proportionOfWidth(0.03f + .5f * k), proportionOfHeight(0.65f), proportionOfWidth(0.44f), proportionOfHeight(0.25f));

		noteBeforeLabel[k]->setBounds(proportionOfWidth(0.08f + .5f * k), proportionOfHeight(h), proportionOfWidth(0.07f), 20);
		noteBefore[k]->setBounds(proportionOfWidth(0.08f + .5f * k), proportionOfHeight(h + 0.05f), proportionOfWidth(0.07f), 20);

		noteBreakLabel[k]->setBounds(proportionOfWidth(0.20f + .5f * k), proportionOfHeight(h), proportionOfWidth(0.09f), 20);
		noteBreak[k]->setBounds(proportionOfWidth(0.20f + .5f * k), proportionOfHeight(h + 0.03f), proportionOfWidth(0.09f), proportionOfHeight(0.12f));

		noteAfterLabel[k]->setBounds(proportionOfWidth(0.34f + .5f * k), proportionOfHeight(h), proportionOfWidth(0.07f), 20);
		noteAfter[k]->setBounds(proportionOfWidth(0.34f + .5f * k), proportionOfHeight(h + 0.05f), proportionOfWidth(0.07f), 20);
	}
    //[/UserResized]
}

void PanelArpAndFilter::sliderValueChanged (Slider* sliderThatWasMoved)
{
    //[UsersliderValueChanged_Pre]
	sliderValueChanged(sliderThatWasMoved, true);
    //[/UsersliderValueChanged_Pre]

    if (sliderThatWasMoved == arpBPM.get())
    {
        //[UserSliderCode_arpBPM] -- add your slider handling code here..
        //[/UserSliderCode_arpBPM]
    }
    else if (sliderThatWasMoved == arpOctavleSlider.get())
    {
        //[UserSliderCode_arpOctavleSlider] -- add your slider handling code here..
        //[/UserSliderCode_arpOctavleSlider]
    }
    else if (sliderThatWasMoved == filterParam1Slider.get())
    {
        //[UserSliderCode_filterParam1Slider] -- add your slider handling code here..
        //[/UserSliderCode_filterParam1Slider]
    }
    else if (sliderThatWasMoved == filterParam2Slider.get())
    {
        //[UserSliderCode_filterParam2Slider] -- add your slider handling code here..
        //[/UserSliderCode_filterParam2Slider]
    }
    else if (sliderThatWasMoved == filterGainSlider.get())
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

    if (comboBoxThatHasChanged == arpDirectionCombo.get())
    {
        //[UserComboBoxCode_arpDirectionCombo] -- add your combo box handling code here..
        //[/UserComboBoxCode_arpDirectionCombo]
    }
    else if (comboBoxThatHasChanged == arpPatternCombo.get())
    {
        //[UserComboBoxCode_arpPatternCombo] -- add your combo box handling code here..
        //[/UserComboBoxCode_arpPatternCombo]
    }
    else if (comboBoxThatHasChanged == arpDivisionCombo.get())
    {
        //[UserComboBoxCode_arpDivisionCombo] -- add your combo box handling code here..
        //[/UserComboBoxCode_arpDivisionCombo]
    }
    else if (comboBoxThatHasChanged == arpDurationCombo.get())
    {
        //[UserComboBoxCode_arpDurationCombo] -- add your combo box handling code here..
        //[/UserComboBoxCode_arpDurationCombo]
    }
    else if (comboBoxThatHasChanged == arpLatchCombo.get())
    {
        //[UserComboBoxCode_arpLatchCombo] -- add your combo box handling code here..
        //[/UserComboBoxCode_arpLatchCombo]
    }
    else if (comboBoxThatHasChanged == arpClockComboBox.get())
    {
        //[UserComboBoxCode_arpClockComboBox] -- add your combo box handling code here..
        //[/UserComboBoxCode_arpClockComboBox]
    }
    else if (comboBoxThatHasChanged == filterComboBox.get())
    {
        //[UserComboBoxCode_filterComboBox] -- add your combo box handling code here..
        //[/UserComboBoxCode_filterComboBox]
    }

    //[UsercomboBoxChanged_Post]
    //[/UsercomboBoxChanged_Post]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...



void PanelArpAndFilter::comboBoxChanged(ComboBox* comboBoxThatHasChanged, bool fromPluginUI) {
	// Update the value if the change comes from the UI
	if (fromPluginUI) {
		AudioProcessorParameter* parameterReady = parameterMap[comboBoxThatHasChanged->getName()];
		if (parameterReady != nullptr) {
			float value = (float)comboBoxThatHasChanged->getSelectedId();
			((MidifiedFloatParameter*)parameterReady)->setRealValue(value);
		}
	}

    if (comboBoxThatHasChanged == arpClockComboBox.get()) {
		if (arpClockComboBox->getSelectedId() == 1) {
			arpIsNow(false, false);
		}
		else if (arpClockComboBox->getSelectedId() == 2) {
			arpIsNow(true, true);
		}
		else if (arpClockComboBox->getSelectedId() == 3) {
			arpIsNow(true, false);
		}
	}
	else if (comboBoxThatHasChanged == filterComboBox.get()) {
		if (filterComboBox->getSelectedId() == 1) {
			filterIsNow(false, false);
		}
		else if (filterComboBox->getSelectedId() == 2) {
			filterIsNow(true, false);
		}
		else {
			filterIsNow(true, true);
		}
	}
}

void PanelArpAndFilter::sliderValueChanged(Slider* sliderThatWasMoved, bool fromPluginUI)
{
	// Update the value if the change comes from the UI
	if (fromPluginUI) {
		AudioProcessorParameter * parameterReady = parameterMap[sliderThatWasMoved->getName()];
		if (parameterReady != nullptr) {
			float value = (float)sliderThatWasMoved->getValue();
			((MidifiedFloatParameter*)parameterReady)->setRealValue(value);
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

	updateComboFromParameter(arpClockComboBox.get());
	updateComboFromParameter(filterComboBox.get());

	updateComboFromParameter(arpDirectionCombo.get());
	updateComboFromParameter(arpPatternCombo.get());
	updateComboFromParameter(arpDivisionCombo.get());
	updateComboFromParameter(arpDurationCombo.get());
	updateComboFromParameter(arpLatchCombo.get());

	updateSliderFromParameter(arpBPM.get());
	updateSliderFromParameter(arpOctavleSlider.get());

	updateComboFromParameter(filterComboBox.get());
	updateSliderFromParameter(filterParam1Slider.get());
	updateSliderFromParameter(filterParam2Slider.get());
	updateSliderFromParameter(filterGainSlider.get());


	for (int k = 0; k < 2; k++) {
		updateComboFromParameter(noteBefore[k].get());
		updateSliderFromParameter(noteBreak[k].get());
		updateComboFromParameter(noteAfter[k].get());
	}

}


void PanelArpAndFilter::updateComboFromParameter_hook(ComboBox* combo) {
	comboBoxChanged(combo, false);
}

void PanelArpAndFilter::updateSliderFromParameter_hook(Slider* slider) {
	sliderValueChanged(slider, false);
}

void PanelArpAndFilter::sliderDragStarted(Slider* slider) {
	AudioProcessorParameter * param = parameterMap[slider->getName()];
	if (param != nullptr) {
		param->beginChangeGesture();
	}
}
void PanelArpAndFilter::sliderDragEnded(Slider* slider) {
	AudioProcessorParameter * param = parameterMap[slider->getName()];
	if (param != nullptr) {
		param->endChangeGesture();
	}
}

//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Projucer information section --

    This is where the Projucer stores the metadata that describe this GUI layout, so
    make changes in here at your peril!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="PanelArpAndFilter" componentName=""
                 parentClasses="public Component, public PanelOfComponents" constructorParams=""
                 variableInitialisers="" snapPixels="8" snapActive="1" snapShown="1"
                 overlayOpacity="0.330" fixedSize="0" initialWidth="900" initialHeight="700">
  <BACKGROUND backgroundColour="0">
    <RECT pos="2 20% 4M 20%" fill="linear: 50 40%, 50 20%, 0=ff14576c, 1=ff083543"
          hasStroke="0"/>
    <RECT pos="2 39% 4M 21%" fill="linear: 50 40%, 50 60%, 0=ff14576c, 1=ff083543"
          hasStroke="0"/>
    <ROUNDRECT pos="9.636% 36.156% 81.316% 21.371%" cornerSize="10.0" fill="linear: 58.78% 35.659%, 71.233% 57.364%, 0=8fa52a2a, 1=b6a5462a"
               hasStroke="1" stroke="2, mitered, butt" strokeColour="solid: ff5f9ea0"/>
  </BACKGROUND>
  <GROUPCOMPONENT name="Arp group" id="13e5d1a66afb37f8" memberName="arpGroupComponent"
                  virtualName="GroupComponent" explicitFocusOrder="0" pos="6.164% 2.326% 88.169% 30.233%"
                  outlinecol="ff5f9ea0" textcol="ff5f9ea0" title="Arpeggiator"
                  textpos="33"/>
  <SLIDER name="Arp bpm" id="834b58daf5daacae" memberName="arpBPM" virtualName="Slider"
          explicitFocusOrder="0" pos="10.025% 17.926% 9.029% 12.112%" min="10.0"
          max="240.0" int="1.0" style="RotaryVerticalDrag" textBoxPos="TextBoxBelow"
          textBoxEditable="1" textBoxWidth="40" textBoxHeight="20" skewFactor="1.0"
          needsCallback="1"/>
  <LABEL name="arp bpm label" id="ae9087ef378fcc73" memberName="arpBPMLabel"
         virtualName="" explicitFocusOrder="0" pos="10.025% 13.953% 9.029% 20"
         edTextCol="ff000000" edBkgCol="0" labelText="BPM" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15.0" kerning="0.0" bold="0" italic="0" justification="12"/>
  <LABEL name="arp direction label" id="dd08708728c535e1" memberName="arpDirectionLabel"
         virtualName="" explicitFocusOrder="0" pos="20.984% 13.953% 8.157% 20"
         edTextCol="ff000000" edBkgCol="0" labelText="Direction" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15.0" kerning="0.0" bold="0" italic="0" justification="12"/>
  <LABEL name="arp octave label" id="a1efff324e6fc45a" memberName="arpOctaveLabel"
         virtualName="" explicitFocusOrder="0" pos="31.009% 13.953% 9.029% 20"
         edTextCol="ff000000" edBkgCol="0" labelText="Octave" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15.0" kerning="0.0" bold="0" italic="0" justification="12"/>
  <LABEL name="arp pattern label" id="81abe99d3c3b9cb" memberName="arpPatternLabel"
         virtualName="" explicitFocusOrder="0" pos="43.026% 13.953% 6.974% 20"
         edTextCol="ff000000" edBkgCol="0" labelText="Pattern" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15.0" kerning="0.0" bold="0" italic="0" justification="12"/>
  <LABEL name="arp division label" id="bc6d9b8d07143332" memberName="arpDivisionLabel"
         virtualName="" explicitFocusOrder="0" pos="55.978% 13.953% 6.974% 20"
         edTextCol="ff000000" edBkgCol="0" labelText="Division" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15.0" kerning="0.0" bold="0" italic="0" justification="12"/>
  <LABEL name="arp Duration label" id="6e39565df396e160" memberName="arpDurationLabel"
         virtualName="" explicitFocusOrder="0" pos="68.991% 13.953% 6.974% 20"
         edTextCol="ff000000" edBkgCol="0" labelText="Duration" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15.0" kerning="0.0" bold="0" italic="0" justification="12"/>
  <LABEL name="arp Latch label" id="4bba356716a40a00" memberName="arpLatchLabel"
         virtualName="" explicitFocusOrder="0" pos="83.126% 13.953% 6.974% 20"
         edTextCol="ff000000" edBkgCol="0" labelText="Latch" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15.0" kerning="0.0" bold="0" italic="0" justification="12"/>
  <COMBOBOX name="Arp direction" id="5403f05ff830eb2e" memberName="arpDirectionCombo"
            virtualName="ComboBox" explicitFocusOrder="0" pos="19.988% 20.155% 10.025% 20"
            editable="0" layout="33" items="Up&#10;Down&#10;Up &amp; Down&#10;As played&#10;Random&#10;Chord&#10;Rotate Up&#10;Rotate Down&#10;Rotate U&amp;D&#10;Shift Up&#10;Shift Down&#10;Shift U&amp;D&#10;"
            textWhenNonSelected="" textWhenNoItems="(no choices)"/>
  <SLIDER name="Arp octave" id="1cb995267258f0bb" memberName="arpOctavleSlider"
          virtualName="Slider" explicitFocusOrder="0" pos="31.009% 17.926% 9.029% 12.112%"
          min="1.0" max="3.0" int="1.0" style="RotaryVerticalDrag" textBoxPos="TextBoxBelow"
          textBoxEditable="1" textBoxWidth="40" textBoxHeight="20" skewFactor="1.0"
          needsCallback="1"/>
  <COMBOBOX name="Arp pattern" id="4ab8dec3ec103766" memberName="arpPatternCombo"
            virtualName="ComboBox" explicitFocusOrder="0" pos="43.026% 20.155% 8.157% 20"
            editable="0" layout="33" items="1&#10;2&#10;3&#10;4&#10;5&#10;6&#10;7&#10;8&#10;9&#10;10&#10;11&#10;12&#10;13&#10;14&#10;15&#10;16&#10;17&#10;18&#10;19&#10;20&#10;21&#10;22&#10;User 1&#10;User 2&#10;User 3&#10;User 4&#10;"
            textWhenNonSelected="" textWhenNoItems="(no choices)"/>
  <COMBOBOX name="Arp division" id="40d9cbf865d21a6d" memberName="arpDivisionCombo"
            virtualName="ComboBox" explicitFocusOrder="0" pos="55.978% 20.155% 8.157% 20"
            editable="0" layout="33" items="2/1&#10;3/2&#10;1/1&#10;3/4&#10;2/3&#10;1/2&#10;3/8&#10;1/3&#10;1/4&#10;1/6&#10;1/8&#10;1/12&#10;1/16&#10;1/24&#10;1/32&#10;1/48&#10;1/96"
            textWhenNonSelected="" textWhenNoItems="(no choices)"/>
  <COMBOBOX name="Arp duration" id="40f06b2b6126c25d" memberName="arpDurationCombo"
            virtualName="ComboBox" explicitFocusOrder="0" pos="68.991% 20.155% 8.157% 20"
            editable="0" layout="33" items="2/1&#10;3/2&#10;1/1&#10;3/4&#10;2/3&#10;1/2&#10;3/8&#10;1/3&#10;1/4&#10;1/6&#10;1/8&#10;1/12&#10;1/16&#10;1/24&#10;1/32&#10;1/48&#10;1/96"
            textWhenNonSelected="" textWhenNoItems="(no choices)"/>
  <COMBOBOX name="Arp latch" id="3072fb2928d8c8f4" memberName="arpLatchCombo"
            virtualName="ComboBox" explicitFocusOrder="0" pos="83.126% 20.155% 8.157% 20"
            editable="0" layout="33" items="Off&#10;On" textWhenNonSelected=""
            textWhenNoItems="(no choices)"/>
  <GROUPCOMPONENT name="Filter group" id="ef53faceed268e04" memberName="filterGroupComponent"
                  virtualName="" explicitFocusOrder="0" pos="10.274% 36.337% 80.884% 20.64%"
                  outlinecol="749fad" textcol="fff5f5dc" title="Filter" textpos="33"/>
  <LABEL name="filter param1 label" id="ad964c1a500045d4" memberName="filterParam1Label"
         virtualName="" explicitFocusOrder="0" pos="45.455% 38.081% 9.029% 20"
         edTextCol="ff000000" edBkgCol="0" labelText="Param1" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15.0" kerning="0.0" bold="0" italic="0" justification="12"/>
  <SLIDER name="Filter param1" id="c05a5ec6435b8dba" memberName="filterParam1Slider"
          virtualName="Slider" explicitFocusOrder="0" pos="45.455% 41.473% 9.029% 12.112%"
          min="0.0" max="1.0" int="0.01" style="RotaryVerticalDrag" textBoxPos="TextBoxBelow"
          textBoxEditable="1" textBoxWidth="40" textBoxHeight="20" skewFactor="1.0"
          needsCallback="1"/>
  <LABEL name="filter param2 label" id="8e05a7e79e0d078c" memberName="filterParam2Label"
         virtualName="" explicitFocusOrder="0" pos="58.406% 37.888% 9.029% 20"
         edTextCol="ff000000" edBkgCol="0" labelText="Param2" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15.0" kerning="0.0" bold="0" italic="0" justification="12"/>
  <SLIDER name="Filter param2" id="d542ada05f27098e" memberName="filterParam2Slider"
          virtualName="Slider" explicitFocusOrder="0" pos="58.406% 41.667% 9.029% 12.112%"
          min="0.0" max="1.0" int="0.01" style="RotaryVerticalDrag" textBoxPos="TextBoxBelow"
          textBoxEditable="1" textBoxWidth="40" textBoxHeight="20" skewFactor="1.0"
          needsCallback="1"/>
  <LABEL name="filter gain label" id="1739e718e2bf97c" memberName="filterGainLabel"
         virtualName="" explicitFocusOrder="0" pos="72.416% 37.888% 9.029% 20"
         edTextCol="ff000000" edBkgCol="0" labelText="Gain" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15.0" kerning="0.0" bold="0" italic="0" justification="12"/>
  <SLIDER name="Filter gain" id="4d28a9c9b11da6ce" memberName="filterGainSlider"
          virtualName="Slider" explicitFocusOrder="0" pos="72.416% 41.473% 9.029% 12.112%"
          min="0.0" max="2.0" int="0.01" style="RotaryVerticalDrag" textBoxPos="TextBoxBelow"
          textBoxEditable="1" textBoxWidth="40" textBoxHeight="20" skewFactor="1.0"
          needsCallback="1"/>
  <COMBOBOX name="Arp clock" id="1b23d19ebc4cb655" memberName="arpClockComboBox"
            virtualName="" explicitFocusOrder="0" pos="16.438% 7.074% 8.157% 20"
            editable="0" layout="33" items="Off&#10;Internal&#10;External&#10;"
            textWhenNonSelected="Off" textWhenNoItems="Off"/>
  <LABEL name="clock label" id="6a7e1148cc077687" memberName="clockLabel"
         virtualName="" explicitFocusOrder="0" pos="9.838% 7.074% 64 24"
         edTextCol="ff000000" edBkgCol="0" labelText="Clock:&#10;" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15.0" kerning="0.0" bold="0" italic="0" justification="33"/>
  <COMBOBOX name="Filter type" id="599ad67e6f27bfd7" memberName="filterComboBox"
            virtualName="" explicitFocusOrder="0" pos="16.002% 45.155% 21.98% 20"
            editable="0" layout="33" items="" textWhenNonSelected="Off" textWhenNoItems="Off"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]

