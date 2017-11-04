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

#include "Pfm2MidiDevice.h"

Pfm2MidiDevice::Pfm2MidiDevice() {
	pfm2MidiOutput = nullptr;
	pfm2MidiInput = nullptr;

	StringArray devices = MidiOutput::getDevices();

	for (int d = 0; d < devices.size(); d++) {
		DBG("Output : " << devices[d]);
		if (devices[d] == "PreenFM mk2") {
			if ((pfm2MidiOutput = MidiOutput::openDevice(d)) != nullptr) {
				DBG("Output found :)");
			}
			break;
		}
	}

	devices = MidiInput::getDevices();
	for (int d = 0; d < devices.size(); d++) {
		DBG("Input : " << devices[d]);
		if (devices[d] == "PreenFM mk2") {
			if ((pfm2MidiInput = MidiInput::openDevice(d, this)) != nullptr) {
				pfm2MidiInput->start();
				DBG("Input found :)");
			}
			break;
		}
	}

}

Pfm2MidiDevice::~Pfm2MidiDevice() {
	if (pfm2MidiInput) {
		pfm2MidiInput->stop();
		delete pfm2MidiInput;
	}
	if (pfm2MidiOutput) {
		delete pfm2MidiOutput;
	}
}



void Pfm2MidiDevice::sendBlockOfMessagesNow(MidiBuffer& midiBuffer) {
	if (pfm2MidiOutput != nullptr && pfm2MidiInput != nullptr) {
		pfm2MidiOutput->sendBlockOfMessagesNow(midiBuffer);
	} else {
		const ScopedLock myScopedLock(messageLock);
		if (showErrorMEssage) {
			showErrorMEssage = false;


			AlertWindow midiWindow("No preenfm2 found",
				"Select your preenfm2 midi ports", 
				AlertWindow::QuestionIcon);

			StringArray devicesFrom = MidiInput::getDevices();
			midiWindow.addComboBox("PortsFrom", devicesFrom, "From your preenfm2 :");


			StringArray devicesTo = MidiOutput::getDevices();
			midiWindow.addComboBox("PortsTo", devicesTo, "To your preenfm2 :");

			//void addButton(const String &name, int returnValue, const KeyPress &shortcutKey1 = KeyPress(), const KeyPress &shortcutKey2 = KeyPress())
			midiWindow.addButton("Cancel", 0);
			midiWindow.addButton("OK", 1);

			const int result = midiWindow.runModalLoop();

			if (result == 1) {
				int deviceFrom = midiWindow.getComboBoxComponent("PortsFrom")->getSelectedId() - 1;
				pfm2MidiInput = MidiInput::openDevice(deviceFrom, this);
				if (pfm2MidiInput != nullptr) {
					pfm2MidiInput->start();
				}
				int deviceTo = midiWindow.getComboBoxComponent("PortsTo")->getSelectedId() - 1;
				pfm2MidiOutput = MidiOutput::openDevice(deviceTo);
			}
		}
	}
}

void Pfm2MidiDevice::addListener(MidiInputCallback *listener) {
	listeners.push_back(listener);
}

void Pfm2MidiDevice::removeListener(MidiInputCallback *listener) {
	MidiInputCallbackList::iterator iterator = listeners.begin();
	while (iterator != listeners.end() && listeners.size() > 0) {
		if (*iterator == listener) {
			iterator = listeners.erase(iterator);
		}
		else {
			++iterator;
		}
	}
}

void Pfm2MidiDevice::handleIncomingMidiMessage(MidiInput *source, const MidiMessage &midiMessage) {
	for (MidiInputCallbackList::const_iterator iterator = listeners.begin(); iterator != listeners.end(); ++iterator) {
		(*iterator)->handleIncomingMidiMessage(source, midiMessage);
	}
}

void Pfm2MidiDevice::handlePartialSysexMessage(MidiInput *source, const uint8 *messageData, int numBytesSoFar, double timestamp) {

}




