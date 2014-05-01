/*
  ==============================================================================

    This file was auto-generated by the Introjucer!

    It contains the basic startup code for a Juce application.

  ==============================================================================
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

void Pfm2AudioProcessorEditor::mustUpdateUI() {
	uiOutOfSync = true;
}

void Pfm2AudioProcessorEditor::timerCallback () {
	if (uiOutOfSync) {
		mainTabs->updateUI();
		uiOutOfSync = false;
	}
}


