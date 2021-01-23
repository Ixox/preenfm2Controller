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

#ifndef PLUGINPROCESSOR_H_INCLUDED
#define PLUGINPROCESSOR_H_INCLUDED

#include <map>
#include <mutex>
#include <unordered_set>
#include "JuceHeader.h"
#include "PreenNrpn.h"
#include "Pfm2MidiDevice.h"
#include "MidifiedFloatParameter.h"




struct Nrpn {
	char paramMSB;
	char paramLSB;
	char valueMSB;
	char valueLSB;
};



class Pfm2AudioProcessorEditor;
//==============================================================================
/**
*/
class Pfm2AudioProcessor : public AudioProcessor, public MidiInputCallback
{
public:
	//==============================================================================
	Pfm2AudioProcessor();
	~Pfm2AudioProcessor();

	//==============================================================================
	void prepareToPlay(double sampleRate, int samplesPerBlock);
	void releaseResources();

	void processBlock(AudioSampleBuffer& buffer, MidiBuffer& midiMessages);

	//==============================================================================
	AudioProcessorEditor* createEditor();
	bool hasEditor() const;

	//==============================================================================
	const String getName() const;

	void setParameter(int index, float newValue);

	bool acceptsMidi() const;
	bool producesMidi() const;
	double getTailLengthSeconds() const;

	//==============================================================================
	int getNumPrograms();
	int getCurrentProgram();
	void setCurrentProgram(int index);
	const String getProgramName(int index);
	void changeProgramName(int index, const String& newName);

	//==============================================================================
	void getStateInformation(MemoryBlock& destData);
	void setStateInformation(const void* data, int sizeInBytes);


	void handleIncomingNrpn(int param, int value, int forceIndex = -1);
	// Parameter observer
	bool isRealtimePriority() const;
	void onParameterUpdated(AudioProcessorParameter *parameter);
	// accessed from editor so must be public
	MidiMessageCollector midiMessageCollector;
	struct Nrpn currentNrpn;
	void flushAllParametrsToNrpn();
	void sendNrpnPresetName();
	void setPresetName(String newName);
	String getPresetName() { return presetName;  }
    void editorClosed();

	void addMidifiedParameter(MidifiedFloatParameter *param);
	void flushMidiOut();

	void parameterUpdatedForUI(int p);
	void handleIncomingMidiMessage(MidiInput* source, const MidiMessage &message);
	void handlePartialSysexMessage(MidiInput* source, const uint8 *messageData, int numBytesSoFar, double timestamp);
	void choseNewMidiDevice();

	// Called from PfmPreset in standalone version only
	void setParameterWithNrpmParamAndRealValue(int param, float pfmValue);
	float getRealValueForPfmBank(int param);

private:
	void sendMidiForParameter(int paramIndex, int nrpnValue, int forceIndex);
	int nrpmIndex[2048];
	int nrpmIndexPfm3[2048];
	int parameterIndex;
	String presetName;
	int currentMidiChannel;
	int pfmType;
	MidiBuffer midiOutBuffer;
	MidiBuffer newMidiNotes;
	// Shared by all plugin instances
	SharedResourcePointer<Pfm2MidiDevice> pfm2MidiDevice;
    int editorWidth;
    int editorHeight;


	Pfm2AudioProcessorEditor* pfm2Editor;
	LookAndFeel* myLookAndFeel;

	//==============================================================================
	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(Pfm2AudioProcessor)
};


#endif  // PLUGINPROCESSOR_H_INCLUDED
