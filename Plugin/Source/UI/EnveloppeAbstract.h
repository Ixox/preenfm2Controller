/*
  ==============================================================================

    EnveloppeAbtract.h
    Created: 10 Apr 2014 1:05:32pm
    Author:  xhosxe

  ==============================================================================
*/

#ifndef ENVELOPPEABTRACT_H_INCLUDED
#define ENVELOPPEABTRACT_H_INCLUDED

#include <stdlib.h>
#include "../JuceLibraryCode/modules/juce_audio_devices/midi_io/juce_MidiOutput.h"
#include "../JuceLibraryCode/modules/juce_core/containers/juce_LinkedListPointer.h"
#include "../JuceLibraryCode/modules/juce_graphics/contexts/juce_GraphicsContext.h"
#include "../JuceLibraryCode/modules/juce_gui_basics/components/juce_Component.h"
#include "EnveloppeListener.h"

namespace juce { class MouseEvent; }

#define CIRCLE_RAY 4
#define MARGIN_TOP CIRCLE_RAY
#define MARGIN_BOTTOM CIRCLE_RAY
#define MARGIN_LEFT CIRCLE_RAY
#define MARGIN_RIGHT CIRCLE_RAY

#define RIGHT_TEXT_SIZE  120

#include "JuceHeader.h"

typedef std::vector<EnveloppeListener *> EnveloppeListenerList;

//==============================================================================

class EnveloppePoint {
    friend class LinkedListPointer<EnveloppePoint>;
public:
    EnveloppePoint(float xMin, float xMax, float yMin, float yMax) {
        this->x = 0.0f;
        this->y = 0.0f;
        this->xMin = xMin;
        this->yMin = yMin;
        this->xMax = xMax;
        this->yMax = yMax;
        this->positionInComponentX = 0;
        this->positionInComponentY = 0;
    }
    void setX(float x) { this->x =  x > xMax ? xMax : (x < xMin ? xMin : x); }
    void setY(float y) { this->y =  y > yMax ? yMax : (y < yMin ? yMin : y); }

    void setXFixedValue(float value) { this->x = value; this-> xMax = value; this-> xMin = value;}
    void setYFixedValue(float value) { this->y = value; this-> yMax = value; this-> yMin = value;}
    bool isXConstrained() { return this->xMax == this-> xMin; };
    bool isYConstrained() { return this->yMax == this-> yMin; };
    float getX() { return this->x; }
    float getY() { return this->y; }
    float getPositionOnScreenX() { return this->positionInComponentX; }
    float getPositionOnScreenY() { return this->positionInComponentY; }
    void setPositionOnScreen(float xOnScreen, float yOnScreen) {
        this->positionInComponentX = xOnScreen;
        this->positionInComponentY = yOnScreen;
    }
private:
    // A linkable object must contain a member with this name and type, which must be
    // accessible by the LinkedListPointer class. (This doesn't mean it has to be public -
    // you could make your class a friend of a LinkedListPointer<MyObject> instead).
    LinkedListPointer<EnveloppePoint> nextListItem;
    float x, xMin, xMax;
    float y, yMin, yMax;
    float positionInComponentX;
    float positionInComponentY;
};


class EnveloppeAbstract : public Component
{
public:
    EnveloppeAbstract();
    ~EnveloppeAbstract();

    void paint (Graphics&);
    virtual void resized();
    void updatePointPositions();
    void setXMax(float x) { xMax = x; }
    void mouseMove(const MouseEvent &event) ;
    void mouseDrag (const MouseEvent &event);
    void mouseDown(const MouseEvent &event);
    void mouseUp(const MouseEvent &event);
    void setMidiBuffer(MidiBuffer* eventsToAdd) {
        this->eventsToAdd = eventsToAdd;
    }
    void sendNrpn (int nrpnParam, int nrpnValue);

    // Can be implemented to deal with point value modification
    virtual void newXValue(int draggingPointIndex, float newX) {};
    virtual void newYValue(int draggingPointIndex, float newY) {};

    int getNumberOfPoints() const { return pointList.size(); }
    float getX(int index) const { return pointList[index].get()->getX(); }
    float getY(int index) const { return pointList[index].get()->getY(); }
    void setX(int index, float x) { pointList[index].get()->setX(x); }
    void setY(int index, float y) { pointList[index].get()->setY(y); }

    virtual const char ** getPointSuffix() const = 0;


    /**
     * Enveloppe Listener Methods
     */
    void addListener(EnveloppeListener *listener) {
    	listeners.push_back(listener);
    }

    void removeListener(EnveloppeListener *listener) {
        EnveloppeListenerList::iterator iterator = listeners.begin();
        while(iterator != listeners.end() && listeners.size() > 0) {
            if(*iterator == listener) {
                iterator = listeners.erase(iterator);
            }
            else {
                ++iterator;
            }
        }
    }

    void notifyObservers(int pointNumber, bool isX) const {
        for(EnveloppeListenerList::const_iterator iterator = listeners.begin(); iterator != listeners.end(); ++iterator) {
            (*iterator)->enveloppeValueChanged(this, pointNumber, isX);
        }
    }


protected:
    LinkedListPointer<EnveloppePoint> pointList;
    volatile int draggingPointIndex;
    int overPointIndex;
    MidiBuffer* eventsToAdd;
    EnveloppeListenerList listeners;

private:

    float xMax;
    float scaleX, scaleY;
    float startDragX, startDragY;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (EnveloppeAbstract)

};


#endif  // ENVELOPPEABTRACT_H_INCLUDED
