/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic startup code for a Juce application.

  ==============================================================================
*/

#ifndef PLUGINPROCESSOR_H_INCLUDED
#define PLUGINPROCESSOR_H_INCLUDED

#include <map>
#include "JuceHeader.h"
#include "PluginParameters/include/PluginParameters.h"
#include "PreenNrpn.h"

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
class Pfm2AudioProcessor  : public AudioProcessor, public teragon::ParameterObserver
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

    int getNumParameters();

    float getParameter (int index);
    void setParameter (int index, float newValue);

    const String getParameterName (int index);
    const String getParameterText (int index);

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
    void onParameterUpdated(const teragon::Parameter *parameter);
    // accessed from editor so must be public
    teragon::ConcurrentParameterSet parameterSet;
	MidiMessageCollector midiMessageCollector;
	struct Nrpn currentNrpn;

private:
	 std::map<int , teragon::Parameter* > nrpmParameterMap;
	 int nrpmIndex[2048];
     Pfm2AudioProcessorEditor* pfm2Editor;
	 bool uiNeedUpdate;
	 LookAndFeel* myLookAndFeel;


	 //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Pfm2AudioProcessor)
};


#endif  // PLUGINPROCESSOR_H_INCLUDED
