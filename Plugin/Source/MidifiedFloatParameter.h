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


class Pfm2AudioProcessor;

class Midificator {
public:
	Midificator(int nrpmP, float minV, float valueM) {
	    setMidificatorParam(nrpmP, minV, valueM);
	    bias = 0;
		paramIndex = paramIndexCounter++;
	};
    
    virtual ~Midificator() {};

	void setMidificatorParam(int nrpmP, float minV, float valueM) {
	    pfm2MinValue = minV;
	    valueMultiplier = valueM;
	    nrpnParam = nrpmP;
	}

	void addNrpn(juce::MidiMessageCollector& midiMessageCollector, const int midiChannel, const double value) const {
		double timeNow = Time::getMillisecondCounterHiRes() * .001;
		MidiMessage byte1 = MidiMessage::controllerEvent(midiChannel, 99, getNrpnParamMSB());
		byte1.setTimeStamp(timeNow);
		midiMessageCollector.addMessageToQueue(byte1);

		MidiMessage byte2 = MidiMessage::controllerEvent(midiChannel, 98, getNrpnParamLSB());
		byte2.setTimeStamp(timeNow);
		midiMessageCollector.addMessageToQueue(byte2);

		MidiMessage byte3 = MidiMessage::controllerEvent(midiChannel, 6, getNrpnValueMSB(value));
		byte3.setTimeStamp(timeNow);
		midiMessageCollector.addMessageToQueue(byte3);

		MidiMessage byte4 = MidiMessage::controllerEvent(midiChannel, 38, getNrpnValueLSB(value));
		byte4.setTimeStamp(timeNow);
		midiMessageCollector.addMessageToQueue(byte4);
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



class MidifiedFloatParameter: public AudioProcessorParameterWithID, public Midificator {
public:

	MidifiedFloatParameter (std::map<int , AudioProcessorParameter* > *nrpmParameterMap,
							String componentName, 
							int nrpnParam, 
							float valueMultipler, 
							float minValue,
							float maxValue,
							float defaultValue
							) 
		: AudioProcessorParameterWithID(componentName.replaceCharacter(' ', '_'), componentName),
		 Midificator(nrpnParam, minValue, valueMultipler),
		 range(minValue, maxValue), value(defaultValue), defaultValue(defaultValue)
	{
		this->componentName = componentName;
		nrpmParameterMap->insert(std::pair<int , AudioProcessorParameter* > (nrpnParam, this));
		rangeFloat = maxValue - minValue;
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
		return (float)value / this->valueMultiplier / rangeFloat - bias;
	}

	void setSendRealValue(bool srv) {
		this->sendRealValue = srv;
	}

	bool getSendRealValue() const {
		return this->sendRealValue;
	}

	void setProcessor(Pfm2AudioProcessor* audioProcessor) {
		this->audioProcessor = audioProcessor;
	}

	// parameter float
	float get() const noexcept { return value; }
	operator float() const noexcept { return value; }
	AudioParameterFloat& operator= (float newValue);

	void setValue(float newValue);
	void setRealValue(float newValue);

	float getValue() const { return range.convertTo0to1(value); }
	float getRealValue() const { return value; }
	float getDefaultValue() const { return range.convertTo0to1(defaultValue); }
	int getNumSteps() const { return AudioProcessorParameterWithID::getNumSteps(); }
	float getValueForText(const String& text) const { return range.convertTo0to1(text.getFloatValue()); }

	String getText(float v, int length) const
	{
		String asText(range.convertFrom0to1(v), 2);
		return length > 0 ? asText.substring(0, length) : asText;
	}

	String getName() {
		return componentName;
	}

	float getMin() {
		return range.getRange().getStart();
	}

	float getMax() {
		return range.getRange().getEnd();
	}

private:
	String componentName;
	NormalisableRange<float> range;
	float value, defaultValue;
	Pfm2AudioProcessor* audioProcessor;
	bool sendRealValue;
	float rangeFloat;

	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(MidifiedFloatParameter)
};

#endif  // MIDIFIEDPARAMETER_H_INCLUDED
