/*
  ==============================================================================

  This is an automatically generated GUI class created by the Projucer!

  Be careful when adding custom code to these files, as only the code within
  the "//[xyz]" and "//[/xyz]" sections will be retained when the file is loaded
  and re-saved.

  Created with Projucer version: 5.1.2

  ------------------------------------------------------------------------------

  The Projucer is part of the JUCE library - "Jules' Utility Class Extensions"
  Copyright (c) 2015 - ROLI Ltd.

  ==============================================================================
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
                           public Slider::Listener,
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
    void updateComboParameter_hook(ComboBox* combo);
    void updateSliderParameter_hook(Slider* slider);
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
