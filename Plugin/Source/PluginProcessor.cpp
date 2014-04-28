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
    printf("fm2AudioProcessor::getNumParameters : %u\n", parameterSet.size());

    return parameterSet.size();
}

float Pfm2AudioProcessor::getParameter (int index)
{
    return parameterSet[index]->getScaledValue();;
}

void Pfm2AudioProcessor::setParameter (int index, float newValue)
{
    parameterSet.setScaled(index, newValue);
}

const String Pfm2AudioProcessor::getParameterName (int index)
{
    return String(parameterSet[index]->getName().c_str());
}

const String Pfm2AudioProcessor::getParameterText (int index)
{
    return String(parameterSet[index]->getDisplayText().c_str());
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
    parameterSet.processRealtimeEvents();
}

//==============================================================================
bool Pfm2AudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

AudioProcessorEditor* Pfm2AudioProcessor::createEditor()
{
    pfm2Editor = new Pfm2AudioProcessorEditor (this);
    printf("createEditor : %u\n", parameterSet.size());
    return pfm2Editor;
}

//==============================================================================
void Pfm2AudioProcessor::getStateInformation (MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // Here's an example of how you can use XML to make it easy and more robust:

    // Create an outer XML element..
    XmlElement xml ("PreenFM2AppStatus");

    // add some attributes to it..
    for (int p=0; p< parameterSet.size(); p++) {
        printf(">>>>>> %s = %f\n", parameterSet[p]->getName().c_str(), parameterSet[p]->getScaledValue());

        xml.setAttribute(parameterSet[p]->getName().c_str(), parameterSet[p]->getScaledValue());
    }

    // then use this helper function to stuff it into the binary blob and return it..
    copyXmlToBinary (xml, destData);
}

void Pfm2AudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.

    // This getXmlFromBinary() helper function retrieves our XML from the binary blob..
    ScopedPointer<XmlElement> xmlState (getXmlFromBinary (data, sizeInBytes));

    if (xmlState != nullptr)
    {
        // make sure that it's actually our type of XML object..
        if (xmlState->hasTagName ("PreenFM2AppStatus"))
        {
            double value;
            for (int p=0; p< parameterSet.size(); p++) {
                value  = (float) xmlState->getDoubleAttribute (parameterSet[p]->getName().c_str(), value);
                parameterSet.setScaled(parameterSet[p]->getName(), value, this);
                printf("<<<<< %s = %f\n", parameterSet[p]->getName().c_str(), value);
            }
        }
    }
}



bool Pfm2AudioProcessor::isRealtimePriority() const {
    return false;
}

/**
 * Method to be called when a parameter's value has been updated.
 */
void Pfm2AudioProcessor::onParameterUpdated(const teragon::Parameter *parameter) {
    printf("Panel Engine onParameterUpdated %s\n = %f\n",  parameter->getName().c_str(), parameter->getValue());
}

//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new Pfm2AudioProcessor();
}
