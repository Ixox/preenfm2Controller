/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic startup code for a Juce application.

  ==============================================================================
 */

#include "PluginProcessor.h"
#include "PluginEditor.h"
#include "MidifiedParameter.h"

int Midificator::paramIndexCounter = 0;

//==============================================================================
Pfm2AudioProcessor::Pfm2AudioProcessor()
{
	// Important !!!! reset paramIndexCounter.
	Midificator::resetParamIndexCounter();

	pfm2Editor = nullptr;
	teragon::Parameter* newParam;
	int parameterIndex = 0;
	// Algo
	int nrpmParam = PREENFM2_NRPN_ALGO;
	newParam = new MidifiedFloatParameter(&nrpmParameterMap, String("Algo").toRawUTF8(), nrpmParam, 1, 1, 28,1);
	newParam->addObserver(this);
	parameterSet.add(newParam);
	nrpmIndex[nrpmParam] = parameterIndex++;

	// Velocity
	nrpmParam = PREENFM2_NRPN_VELOCITY;
	newParam = new MidifiedFloatParameter(&nrpmParameterMap, String("Velocity").toRawUTF8(), nrpmParam, 1, 0, 16,1);
	newParam->addObserver(this);
	parameterSet.add(newParam);
	nrpmIndex[nrpmParam] = parameterIndex++;

	// Voices
	nrpmParam = PREENFM2_NRPN_VOICE;
	newParam = new MidifiedFloatParameter(&nrpmParameterMap, String("Voices").toRawUTF8(), nrpmParam, 1, 0, 16,1);
	newParam->addObserver(this);
	parameterSet.add(newParam);
	nrpmIndex[nrpmParam] = parameterIndex++;

	// Velocity
	nrpmParam = PREENFM2_NRPN_GLIDE;
	newParam = new MidifiedFloatParameter(&nrpmParameterMap, String("Glide").toRawUTF8(), nrpmParam, 1, 0, 10,1);
	newParam->addObserver(this);
	parameterSet.add(newParam);
	nrpmIndex[nrpmParam] = parameterIndex++;

	for (int k=0; k<6; k++) {
		nrpmParam = PREENFM2_NRPN_MIX1 + k * 2;
		newParam = new MidifiedFloatParameter(&nrpmParameterMap, String("Volume "+String(k+1)).toRawUTF8(), nrpmParam, 100, 0,1,1);
		newParam->addObserver(this);
		parameterSet.add(newParam);
		nrpmIndex[nrpmParam] = parameterIndex++;
	}
	for (int k=0; k<6; k++) {
		nrpmParam = PREENFM2_NRPN_PAN1 + k * 2;
		newParam = new MidifiedFloatParameter(&nrpmParameterMap, String("Pan "+String(k+1)).toRawUTF8(), nrpmParam, 100, -1, 1, 0);
		newParam->addObserver(this);
		parameterSet.add(newParam);
		nrpmIndex[nrpmParam] = parameterIndex++;
	}
	for (int k=0; k<5; k++) {
		nrpmParam = PREENFM2_NRPN_IM1 + k * 2;
		newParam = new MidifiedFloatParameter(&nrpmParameterMap, String("IM "+String(k+1)).toRawUTF8(), nrpmParam, 100, 0,16,1.5);
		newParam->addObserver(this);
		parameterSet.add(newParam);
		nrpmIndex[nrpmParam] = parameterIndex++;
	}
	for (int k=0; k<5; k++) {
		nrpmParam = PREENFM2_NRPN_IM1_VELOCITY + k * 2;
		newParam = new MidifiedFloatParameter(&nrpmParameterMap, String("IM Velocity "+String(k+1)).toRawUTF8(), nrpmParam, 100, 0,16,1);
		newParam->addObserver(this);
		parameterSet.add(newParam);
		nrpmIndex[nrpmParam] = parameterIndex++;
	}
	// OPERATOR
	for (int k=0; k<6; k++) {
		//        opShape[k] = new ComboBox("OP"+String(k+1)+" Shape");
		//		0, 7,
		nrpmParam = PREENFM2_NRPN_OPERATOR1_SHAPE + k * 4;
		newParam = new MidifiedFloatParameter(&nrpmParameterMap, String("Op"+String(k+1)+" Shape").toRawUTF8(), nrpmParam, 1, 1, 8, 1);
		newParam->addObserver(this);
		parameterSet.add(newParam);
		nrpmIndex[nrpmParam] = parameterIndex++;

	}
	for (int k=0; k<6; k++) {
		//        opFrequencyType[k] = new ComboBox("Op"+ String(1) + " Freq Type");
		//        0, 1
		nrpmParam = PREENFM2_NRPN_OPERATOR1_FREQUENCY_TYPE + k * 4;
		newParam = new MidifiedFloatParameter(&nrpmParameterMap, String("Op"+String(k+1)+" Freq Type").toRawUTF8(), nrpmParam, 1, 1, 2, 1);
		newParam->addObserver(this);
		parameterSet.add(newParam);
		nrpmIndex[nrpmParam] = parameterIndex++;
	}
	for (int k=0; k<6; k++) {
		//
		//        opFrequency[k] = new Slider("Op" + String(k+1) + " Frequency");
		//        opFrequency[k]->setRange (0, 16, 1.0f / 12.0f);
		nrpmParam = PREENFM2_NRPN_OPERATOR1_FREQUENCY + k * 4;
		newParam = new MidifiedFloatParameter(&nrpmParameterMap, String("Op" + String(k+1) + " Frequency").toRawUTF8(), nrpmParam, 100, 0, 16, 1.0);
		newParam->addObserver(this);
		parameterSet.add(newParam);
		nrpmIndex[nrpmParam] = parameterIndex++;
	}
	for (int k=0; k<6; k++) {
		//        opFrequencyFineTune[k] = new Slider("Op"+ String(k+1)+ " Fine Tune");
		//        opFrequencyFineTune[k]->setRange (-1.0f, 1.0f, .01f);
		nrpmParam = PREENFM2_NRPN_OPERATOR1_FREQUENCY_FINE_TUNE + k * 4;
		newParam = new MidifiedFloatParameter(&nrpmParameterMap, String("Op"+ String(k+1)+ " Fine Tune").toRawUTF8(), nrpmParam, 100, -1, 1, 0);
		newParam->addObserver(this);
		parameterSet.add(newParam);
		nrpmIndex[nrpmParam] = parameterIndex++;

	}
	for (int k=0; k<6; k++) {
		for (int p=0; p<4; p++) {
			const char* pointName[] = { " Attk", " Deca", " Sust", " Rele" };
			nrpmParam = PREENFM2_NRPN_ENV1_ATTK + k * 8 + p * 2;
			newParam = new MidifiedFloatParameter(&nrpmParameterMap, String("Op"+String(k+1)+" Env"+ pointName[p]).toRawUTF8(), nrpmParam, 100, 0, 16, 1);
			newParam->addObserver(this);
			parameterSet.add(newParam);
			nrpmIndex[nrpmParam] = parameterIndex++;
		}
		for (int p=0; p<4; p++) {
			const char* pointName[] = { " Attk lvl", " Deca lvl", " Sust lvl", " Rele lvl" };
			float level[] = { 1.0, 1.0, 1.0, 0.0 };
			nrpmParam = PREENFM2_NRPN_ENV1_ATTK_LEVEL + k * 8 + p * 2;
			newParam = new MidifiedFloatParameter(&nrpmParameterMap, String("Op"+String(k+1)+" Env"+ pointName[p]).toRawUTF8(), nrpmParam, 100, 0, 1, level[p]);
			newParam->addObserver(this);
			parameterSet.add(newParam);
			nrpmIndex[nrpmParam] = parameterIndex++;
		}
		//        enveloppe[k]->setName (TRANS("enveloppe " + String(k+1)));
		//
	}


	midiMessageCollector.reset(44100);
	uiNeedUpdate = false;
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
	return parameterSet.size();
}

