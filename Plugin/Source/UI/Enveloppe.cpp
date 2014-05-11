/*
  ==============================================================================

    Enveloppe.cpp
    Created: 6 Apr 2014 2:32:14pm
    Author:  xhosxe

  ==============================================================================
 */

#include "../JuceLibraryCode/JuceHeader.h"
#include "Enveloppe.h"


//==============================================================================
Enveloppe::Enveloppe(int nrpnBase)
{

	this->nrpnBase = nrpnBase;
	EnveloppePoint* point0 = new EnveloppePoint(this, 0, 0,0,0,0);
	point0->setX(0, false);
	point0->setY(0, false);
    EnveloppePoint* point1 = new EnveloppePoint(this, 1, 0,16.0,0.0, 1.0);
    point1->setX(0.2, false);
    point1->setY(1.0, false);
    EnveloppePoint* point2 = new EnveloppePoint(this, 2, 0,16.0,0,1.0);
    point2->setX(0.2, false);
    point2->setY(0.6, false);
    EnveloppePoint* point3 = new EnveloppePoint(this, 3, 0,16.0,0, 1.0);
    point3->setX(0.4, false);
    point3->setY(0.8, false);
    EnveloppePoint* point4 = new EnveloppePoint(this, 4, 0,16.0,0, 1.0);
    point4->setX(1.0, false);
    point4->setY(0, false);
	pointList.append(point0);
    pointList.append(point1);
    pointList.append(point2);
    pointList.append(point3);
    pointList.append(point4);
}

Enveloppe::~Enveloppe()
{
}


void Enveloppe::paint (Graphics& g)
{
    EnveloppeAbstract::paint(g);


    static const String adsr[] = { "A", "D", "S", "R" } ;
    for (int v=0; v<4; v++) {

        g.setColour (Colours::black);
        g.drawText(adsr[v], getWidth() - RIGHT_TEXT_SIZE , 20 + v* 20, 50, 10, Justification::centred, true);

        if (draggingPointIndex == v + 1) {
            g.setColour (Colours::red);
        } else {
            g.setColour (Colours::black);
        }

        String posisionX = String(pointList[v+1].get()->getX(), 2);
        g.drawText(posisionX, getWidth() - RIGHT_TEXT_SIZE / 3 * 2 - 10, 20 + v* 20, 50, 10, Justification::centred, true);
        posisionX = String(pointList[v+1].get()->getY(), 2);
        g.drawText(posisionX, getWidth() - RIGHT_TEXT_SIZE / 3 - 10, 20 + v* 20, 50, 10, Justification::centred, true);
    }
}



void Enveloppe::newXValue(int draggingPointIndex, float newX) {
}

void Enveloppe::newYValue(int draggingPointIndex, float newY) {
}

static const char* __enveloppePointSuffix[] = { " Attk", " Attk lvl", " Deca", " Deca lvl", " Sust", " Sust lvl", " Rele", " Rele lvl" };
const char ** Enveloppe::getPointSuffix() const {
	return __enveloppePointSuffix;
}

const char* Enveloppe::getPointSuffix(int pointNumber, bool isX) const {
    return __enveloppePointSuffix[(pointNumber - 1) *2 + (isX ? 0 : 1)];
}
