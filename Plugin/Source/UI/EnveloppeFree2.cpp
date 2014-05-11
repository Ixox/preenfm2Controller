/*
  ==============================================================================

    EnveloppeFree2.cpp
    Created: 10 Apr 2014 7:05:10pm
    Author:  xhosxe

  ==============================================================================
*/

#include "EnveloppeFree2.h"



#include "../JuceLibraryCode/JuceHeader.h"
#include "Enveloppe.h"
#include "MidifiedComponent.h"

//==============================================================================
EnveloppeFree2::EnveloppeFree2(int nrpnBase)
{

	this->nrpnBase = nrpnBase;
	EnveloppePoint* point0 = new EnveloppePoint(this, 0, 0,0,0,0);
	point0->setX(0, false);
	point0->setY(0, false);
    EnveloppePoint* point1 = new EnveloppePoint(this, 1, 0,16.0, 0, 0);
    point1->setX(0.2, false);
    point1->setY(1.0, false);
    EnveloppePoint* point2 = new EnveloppePoint(this, 2, 0,16.0,1,1);
    point2->setX(0.2, false);
    point2->setY(0.5, false);
    EnveloppePoint* point3 = new EnveloppePoint(this, 3, 0, 16 , 0,0);
    point3->setX(1, false);
    point3->setY(0.5, false);
	pointList.append(point0);
    pointList.append(point1);
    pointList.append(point2);
    pointList.append(point3);


}

EnveloppeFree2::~EnveloppeFree2()
{
}


void EnveloppeFree2::paint (Graphics& g)
{
    EnveloppeAbstract::paint(g);


    static const String adsr[] = { "S", "A", "R"} ;
    for (int v=0; v<3; v++) {

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
            g.drawText(String(pointList[v+1].get()->getX(), 2), getWidth() - 50 , 10 + v* 16, 50, 10, Justification::centred, true);
        	break;
        }
    }
}


//void EnveloppeFree2::handleIncomingNrpn(int param, int value) {
//	switch (param - nrpnBase) {
//	case 0:
//	case 1:
//	case 2:
//		pointList[param - nrpnBase + 1].get()->setX(value / 100.0f);
//		repaint();
//		break;
//	case 3:
//		loopCombo->setSelectedId(value + 1, dontSendNotification);
//		break;
//	}
//}

void EnveloppeFree2::comboBoxChanged (ComboBox* comboBoxThatHasChanged) {
/*
	MidifiedComboBox* midifiedComboBox = dynamic_cast<MidifiedComboBox*>(comboBoxThatHasChanged);
	if(midifiedComboBox != nullptr) {
		sendNrpn(nrpnBase + 3,  midifiedComboBox->getSelectedId() - 1);
	}
	*/
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

