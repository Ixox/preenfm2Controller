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

#include "JuceHeader.h"
#include "PluginProcessor.h"
#include "MidifiedFloatParameter.h"

int MidifiedFloatParameter::paramIndexCounter = 0;

void MidifiedFloatParameter::setValue(float newValue) {
	float tmpValue = range.convertFrom0to1(newValue);
	if (value != tmpValue) {
		value = tmpValue;
	}
}

void MidifiedFloatParameter::setValueFromNrpn(int nrpnValue) {
	float newValue = getValueFromNrpn(nrpnValue);
	value = newValue;
}

void MidifiedFloatParameter::setRealValue(float newValue) {
	if (value != newValue) {
		value = newValue;
		audioProcessor->onParameterUpdated(this);
	}
}

void MidifiedFloatParameter::addNrpn(MidiBuffer& midiBuffer, const int midiChannel) {
	double time = Time::getMillisecondCounterHiRes() * .001;
	MidiMessage byte1 = MidiMessage::controllerEvent(midiChannel, 99, getNrpnParamMSB());
	byte1.setTimeStamp(time);
	midiBuffer.addEvent(byte1, 512);

	MidiMessage byte2 = MidiMessage::controllerEvent(midiChannel, 98, getNrpnParamLSB());
	byte2.setTimeStamp(time);
	midiBuffer.addEvent(byte2, 512);

	MidiMessage byte3 = MidiMessage::controllerEvent(midiChannel, 6, getNrpnValueMSB());
	byte3.setTimeStamp(time);
	midiBuffer.addEvent(byte3, 512);

	MidiMessage byte4 = MidiMessage::controllerEvent(midiChannel, 38, getNrpnValueLSB());
	byte4.setTimeStamp(time);
	midiBuffer.addEvent(byte4, 512);
}

