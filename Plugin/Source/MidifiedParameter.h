/*
 * Copyright 2014 Xavier Hosxe
 *
 * Author: Xavier Hosxe (xavier <dot> hosxe
 *                      (at) g m a i l <dot> com)
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */


#ifndef MIDIFIEDPARAMETER_H_INCLUDED
#define MIDIFIEDPARAMETER_H_INCLUDED


#include <stdlib.h>
#include <map>

#include "JuceHeader.h"
#include "PluginParameters/include/Parameter.h"
#include "PluginParameters/include/FloatParameter.h"

using namespace teragon;

class Midificator {
public:
	Midificator(int nrpmP, float minV, float valueM) {
	    setMidificatorParam(nrpmP, minV, valueM);
	    bias = 0;
		paramIndex = paramIndexCounter++;
	};

	void setMidificatorParam(int nrpmP, float minV, float valueM) {
	    pfm2MinValue = minV;
	    valueMultiplier = valueM;
	    nrpnParam = nrpmP;
	}

	void addNrpn(juce::MidiMessageCollector& midiMessageCollector, double value) const {
		double timeNow = Time::getMillisecondCounterHiRes() * .001;
		MidiMessage byte1 = MidiMessage::controllerEvent(1, 99, getNrpnParamMSB());
		byte1.setTimeStamp(timeNow);
		midiMessageCollector.addMessageToQueue(byte1);

		MidiMessage byte2 = MidiMessage::controllerEvent(1, 98, getNrpnParamLSB());
		byte2.setTimeStamp(timeNow);
		midiMessageCollector.addMessageToQueue(byte2);

		MidiMessage byte3 = MidiMessage::controllerEvent(1, 6, getNrpnValueMSB(value));
		byte3.setTimeStamp(timeNow);
		midiMessageCollector.addMessageToQueue(byte3);

		MidiMessage byte4 = MidiMessage::controllerEvent(1, 38, getNrpnValueLSB(value));
		byte4.setTimeStamp(timeNow);
		midiMessageCollector.addMessageToQueue(byte4);
//		printf("addNrpn : %d > %d\r\n", nrpnParam, ((getNrpnValueMSB(value)) << 7)+getNrpnValueLSB(value));
	}

	int getNrpnParamMSB() const { return nrpnParam >> 7; }
	int getNrpnParamLSB() const { return nrpnParam & 0xff; }
	virtual int getNrpnValueMSB (double value) const {
		int iv = (value - pfm2MinValue + bias) * valueMultiplier + .005f ;
		return iv >> 7;
	}
	virtual int getNrpnValueLSB(double value) const {
		int iv = (value - pfm2MinValue + bias) * valueMultiplier + .005f;
		return iv & 0x7f;
	}

	static void resetParamIndexCounter() { paramIndexCounter = 0; }
	int getParamIndex() const { return paramIndex; }

    void setBias(float b) {
        this->bias = b;
    }

    bool getBias() const {
        return this->bias;
    }

    int getNrpn() const {
        return this->nrpnParam;
    }

protected:
	float pfm2MinValue;
	float valueMultiplier;
	int nrpnParam;
	int paramIndex;
	static int paramIndexCounter;
    float bias;

};

class MidifiedFloatParameter: public FloatParameter, public Midificator {
public:

	MidifiedFloatParameter (std::map<int , Parameter* > *nrpmParameterMap,
							const char* componentName, 
							int nrpnParam, 
							float valueMultipler, 
							float minValue,
							float maxValue,
							float defaultValue
							) 
		: FloatParameter(componentName, minValue, maxValue, defaultValue), Midificator(nrpnParam, minValue, valueMultipler) 
	{
		nrpmParameterMap->insert(std::pair<int , teragon::Parameter* > (nrpnParam, this));
		range = maxValue - minValue;
		sendRealValue = false;
	}

	int getNrpnValueMSB (double value) const {
		if (!sendRealValue) {
			return Midificator::getNrpnValueMSB(value);
		} else {
			int iv = value + .005f + bias;
			return iv >> 7;
		}
	}
	int getNrpnValueLSB(double value) const {
		if (!sendRealValue) {
			return Midificator::getNrpnValueLSB(value);
		} else {
			int iv = value + .005f + bias;
			return iv & 0x7f;
		}
	}


	float getValueFromNrpn(int value) const {
		if (!sendRealValue) {
			return (float)value / this->valueMultiplier + this->pfm2MinValue - bias;
		} else {
			return value - bias;
		}
	}

	float getScaledValueFromNrpn(int value) const {
		return (float)value / this->valueMultiplier / range - bias;
	}

	void setSendRealValue(bool srv) {
		this->sendRealValue = srv;
	}

	bool getSendRealValue() const {
		return this->sendRealValue;
	}

private:
	bool sendRealValue;
	float range;
};
/*
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
*/

#endif  // MIDIFIEDPARAMETER_H_INCLUDED
