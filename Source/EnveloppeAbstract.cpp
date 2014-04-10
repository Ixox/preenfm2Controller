/*
  ==============================================================================

    EnveloppeAbstract.cpp
    Created: 10 Apr 2014 1:31:09pm
    Author:  xhosxe

  ==============================================================================
*/

#include "../JuceLibraryCode/JuceHeader.h"
#include "EnveloppeAbstract.h"

//==============================================================================
EnveloppeAbstract::EnveloppeAbstract()
{
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.
    this->scaleX = 1;
    this->scaleY = 1;
    this->draggingPointIndex = -1;
    this->overPointIndex = -1;
}

EnveloppeAbstract::~EnveloppeAbstract()
{
}

void EnveloppeAbstract::paint (Graphics& g)
{
    updatePointPositions();

    float lineX = scaleX;
    g.setColour (Colours::grey);
    while (lineX < getWidth() - MARGIN_RIGHT) {
        g.drawVerticalLine((int)(lineX + MARGIN_LEFT), MARGIN_TOP, getHeight()-MARGIN_BOTTOM);
        lineX += scaleX;
    }
    g.drawVerticalLine(MARGIN_LEFT, MARGIN_TOP, getHeight() - MARGIN_BOTTOM);
    g.drawVerticalLine(getWidth() - MARGIN_RIGHT, MARGIN_TOP, getHeight() - MARGIN_BOTTOM);
    g.drawHorizontalLine(MARGIN_TOP, MARGIN_LEFT, getWidth() - MARGIN_RIGHT);
    g.drawHorizontalLine(getHeight() - MARGIN_BOTTOM, MARGIN_LEFT, getWidth() - MARGIN_RIGHT);

//    g.drawLine(pointPositionX[3], pointPositionY[3], pointPositionX[3], getHeight() - MARGIN_BOTTOM);
    // Draw main enveloppe shapr
    g.setColour (Colours::blue);
    for (int p = 0; p < pointList.size() -1; p++) {
        g.drawLine(pointList[p].get()->getPositionOnScreenX(),
                pointList[p].get()->getPositionOnScreenY(),
                pointList[p+1].get()->getPositionOnScreenX(),
                pointList[p+1].get()->getPositionOnScreenY());
    }

    for (int p = 0; p < pointList.size(); p++) {
        if (draggingPointIndex == p) {
            g.setColour (Colours::red);
            g.fillEllipse((int)pointList[p].get()->getPositionOnScreenX() - CIRCLE_RAY,
                    (int)pointList[p].get()->getPositionOnScreenY() - CIRCLE_RAY ,
                    CIRCLE_RAY*2, CIRCLE_RAY*2);
//            g.setColour (Colours::black);
            g.drawVerticalLine((int)pointList[p].get()->getPositionOnScreenX(), MARGIN_TOP, getHeight() - MARGIN_BOTTOM);
            g.drawHorizontalLine((int)pointList[p].get()->getPositionOnScreenY(), MARGIN_LEFT, getWidth() - MARGIN_RIGHT);
        } else {
            if (overPointIndex == p) {
                g.setColour (Colours::red);
            } else {
                g.setColour (Colours::blue);
            }
            g.drawEllipse((int)pointList[p].get()->getPositionOnScreenX() - CIRCLE_RAY,
                    (int)pointList[p].get()->getPositionOnScreenY() - CIRCLE_RAY ,
                    CIRCLE_RAY*2, CIRCLE_RAY*2, 1);
        }
    }

}


void EnveloppeAbstract::mouseMove(const MouseEvent &event)  {

    for (int p = 0 ; p< pointList.size(); p++) {
        if (abs(event.x - pointList[p+1].get()->getX()) < 5
                && abs(event.y - pointList[p+1].get()->getY()) < 5) {
            if (overPointIndex != p) {
                overPointIndex = p;
                setMouseCursor(MouseCursor::PointingHandCursor);
                repaint();
            }
            return;
        }
    }
    if (overPointIndex != -1) {
        overPointIndex = -1;
        setMouseCursor(MouseCursor::NormalCursor);
        repaint();
    }
    return;

}

