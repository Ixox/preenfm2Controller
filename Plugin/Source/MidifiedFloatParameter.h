/*
 * Copyright 2017 Xavier Hosxe
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


class MidifiedFloatParameter : public AudioProcessorParameter {
public:
    MidifiedFloatParameter(String componentName,
        int nrpnParam,
        float valueMultipler,
        float minValue,
        float maxValue,
        float defaultValueParam
    )
        : AudioProcessorParameter(),
        oldXmlName(""), range(minValue, maxValue), value(defaultValueParam), defaultValue(defaultValueParam)
    {
        this->componentName = componentName;
        rangeFloat = maxValue - minValue;
        sendRealValue = false;

        this->pfm2MinValue = minValue;
        this->valueMultiplier = valueMultipler;
        this->nrpnParam = nrpnParam;

        bias = 0;
        paramIndex = paramIndexCounter++;
        bIsAutomatable = true;
    }


    int getNrpnValueLSB() const {
        if (!sendRealValue) {
            int iv = (int)((value - pfm2MinValue + bias) * valueMultiplier + .005f);
            return iv & 0x7f;
        }
        else {
            int iv = (int)(value + .005f + bias);
            return iv & 0x7f;
        }
    }
    int getNrpnValueMSB() const {
        if (!sendRealValue) {
            int iv = (int)((value - pfm2MinValue + bias) * valueMultiplier + .005f);
            return iv >> 7;
        }
        else {
            int iv = (int)(value + .005f + bias);
            return iv >> 7;
        }
    }
    int getNrpnParamMSB() const {
        return nrpnParam >> 7;
    }
    int getNrpnParamLSB() const {
        return nrpnParam & 0xff;
    }


    float getValueFromNrpn(int nrpnValue) const {
        if (!sendRealValue) {
            return range.snapToLegalValue(((float)nrpnValue) / this->valueMultiplier + this->pfm2MinValue - bias);
        }
        else {
            return range.snapToLegalValue((float)nrpnValue - bias);
        }
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

    void addNrpn(MidiBuffer& midiBuffer, const int midiChannel);

    static void resetParamIndexCounter() {
        paramIndexCounter = 0;
    }

    int getParamIndex() const {
        return paramIndex;
    }
    void setBias(float b) {
        this->bias = b;
    }

    float getBias() const {
        return this->bias;
    }
    void setValueFromNrpn(int nrpnValue);

    // parameter float
    float get() const noexcept { return value; }
    operator float() const noexcept { return value; }

    // setValue is in Juce 5.4.5 called when host modify a parameter value
    void setValue(float newValue);

    void setRealValue(float newValue);
    void setRealValueNoNotification(float newValue) { value = newValue; }
    void setPfmBankValue(float pfmValue);
    float getPfmBankValue();
    
    float getValue() const { return range.convertTo0to1(value); }
    float getRealValue() const { return value; }
    float getDefaultValue() const { return range.convertTo0to1(defaultValue); }
    float getValueForText(const String& text) const { return range.convertTo0to1(text.getFloatValue()); }

    String getText(float v, int length) const
    {
        String asText(range.convertFrom0to1(v), 2);
        return length > 0 ? asText.substring(0, length) : asText;
    }

    String getName() {
        return componentName;
    }

    void setOldName(String oldName) {
        for (int i = 0; i < oldName.length(); ++i) {
            if (((oldName[i] >= 'a' && oldName[i] <= 'z') ||
                (oldName[i] >= '0' && oldName[i] <= '9') ||
                (oldName[i] >= 'A' && oldName[i] <= 'Z'))) {
                oldXmlName += oldName[i];
            }
        }
    }


    String getNameForXML() {
        if (oldXmlName.length() == 0) {
            setOldName(componentName);
        }
        return oldXmlName;
    }

    float getMin() {
        return range.getRange().getStart();
    }

    float getMax() {
        return range.getRange().getEnd();
    }

    String getName(int maximumStringLength) const {
        return componentName.substring(0, maximumStringLength);
    }
    String getLabel() const {
        return componentName;
    }

    void setIsAutomatable(bool automatable) {
        bIsAutomatable = automatable;
    }

    bool isAutomatable() const {
        return bIsAutomatable;
    }

private:
    static int paramIndexCounter;
    float pfm2MinValue;
    float valueMultiplier;
    int nrpnParam;
    int paramIndex;
    float bias;
    String componentName;
    String oldXmlName; // To save XML for compatibility
    NormalisableRange<float> range;
    float value, defaultValue;
    Pfm2AudioProcessor* audioProcessor;
    bool sendRealValue;
    float rangeFloat;
    bool bIsAutomatable;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(MidifiedFloatParameter)
};

#endif  // MIDIFIEDPARAMETER_H_INCLUDED

