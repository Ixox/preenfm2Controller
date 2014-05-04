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
	EnveloppePoint* point0 = new EnveloppePoint(0,0,0,0);
	point0->setX(0);
	point0->setY(0);
    EnveloppePoint* point1 = new EnveloppePoint(0,16.0, 0, 0);
    point1->setX(0.2);
    point1->setY(1.0);
    EnveloppePoint* point2 = new EnveloppePoint(0,16.0,1,1);
    point2->setX(0.2);
    point2->setY(0.5);
    EnveloppePoint* point3 = new EnveloppePoint(0, 16 , 0,0);
    point3->setX(1);
    point3->setY(0.5);
	pointList.append(point0);
    pointList.append(point1);
    pointList.append(point2);
    pointList.append(point3);

    addAndMakeVisible(loopCombo = new ComboBox("loop combo"));
    loopCombo->setEditableText (false);
    loopCombo->setJustificationType (Justification::centred);
    loopCombo->addItem("None", 1);
    loopCombo->addItem("Silence", 2);
    loopCombo->addItem("Attack", 3);
    loopCombo->setSelectedId(1);
    loopCombo->addListener (this);

	addAndMakeVisible(loopComboLabel = new Label("loop combo Label", "Loop"));

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


void EnveloppeFree2::handleIncomingNrpn(int param, int value) {
	switch (param - nrpnBase) {
	case 0:
	case 1:
	case 2:
		pointList[param - nrpnBase + 1].get()->setX(value / 100.0f);
		repaint();
		break;
	case 3:
		loopCombo->setSelectedId(value + 1, dontSendNotification);
		break;
	}
}

void EnveloppeFree2::comboBoxChanged (ComboBox* comboBoxThatHasChanged) {
/*
	MidifiedComboBox* midifiedComboBox = dynamic_cast<MidifiedComboBox*>(comboBoxThatHasChanged);
	if(midifiedComboBox != nullptr) {
		sendNrpn(nrpnBase + 3,  midifiedComboBox->getSelectedId() - 1);
	}
	*/
}

void EnveloppeFree2::resized() {
	loopComboLabel->setBounds(proportionOfWidth (0.82) - 37 , proportionOfHeight (.69f), 80, 20);
	loopCombo->setBounds(proportionOfWidth (0.82)  , proportionOfHeight (.69f), 80, 20);
}

void EnveloppeFree2::newXValue(int draggingPointIndex, float newX) {
	switch (draggingPointIndex) {
		case 1:
		case 2:
		case 3:
			sendNrpn(nrpnBase + draggingPointIndex - 1, newX * 100.0f);
			break;
	}
}

static const char* __enveloppeFree2PointSuffix[] = { " Attk", " Attk lvl", " Deca", " Deca lvl", " Sust", " Sust lvl", " Rele", " Rele lvl" };
const char ** EnveloppeFree2::getPointSuffix() const {
	return __enveloppeFree2PointSuffix;
}
