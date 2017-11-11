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


#include "EnveloppeFree2.h"

#include "Enveloppe.h"

 //==============================================================================
EnveloppeFree2::EnveloppeFree2(int nrpnBase)
{

	this->nrpnBase = nrpnBase;
	EnveloppePoint* point0 = new EnveloppePoint(this, 0, 0.0f, 0.0f, 0.0f, 0.0f);
	point0->setX(0.0f, false);
	point0->setY(0.0f, false);
	EnveloppePoint* point1 = new EnveloppePoint(this, 1, 0.0f, 16.0f, 0.0f, 0.0f);
	point1->setX(0.2f, false);
	point1->setY(1.0f, false);
	EnveloppePoint* point2 = new EnveloppePoint(this, 2, 0.0f, 16.0f, 1.0f, 1.0f);
	point2->setX(0.2f, false);
	point2->setY(0.5f, false);
	EnveloppePoint* point3 = new EnveloppePoint(this, 3, 0.0f, 16.0f, 0.0f, 0.0f);
	point3->setX(1.0f, false);
	point3->setY(0.5f, false);
	pointList.append(point0);
	pointList.append(point1);
	pointList.append(point2);
	pointList.append(point3);


}

EnveloppeFree2::~EnveloppeFree2()
{
}


void EnveloppeFree2::paint(Graphics& g)
{
	EnveloppeAbstract::paint(g);


	static const String adsr[] = { "S", "A", "R" };
	for (int v = 0; v < 3; v++) {

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
			g.drawText(String(pointList[v + 1].get()->getX(), 2), getWidth() - 50, 10 + v * 16, 50, 10, Justification::centred, true);
			break;
		}
	}
}



void EnveloppeFree2::comboBoxChanged(ComboBox* comboBoxThatHasChanged) {
}

void EnveloppeFree2::resized() {
}

void EnveloppeFree2::newXValue(int draggingPointIndex, float newX) {
}

static const char* __enveloppeFree2PointSuffix[] = { " Sile", " Attk", " Deca" };
const char ** EnveloppeFree2::getPointSuffix() const {
	return __enveloppeFree2PointSuffix;
}

const char* EnveloppeFree2::getPointSuffix(int pointNumber, bool isX) const {
	return __enveloppeFree2PointSuffix[(pointNumber - 1)];
}

