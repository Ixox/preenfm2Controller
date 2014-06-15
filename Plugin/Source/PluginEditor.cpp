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
#include "PluginParameters/include/PluginParameters.h"

//==============================================================================
Pfm2AudioProcessorEditor::Pfm2AudioProcessorEditor (Pfm2AudioProcessor* ownerFilter)
    : AudioProcessorEditor (ownerFilter)
{
    addAndMakeVisible (mainTabs = new MainTabs());
    mainTabs->buildParameters(ownerFilter->parameterSet);
    // This is where our plugin's editor size is set.
    setSize (900, 710);
	startTimer(200);
	uiOutOfSync = false;
}

Pfm2AudioProcessorEditor::~Pfm2AudioProcessorEditor()
{
    delete mainTabs;
}

//==============================================================================
void Pfm2AudioProcessorEditor::paint (Graphics& g)
{
}

void Pfm2AudioProcessorEditor::updateUIWith(std::unordered_set<const char*> &ptu) {
    for(std::unordered_set<const char*>::iterator it = ptu.begin(); it != ptu.end(); ++it) {
		this->parametersToUpdate.insert(*it);
	}
}


void Pfm2AudioProcessorEditor::timerCallback () {
	if (this->parametersToUpdate.size() > 0) {
		std::unordered_set<const char*> newSet;
		newSet.swap(this->parametersToUpdate);
		mainTabs->updateUI(newSet);
	}
}

void Pfm2AudioProcessorEditor::newNrpnParam(int nrpn, int value) {
    mainTabs->newNrpnParam(nrpn, value);
}


