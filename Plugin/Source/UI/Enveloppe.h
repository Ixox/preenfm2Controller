/*
  ==============================================================================

    Enveloppe.h
    Created: 6 Apr 2014 2:32:14pm
    Author:  xhosxe

  ==============================================================================
*/

#ifndef ENVELOPPE_H_INCLUDED
#define ENVELOPPE_H_INCLUDED

#include "JuceHeader.h"
#include "EnveloppeAbstract.h"
//==============================================================================
/*
*/
class Enveloppe    : public  EnveloppeAbstract
{
public:
    Enveloppe(int nrpnBase);
    ~Enveloppe();

    void paint (Graphics&);
    // Must be implemented to deal with point value modification
    void newXValue(int draggingPointIndex, float newX);
    void newYValue(int draggingPointIndex, float newY);
    const char ** getPointSuffix() const;
    const char *getPointSuffix(int pointNumber, bool isX) const;


private:

    int nrpnBase;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Enveloppe)





};


#endif  // ENVELOPPE_H_INCLUDED
