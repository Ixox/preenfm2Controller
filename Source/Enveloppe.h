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

//==============================================================================
/*
*/
class Enveloppe    : public Component
{
public:
    Enveloppe(int nrpnBase);
    ~Enveloppe();

    void paint (Graphics&);
    void resized();
    void mouseDrag (const MouseEvent &event);
    void mouseDown(const MouseEvent &event);
    void mouseUp(const MouseEvent &event);
    void mouseMove(const MouseEvent &event);
    void updatePosition();
    void handleIncomingNrpn(int param, int value);


    class JUCE_API  Listener
    {
    public:
        virtual ~Listener() {}
        virtual void enveloppeValueChanged (int nrpnParam, float value) = 0;
    };

    void addListener (Listener* listener);
    void removeListener (Listener* listener);

private:
    float values[8];
    float pointPositionX[5];
    float pointPositionY[5];
    float scaleX, scaleY;
    float startDragValueX, startDragValueY;
    int draggingPoint;
    int overPoint;
    int cptDebug;
    int nrpnBase;
    ListenerList <Enveloppe::Listener> listeners;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Enveloppe)





};


#endif  // ENVELOPPE_H_INCLUDED
