/*
  ==============================================================================

    StepSequencer.h
    Created: 7 Apr 2014 9:40:09pm
    Author:  xhosxe

  ==============================================================================
*/

#ifndef STEPSEQUENCER_H_INCLUDED
#define STEPSEQUENCER_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"

//==============================================================================
/*
*/
class StepSequencer    : public Component
{
public:
    StepSequencer(int numberOfValues, int maxValue, int nrpnBase);
    ~StepSequencer();
    void mouseDrag (const MouseEvent &event);
    void mouseDown(const MouseEvent &event);
    void mouseUp(const MouseEvent &event);
    void mouseDoubleClick (const MouseEvent& event) override;
    void mouseWheelMove (const MouseEvent& event, const MouseWheelDetails& wheel);
    int  limitX(int x);
    int  limitY(int y);
    void updateValues(const MouseEvent& event);
    void setMidiOutput(MidiOutput *midiOutput) { this->midiOutput = midiOutput; }
    void sendNrpn (int nrpnParam, int nrpnValue);
    void setValues(int x, int y);
    void handleIncomingNrpn(int param, int value);

    void paint (Graphics&);
    void resized();

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (StepSequencer)

	int numberOfValues;
    int maxValue;
	int* values;
	bool dragging;
	int nrpnBase;
    MidiOutput* midiOutput;

	// DEBUG
	float debugValue;
};


#endif  // STEPSEQUENCER_H_INCLUDED
