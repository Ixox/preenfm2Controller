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

#ifndef __JUCE_HEADER_7380AAF86AC445A4__
#define __JUCE_HEADER_7380AAF86AC445A4__

//[Headers]     -- You can add your own extra header files here --
#include "JuceHeader.h"
#include "Enveloppe.h"

#define NUMBER_OF_OPERATORS 6
#define NUMBER_OF_IM 5
#define NUMBER_OF_MIX 6
#define NUMBER_OF_ALGO 28
//[/Headers]



//==============================================================================
/**
                                                                    //[Comments]
    An auto-generated component, created by the Introjucer.

    Describe your class and how it works here!
                                                                    //[/Comments]
*/
class PanelEngine  : public Component,
                     public Enveloppe::Listener,
                     public Slider::Listener,
                     public Button::Listener,
                     public ComboBox::Listener
{
public:
    //==============================================================================
    PanelEngine ();
    ~PanelEngine();

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.
    void setMidiOutput(MidiOutput* midiOutput) {
    	this->midiOutput = midiOutput;
    }
    void handleIncomingNrpn(int param, int value);
    void sendNrpn(MidiOutput* midiOutput, int param, int value);
    void enveloppeValueChanged (int nrpnParam, float value);
    void buttonClicked (Button* buttonThatWasClicked);
    void sliderValueChanged (Slider* sliderThatWasMoved);
    void comboBoxChanged (ComboBox* comboBoxThatHasChanged);
    void resizeAlgoDrawableImage();
    //[/UserMethods]

    void paint (Graphics& g);
    void resized();



private:
    //[UserVariables]   -- You can add your own custom variables in this section.
    ScopedPointer<Enveloppe> enveloppe[NUMBER_OF_OPERATORS];
    ScopedPointer<TextButton> enveloppeButton [NUMBER_OF_OPERATORS];
    ScopedPointer<Slider> volumeKnob[NUMBER_OF_MIX];
    ScopedPointer<Slider> panKnob[NUMBER_OF_MIX];
    ScopedPointer<Label> mixLabel[NUMBER_OF_MIX];
    ScopedPointer<Label> IMLabel;
    ScopedPointer<Label> IMVelocityLabel;
    ScopedPointer<Label> IMNumber[NUMBER_OF_IM];
    ScopedPointer<Slider> IMKnob[NUMBER_OF_IM];
    ScopedPointer<Slider> IMVelocityKnob[NUMBER_OF_IM];
    ScopedPointer<Label> algoChooserLabel;
    ScopedPointer<Slider> algoChooser;
    ScopedPointer<DrawableImage> algoDrawableImage;
    MidiOutput *midiOutput;
    Image algoImages[NUMBER_OF_ALGO];
    ScopedPointer<Label> velocityLabel;
    ScopedPointer<Slider> velocity;
    ScopedPointer<Label> voicesLabel;
    ScopedPointer<Slider> voices;
    ScopedPointer<Label> glideLabel;
    ScopedPointer<Slider> glide;

    ScopedPointer<Label> opShapeLabel;
    ScopedPointer<ComboBox> opShape[NUMBER_OF_OPERATORS];

    ScopedPointer<Label> opFrequencyTypeLabel;
    ScopedPointer<ComboBox> opFrequencyType[NUMBER_OF_OPERATORS];

    ScopedPointer<Label> opFrequencyLabel;
    ScopedPointer<Slider> opFrequency[NUMBER_OF_OPERATORS];

    ScopedPointer<Label> opFrequencyFineTuneLabel;
    ScopedPointer<Slider> opFrequencyFineTune[NUMBER_OF_OPERATORS];
    //[/UserVariables]

    //==============================================================================
    ScopedPointer<GroupComponent> operatorGroup;
    ScopedPointer<GroupComponent> mixerGroup;
    ScopedPointer<GroupComponent> imGroup;


    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PanelEngine)
};

//[EndFile] You can add extra defines here...
struct AlgoInformation {
    unsigned char osc;
    unsigned char im;
    unsigned char mix;
};
//[/EndFile]

#endif   // __JUCE_HEADER_7380AAF86AC445A4__
