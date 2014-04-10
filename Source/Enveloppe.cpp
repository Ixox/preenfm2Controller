/*
  ==============================================================================

    Enveloppe.cpp
    Created: 6 Apr 2014 2:32:14pm
    Author:  xhosxe

  ==============================================================================
 */

#include "../JuceLibraryCode/JuceHeader.h"
#include "Enveloppe.h"

#define CIRCLE_RAY 4
#define RIGHT_TEXT_SIZE 120
#define MARGIN_TOP CIRCLE_RAY
#define MARGIN_BOTTOM CIRCLE_RAY
#define MARGIN_LEFT CIRCLE_RAY
#define MARGIN_RIGHT CIRCLE_RAY

//==============================================================================
Enveloppe::Enveloppe(int nrpnBase)
{
	// In your constructor, you should add any child components, and
	// initialise any special settings that your component needs.
	this->values[0] = 0.3;
	this->values[1] = 1.0;
	this->values[2] = 0.3;
	this->values[3] = .5;
	this->values[4] = 0.5;
	this->values[5] = 0.6;
	this->values[6] = 0.3;
	this->values[7] = 0.0;

	this->draggingPoint = -1;
	this->overPoint = -1;
	this->nrpnBase = nrpnBase;

}

Enveloppe::~Enveloppe()
{
}

void Enveloppe::updatePosition() {
	float allX = values[0] + values[2] + values[4] + values[6];
	allX = allX < 4.0f ? 4.0f : allX;
	scaleX = (getWidth() - MARGIN_LEFT - MARGIN_RIGHT) / allX;
	scaleY = getHeight() - MARGIN_TOP - MARGIN_BOTTOM;
	float offsetX = 0;

	pointPositionX[0] = MARGIN_LEFT;
	pointPositionY[0] = getHeight() - MARGIN_BOTTOM;

	for (int k = 0; k<4; k++ ) {
		pointPositionX[k+1] = offsetX + values[k*2] * scaleX + MARGIN_LEFT;
		pointPositionY[k+1] = getHeight() - values[k*2+1] * scaleY - MARGIN_BOTTOM;
		offsetX += values[k*2] * scaleX;
	}
}

void Enveloppe::paint (Graphics& g)
{
	/* This demo code just fills the component's background and
       draws some placeholder text to get you started.

       You should replace everything in this method with your own
       drawing code..
	 */
	updatePosition();

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

    g.drawLine(pointPositionX[3], pointPositionY[3], pointPositionX[3], getHeight() - MARGIN_BOTTOM);
	g.setColour (Colours::blue);
	for (int p = 0; p<4; p++) {
		g.drawLine(pointPositionX[p], pointPositionY[p] , pointPositionX[p+1], pointPositionY[p+1]);
	}

	for (int p = 1; p<5; p++) {
		if (draggingPoint == p -1) {
			g.setColour (Colours::red);
			g.fillEllipse((int)pointPositionX[p] - CIRCLE_RAY, (int)pointPositionY[p] - CIRCLE_RAY , CIRCLE_RAY*2, CIRCLE_RAY*2);
//            g.setColour (Colours::black);
            g.drawVerticalLine((int)pointPositionX[p], MARGIN_TOP, getHeight() - MARGIN_BOTTOM);
            g.drawHorizontalLine((int)pointPositionY[p], MARGIN_LEFT, getWidth() - MARGIN_RIGHT);
		} else {
			if (overPoint == p-1) {
				g.setColour (Colours::red);
			} else {
				g.setColour (Colours::blue);
			}
			g.drawEllipse((int)pointPositionX[p] - CIRCLE_RAY, (int)pointPositionY[p] - CIRCLE_RAY , CIRCLE_RAY*2, CIRCLE_RAY*2, 1);
		}
	}

	static const String adsr[] = { "A", "D", "S", "R" } ;
	for (int v=0; v<4; v++) {

		g.setColour (Colours::black);
		g.drawText(adsr[v], getWidth() - RIGHT_TEXT_SIZE , 20 + v* 20, 50, 10, Justification::centred, true);

		if (draggingPoint == v) {
			g.setColour (Colours::red);
		} else {
			g.setColour (Colours::black);
		}

		String posisionX = String(values[v * 2], 2);
		g.drawText(posisionX, getWidth() - RIGHT_TEXT_SIZE / 3 * 2 - 10, 20 + v* 20, 50, 10, Justification::centred, true);
		posisionX = String(values[v * 2  +1] , 2);
		g.drawText(posisionX, getWidth() - RIGHT_TEXT_SIZE / 3 - 10, 20 + v* 20, 50, 10, Justification::centred, true);
	}

}

