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
	Midificator(int nrpmP, float minV, float valueM) : minValue(minV), nrpnParam(nrpmP), valueMultiplier(valueM) {

	};

	void sendNrpn(MidiOutput* midiOutput, double value) {
		if (midiOutput != nullptr) {
			midiOutput->sendMessageNow(MidiMessage::controllerEvent(1, 99, getNrpnParamMSB()));
			midiOutput->sendMessageNow(MidiMessage::controllerEvent(1, 98, getNrpnParamLSB()));
			midiOutput->sendMessageNow(MidiMessage::controllerEvent(1, 6, getNrpnValueMSB(value)));
			midiOutput->sendMessageNow(MidiMessage::controllerEvent(1, 38, getNrpnValueLSB(value)));
		}
	}

	int getNrpnParamMSB() { return nrpnParam >> 7; }
	int getNrpnParamLSB() { return nrpnParam & 0xff; }
	int getNrpnValueMSB(double value) {
		int iv = (value - minValue + .005f) * valueMultiplier;
		return iv >> 7;
	}
	int getNrpnValueLSB(double value) {
		int iv = (value - minValue + .005f) * valueMultiplier;
		return iv & 0xff;
	}

private:
	float minValue;
	float valueMultiplier;
	int nrpnParam;
};

class MidifiedSlider : public Slider, public Midificator {
public:
	MidifiedSlider (const String& componentName, int nrpnParam, float minValue, float valueMultipler = 100.0f) : Slider(componentName), Midificator(nrpnParam, minValue, valueMultipler) {
	}

    void mouseWheelMove (const MouseEvent& e, const MouseWheelDetails& wheel) override
    {
    	if (wheel.deltaY != 0) {
			float y = getValue() + (wheel.deltaY > 0 ? getInterval() : -1 * getInterval() ) * (wheel.isReversed ? -1.0f : 1.0f);

			setValue (y);
    	}
    }

    int getNumDecimalPlacesToDisplay() const noexcept   override {
    	return 2;
    }

};

class MidifiedComboBox: public ComboBox, public Midificator {
public:
	MidifiedComboBox (const String& componentName, int nrpnParam, float minValue, float valueMultipler = 100.0f) : ComboBox(componentName), Midificator(nrpnParam, minValue, valueMultipler) {
	}
};

#endif  // MIDIFIEDCOMPONENT_H_INCLUDED
