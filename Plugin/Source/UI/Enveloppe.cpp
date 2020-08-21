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
#include "Enveloppe.h"


 //==============================================================================
Enveloppe::Enveloppe()
{
	EnveloppePoint* point0 = new EnveloppePoint(this, 0, 0.0f, 0.0f, 0.0f, 0.0f);
	point0->setX(0.0f, false);
	point0->setY(0.0f, false);
	EnveloppePoint* point1 = new EnveloppePoint(this, 1, 0.0f, 16.0f, 0.0f, 1.0f);
	point1->setX(0.2f, false);
	point1->setY(1.0f, false);
	EnveloppePoint* point2 = new EnveloppePoint(this, 2, 0.0f, 16.0f, 0.0f, 1.0f);
	point2->setX(0.2f, false);
	point2->setY(0.6f, false);
	EnveloppePoint* point3 = new EnveloppePoint(this, 3, 0.0f, 16.0f, 0.0f, 1.0f);
	point3->setX(0.4f, false);
	point3->setY(0.8f, false);
	EnveloppePoint* point4 = new EnveloppePoint(this, 4, 0.0f, 16.0f, 0.0f, 1.0f);
	point4->setX(1.0f, false);
	point4->setY(0.0f, false);
	pointList.append(point0);
	pointList.append(point1);
	pointList.append(point2);
	pointList.append(point3);
	pointList.append(point4);

	loop = new ToggleButton("Loop");
	loop->setTooltip("Sets release values to make the enveloppe loops");
	addAndMakeVisible(loop);
	loop->addListener(this);
}

Enveloppe::~Enveloppe()
{
}


void Enveloppe::paint(Graphics& g)
{
	EnveloppeAbstract::paint(g);

	static const String adsr[] = { "A", "D", "S", "R" };
	for (int v = 0; v < 4; v++) {
		int moveReleaseY = (v == 3 ? 20 : 0);
		g.setColour(Colours::whitesmoke);
		g.drawText(adsr[v], getWidth() - RIGHT_TEXT_SIZE, 20 + v * 20 + moveReleaseY, 50, 10, Justification::centred, true);

        if (overPointIndex == v + 1 && isMouseOverX()) {
			g.setColour(Colours::yellow);
		}
		else {
			g.setColour(Colours::whitesmoke);
		}
		String posisionX = String(pointList[v + 1].get()->getX(), 2);
		g.drawText(posisionX, getWidth() - RIGHT_TEXT_SIZE / 3 * 2 - 10, 20 + v * 20 + moveReleaseY, 50, 10, Justification::centred, true);
        if (overPointIndex == v + 1 && !isMouseOverX()) {
            g.setColour(Colours::yellow);
        }
        else {
            g.setColour(Colours::whitesmoke);
        }
        posisionX = String(pointList[v + 1].get()->getY(), 2);
		g.drawText(posisionX, getWidth() - RIGHT_TEXT_SIZE / 3 - 10, 20 + v * 20 + moveReleaseY, 50, 10, Justification::centred, true);
	}

}

void Enveloppe::newXValue(int draggingPointIndex, float newX) {
	if (draggingPointIndex == 4) {
		loop->setToggleState(getX(4) == 0.0f && getY(4) == 1.0f, false);
	}
}

void Enveloppe::newYValue(int draggingPointIndex, float newY) {
	if (draggingPointIndex == 4) {
		loop->setToggleState(getX(4) == 0.0f && getY(4) == 1.0f, false);
	}
}




static const char* __enveloppePointSuffix[] = { " Attk", " Attk lvl", " Deca", " Deca lvl", " Sust", " Sust lvl", " Rele", " Rele lvl" };
const char ** Enveloppe::getPointSuffix() const {
	return __enveloppePointSuffix;
}

const char* Enveloppe::getPointSuffix(int pointNumber, bool isX) const {
	return __enveloppePointSuffix[(pointNumber - 1) * 2 + (isX ? 0 : 1)];
}

void Enveloppe::resized() {
	loop->setBounds(getWidth() - RIGHT_TEXT_SIZE + 15, 20 + 57, 60, 18);
}


void Enveloppe::buttonClicked(Button* buttonThatWasClicked) {
	if (buttonThatWasClicked == loop) {
		if (loop->getToggleState()) {
			releaseTimeBeforeLoop = getX(4);
			releaseLevelBeforeLoop = getY(4);
			setX(4, 0.0f);
			setY(4, 1.0f);
		} else {
			setX(4, releaseTimeBeforeLoop);
			setY(4, releaseLevelBeforeLoop);
		}
		notifyObservers(3, true);
		this->repaint();
	}
}

