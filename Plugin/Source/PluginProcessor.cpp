/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic startup code for a Juce application.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"


//==============================================================================
Pfm2AudioProcessor::Pfm2AudioProcessor()
{
    pfm2Editor = nullptr;
}

Pfm2AudioProcessor::~Pfm2AudioProcessor()
{
}

//==============================================================================
const String Pfm2AudioProcessor::getName() const
{
    return JucePlugin_Name;
}

int Pfm2AudioProcessor::getNumParameters()
{
    return 0;
}

float Pfm2AudioProcessor::getParameter (int index)
{
    return 0.0f;
}

void Pfm2AudioProcessor::setParameter (int index, float newValue)
{
}

const String Pfm2AudioProcessor::getParameterName (int index)
{
    return String::empty;
}

const String Pfm2AudioProcessor::getParameterText (int index)
{
    return String::empty;
}

const String Pfm2AudioProcessor::getInputChannelName (int channelIndex) const
{
    return String (channelIndex + 1);
}

const String Pfm2AudioProcessor::getOutputChannelName (int channelIndex) const
{
    return String (channelIndex + 1);
}

bool Pfm2AudioProcessor::isInputChannelStereoPair (int index) const
{
    return true;
}

bool Pfm2AudioProcessor::isOutputChannelStereoPair (int index) const
{
    return true;
}

bool Pfm2AudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool Pfm2AudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool Pfm2AudioProcessor::silenceInProducesSilenceOut() const
{
    return false;
}

double Pfm2AudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int Pfm2AudioProcessor::getNumPrograms()
{
    return 0;
}

int Pfm2AudioProcessor::getCurrentProgram()
{
    return 0;
}

void Pfm2AudioProcessor::setCurrentProgram (int index)
{
}

const String Pfm2AudioProcessor::getProgramName (int index)
{
    return String::empty;
}

void Pfm2AudioProcessor::changeProgramName (int index, const String& newName)
{
}

//==============================================================================
void Pfm2AudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // Use this method as the place to do any pre-playback
    // initialisation that you need..
}

void Pfm2AudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

void Pfm2AudioProcessor::processBlock (AudioSampleBuffer& buffer, MidiBuffer& midiMessages)
{
    if (pfm2Editor != nullptr) {
        pfm2Editor->handleIncomingMidiBuffer(midiMessages, buffer.getNumSamples());
    }
}

//==============================================================================
bool Pfm2AudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

AudioProcessorEditor* Pfm2AudioProcessor::createEditor()
{
    pfm2Editor = new Pfm2AudioProcessorEditor (this);
    return pfm2Editor;
}

//==============================================================================
void Pfm2AudioProcessor::getStateInformation (MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void Pfm2AudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new Pfm2AudioProcessor();
}
