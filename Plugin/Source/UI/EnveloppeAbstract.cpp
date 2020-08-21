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
    this->mouseOver = MOUSE_OVER_NONE;
}

EnveloppeAbstract::~EnveloppeAbstract()
{
}

void EnveloppeAbstract::updatePointPositions() {
	float allX = 0;
	for (int p = 0; p < pointList.size(); p++) {
		allX += pointList[p].get()->getX();
	}

	allX = allX < this->xMax ? this->xMax : allX;
	scaleX = (getWidth() - MARGIN_HORIZONTAL - MARGIN_HORIZONTAL) / allX;
    scaleY = (float)(getHeight() - MARGIN_VERTICAL - MARGIN_VERTICAL);
	float offsetX = MARGIN_HORIZONTAL;
	for (int k = 0; k < pointList.size(); k++) {
		float xPositionOnScreen = offsetX + pointList[k].get()->getX() * scaleX;
		float yPositionOnScreen = getHeight() - pointList[k].get()->getY() * scaleY - MARGIN_VERTICAL;
		pointList[k].get()->setPositionOnScreen(xPositionOnScreen, yPositionOnScreen);
		offsetX = xPositionOnScreen;
	}
}

void EnveloppeAbstract::paint(Graphics& g)
{
    updatePointPositions();


	float lineX = scaleX;
	g.setColour(Colours::grey);
	while (lineX < getWidth() - MARGIN_HORIZONTAL) {
		g.drawVerticalLine((int)(lineX + MARGIN_HORIZONTAL), MARGIN_VERTICAL, (float)getHeight() - MARGIN_VERTICAL);
		lineX += scaleX;
	}
	g.drawVerticalLine(MARGIN_HORIZONTAL, (float)MARGIN_VERTICAL, (float)getHeight() - MARGIN_VERTICAL);
	g.drawVerticalLine(getWidth() - MARGIN_HORIZONTAL, (float)MARGIN_VERTICAL, (float)getHeight() - MARGIN_VERTICAL);
	g.drawHorizontalLine(MARGIN_VERTICAL, (float)MARGIN_HORIZONTAL, (float)getWidth() - MARGIN_HORIZONTAL);
	g.drawHorizontalLine(getHeight() - MARGIN_VERTICAL, (float)MARGIN_HORIZONTAL, (float)getWidth() - MARGIN_HORIZONTAL);

	// Draw main enveloppe shape
	g.setColour(Colours::whitesmoke);
	Path path;
	path.startNewSubPath(pointList[0].get()->getPositionOnScreenX(),
		pointList[0].get()->getPositionOnScreenY());
	for (int p = 1; p < pointList.size(); p++) {
		path.lineTo(pointList[p].get()->getPositionOnScreenX(),
			pointList[p].get()->getPositionOnScreenY());
	}
	g.setColour(Colours::whitesmoke);
	g.strokePath(path, PathStrokeType(1.8f, PathStrokeType::beveled, PathStrokeType::rounded));

	// Back to bottom
	path.lineTo(pointList[pointList.size() - 1].get()->getPositionOnScreenX(),
		pointList[0].get()->getPositionOnScreenY());

	// Back to first point
	path.lineTo(pointList[0].get()->getPositionOnScreenX(),
		pointList[0].get()->getPositionOnScreenY());
	g.setColour(Colour(0x33bbbbbb));
	g.fillPath(path);


    for (int p = 1; p < pointList.size(); p++) {
        if (draggingPointIndex == p || overPointIndex == p) {

            if (isMouseOverX() || (draggingPointIndex == p && !pointList[p].get()->isXLocked())) {
                g.setColour(Colours::yellow);
            }
            else {
                g.setColour(Colours::whitesmoke);
            }
            g.drawHorizontalLine((int)pointList[p].get()->getPositionOnScreenY(), (float)MARGIN_HORIZONTAL, (float)getWidth() - MARGIN_HORIZONTAL);

            if (isMouseOverY() || (draggingPointIndex == p && !pointList[p].get()->isYLocked())) {
                g.setColour(Colours::yellow);
            }
            else {
                g.setColour(Colours::whitesmoke);
            }
            g.drawVerticalLine((int)pointList[p].get()->getPositionOnScreenX(), (float)MARGIN_VERTICAL, (float)getHeight() - MARGIN_VERTICAL);

            g.setColour(Colours::yellow);
            if (draggingPointIndex == p) {
                g.fillEllipse((float)pointList[p].get()->getPositionOnScreenX() - CIRCLE_RAY,
                    (float)pointList[p].get()->getPositionOnScreenY() - CIRCLE_RAY,
                    CIRCLE_RAY*2.0f, CIRCLE_RAY*2.0f);
            }
            else {
                g.drawEllipse((float)pointList[p].get()->getPositionOnScreenX() - CIRCLE_RAY,
                    (float)pointList[p].get()->getPositionOnScreenY() - CIRCLE_RAY,
                    CIRCLE_RAY * 2.0f, CIRCLE_RAY * 2.0f, 1.0f);
            }
		}
        else {
            g.setColour(Colours::whitesmoke);

            g.fillEllipse((float)pointList[p].get()->getPositionOnScreenX() - 2,
                (float)pointList[p].get()->getPositionOnScreenY() - 2,
                5.0f, 5.0f);
        }
	}
}


