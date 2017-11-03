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
