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
	EnveloppePoint* point0 = new EnveloppePoint(0,0,0,0);
    EnveloppePoint* point1 = new EnveloppePoint(0,16.0,0, 1.0);
    EnveloppePoint* point2 = new EnveloppePoint(0,16.0,0, 1.0);
    EnveloppePoint* point3 = new EnveloppePoint(0,16.0,0, 1.0);
    EnveloppePoint* point4 = new EnveloppePoint(0,16.0,0, 1.0);
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


void Enveloppe::resized()
{
	// This method is where you should set the bounds of any child
	// components that your component contains..

}

void Enveloppe::handleIncomingNrpn(int param, int value) {
	if (param >= nrpnBase && param <= nrpnBase + 8) {
//		values[param - nrpnBase] = value / 100.0f;
		repaint();
	}
}

void Enveloppe::addListener (Enveloppe::Listener* const listener)       { listeners.add (listener); }
void Enveloppe::removeListener (Enveloppe::Listener* const listener)    { listeners.remove (listener); }