void EnveloppeAbstract::mouseMove(const MouseEvent &event) {
    if (abs(oldMouseX - event.x) <= 2 && abs(oldMouseY - event.y) <= 2) {
        // Prevent switching point when mouse wheel
        return;
    }

    oldMouseX = event.x;
    oldMouseY = event.y;

    float smallestDistance = 999999999999;
    MouseOverEnum oldMouseOver = mouseOver;
    int oldOverPointIndex = overPointIndex;
    int closestPoint = 0;


    // Distance to lines
    for (int p = 0; p < pointList.size(); p++) {

        if (pointList[p].get()->isXLocked() && pointList[p].get()->isYLocked()) {
            continue;
        }

        float distanceX = abs(event.x - pointList[p].get()->getPositionOnScreenX());
        float distanceY = abs(event.y - pointList[p].get()->getPositionOnScreenY());
        // Handicap for far distance
        float distance = sqrt(distanceX * distanceX + distanceY * distanceY) / getWidth();
        distanceX += distance * 20;
        distanceY += distance * 20;

        if (distanceX < smallestDistance) {
            if (!pointList[p].get()->isYLocked()) {
                mouseOver = MOUSE_OVER_Y;
            }
            else {
                mouseOver = MOUSE_OVER_X;
            }
            overPointIndex = p;
            closestPoint = p;
            smallestDistance = distanceX;
        }

        if (distanceY < smallestDistance) {
            //if (distanceY == smallestDistance && distanceX <= abs(event.x - pointList[closestPoint].get()->getPositionOnScreenX())) {
            //    DBG("ICI");
            //}
            if (!pointList[p].get()->isXLocked()) {
                mouseOver = MOUSE_OVER_X;
            }
            else {
                mouseOver = MOUSE_OVER_Y;
            }
            overPointIndex = p;
            closestPoint = p;
            smallestDistance = distanceY;
        }
    }

    if (oldOverPointIndex != overPointIndex || oldMouseOver != mouseOver) {
		repaint();
	}
    return;
}

void EnveloppeAbstract::mouseExit(const MouseEvent &event) {
    this->mouseOver = MOUSE_OVER_NONE;
	overPointIndex = -1;
    draggingPointIndex = -1;
	repaint();
}

void EnveloppeAbstract::mouseDown(const MouseEvent &event) {
	if (overPointIndex != -1) {
		draggingPointIndex = overPointIndex;
		startDragX = (float)event.x;
		startDragY = (float)event.y;
		repaint();
		return;
	}
}

void EnveloppeAbstract::mouseUp(const MouseEvent &event) {
	if (draggingPointIndex != -1) {
		draggingPointIndex = -1;
	}
	setMouseCursor(MouseCursor::NormalCursor);
	repaint();
}

void EnveloppeAbstract::mouseDrag(const MouseEvent &event) {
	if (draggingPointIndex == -1) {
		return;
	}
	float slowMoveRatio = (event.mods.isCtrlDown() || event.mods.isRightButtonDown() ? .05f : 1.0f);
	float oldVX = pointList[draggingPointIndex].get()->getX();
	pointList[draggingPointIndex].get()->setX(pointList[draggingPointIndex].get()->getX() + (event.x - startDragX) / scaleX * slowMoveRatio);
	float oldVY = pointList[draggingPointIndex].get()->getY();
	pointList[draggingPointIndex].get()->setY(pointList[draggingPointIndex].get()->getY() - (event.y - startDragY) / scaleY * slowMoveRatio);
	if (oldVX != pointList[draggingPointIndex].get()->getX()) {
		// Tell listeners
		notifyObservers(draggingPointIndex, true);
		startDragX = (float)event.x;
	}
	if (oldVY != pointList[draggingPointIndex].get()->getY()) {
		// Tell listeners
		notifyObservers(draggingPointIndex, false);
		startDragY = (float)event.y;
	}
	repaint();
}

void EnveloppeAbstract::mouseWheelMove(const MouseEvent& e, const MouseWheelDetails& wheel) {
    if (overPointIndex != -1) {
        float delta = e.mods.isCtrlDown() ? .01f : .05f;
        if (isMouseOverX()) {
            pointList[overPointIndex].get()->setX(pointList[overPointIndex].get()->getX() + (wheel.deltaY < 0 ? -delta : delta));
            notifyObservers(overPointIndex, true);
            repaint();
        }
        else if (isMouseOverY()) {
            pointList[overPointIndex].get()->setY(pointList[overPointIndex].get()->getY() + (wheel.deltaY < 0 ? -delta : delta));
            notifyObservers(overPointIndex, false);
            repaint();
        }
    }
}

void EnveloppeAbstract::resized()
{
	// This method is where you should set the bounds of any child
	// components that your component contains..
}

int EnveloppeAbstract::getNumberOfPoints() const { return pointList.size(); }
float EnveloppeAbstract::getX(int index) const { return pointList[index].get()->getX(); }
float EnveloppeAbstract::getY(int index) const { return pointList[index].get()->getY(); }

void EnveloppeAbstract::setX(int index, float x) { 
    pointList[index].get()->setX(x); 
}

void EnveloppeAbstract::setY(int index, float y) { 
    pointList[index].get()->setY(y); 
}


