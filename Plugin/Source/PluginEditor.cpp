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

#include "PluginProcessor.h"
#include "PluginEditor.h"

#include "UI/MainTabs.h"

//==============================================================================
Pfm2AudioProcessorEditor::Pfm2AudioProcessorEditor (Pfm2AudioProcessor* ownerFilter)
    : AudioProcessorEditor (ownerFilter)
{
	this->ownerFilter = ownerFilter;
    addAndMakeVisible (mainTabs = new MainTabs());
    mainTabs->buildParameters(getAudioProcessor());
    // This is where our plugin's editor size is set.

	setSize (1000, 750);
	
	startTimer(200);
	uiOutOfSync = false;
}

Pfm2AudioProcessorEditor::~Pfm2AudioProcessorEditor()
{
	this->ownerFilter->editorClosed();
    delete mainTabs;
}

//==============================================================================
void Pfm2AudioProcessorEditor::paint (Graphics& g)
{
}


void Pfm2AudioProcessorEditor::resized() {
	mainTabs->setSize(getWidth(), getHeight());
}


void Pfm2AudioProcessorEditor::updateUIWith(std::unordered_set<String> &paramSet) {
	this->parametersToUpdateMutex.lock();
	for(std::unordered_set<String>::iterator it = paramSet.begin(); it != paramSet.end(); ++it) {
		this->parametersToUpdate.insert(*it);
	}
	this->parametersToUpdateMutex.unlock();
}


void Pfm2AudioProcessorEditor::removeParamToUpdateUI(const char* paramName) {
	this->parametersToUpdateMutex.lock();
	if (this->parametersToUpdate.count(paramName) > 0) {
//        printf("#### Pfm2AudioProcessorEditor ERASE %d times\r\n", this->parametersToUpdate.count(paramName));
        this->parametersToUpdate.erase(paramName);
	}
	this->parametersToUpdateMutex.unlock();
}

void Pfm2AudioProcessorEditor::timerCallback () {
	if (this->parametersToUpdate.size() > 0) {
		std::unordered_set<String> newSet;
		this->parametersToUpdateMutex.lock();
		newSet.swap(this->parametersToUpdate);
		this->parametersToUpdateMutex.unlock();
		mainTabs->updateUI(newSet);
	}
}

void Pfm2AudioProcessorEditor::newNrpnParam(int nrpn, int value) {
    mainTabs->newNrpnParam(nrpn, value);
}

void Pfm2AudioProcessorEditor::setMidiMessageCollector(MidiMessageCollector &midiMessageCollector) {
    mainTabs->setMidiMessageCollector(midiMessageCollector);
}

void Pfm2AudioProcessorEditor::setMidiChannel(int newMidiChannel) {
	mainTabs->setMidiChannel(newMidiChannel);
}

void Pfm2AudioProcessorEditor::setPresetNamePtr(char* presetNamePtr) {
    mainTabs->setPresetNamePtr(presetNamePtr);
}

void Pfm2AudioProcessorEditor::setPresetName(const char* presetName) {
    mainTabs->setPresetName(presetName);
}

void Pfm2AudioProcessorEditor::setPushButtonEnabled(bool enabled) {
	mainTabs->setPushButtonEnabled(enabled);
}