float Pfm2AudioProcessor::getParameter (int index)
{
	return parameterSet[index]->getScaledValue();
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
	handleIncomingMidiBuffer(midiMessages, buffer.getNumSamples());

	// Clear sound
	for (int i = 0; i < getNumOutputChannels(); ++i)
		buffer.clear (i, 0, buffer.getNumSamples());

	// dispatch realtime events to non realtime observer
	parameterSet.processRealtimeEvents();
	midiMessageCollector.removeNextBlockOfMessages(midiMessages,  buffer.getNumSamples());
	if (pfm2Editor && uiNeedUpdate) {
		pfm2Editor->mustUpdateUI();
	}
	uiNeedUpdate = false;
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
		printf("%s  Min:%f - Max:%f\n", parameterSet[p]->getName().c_str(), parameterSet[p]->getMinValue(), parameterSet[p]->getMaxValue());

		xml.setAttribute(teragon::Parameter::makeSafeName(parameterSet[p]->getName()).c_str(), parameterSet[p]->getScaledValue());
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
				value  = (float) xmlState->getDoubleAttribute (teragon::Parameter::makeSafeName(parameterSet[p]->getName()).c_str(), value);
				parameterSet.setScaled(parameterSet[p]->getName(), value, this);
				printf("<<<<< %s = %f\n", parameterSet[p]->getName().c_str(), value);
			}
		}
	}
}



