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


#pragma once

//[Headers]     -- You can add your own extra header files here --
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
                           public ComboBox::Listener
{
public:
    //==============================================================================
    PanelArpAndFilter ();
    ~PanelArpAndFilter();

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.
    void arpIsNow(bool arpOn, bool enableBPM);
    void filterIsNow(bool paramOn1, bool paramOn2);
    void setMidiBuffer(MidiBuffer& eventsToAdd) { this->eventsToAdd = &eventsToAdd; }
    void buildParameters();
    void comboBoxChanged (ComboBox* comboBoxThatHasChanged, bool fromPluginUI);
    void sliderValueChanged (Slider* sliderThatWasMoved, bool fromPluginUI);
    void updateComboFromParameter_hook(ComboBox* combo);
    void updateSliderFromParameter_hook(Slider* slider);
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
    ScopedPointer<GroupComponent> arpGroupComponent;
    ScopedPointer<Slider> arpBPM;
    ScopedPointer<Label> arpBPMLabel;
    ScopedPointer<Label> arpDirectionLabel;
    ScopedPointer<Label> arpOctaveLabel;
    ScopedPointer<Label> arpPatternLabel;
    ScopedPointer<Label> arpDivisionLabel;
    ScopedPointer<Label> arpDurationLabel;
    ScopedPointer<Label> arpLatchLabel;
    ScopedPointer<ComboBox> arpDirectionCombo;
    ScopedPointer<Slider> arpOctavleSlider;
    ScopedPointer<ComboBox> arpPatternCombo;
    ScopedPointer<ComboBox> arpDivisionCombo;
    ScopedPointer<ComboBox> arpDurationCombo;
    ScopedPointer<ComboBox> arpLatchCombo;
    ScopedPointer<GroupComponent> filterGroupComponent;
    ScopedPointer<Label> filterParam1Label;
    ScopedPointer<Slider> filterParam1Slider;
    ScopedPointer<Label> filterParam2Label;
    ScopedPointer<Slider> filterParam2Slider;
    ScopedPointer<Label> filterGainLabel;
    ScopedPointer<Slider> filterGainSlider;
    ScopedPointer<ComboBox> arpClockComboBox;
    ScopedPointer<Label> clockLabel;
    ScopedPointer<ComboBox> filterComboBox;


    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PanelArpAndFilter)
};

//[EndFile] You can add extra defines here...
//[/EndFile]
