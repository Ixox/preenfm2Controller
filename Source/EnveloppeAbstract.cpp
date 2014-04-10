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
    this->xMax = 4.0;
    this->midiOutput = nullptr;
}

EnveloppeAbstract::~EnveloppeAbstract()
{
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
            if (!pointList[p].get()->isYConstrained()) {
            	g.drawVerticalLine((int)pointList[p].get()->getPositionOnScreenX(), MARGIN_TOP, getHeight() - MARGIN_BOTTOM);
            }
            if (!pointList[p].get()->isXConstrained()) {
            	g.drawHorizontalLine((int)pointList[p].get()->getPositionOnScreenY(), MARGIN_LEFT, getWidth() - MARGIN_RIGHT);
            }
        } else {
            if (overPointIndex == p) {
                g.setColour (Colours::red);
                if (!pointList[p].get()->isYConstrained()) {
                	g.drawVerticalLine((int)pointList[p].get()->getPositionOnScreenX(), MARGIN_TOP, getHeight() - MARGIN_BOTTOM);
                }
                if (!pointList[p].get()->isXConstrained()) {
                	g.drawHorizontalLine((int)pointList[p].get()->getPositionOnScreenY(), MARGIN_LEFT, getWidth() - MARGIN_RIGHT);
                }
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
        if (abs(event.x - pointList[p].get()->getPositionOnScreenX()) < 5
                && abs(event.y - pointList[p].get()->getPositionOnScreenY()) < 5) {
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
    for (int p = 0 ; p< pointList.size(); p++) {
        if (abs(event.x - pointList[p].get()->getPositionOnScreenX()) < 5
                && abs(event.y - pointList[p].get()->getPositionOnScreenY()) < 5) {
            draggingPointIndex = p  ;
            startDragX = event.x;
            startDragY = event.y;
//            setMouseCursor(MouseCursor::NoCursor);
            repaint();
            return;
        }
    }
}

void EnveloppeAbstract::mouseUp (const MouseEvent &event)  {
    if (draggingPointIndex != -1) {
        Desktop::setMousePosition(Point<int>(getScreenX() + pointList[draggingPointIndex].get()->getPositionOnScreenX(),
                getScreenY() + pointList[draggingPointIndex].get()->getPositionOnScreenY()));
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
    float oldVX = pointList[draggingPointIndex].get()->getX();
    pointList[draggingPointIndex].get()->setX(pointList[draggingPointIndex].get()->getX() + (float)(event.x - startDragX) / scaleX * slowMoveRatio);
    float oldVY = pointList[draggingPointIndex].get()->getY();
    pointList[draggingPointIndex].get()->setY(pointList[draggingPointIndex].get()->getY() - (float)(event.y - startDragY) / scaleY * slowMoveRatio);
    if (oldVX != pointList[draggingPointIndex].get()->getX()) {
    	newXValue(draggingPointIndex, pointList[draggingPointIndex].get()->getX());
        startDragX = event.x;
    }
    if (oldVY != pointList[draggingPointIndex ].get()->getY()) {
    	newYValue(draggingPointIndex, pointList[draggingPointIndex].get()->getY());
        startDragY = event.y;
    }
    repaint();
}

void EnveloppeAbstract::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains..
}


void EnveloppeAbstract::sendNrpn (int nrpnParam, int nrpnValue) {
	if (midiOutput != nullptr) {
		midiOutput->sendMessageNow(MidiMessage::controllerEvent(1, 99, (nrpnParam >> 7)));
		midiOutput->sendMessageNow(MidiMessage::controllerEvent(1, 98, (nrpnParam & 0xFF)));
		midiOutput->sendMessageNow(MidiMessage::controllerEvent(1, 6, (nrpnValue >> 7)));
		midiOutput->sendMessageNow(MidiMessage::controllerEvent(1, 38, (nrpnValue & 0xFF)));
	}
}
