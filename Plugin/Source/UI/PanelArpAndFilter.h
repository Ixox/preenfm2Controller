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

#ifndef __JUCE_HEADER_1D750F415828AF8__
#define __JUCE_HEADER_1D750F415828AF8__

//[Headers]     -- You can add your own extra header files here --
#include "JuceHeader.h"
#include "MidifiedComponent.h"
#include "PanelOfParameters.h"

//[/Headers]



//==============================================================================
/**
                                                                    //[Comments]
    An auto-generated component, created by the Introjucer.

    Describe your class and how it works here!
                                                                    //[/Comments]
*/
class PanelArpAndFilter  : public Component,
                           public PanelOfParameters,
                           public SliderListener,
                           public ComboBoxListener
{
public:
    //==============================================================================
    PanelArpAndFilter ();
    ~PanelArpAndFilter();

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.
    void setMidiOutput(MidiOutput* midiOutput);
    void handleIncomingNrpn(int param, int value);
    void arpIsNow(bool arpOn, bool enableBPM);
    void filterIsNow(bool paramOn1, bool paramOn2);
    void setMidiBuffer(MidiBuffer& eventsToAdd) { this->eventsToAdd = &eventsToAdd; }
    void buildParameters();
    void onParameterUpdated(const teragon::Parameter *parameter);
    void comboBoxChanged (ComboBox* comboBoxThatHasChanged, bool fromPluginUI);
    void sliderValueChanged (Slider* sliderThatWasMoved, bool fromPluginUI);
    void updateComboParameter_hook(ComboBox* combo);
    void updateSliderParameter_hook(Slider* slider);
    //[/UserMethods]

    void paint (Graphics& g);
    void resized();
    void sliderValueChanged (Slider* sliderThatWasMoved);
    void comboBoxChanged (ComboBox* comboBoxThatHasChanged);



private:
    //[UserVariables]   -- You can add your own custom variables in this section.
    MidiBuffer* eventsToAdd;
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

#endif   // __JUCE_HEADER_1D750F415828AF8__
