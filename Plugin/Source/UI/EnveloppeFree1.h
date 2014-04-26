/*
  ==============================================================================

    EnveloppeFree1.h
    Created: 10 Apr 2014 6:10:05pm
    Author:  xhosxe

  ==============================================================================
*/

#ifndef ENVELOPPEFREE1_H_INCLUDED
#define ENVELOPPEFREE1_H_INCLUDED



#include "JuceHeader.h"

#include "EnveloppeAbstract.h"
//==============================================================================
/*
*/
class EnveloppeFree1    : public  EnveloppeAbstract
{
public:
    EnveloppeFree1(int nrpnBase);
    ~EnveloppeFree1();

    void paint (Graphics&);
    void handleIncomingNrpn(int param, int value);
    // override
    // Must be implemented to deal with point value modification
    void newXValue(int draggingPointIndex, float newX);
    void newYValue(int draggingPointIndex, float newY);


private:

    int nrpnBase;
    EnveloppePoint* decayPoint;
    EnveloppePoint* sustainPoint;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (EnveloppeFree1)





};

#endif  // ENVELOPPEFREE1_H_INCLUDED
