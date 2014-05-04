/*
  ==============================================================================

    EnveloppeFree1.cpp
    Created: 10 Apr 2014 6:10:05pm
    Author:  xhosxe

  ==============================================================================
*/

#include "EnveloppeFree1.h"


#include "../JuceLibraryCode/JuceHeader.h"
#include "Enveloppe.h"


//==============================================================================
EnveloppeFree1::EnveloppeFree1(int nrpnBase)
{

	this->nrpnBase = nrpnBase;
	EnveloppePoint* point0 = new EnveloppePoint(0,0,0,0);
	point0->setX(0);
	point0->setY(0);
    EnveloppePoint* point1 = new EnveloppePoint(0,16.0, 1.0, 1.0);
    point1->setX(0.2);
    point1->setY(1.0);
    EnveloppePoint* point2 = new EnveloppePoint(0,16.0,.5,.5);
    point2->setX(0.2);
    point2->setY(0.5);
    EnveloppePoint* point3 = new EnveloppePoint(1,1 , 0,1);
    point3->setX(1);
    point3->setY(0.5);
    EnveloppePoint* point4 = new EnveloppePoint(0,16.0,0, 0);
    point4->setX(1.0);
    point4->setY(0);
	pointList.append(point0);
    pointList.append(point1);
    pointList.append(point2);
    pointList.append(point3);
    pointList.append(point4);



}

EnveloppeFree1::~EnveloppeFree1()
{
}


void EnveloppeFree1::paint (Graphics& g)
{
    EnveloppeAbstract::paint(g);


    static const String adsr[] = { "A", "D", "S", "R" } ;
    for (int v=0; v<4; v++) {

        g.setColour (Colours::black);
        g.drawText(adsr[v], getWidth() - 80 , 10 + v * 16, 50, 10, Justification::centred, true);

        if (draggingPointIndex == v + 1) {
            g.setColour (Colours::red);
        } else {
            g.setColour (Colours::black);
        }


        switch (v) {
        case 0:
            g.drawText(String(pointList[v+1].get()->getX(), 2), getWidth() - 50, 10 + v* 16, 50, 10, Justification::centred, true);
        	break;
        case 1:
            g.drawText(String(pointList[v+1].get()->getX(), 2), getWidth() - 50, 10 + v* 16, 50, 10, Justification::centred, true);
        	break;
        case 2:
            g.drawText(String(pointList[v+1].get()->getY(), 2), getWidth() - 50, 10 + v* 16, 50, 10, Justification::centred, true);
        	break;
        case 3:
            g.drawText(String(pointList[v+1].get()->getX(), 2), getWidth() - 50, 10 + v* 16, 50, 10, Justification::centred, true);
        	break;
        }
    }
}


void EnveloppeFree1::handleIncomingNrpn(int param, int value) {
	switch (param - nrpnBase) {
	case 0:
	case 1:
	case 3:
		pointList[param - nrpnBase + 1].get()->setX(value / 100.0f);
		repaint();
		break;
	case 2:
		pointList[2].get()->setYFixedValue(value / 100.0f);
		pointList[param - nrpnBase + 1].get()->setY(value / 100.0f);
		repaint();
		break;
	}
}



void EnveloppeFree1::newXValue(int draggingPointIndex, float newX) {
	switch (draggingPointIndex) {
		case 1:
		case 2:
		case 4:
			sendNrpn(nrpnBase + draggingPointIndex - 1, newX * 100.0f);
			break;
	}
}

void EnveloppeFree1::newYValue(int draggingPointIndex, float newY) {
	if (draggingPointIndex == 3) {
		pointList[2].get()->setYFixedValue(newY);
		sendNrpn(nrpnBase + draggingPointIndex - 1, newY * 100.0f);
	}
}

static const char* __enveloppeFree2PointSuffix[] = { " Attk", " Attk lvl", " Deca", " Deca lvl", " Sust", " Sust lvl", " Rele", " Rele lvl" };
const char ** EnveloppeFree1::getPointSuffix() const {
	return __enveloppeFree2PointSuffix;
}
