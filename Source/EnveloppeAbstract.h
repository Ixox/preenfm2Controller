/*
  ==============================================================================

    EnveloppeAbtract.h
    Created: 10 Apr 2014 1:05:32pm
    Author:  xhosxe

  ==============================================================================
*/

#ifndef ENVELOPPEABTRACT_H_INCLUDED
#define ENVELOPPEABTRACT_H_INCLUDED

#define CIRCLE_RAY 4
#define MARGIN_TOP CIRCLE_RAY
#define MARGIN_BOTTOM CIRCLE_RAY
#define MARGIN_LEFT CIRCLE_RAY
#define MARGIN_RIGHT CIRCLE_RAY

#define RIGHT_TEXT_SIZE  120

#include "../JuceLibraryCode/JuceHeader.h"

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
    void resized();
    void updatePointPositions();
    void setXMax(float x) { xMax = x; }
    void mouseMove(const MouseEvent &event) ;
    void mouseDrag (const MouseEvent &event);
    void mouseDown(const MouseEvent &event);
    void mouseUp(const MouseEvent &event);

    class JUCE_API  Listener
    {
    public:
        virtual ~Listener() {}
        virtual void enveloppeValueChanged (int nrpnParam, float value) = 0;
    };
protected:
    LinkedListPointer<EnveloppePoint> pointList;
    ListenerList <EnveloppeAbstract::Listener> listeners;
    int draggingPointIndex, overPointIndex;

private:

    float xMax;
    float scaleX, scaleY;
    float startDragX, startDragY;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (EnveloppeAbstract)

};


#endif  // ENVELOPPEABTRACT_H_INCLUDED
