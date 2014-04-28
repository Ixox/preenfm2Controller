/*
  ==============================================================================

    MidifiedComponent.h
    Created: 8 Apr 2014 10:20:40pm
    Author:  xhosxe

  ==============================================================================
*/

#ifndef MIDIFIEDCOMPONENT_H_INCLUDED
#define MIDIFIEDCOMPONENT_H_INCLUDED

#include "JuceHeader.h"

class Midificator {
public:
	Midificator(int nrpmP, float minV, float valueM) {
	    setMidificatorParam(nrpmP, minV, valueM);
	};

	void setMidificatorParam(int nrpmP, float minV, float valueM) {
	    minValue = minV;
	    valueMultiplier = valueM;
	    nrpnParam = nrpmP;
	}

	virtual void sendNrpn(MidiBuffer* midiBuffer, double value) {
		if (midiBuffer != nullptr) {
		    midiBuffer->addEvent(MidiMessage::controllerEvent(1, 99, getNrpnParamMSB()), Time::getMillisecondCounter());
		    midiBuffer->addEvent(MidiMessage::controllerEvent(1, 98, getNrpnParamLSB()), Time::getMillisecondCounter());
		    midiBuffer->addEvent(MidiMessage::controllerEvent(1, 6, getNrpnValueMSB(value)), Time::getMillisecondCounter());
		    midiBuffer->addEvent(MidiMessage::controllerEvent(1, 38, getNrpnValueLSB(value)), Time::getMillisecondCounter());
		}
	}

	int getNrpnParamMSB() { return nrpnParam >> 7; }
	int getNrpnParamLSB() { return nrpnParam & 0xff; }
	virtual int getNrpnValueMSB(double value) {
		int iv = (value - minValue ) * valueMultiplier + .005f;
		return iv >> 7;
	}
	virtual int getNrpnValueLSB(double value) {
		int iv = (value - minValue ) * valueMultiplier + .005f;
		return iv & 0x7f;
	}

protected:
	float minValue;
	float valueMultiplier;
	int nrpnParam;
};

class MidifiedSlider : public Slider, public Midificator {
public:

	MidifiedSlider (const String& componentName, int nrpnParam = -1, float minValue = 0.0f, float valueMultipler = 100.0f) : Slider(componentName), Midificator(nrpnParam, minValue, valueMultipler) {
	}

    void mouseWheelMove (const MouseEvent& e, const MouseWheelDetails& wheel) override
    {
        if (!isEnabled() || !isVisible()) {
            return;
        }
    	if (wheel.deltaY != 0) {
			float y = getValue() + (wheel.deltaY > 0 ? getInterval() : -1 * getInterval() ) * (wheel.isReversed ? -1.0f : 1.0f);

			setValue (y);
    	}
    }

    int getNumDecimalPlacesToDisplay() const noexcept    {
    	return 2;
    }

};

class MidifiedComboBox: public ComboBox, public Midificator {
public:
	MidifiedComboBox (const String& componentName, int nrpnParam = -1, float minValue = 0.0f, float valueMultipler = 100.0f) : ComboBox(componentName), Midificator(nrpnParam, minValue, valueMultipler) {
	}
};


class MidifiedToggleButton: public ToggleButton, public Midificator {
public:
    // sendNrpn is overloaded, we don't use valueMultiplier here
    MidifiedToggleButton(const String& componentName, int nrpnParam = -1, int nrpnValue = -1) : ToggleButton(componentName), Midificator(nrpnParam, nrpnValue, 0) {
    }

    void sendNrpn(MidiBuffer* midiBuffer) {
        if (midiBuffer != nullptr) {
            midiBuffer->addEvent(MidiMessage::controllerEvent(1, 99, getNrpnParamMSB()), Time::getMillisecondCounter());
            midiBuffer->addEvent(MidiMessage::controllerEvent(1, 98, getNrpnParamLSB()), Time::getMillisecondCounter());
            midiBuffer->addEvent(MidiMessage::controllerEvent(1, 6, ((int)minValue) >> 7), Time::getMillisecondCounter());
            midiBuffer->addEvent(MidiMessage::controllerEvent(1, 38, ((int)minValue) & 0x7f), Time::getMillisecondCounter());
        }
    }
};

#endif  // MIDIFIEDCOMPONENT_H_INCLUDED