bool Pfm2AudioProcessor::isRealtimePriority() const {
	return true;
}


// 
void Pfm2AudioProcessor::handleIncomingMidiBuffer(MidiBuffer &buffer, int numberOfSamples) {
	if (!buffer.isEmpty()) {
		MidiBuffer newBuffer;
		MidiMessage midiMessage;
		int samplePosition;
		MidiBuffer::Iterator midiIterator(buffer);
		while (midiIterator.getNextEvent(midiMessage, samplePosition)) {
			bool copyMessageInNewBuffer = true;

			if (midiMessage.isController()) {
				switch (midiMessage.getControllerNumber()) {
				case 99:
					currentNrpn.paramMSB = midiMessage.getControllerValue();
					copyMessageInNewBuffer = false;
					break;
				case 98:
					currentNrpn.paramLSB = midiMessage.getControllerValue();
					copyMessageInNewBuffer = false;
					break;
				case 6:
					currentNrpn.valueMSB = midiMessage.getControllerValue();
					copyMessageInNewBuffer = false;
					break;
				case 38:
				{
					currentNrpn.valueLSB = midiMessage.getControllerValue();
					copyMessageInNewBuffer = false;
					int param = (int)(currentNrpn.paramMSB << 7) + currentNrpn.paramLSB;
					int value = (int)(currentNrpn.valueMSB << 7) + currentNrpn.valueLSB;

					const MessageManagerLock mmLock;
					handleIncomingNrpn(param, value);
					break;
				}
				}
			}
			if (copyMessageInNewBuffer) {
				newBuffer.addEvent(midiMessage, samplePosition);
			}
		}
		buffer.swapWith(newBuffer);
	}
}

/**
 * Values updated by the HOST
 * . Modify value
    . Send NRPN
	. Refresh UI
 */
void Pfm2AudioProcessor::setParameter (int index, float newValue)
{
	parameterSet.setScaled(index, newValue, this);

	printf("Pfm2AudioProcessor::setParameter  %d : %f\r\n", index, newValue);
	const MidifiedFloatParameter* midifiedFP = dynamic_cast<const MidifiedFloatParameter*>(parameterSet[index]);
	if (midifiedFP != nullptr) {
		int index = midifiedFP->getParamIndex();
		// send nrpn
		midifiedFP->addNrpn(midiMessageCollector, midifiedFP->getValue());
	}
	// REDRAW UI : must be done in processblock after parameterSet is really udpated.
	uiNeedUpdate = true;
}


/**
 * Values updated by the PreenFM2
 * Here the values has to be modified
  . Modify Value
  . tell host
  . refresh UI
 */
void Pfm2AudioProcessor::handleIncomingNrpn(int param, int value) {
	// NRPM from the preenFM2 

	int index = nrpmIndex[param];
	Parameter* parameter = parameterSet[index];

	printf("Pfm2AudioProcessor::handleIncomingNrpn(%d, %d) : %s\r\n", param, value, parameter->getName().c_str());

	MidifiedFloatParameter* midifiedFP = dynamic_cast<MidifiedFloatParameter*>(parameter);
	if (parameter != nullptr) {
		float newFloatValue = midifiedFP->getValueFromNrpn(value);
		// Set the value but we don't want to be notified
		parameterSet.set(index, midifiedFP->getValueFromNrpn(value), this);
		// Notify host
		sendParamChangeMessageToListeners(index, midifiedFP->getScaledValueFromNrpn(value));
		// REDRAW UI : must be done in processblock after parameterSet is really udpated.
		uiNeedUpdate = true;
	}
}

/**
 * Values updated by the UI
 * Here values are already up to date
 . tell host
 . Send NRPN
 */
void Pfm2AudioProcessor::onParameterUpdated(const teragon::Parameter *parameter) {
	printf("Pfm2AudioProcessor::onParameterUpdated %s = %f\n",  parameter->getName().c_str(), parameter->getValue());

	const MidifiedFloatParameter* midifiedFP = dynamic_cast<const MidifiedFloatParameter*>(parameter);
	if (midifiedFP != nullptr) {
		int index = midifiedFP->getParamIndex();
		// Notify host
		sendParamChangeMessageToListeners(index, parameter->getScaledValue());
		// send nrpn
		midifiedFP->addNrpn(midiMessageCollector, parameter->getValue());
	}
}




//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
	return new Pfm2AudioProcessor();
}

