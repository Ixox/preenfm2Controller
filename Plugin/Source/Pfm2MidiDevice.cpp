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

#define MIDI_INPUT "midiInput"
#define MIDI_OUTPUT "midiOutput"

Pfm2MidiDevice::Pfm2MidiDevice() {
	String pfm2InputDevice = "PreenFM mk2";
	String pfm2OutputDevice = "PreenFM mk2";

	PropertiesFile::Options options;
	options.commonToAllUsers = false;
	options.applicationName = ProjectInfo::projectName;
	options.osxLibrarySubFolder = "Application Support/preenfm2 Editor";
	options.filenameSuffix = ".midi.xml";
	options.storageFormat = PropertiesFile::StorageFormat::storeAsXML;

	midiPropertyFile = new PropertiesFile(options);

	if (midiPropertyFile->getFile().exists()) {
		if (midiPropertyFile->containsKey(MIDI_INPUT)) {
			pfm2InputDevice = midiPropertyFile->getValue(MIDI_INPUT);
		}

		if (midiPropertyFile->containsKey(MIDI_OUTPUT)) {
			pfm2OutputDevice = midiPropertyFile->getValue(MIDI_OUTPUT);
		}
	}

	pfm2MidiOutput = nullptr;
	pfm2MidiInput = nullptr;

	StringArray devices = MidiOutput::getDevices();

	for (int d = 0; d < devices.size(); d++) {
		DBG("Output : " << devices[d]);
		if (devices[d] == pfm2OutputDevice) {
			pfm2MidiOutput = MidiOutput::openDevice(d);
			if (pfm2MidiOutput.get() != nullptr) {
				DBG("Output found :)");
				currentMidiOutputDevice = devices[d];
			}
			else {
				DBG("Output could not be open)");
			}
			break;
		}
	}

	devices = MidiInput::getDevices();
	for (int d = 0; d < devices.size(); d++) {
		DBG("Input : " << devices[d]);
		if (devices[d] == pfm2InputDevice) {
			pfm2MidiInput = MidiInput::openDevice(d, this);
			if (pfm2MidiInput.get() != nullptr) {
				pfm2MidiInput->start();
				currentMidiInputDevice = devices[d];
				DBG("Input found :)");
			}
			else {
				DBG("Input could not be open)");
			}
			break;
		}
	}
}

Pfm2MidiDevice::~Pfm2MidiDevice() {
	resetDevices();
	delete midiPropertyFile;
}

void Pfm2MidiDevice::resetDevices() {

	if (pfm2MidiInput) {
		pfm2MidiInput->stop();
		pfm2MidiInput.reset();
	}
	if (pfm2MidiOutput) {
		pfm2MidiOutput.reset();
	}
}


void Pfm2MidiDevice::sendBlockOfMessagesNow(MidiBuffer& midiBuffer) {
	if (pfm2MidiOutput != nullptr && pfm2MidiInput != nullptr) {
		pfm2MidiOutput->sendBlockOfMessagesNow(midiBuffer);
	}
	else {
		choseNewDevices();
	}
}


void Pfm2MidiDevice::forceChoseNewDevices() {
	showErrorMEssage = true;
	choseNewDevices();
}

void Pfm2MidiDevice::choseNewDevices() {
	const ScopedTryLock myScopedTryLock(messageLock);

	if (!myScopedTryLock.isLocked()) {
		return;
	}

	if (showErrorMEssage) {
		showErrorMEssage = false;

		AlertWindow midiWindow("Where is your preenfm ?",
			"",
			AlertWindow::QuestionIcon);

		Label errorMessage("");
		errorMessage.setColour(Label::textColourId, Colour::fromRGB(200, 80, 80));
		errorMessage.setSize(400, 20);
		midiWindow.addCustomComponent(&errorMessage);

		StringArray devicesFrom = MidiInput::getDevices();
		devicesFrom.insert(0, "<Select>");
		midiWindow.addComboBox("From", devicesFrom, "Input from preenfm");
		int currentInput = devicesFrom.indexOf(currentMidiInputDevice);
		if (currentInput > -1) {
			midiWindow.getComboBoxComponent("From")->setSelectedId(currentInput + 1);
		}

		StringArray devicesTo = MidiOutput::getDevices();
		devicesTo.insert(0, "<Select>");
		midiWindow.addComboBox("To", devicesTo, "Output to preenfm");
		int currentOutput = devicesTo.indexOf(currentMidiOutputDevice);
		if (currentOutput > -1) {
			midiWindow.getComboBoxComponent("To")->setSelectedId(currentOutput + 1);
		}

		//void addButton(const String &name, int returnValue, const KeyPress &shortcutKey1 = KeyPress(), const KeyPress &shortcutKey2 = KeyPress())
		midiWindow.addButton("Cancel", 0);
		midiWindow.addButton("OK", 1);

		int result = 1;
		do {

			do {
				result = midiWindow.runModalLoop();
				errorMessage.setText("You must select both input and output", NotificationType::sendNotification);
				midiWindow.repaint();
			} while ((midiWindow.getComboBoxComponent("From")->getSelectedId() == 1 || midiWindow.getComboBoxComponent("To")->getSelectedId() == 1) && result == 1);

			if (result == 1) {

				if (pfm2MidiOutput.get() != nullptr) {
					pfm2MidiOutput.reset();
				}
				if (pfm2MidiInput.get() != nullptr) {
					pfm2MidiInput->stop();
					pfm2MidiInput.reset();
				}

				// -2 because of the <Select>.
				int deviceFrom = midiWindow.getComboBoxComponent("From")->getSelectedId() - 2;
				currentMidiInputDevice = devicesFrom[deviceFrom + 1];
				int deviceTo = midiWindow.getComboBoxComponent("To")->getSelectedId() - 2;
				currentMidiOutputDevice = devicesTo[deviceTo + 1];

				pfm2MidiInput = MidiInput::openDevice(deviceFrom, this);
				if (pfm2MidiInput.get() != nullptr) {
					pfm2MidiInput->start();
				}
				else {
					errorMessage.setText("Input cannot be open", NotificationType::dontSendNotification);
				}
				// No need to test output if input did not work
				if (pfm2MidiInput.get() != nullptr) {
					pfm2MidiOutput = MidiOutput::openDevice(deviceTo);
					if (pfm2MidiOutput.get() == nullptr) {
						errorMessage.setText("Output cannot be open", NotificationType::dontSendNotification);
						// let's close input before rexiting
						resetDevices();
					}
					else {
						// We're good
						midiPropertyFile->setValue(MIDI_INPUT, currentMidiInputDevice);
						midiPropertyFile->setValue(MIDI_OUTPUT, currentMidiOutputDevice);
						midiPropertyFile->saveIfNeeded();
					}
				}
			}
		} while ((pfm2MidiInput.get() == nullptr || pfm2MidiOutput.get() == nullptr) && result == 1);
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

void Pfm2MidiDevice::handleIncomingMidiMessage(MidiInput * source, const MidiMessage &midiMessage) {
	for (MidiInputCallbackList::const_iterator iterator = listeners.begin(); iterator != listeners.end(); ++iterator) {
		(*iterator)->handleIncomingMidiMessage(source, midiMessage);
	}
}

void Pfm2MidiDevice::handlePartialSysexMessage(MidiInput *source, const uint8 *messageData, int numBytesSoFar, double timestamp) {

}




