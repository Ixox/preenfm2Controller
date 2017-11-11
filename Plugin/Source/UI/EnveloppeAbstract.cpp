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
	scaleX = (getWidth() - MARGIN_LEFT - MARGIN_RIGHT) / allX;
	// y is always 0 to 1
	scaleY = (float)(getHeight() - MARGIN_TOP - MARGIN_BOTTOM);
	float offsetX = MARGIN_LEFT;
	for (int k = 0; k < pointList.size(); k++) {
		float xPositionOnScreen = offsetX + pointList[k].get()->getX() * scaleX;
		float yPositionOnScreen = getHeight() - pointList[k].get()->getY() * scaleY - MARGIN_BOTTOM;
		pointList[k].get()->setPositionOnScreen(xPositionOnScreen, yPositionOnScreen);
		offsetX = xPositionOnScreen;
	}
}

void EnveloppeAbstract::paint(Graphics& g)
{
	updatePointPositions();

	float lineX = scaleX;
	g.setColour(Colours::grey);
	while (lineX < getWidth() - MARGIN_RIGHT) {
		g.drawVerticalLine((int)(lineX + MARGIN_LEFT), MARGIN_TOP, (float)getHeight() - MARGIN_BOTTOM);
		lineX += scaleX;
	}
	g.drawVerticalLine(MARGIN_LEFT, (float)MARGIN_TOP, (float)getHeight() - MARGIN_BOTTOM);
	g.drawVerticalLine(getWidth() - MARGIN_RIGHT, (float)MARGIN_TOP, (float)getHeight() - MARGIN_BOTTOM);
	g.drawHorizontalLine(MARGIN_TOP, (float)MARGIN_LEFT, (float)getWidth() - MARGIN_RIGHT);
	g.drawHorizontalLine(getHeight() - MARGIN_BOTTOM, (float)MARGIN_LEFT, (float)getWidth() - MARGIN_RIGHT);

	// Draw main enveloppe shapr
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




	for (int p = 0; p < pointList.size(); p++) {
		if (draggingPointIndex == p) {
			g.setColour(Colours::yellow);
			g.fillEllipse((float)pointList[p].get()->getPositionOnScreenX() - CIRCLE_RAY,
				(float)pointList[p].get()->getPositionOnScreenY() - CIRCLE_RAY,
				CIRCLE_RAY*2.0f, CIRCLE_RAY*2.0f);

			if (!pointList[p].get()->isYConstrained()) {
				g.drawVerticalLine((int)pointList[p].get()->getPositionOnScreenX(), (float)MARGIN_TOP, (float)getHeight() - MARGIN_BOTTOM);
			}
			if (!pointList[p].get()->isXConstrained()) {
				g.drawHorizontalLine((int)pointList[p].get()->getPositionOnScreenY(), (float)MARGIN_LEFT, (float)getWidth() - MARGIN_RIGHT);
			}
		}
		else {
			if (overPointIndex == p) {
				g.setColour(Colours::yellow);
				if (!pointList[p].get()->isYConstrained()) {
					g.drawVerticalLine((int)pointList[p].get()->getPositionOnScreenX(), (float)MARGIN_TOP, (float)getHeight() - MARGIN_BOTTOM);
				}
				if (!pointList[p].get()->isXConstrained()) {
					g.drawHorizontalLine((int)pointList[p].get()->getPositionOnScreenY(), (float)MARGIN_LEFT, (float)getWidth() - MARGIN_RIGHT);
				}
				g.drawEllipse((float)pointList[p].get()->getPositionOnScreenX() - CIRCLE_RAY,
					(float)pointList[p].get()->getPositionOnScreenY() - CIRCLE_RAY,
					CIRCLE_RAY * 2.0f, CIRCLE_RAY * 2.0f, 1.0f);
			}
			else {
				g.setColour(Colours::whitesmoke);
				g.fillEllipse((float)pointList[p].get()->getPositionOnScreenX() - 2,
					(float)pointList[p].get()->getPositionOnScreenY() - 2,
					4.0f, 4.0f);
			}
		}
	}

}


void EnveloppeAbstract::mouseMove(const MouseEvent &event) {

	for (int p = pointList.size() - 1; p >= 0; p--) {
		if (abs(event.x - pointList[p].get()->getPositionOnScreenX()) < (CIRCLE_RAY + 2)
			&& abs(event.y - pointList[p].get()->getPositionOnScreenY()) < (CIRCLE_RAY + 2)) {
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

void EnveloppeAbstract::mouseExit(const MouseEvent &event) {
	overPointIndex = -1;
	setMouseCursor(MouseCursor::NormalCursor);
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
	for (int p = pointList.size() - 1; p >= 0; p--) {
		if (abs(event.x - pointList[p].get()->getPositionOnScreenX()) < (CIRCLE_RAY + 2)
			&& abs(event.y - pointList[p].get()->getPositionOnScreenY()) < (CIRCLE_RAY + 2)) {
			draggingPointIndex = p;
			startDragX = (float)event.x;
			startDragY = (float)event.y;
			repaint();
			return;
		}
	}
}

void EnveloppeAbstract::mouseUp(const MouseEvent &event) {
	if (draggingPointIndex != -1) {
		Desktop::setMousePosition(Point<int>((int)(getScreenX() + pointList[draggingPointIndex].get()->getPositionOnScreenX()),
			(int)(getScreenY() + pointList[draggingPointIndex].get()->getPositionOnScreenY())));
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

void EnveloppeAbstract::resized()
{
	// This method is where you should set the bounds of any child
	// components that your component contains..
}

int EnveloppeAbstract::getNumberOfPoints() const { return pointList.size(); }
float EnveloppeAbstract::getX(int index) const { return pointList[index].get()->getX(); }
float EnveloppeAbstract::getY(int index) const { return pointList[index].get()->getY(); }
void EnveloppeAbstract::setX(int index, float x) { pointList[index].get()->setX(x); }
void EnveloppeAbstract::setY(int index, float y) { pointList[index].get()->setY(y); }


