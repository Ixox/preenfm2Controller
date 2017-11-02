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




class MidifiedFloatParameter: public AudioProcessorParameterWithID {
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
		 range(minValue, maxValue), value(defaultValue), defaultValue(defaultValue)
	{
		this->componentName = componentName;
		nrpmParameterMap->insert(std::pair<int , AudioProcessorParameter* > (nrpnParam, this));
		rangeFloat = maxValue - minValue;
		sendRealValue = false;

		this->pfm2MinValue = minValue;
		this->valueMultiplier = valueMultipler;
		this->nrpnParam = nrpnParam;


		bias = 0;
		paramIndex = paramIndexCounter++;
	}


	int getNrpnValueLSB() const {
		if (!sendRealValue) {
			int iv = (value - pfm2MinValue + bias) * valueMultiplier + .005f;
			return iv & 0x7f;
		} else {
			int iv = value + .005f + bias;
			return iv & 0x7f;
		}
	}
	int getNrpnValueMSB() const {
		if (!sendRealValue) {
			int iv = (value - pfm2MinValue + bias) * valueMultiplier + .005f;
			return iv >> 7;
		}
		else {
			int iv = value + .005f + bias;
			return iv >> 7;
		}
	}
	int getNrpnParamMSB() const {
		return nrpnParam >> 7;
	}
	int getNrpnParamLSB() const {
		return nrpnParam & 0xff;
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

	void addNrpn(juce::MidiMessageCollector& midiMessageCollector, const int midiChannel);

	static void resetParamIndexCounter() { 
		paramIndexCounter = 0; 
	}

	int getParamIndex() const { return 
		paramIndex; 
	}

	void setBias(float b) {
		this->bias = b;
	}

	bool getBias() const {
		return this->bias;
	}

	int getNrpn() const {
		return this->nrpnParam;
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

protected:
	static int paramIndexCounter;
	float pfm2MinValue;
	float valueMultiplier;
	int nrpnParam;
	int paramIndex;
	float bias;

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
