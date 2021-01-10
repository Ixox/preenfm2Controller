/*
  ==============================================================================

  This is an automatically generated GUI class created by the Projucer!

  Be careful when adding custom code to these files, as only the code within
  the "//[xyz]" and "//[/xyz]" sections will be retained when the file is loaded
  and re-saved.

  Created with Projucer version: 5.4.7

  ------------------------------------------------------------------------------

  The Projucer is part of the JUCE library.
  Copyright (c) 2017 - ROLI Ltd.

  ==============================================================================
*/

#pragma once

//[Headers]     -- You can add your own extra header files here --
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
#include "PanelOfComponents.h"



//[/Headers]



//==============================================================================
/**
                                                                    //[Comments]
	An auto-generated component, created by the Introjucer.

	Describe your class and how it works here!
                                                                    //[/Comments]
*/
class PanelArpAndFilter  : public Component,
                           public PanelOfComponents,
                           public Slider::Listener,
                           public ComboBox::Listener
{
public:
    //==============================================================================
    PanelArpAndFilter ();
    ~PanelArpAndFilter() override;

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.
	void arpIsNow(bool arpOn, bool enableBPM);
	void filterIsNow(bool paramOn1, bool paramOn2);
	void setMidiBuffer(MidiBuffer& eventsToAdd) { this->eventsToAdd = &eventsToAdd; }
    void buildParameters() override;
	void comboBoxChanged(ComboBox* comboBoxThatHasChanged, bool fromPluginUI);
	void sliderValueChanged(Slider* sliderThatWasMoved, bool fromPluginUI);
	void updateComboFromParameter_hook(ComboBox* combo) override;
	void updateSliderFromParameter_hook(Slider* slider) override;
	void sliderDragStarted(Slider* slider)	override;
	void sliderDragEnded(Slider* slider) override;
    //[/UserMethods]

    void paint (Graphics& g) override;
    void resized() override;
    void sliderValueChanged (Slider* sliderThatWasMoved) override;
    void comboBoxChanged (ComboBox* comboBoxThatHasChanged) override;



private:
    //[UserVariables]   -- You can add your own custom variables in this section.
	MidiBuffer* eventsToAdd;

	ScopedPointer<GroupComponent> noteGroupComponent[2];
	ScopedPointer<Label> noteBeforeLabel[2];
	ScopedPointer<ComboBox> noteBefore[2];
	ScopedPointer<Label> noteBreakLabel[2];
	ScopedPointer<Slider> noteBreak[2];
	ScopedPointer<Label> noteAfterLabel[2];
	ScopedPointer<ComboBox> noteAfter[2];


    //[/UserVariables]

    //==============================================================================
    std::unique_ptr<GroupComponent> arpGroupComponent;
    std::unique_ptr<Slider> arpBPM;
    std::unique_ptr<Label> arpBPMLabel;
    std::unique_ptr<Label> arpDirectionLabel;
    std::unique_ptr<Label> arpOctaveLabel;
    std::unique_ptr<Label> arpPatternLabel;
    std::unique_ptr<Label> arpDivisionLabel;
    std::unique_ptr<Label> arpDurationLabel;
    std::unique_ptr<Label> arpLatchLabel;
    std::unique_ptr<ComboBox> arpDirectionCombo;
    std::unique_ptr<Slider> arpOctavleSlider;
    std::unique_ptr<ComboBox> arpPatternCombo;
    std::unique_ptr<ComboBox> arpDivisionCombo;
    std::unique_ptr<ComboBox> arpDurationCombo;
    std::unique_ptr<ComboBox> arpLatchCombo;
    std::unique_ptr<GroupComponent> filterGroupComponent;
    std::unique_ptr<Label> filterParam1Label;
    std::unique_ptr<Slider> filterParam1Slider;
    std::unique_ptr<Label> filterParam2Label;
    std::unique_ptr<Slider> filterParam2Slider;
    std::unique_ptr<Label> filterGainLabel;
    std::unique_ptr<Slider> filterGainSlider;
    std::unique_ptr<ComboBox> arpClockComboBox;
    std::unique_ptr<Label> clockLabel;
    std::unique_ptr<ComboBox> filterComboBox;


    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PanelArpAndFilter)
};

//[EndFile] You can add extra defines here...
//[/EndFile]

