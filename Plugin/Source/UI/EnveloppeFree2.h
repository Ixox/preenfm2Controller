/*
  ==============================================================================

    EnveloppeFree2.h
    Created: 10 Apr 2014 7:05:10pm
    Author:  xhosxe

  ==============================================================================
*/

#ifndef ENVELOPPEFREE2_H_INCLUDED
#define ENVELOPPEFREE2_H_INCLUDED


#include "JuceHeader.h"
#include "EnveloppeAbstract.h"
//==============================================================================
/*
*/
class EnveloppeFree2    : public  EnveloppeAbstract, public ComboBox::Listener
{
public:
    EnveloppeFree2(int nrpnBase);
    ~EnveloppeFree2();
    void resized();
    void paint (Graphics&);
    void comboBoxChanged (ComboBox* comboBoxThatHasChanged);
    // Must be implemented to deal with point value modification
    void newXValue(int draggingPointIndex, float newX);
    const char ** getPointSuffix() const;
    const char *getPointSuffix(int pointNumber, bool isX) const;

private:

    int nrpnBase;
    EnveloppePoint* decayPoint;
    EnveloppePoint* sustainPoint;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (EnveloppeFree2)





};


#endif  // ENVELOPPEFREE2_H_INCLUDED
