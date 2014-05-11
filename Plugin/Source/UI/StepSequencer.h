/*
  ==============================================================================

    StepSequencer.h
    Created: 7 Apr 2014 9:40:09pm
    Author:  xhosxe

  ==============================================================================
*/

#ifndef STEPSEQUENCER_H_INCLUDED
#define STEPSEQUENCER_H_INCLUDED

#include "JuceHeader.h"
#include "StepSequencerListener.h"

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
    void setValues(int x, int y);
    int getValue(int step) const { if (step <numberOfValues) return values[step]; else return 0; }
//    void setMidiBuffer(MidiBuffer* eventsToAdd) {
//        this->eventsToAdd = eventsToAdd;
//    }
//    void sendNrpn (int nrpnParam, int nrpnValue);
//    void handleIncomingNrpn(int param, int value);

    void paint (Graphics&);
    void resized();


    /**
     * Enveloppe Listener Methods
     */
    void addListener(StepSequencerListener *listener) {
        listeners.push_back(listener);
    }

    void removeListener(StepSequencerListener *listener) {
        StepSequencerListenerList::iterator iterator = listeners.begin();
        while(iterator != listeners.end() && listeners.size() > 0) {
            if(*iterator == listener) {
                iterator = listeners.erase(iterator);
            }
            else {
                ++iterator;
            }
        }
    }

    void notifyObservers(int pointNumber) const {
        for(StepSequencerListenerList::const_iterator iterator = listeners.begin(); iterator != listeners.end(); ++iterator) {
            (*iterator)->stepSeqSequencerChanged(this, pointNumber);
        }
    }



private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (StepSequencer)

	int numberOfValues;
    int maxValue;
	int* values;
	bool dragging;
	StepSequencerListenerList listeners;
	// DEBUG
	float debugValue;
};


#endif  // STEPSEQUENCER_H_INCLUDED
