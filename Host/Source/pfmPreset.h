/*
* Copyright 2020 Xavier Hosxe
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

#pragma once

#include <stdint.h>
#include "JuceHeader.h"
#include "../../Plugin/Source/PluginProcessor.h"


enum ConvertDirectionEnum {
    PARAM_TO_EDITOR = 1,
    EDITOR_TO_PARAM
};


enum {
    GLIDE_TYPE_OFF = 0,
    GLIDE_TYPE_OVERLAP,
    GLIDE_TYPE_ALWAYS
};

enum {
    PLAY_MODE_MONO = 0,
    PLAY_MODE_POLY,
    PLAY_MODE_UNISON
};

struct Engine1Params {
    float algo;
    float velocity;
    float playMode;
    float glideSpeed;
};

struct Engine2Params {
    float glideType;
    float unisonSpread;
    float unisonDetune;
    float pfm3Version;
};


struct EngineArp1 {
    float clock;
    float BPM;
    float direction;
    float octave;
};

struct EngineArp2 {
    float pattern;
    float division;
    float duration;
    float latche;
};

typedef uint32_t arp_pattern_t;

struct EngineArpUserPatterns {
    arp_pattern_t patterns[4];
};

struct EngineIm1 {
    float modulationIndex1;
    float modulationIndexVelo1;
    float modulationIndex2;
    float modulationIndexVelo2;
};

struct EngineIm2 {
    float modulationIndex3;
    float modulationIndexVelo3;
    float modulationIndex4;
    float modulationIndexVelo4;
};

struct EngineIm3 {
    float modulationIndex5;
    float modulationIndexVelo5;
    float modulationIndex6;
    float modulationIndexVelo6;
};

struct FlashEngineIm1 {
    float modulationIndex1;
    float modulationIndex2;
    float modulationIndex3;
    float modulationIndex4;
};

struct FlashEngineIm2 {
    float modulationIndex5;
    float modulationIndex6;
    float notUsed1;
    float notUsed2;
};

struct FlashEngineVeloIm1 {
    float modulationIndexVelo1;
    float modulationIndexVelo2;
    float modulationIndexVelo3;
    float modulationIndexVelo4;
};

struct FlashEngineVeloIm2 {
    float modulationIndexVelo5;
    float modulationIndexVelo6;
    float notUsed1;
    float notUsed2;
};

struct EngineMix1 {
    float mixOsc1;
    float panOsc1;
    float mixOsc2;
    float panOsc2;
};

struct EngineMix2 {
    float mixOsc3;
    float panOsc3;
    float mixOsc4;
    float panOsc4;
};

struct EngineMix3 {
    float mixOsc5;
    float panOsc5;
    float mixOsc6;
    float panOsc6;
};

struct EnvelopeParamsA {
    float attackTime;
    float attackLevel;
    float decayTime;
    float decayLevel;
};

struct EnvelopeParamsB {
    float sustainTime;
    float sustainLevel;
    float releaseTime;
    float releaseLevel;
};

struct EnvelopeParams {
    float attack;
    float decay;
    float sustain;
    float release;
};

struct Envelope2Params {
    float silence;
    float attack;
    float decay;
    float loop;
};

struct OscillatorParams {
    float shape; // OSC_SHAPE_*
    float frequencyType; // OSC_FT_*
    float frequencyMul;
    float detune;
};

struct MatrixRowParams {
    float source;
    float mul;
    float dest1;
    float dest2;
};

struct LfoParams {
    float shape; // LFO_SHAPE_*
    float freq;  // lfoFreq[]*
    float bias;
    float keybRamp;
};

struct StepSequencerParams {
    float bpm;
    float gate;
    float unused1;
    float unused2;
};

struct StepSequencerSteps {
    char steps[16];
};

struct EffectRowParams {
    float type;
    float param1;
    float param2;
    float param3;
};

struct PerformanceRowParams {
    float perf1;
    float perf2;
    float perf3;
    float perf4;
};

struct LfoPhaseRowParams {
    float phaseLfo1;
    float phaseLfo2;
    float phaseLfo3;
    float unused1;
};

struct MidiNoteCurveRowParams {
    float curveBefore;
    float breakNote;
    float curveAfter;
    float unused1;
};


// Storage maping of the parameters
struct FlashSynthParams {
    struct Engine1Params engine1;
    struct FlashEngineIm1 flashEngineIm1;
    struct FlashEngineIm2 flashEngineIm2;
    struct EngineMix1 engineMix1;
    struct EngineMix2 engineMix2;
    struct EngineMix3 engineMix3;
    struct OscillatorParams osc1;
    struct OscillatorParams osc2;
    struct OscillatorParams osc3;
    struct OscillatorParams osc4;
    struct OscillatorParams osc5;
    struct OscillatorParams osc6;
    struct EnvelopeParamsA env1a;
    struct EnvelopeParamsB env1b;
    struct EnvelopeParamsA env2a;
    struct EnvelopeParamsB env2b;
    struct EnvelopeParamsA env3a;
    struct EnvelopeParamsB env3b;
    struct EnvelopeParamsA env4a;
    struct EnvelopeParamsB env4b;
    struct EnvelopeParamsA env5a;
    struct EnvelopeParamsB env5b;
    struct EnvelopeParamsA env6a;
    struct EnvelopeParamsB env6b;
    struct MatrixRowParams matrixRowState1;
    struct MatrixRowParams matrixRowState2;
    struct MatrixRowParams matrixRowState3;
    struct MatrixRowParams matrixRowState4;
    struct MatrixRowParams matrixRowState5;
    struct MatrixRowParams matrixRowState6;
    struct MatrixRowParams matrixRowState7;
    struct MatrixRowParams matrixRowState8;
    struct MatrixRowParams matrixRowState9;
    struct MatrixRowParams matrixRowState10;
    struct MatrixRowParams matrixRowState11;
    struct MatrixRowParams matrixRowState12;
    struct LfoParams lfoOsc1;
    struct LfoParams lfoOsc2;
    struct LfoParams lfoOsc3;
    struct EnvelopeParams lfoEnv1;
    struct Envelope2Params lfoEnv2;
    struct StepSequencerParams lfoSeq1;
    struct StepSequencerParams lfoSeq2;
    struct StepSequencerSteps lfoSteps1;
    struct StepSequencerSteps lfoSteps2;
    char presetName[13];
    struct EngineArp1 engineArp1;
    struct EngineArp2 engineArp2;
    struct FlashEngineVeloIm1 flashEngineVeloIm1;
    struct FlashEngineVeloIm2 flashEngineVeloIm2;
    struct EffectRowParams effect;
    struct EngineArpUserPatterns engineArpUserPatterns;
    struct LfoPhaseRowParams lfoPhases;
    struct MidiNoteCurveRowParams midiNote1Curve;
    struct MidiNoteCurveRowParams midiNote2Curve;
    struct Engine2Params engine2;
};


struct OneSynthParams {
    struct Engine1Params engine1;
    struct EngineIm1 engineIm1;
    struct EngineIm2 engineIm2;
    struct EngineIm3 engineIm3;
    struct EngineMix1 engineMix1;
    struct EngineMix2 engineMix2;
    struct EngineMix3 engineMix3;
    struct EngineArp1 engineArp1;
    struct EngineArp2 engineArp2;
    struct EngineArpUserPatterns engineArpUserPatterns;
    struct EffectRowParams effect;
    struct OscillatorParams osc1;
    struct OscillatorParams osc2;
    struct OscillatorParams osc3;
    struct OscillatorParams osc4;
    struct OscillatorParams osc5;
    struct OscillatorParams osc6;
    struct EnvelopeParamsA env1a;
    struct EnvelopeParamsB env1b;
    struct EnvelopeParamsA env2a;
    struct EnvelopeParamsB env2b;
    struct EnvelopeParamsA env3a;
    struct EnvelopeParamsB env3b;
    struct EnvelopeParamsA env4a;
    struct EnvelopeParamsB env4b;
    struct EnvelopeParamsA env5a;
    struct EnvelopeParamsB env5b;
    struct EnvelopeParamsA env6a;
    struct EnvelopeParamsB env6b;
    struct MatrixRowParams matrixRowState1;
    struct MatrixRowParams matrixRowState2;
    struct MatrixRowParams matrixRowState3;
    struct MatrixRowParams matrixRowState4;
    struct MatrixRowParams matrixRowState5;
    struct MatrixRowParams matrixRowState6;
    struct MatrixRowParams matrixRowState7;
    struct MatrixRowParams matrixRowState8;
    struct MatrixRowParams matrixRowState9;
    struct MatrixRowParams matrixRowState10;
    struct MatrixRowParams matrixRowState11;
    struct MatrixRowParams matrixRowState12;
    struct PerformanceRowParams performance1;
    struct LfoParams lfoOsc1;
    struct LfoParams lfoOsc2;
    struct LfoParams lfoOsc3;
    struct LfoPhaseRowParams lfoPhases;
    struct EnvelopeParams lfoEnv1;
    struct Envelope2Params lfoEnv2;
    struct StepSequencerParams lfoSeq1;
    struct StepSequencerParams lfoSeq2;
    struct MidiNoteCurveRowParams midiNote1Curve;
    struct MidiNoteCurveRowParams midiNote2Curve;
    struct StepSequencerSteps lfoSteps1;
    struct StepSequencerSteps lfoSteps2;
    struct Engine2Params engine2;
    char presetName[13];
};



class PfmPreset {
public:
    PfmPreset();
    virtual ~PfmPreset() {};

    void savePresetsFolder(File& bankFile);
    void savePfmBankFile(File& presetFolder);
    void organizeBank(File& bankFile);


private:
    void reorderBank(String folderPath, String bankFileName, MemoryBlock& bankMem);
    void getEditorPatchMemoryBlock(int presetNumber, MemoryBlock& presetMemBlock);
    void updateDefaultValuesForOldPreset(FlashSynthParams* params);
    void convertParameters(float* values, int nrpnStartParam, int numberOfFloats, ConvertDirectionEnum direction);
    void convert(FlashSynthParams* paramSource, ConvertDirectionEnum direction);
    File* bankFile_;

    MemoryBlock bankMemory_;
    ScopedPointer<Pfm2AudioProcessor> processor_;
    DocumentWindow* reorderingWindow;
};
