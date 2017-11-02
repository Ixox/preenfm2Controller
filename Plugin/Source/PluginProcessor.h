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

#ifndef PLUGINPROCESSOR_H_INCLUDED
#define PLUGINPROCESSOR_H_INCLUDED

#include <map>
#include <mutex>
#include <unordered_set>
#include "JuceHeader.h"
#include "PreenNrpn.h"
#include "MidifiedFloatParameter.h"


#define NUMBER_OF_PROGRAM 1

#define FLUSH_START  -1
#define FLUSH_FINISHED -2

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
class Pfm2AudioProcessor  : public AudioProcessor
{
public:
    //==============================================================================
    Pfm2AudioProcessor();
    ~Pfm2AudioProcessor();

    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock);
    void releaseResources();

    void processBlock (AudioSampleBuffer& buffer, MidiBuffer& midiMessages);

    //==============================================================================
    AudioProcessorEditor* createEditor();
    bool hasEditor() const;

    //==============================================================================
    const String getName() const;

    void setParameter (int index, float newValue);


    const String getInputChannelName (int channelIndex) const;
    const String getOutputChannelName (int channelIndex) const;
    bool isInputChannelStereoPair (int index) const;
    bool isOutputChannelStereoPair (int index) const;

    bool acceptsMidi() const;
    bool producesMidi() const;
    bool silenceInProducesSilenceOut() const;
    double getTailLengthSeconds() const;

    //==============================================================================
    int getNumPrograms();
    int getCurrentProgram();
    void setCurrentProgram (int index);
    const String getProgramName (int index);
    void changeProgramName (int index, const String& newName);

    //==============================================================================
    void getStateInformation (MemoryBlock& destData);
    void setStateInformation (const void* data, int sizeInBytes);

	void handleIncomingMidiBuffer(MidiBuffer &buffer, int numberOfSamples);
	void handleIncomingNrpn(int param, int value, int forceIndex = -1);
    // Parameter observer
    bool isRealtimePriority() const;
    void onParameterUpdated(AudioProcessorParameter *parameter);
    // accessed from editor so must be public
	MidiMessageCollector midiMessageCollector;
	struct Nrpn currentNrpn;
	void flushAllParametrsToNrpn();
    void sendNrpnPresetName();
	void editorClosed() {  pfm2Editor = nullptr; }

	void addMidifiedParameter(MidifiedFloatParameter *param);

private:
	std::map<int, AudioProcessorParameter* > nrpmParameterMap;
	int nrpmIndex[2048];
	int parameterIndex;
	char presetName[13];
    int currentProgram;
    String programName[NUMBER_OF_PROGRAM];
    int currentMidiChannel;
	int flushAllParametrsToNrpnStatus;

     Pfm2AudioProcessorEditor* pfm2Editor;
	 LookAndFeel* myLookAndFeel;
     std::unordered_set<String> parametersToUpdate;
	 std::mutex parametersToUpdateMutex;

	 //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Pfm2AudioProcessor)
};


#endif  // PLUGINPROCESSOR_H_INCLUDED
