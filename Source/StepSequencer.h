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
    StepSequencer(int numberOfValues, int maxValue);
    ~StepSequencer();
    void mouseDrag (const MouseEvent &event);
    void mouseDown(const MouseEvent &event);
    void mouseUp(const MouseEvent &event);
    void mouseDoubleClick (const MouseEvent& event) override;
    void mouseWheelMove (const MouseEvent& event, const MouseWheelDetails& wheel);
    int  limitX(int x);
    int  limitY(int y);
    bool updateValues(const MouseEvent& event);

    void paint (Graphics&);
    void resized();

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (StepSequencer)

	int numberOfValues;
    int maxValue;
	int* values;
	bool dragging;

	// DEBUG
	float debugValue;
};


#endif  // STEPSEQUENCER_H_INCLUDED