void EnveloppeAbstract::mouseDown (const MouseEvent &event)  {
    for (int p =1 ; p<5; p++) {
        if (abs(event.x - pointList[p+1].get()->getX()) < 5
                && abs(event.y - pointList[p+1].get()->getY()) < 5) {
            draggingPointIndex = p - 1  ;
            startDragX = event.x;
            startDragY = event.y;
            setMouseCursor(MouseCursor::NoCursor);
            repaint();
            return;
        }
    }
}

void EnveloppeAbstract::mouseUp (const MouseEvent &event)  {
    if (draggingPointIndex != -1) {
        float positionX = 0;
        for (int p=0; p<=draggingPointIndex; p++) {
            positionX += pointList[p * 2].get()->getX() * scaleX;
        }
        Desktop::setMousePosition(Point<int>(getScreenX() + positionX,
                getScreenY() + getHeight() - pointList[draggingPointIndex * 2 + 1].get()->getX() * scaleY));
        draggingPointIndex = -1;
    }
    setMouseCursor(MouseCursor::NormalCursor);
    repaint();
}

void EnveloppeAbstract::mouseDrag (const MouseEvent &event)  {
    if (draggingPointIndex == -1) {
        return;
    }
    float slowMoveRatio = (event.mods.isCtrlDown() || event.mods.isRightButtonDown() ? .05f : 1.0f);
    float oldVX = pointList[draggingPointIndex * 2].get()->getX();
    pointList[draggingPointIndex * 2].get()->setY(pointList[draggingPointIndex * 2].get()->getX() + (float)(event.x - startDragX) / scaleX * slowMoveRatio);
//    if (pointList[draggingPointIndex * 2].get()->getX() < pointList[draggingPointIndex * 2].get()->get) {
//        pointList[draggingPointIndex * 2].get()->getX() = 0.0f;
//    }
//    if (pointList[draggingPointIndex * 2].get()->getX() > 16.0f) {
//        pointList[draggingPointIndex * 2].get()->getX() = 16.0f;
//    }
    float oldVY = pointList[draggingPointIndex * 2 + 1].get()->getX();
    pointList[draggingPointIndex * 2 + 1].get()->setX(pointList[draggingPointIndex * 2 + 1].get()->getX() - (float)(event.y - startDragY) / scaleY * slowMoveRatio);
//    if (pointList[draggingPointIndex * 2 + 1].get()->getX() < 0.0f) {
//        pointList[draggingPointIndex * 2 + 1].get()->getX() = 0.0f;
//    }
//    if (pointList[draggingPointIndex * 2 + 1].get()->getX() > 1.0f) {
//        pointList[draggingPointIndex * 2 + 1].get()->getX() = 1.0f;
//    }
    if (oldVX != pointList[draggingPointIndex * 2].get()->getX() || oldVY != pointList[draggingPointIndex * 2 + 1].get()->getX()) {
        // listeners.call(&Listener::enveloppeValueChanged, nrpnBase + draggingPointIndex * 2, pointList[draggingPointIndex * 2].get()->getX());
        startDragX = event.x;
        startDragY = event.y;
    }
    repaint();
}

void EnveloppeAbstract::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains..

}


void EnveloppeAbstract::updatePointPositions() {
    float allX = 0;
    for (int p=0; p < pointList.size(); p++) {
        allX += pointList[p].get()->getX();
    }

    allX = allX < this->xMax ? this->xMax : allX;
    scaleX = (getWidth() - MARGIN_LEFT - MARGIN_RIGHT) / allX;
    // y is always 0 to 1
    scaleY = getHeight() - MARGIN_TOP - MARGIN_BOTTOM;
    float offsetX = MARGIN_LEFT;
    for (int k = 0; k < pointList.size(); k++ ) {
        float xPositionOnScreen = offsetX + pointList[k].get()->getX() * scaleX;
        float yPositionOnScreen = getHeight() - pointList[k].get()->getY() * scaleY - MARGIN_BOTTOM;
        pointList[k].get()->setPositionOnScreen(xPositionOnScreen, yPositionOnScreen);
        offsetX = xPositionOnScreen;
    }
}

