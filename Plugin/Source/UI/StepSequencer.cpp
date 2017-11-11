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


#include "StepSequencer.h"

//==============================================================================
StepSequencer::StepSequencer(int numberOfValues, int maxValue, int nrpnBase)
{
	// In your constructor, you should add any child components, and
	// initialise any special settings that your component needs.

	this->numberOfValues = numberOfValues;
	this->maxValue = maxValue;
	this->values = new int[numberOfValues];
	for (int k = 0; k < numberOfValues; k++) {
		this->values[k] = (int)((float)maxValue / numberOfValues * k);
	}
}

StepSequencer::~StepSequencer()
{
	if (this->values != nullptr) {
		delete this->values;
	}
}

void StepSequencer::paint(Graphics& g)
{
	float width = (float)getWidth() / numberOfValues;

	for (int k = 0; k < numberOfValues; k++) {
		float height = (float)getHeight() * values[k] / (maxValue - 1);
		uint8 alpha = (uint8)(100.0f + height * 70.0f / getHeight());
		g.setColour(Colour::fromRGBA(180, 200, 220, alpha));
		g.fillRect((float)k * width, (float)getHeight() - height, width, height);
	}

	for (int k = 0; k < numberOfValues; k++) {
		g.setColour(Colours::grey);
		g.drawVerticalLine((int)(width * (1.0f + k)), 0.0f, (float)getHeight());

		g.setColour(Colours::whitesmoke);
		g.drawText(String(values[k]), (int)(k * width), getHeight() - 20, (int)width, 10, Justification::centred, true);
	}

	g.setColour(Colours::grey);
	g.drawRect(getLocalBounds(), 1);   // draw an outline around the component
}

int  StepSequencer::limitX(int x) {
	return x < 0 ? 0 : (x >= numberOfValues ? numberOfValues - 1 : x);
}
int  StepSequencer::limitY(int y) {
	return y < 0 ? 0 : (y > maxValue ? maxValue : y);
}


void StepSequencer::updateValues(const MouseEvent& event) {
	if (event.mods.isRightButtonDown()) {
		int x = limitX(event.x * numberOfValues / getWidth());
		setValues(x, 0);
	}
	else {
		int x = limitX(event.x * numberOfValues / getWidth());
		int y = limitY((int)((float)maxValue * (getHeight() - event.y) / getHeight()));
		setValues(x, y);
	}
	return;
}

void StepSequencer::mouseDown(const MouseEvent &event) {
	if (event.getNumberOfClicks() != 1) {
		return;
	}
	updateValues(event);
}

void StepSequencer::mouseUp(const MouseEvent &event) {
}

void StepSequencer::mouseDrag(const MouseEvent &event) {
	updateValues(event);
}

void StepSequencer::mouseDoubleClick(const MouseEvent& event) {
	if (!event.mods.isLeftButtonDown()) {
		return;
	}
	int x = limitX(event.x * numberOfValues / getWidth());
	setValues(x, maxValue);
}

void StepSequencer::mouseWheelMove(const MouseEvent& event, const MouseWheelDetails& wheel) {
	//	debugValue = wheel.deltaY;
	if (wheel.deltaY == 0) {
		return;
	}
	int x = event.x * numberOfValues / getWidth();
	int y = values[x] + (wheel.deltaY > 0 ? 1 : -1) * (wheel.isReversed ? -1 : 1);
	y = y < 0 ? 0 : (y > maxValue ? maxValue : y);
	setValues(x, y);
}


void StepSequencer::resized()
{
	// This method is where you should set the bounds of any child
	// components that your component contains..

}

void StepSequencer::setValuesNoNotify(int x, int y) {
	values[x] = y;
}


void StepSequencer::setValues(int x, int y) {
	if (values[x] != y && y >= 0 && y < maxValue) {
		values[x] = y;
		notifyObservers(x);
		repaint();
	}
}