void Enveloppe::mouseMove(const MouseEvent &event)  {

	for (int p =1 ; p<5; p++) {
		if (abs(event.x - pointPositionX[p]) < 5
				&& abs(event.y - pointPositionY[p]) < 5) {
			if (overPoint != p -1) {
				overPoint = p - 1;
				setMouseCursor(MouseCursor::PointingHandCursor);
				repaint();
			}
			return;
		}
	}
	if (overPoint != -1) {
		overPoint = -1;
		setMouseCursor(MouseCursor::NormalCursor);
		repaint();
	}
	return;

}

void Enveloppe::mouseDown (const MouseEvent &event)  {
	for (int p =1 ; p<5; p++) {
		if (abs(event.x - pointPositionX[p]) < 5
				&& abs(event.y - pointPositionY[p]) < 5) {
			draggingPoint = p - 1  ;
			startDragX = event.x;
			startDragY = event.y;
			cptDebug = 0;
			setMouseCursor(MouseCursor::NoCursor);
			repaint();
			return;
		}
	}
}

void Enveloppe::mouseUp (const MouseEvent &event)  {
    if (draggingPoint != -1) {
        float positionX = 0;
        for (int p=0; p<=draggingPoint; p++) {
            positionX += values[p * 2] * scaleX;
        }
        Desktop::setMousePosition(Point<int>(getScreenX() + positionX,
                getScreenY() + getHeight() - values[draggingPoint * 2 + 1] * scaleY));
        draggingPoint = -1;
    }
    setMouseCursor(MouseCursor::NormalCursor);
	repaint();
}

void Enveloppe::mouseDrag (const MouseEvent &event)  {
	if (draggingPoint == -1) {
		return;
	}
	cptDebug ++;
	float oldVX = values[draggingPoint * 2];
	values[draggingPoint * 2] = values[draggingPoint * 2] + (float)(event.x - startDragX) / scaleX;
	if (values[draggingPoint * 2] < 0.0f) {
		values[draggingPoint * 2] = 0.0f;
	}
	if (values[draggingPoint * 2] > 16.0f) {
		values[draggingPoint * 2] = 16.0f;
	}
	float oldVY = values[draggingPoint * 2 + 1];
	values[draggingPoint * 2 + 1] = values[draggingPoint * 2 + 1] - (float)(event.y - startDragY) / scaleY;
	if (values[draggingPoint * 2 + 1] < 0.0f) {
		values[draggingPoint * 2 + 1] = 0.0f;
	}
	if (values[draggingPoint * 2 + 1] > 1.0f) {
		values[draggingPoint * 2 + 1] = 1.0f;
	}
    if (oldVX != values[draggingPoint * 2] || oldVY != values[draggingPoint * 2 + 1]) {
        listeners.call(&Listener::enveloppeValueChanged, nrpnBase + draggingPoint * 2, values[draggingPoint * 2]);
        startDragX = event.x;
        startDragY = event.y;
    }
	repaint();
}

void Enveloppe::resized()
{
	// This method is where you should set the bounds of any child
	// components that your component contains..

}

void Enveloppe::handleIncomingNrpn(int param, int value) {
	if (param >= nrpnBase && param <= nrpnBase + 8) {
		values[param - nrpnBase] = value / 100.0f;
		repaint();
	}
}

void Enveloppe::addListener (Enveloppe::Listener* const listener)       { listeners.add (listener); }
void Enveloppe::removeListener (Enveloppe::Listener* const listener)    { listeners.remove (listener); }

