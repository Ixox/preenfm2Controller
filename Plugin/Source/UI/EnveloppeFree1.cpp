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


#include "EnveloppeFree1.h"


#include "../JuceLibraryCode/JuceHeader.h"
#include "Enveloppe.h"


 //==============================================================================
EnveloppeFree1::EnveloppeFree1(int nrpnBase)
{

	this->nrpnBase = nrpnBase;
	EnveloppePoint* point0 = new EnveloppePoint(this, 0, 0.0f, 0.0f, 0.0f, 0.0f);
	EnveloppePoint* point1 = new EnveloppePoint(this, 1, 0.0f, 16.0f, 1.0, 1.0f);
	EnveloppePoint* point2 = new EnveloppePoint(this, 2, 0.0f, 16.0f, 0.5f, .5f);
	EnveloppePoint* point3 = new EnveloppePoint(this, 3, 1.0f, 1.0f, 0.0f, 1.0f);
	EnveloppePoint* point4 = new EnveloppePoint(this, 4, 0.0f, 16.0f, 0.0f, 0.0f);
	point0->setX(0.0f, false);
	point0->setY(0.0f, false);
	point1->setX(0.2f, false);
	point1->setY(1.0f, false);
	point2->setX(0.2f, false);
	point2->setY(0.5f, false);
	point3->setX(10.0f, false);
	point3->setY(0.5f, false);
	point4->setX(1.0f, false);
	point4->setY(0.0f, false);
	pointList.append(point0);
	pointList.append(point1);
	pointList.append(point2);
	pointList.append(point3);
	pointList.append(point4);
}


EnveloppeFree1::~EnveloppeFree1()
{
}


void EnveloppeFree1::paint(Graphics& g)
{
	EnveloppeAbstract::paint(g);


	static const String adsr[] = { "A", "D", "S", "R" };
	for (int v = 0; v < 4; v++) {

		g.setColour(Colours::whitesmoke);
		g.drawText(adsr[v], getWidth() - 80, 10 + v * 16, 50, 10, Justification::centred, true);

		if (draggingPointIndex == v + 1) {
			g.setColour(Colours::yellow);
		}
		else {
			g.setColour(Colours::whitesmoke);
		}


		switch (v) {
		case 0:
			g.drawText(String(pointList[v + 1].get()->getX(), 2), getWidth() - 50, 10 + v * 16, 50, 10, Justification::centred, true);
			break;
		case 1:
			g.drawText(String(pointList[v + 1].get()->getX(), 2), getWidth() - 50, 10 + v * 16, 50, 10, Justification::centred, true);
			break;
		case 2:
			g.drawText(String(pointList[v + 1].get()->getY(), 2), getWidth() - 50, 10 + v * 16, 50, 10, Justification::centred, true);
			break;
		case 3:
			g.drawText(String(pointList[v + 1].get()->getX(), 2), getWidth() - 50, 10 + v * 16, 50, 10, Justification::centred, true);
			break;
		}
	}
}


void EnveloppeFree1::newXValue(int draggingPointIndex, float newX) {
}

void EnveloppeFree1::newYValue(int draggingPointIndex, float newY) {
	if (draggingPointIndex == 3) {
		pointList[2].get()->setYLockedValue(newY);
	}
}

static const char* __enveloppeFree2PointSuffix[] = { " Attk", " Deca", " Sust", " Rele" };
const char ** EnveloppeFree1::getPointSuffix() const {
	return __enveloppeFree2PointSuffix;
}

const char* EnveloppeFree1::getPointSuffix(int pointNumber, bool isX) const {
	return __enveloppeFree2PointSuffix[(pointNumber - 1)];
}

