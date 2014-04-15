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

#ifndef __JUCE_HEADER_28A483671129C6B8__
#define __JUCE_HEADER_28A483671129C6B8__

//[Headers]     -- You can add your own extra header files here --
#include "JuceHeader.h"
#include "StepSequencer.h"
#include "EnveloppeFree1.h"
#include "EnveloppeFree2.h"

#define NUMBER_OF_STEP_SEQ 2
#define NUMBER_OF_LFO 3

#define NUMBER_OF_MATRIX_ROW 12
//[/Headers]



//==============================================================================
/**
                                                                    //[Comments]
    An auto-generated component, created by the Introjucer.

    Describe your class and how it works here!
                                                                    //[/Comments]
*/
class PanelModulation  : public Component,
                         public Slider::Listener,
                         public Button::Listener,
                         public ComboBox::Listener
{
public:
    //==============================================================================
    PanelModulation ();
    ~PanelModulation();

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.
    void setMidiOutput(MidiOutput* midiOutput);
    void buttonClicked (Button* buttonThatWasClicked);
    void sliderValueChanged (Slider* sliderThatWasMoved);
    void comboBoxChanged (ComboBox* comboBoxThatHasChanged);
    void handleIncomingNrpn(int param, int value);

    //[/UserMethods]

    void paint (Graphics& g);
    void resized();



private:
    //[UserVariables]   -- You can add your own custom variables in this section.
    ScopedPointer<StepSequencer> stepSequencer[NUMBER_OF_STEP_SEQ];
    ScopedPointer<TextButton> stepSeqButton [NUMBER_OF_STEP_SEQ];

    // LFO
    ScopedPointer<TextButton> lfoButton [NUMBER_OF_LFO];
    ScopedPointer<ComboBox> lfoShape[NUMBER_OF_LFO];
    ScopedPointer<ComboBox> lfoExtMidiSync[NUMBER_OF_LFO];
    ScopedPointer<Slider> lfoFrequency[NUMBER_OF_LFO];
    ScopedPointer<Slider> lfoBias[NUMBER_OF_LFO];
    ScopedPointer<ComboBox> lfoKsynOnOff[NUMBER_OF_LFO];
    ScopedPointer<Slider> lfoKSync[NUMBER_OF_LFO];
    ScopedPointer<Label> lfoFrequencyLabel;
    ScopedPointer<Label> lfoBiasLabel;
    ScopedPointer<Label> lfoKSynLabel;



    // MATRIX
    ScopedPointer<Label> matrixRowLabel [NUMBER_OF_MATRIX_ROW];
    ScopedPointer<ComboBox> matrixSource[NUMBER_OF_MATRIX_ROW];
    ScopedPointer<Slider> matrixMultipler[NUMBER_OF_MATRIX_ROW];
    ScopedPointer<ComboBox> matrixDestination[NUMBER_OF_MATRIX_ROW];

    ScopedPointer<EnveloppeFree1> enveloppeFree1;
    ScopedPointer<EnveloppeFree2> enveloppeFree2;
    MidiOutput *midiOutput;
    //[/UserVariables]

    //==============================================================================
    ScopedPointer<GroupComponent> matrixGroup;
    ScopedPointer<GroupComponent> lfoGroup;
    ScopedPointer<GroupComponent> env1Group;
    ScopedPointer<GroupComponent> env2Group;
    ScopedPointer<GroupComponent> stepSeqGroup;


    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PanelModulation)
};

//[EndFile] You can add extra defines here...
//[/EndFile]

#endif   // __JUCE_HEADER_28A483671129C6B8__
