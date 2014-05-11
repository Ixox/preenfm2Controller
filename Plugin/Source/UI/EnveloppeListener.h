/*
  ==============================================================================

    EnveloppeListener.h
    Created: 4 May 2014 9:06:01pm
    Author:  xhosxe

  ==============================================================================
*/

#ifndef ENVELOPPELISTENER_H_INCLUDED
#define ENVELOPPELISTENER_H_INCLUDED

class EnveloppeAbstract;

class EnveloppeListener {
public:
    virtual ~EnveloppeListener() {}

    /**
     * Method to be called when a enveloppe's value has been updated.
     */
    virtual void enveloppeValueChanged(const EnveloppeAbstract* enveloppeThatWasMoved, int pointNumber, bool isX) = 0;
};

typedef std::vector<EnveloppeListener *> EnveloppeListenerList;

#endif  // ENVELOPPELISTENER_H_INCLUDED
