/*
  ==============================================================================

    Enveloppe.h
    Created: 6 Apr 2014 2:32:14pm
    Author:  xhosxe

  ==============================================================================
*/

#ifndef ENVELOPPE_H_INCLUDED
#define ENVELOPPE_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"
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
    void handleIncomingNrpn(int param, int value);


private:

    int nrpnBase;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Enveloppe)





};


#endif  // ENVELOPPE_H_INCLUDED
