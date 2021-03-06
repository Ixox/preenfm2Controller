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


#ifndef PREENNRPN_H_INCLUDED
#define PREENNRPN_H_INCLUDED

enum {
	PREENFM2_NRPN_ALGO = 0,
	PREENFM2_NRPN_VELOCITY,
	PREENFM2_NRPN_VOICE,
	PREENFM2_NRPN_GLIDE,

	PREENFM2_NRPN_IM1 = 4,
	PREENFM2_NRPN_IM1_VELOCITY,
	PREENFM2_NRPN_IM2,
	PREENFM2_NRPN_IM2_VELOCITY,
	PREENFM2_NRPN_IM3,
	PREENFM2_NRPN_IM3_VELOCITY,
	PREENFM2_NRPN_IM4,
	PREENFM2_NRPN_IM4_VELOCITY,
	PREENFM2_NRPN_IM5,
	PREENFM2_NRPN_IM5_VELOCITY,
	PREENFM2_NRPN_IM6,
	PREENFM2_NRPN_IM6_VELOCITY,

	PREENFM2_NRPN_MIX1 = 16,
	PREENFM2_NRPN_PAN1,
	PREENFM2_NRPN_MIX2,
	PREENFM2_NRPN_PAN2,
	PREENFM2_NRPN_MIX3,
	PREENFM2_NRPN_PAN3,
	PREENFM2_NRPN_MIX4,
	PREENFM2_NRPN_PAN4,
	PREENFM2_NRPN_MIX5,
	PREENFM2_NRPN_PAN5,
	PREENFM2_NRPN_MIX6,
	PREENFM2_NRPN_PAN6,

	PREENFM2_NRPN_ARP_CLOCK = 28,
	PREENFM2_NRPN_ARP_BPM,
	PREENFM2_NRPN_ARP_DIRECTION,
	PREENFM2_NRPN_ARP_OCTAVE,
	PREENFM2_NRPN_ARP_PATTERN = 32,
	PREENFM2_NRPN_ARP_DIVISION,
	PREENFM2_NRPN_ARP_DURATION,
	PREENFM2_NRPN_ARP_LATCH,

	PREENFM2_NRPN_FILTER_TYPE = 40,
	PREENFM2_NRPN_FILTER_PARAM1,
	PREENFM2_NRPN_FILTER_PARAM2,
	PREENFM2_NRPN_FILTER_GAIN,

	PREENFM2_NRPN_OPERATOR1_SHAPE = 44,
	PREENFM2_NRPN_OPERATOR1_FREQUENCY_TYPE,
	PREENFM2_NRPN_OPERATOR1_FREQUENCY,
	PREENFM2_NRPN_OPERATOR1_FREQUENCY_FINE_TUNE,

	PREENFM2_NRPN_OPERATOR2_SHAPE,
	PREENFM2_NRPN_OPERATOR2_FREQUENCY_TYPE,
	PREENFM2_NRPN_OPERATOR2_FREQUENCY,
	PREENFM2_NRPN_OPERATOR2_FREQUENCY_FINE_TUNE,

	PREENFM2_NRPN_OPERATOR3_SHAPE,
	PREENFM2_NRPN_OPERATOR3_FREQUENCY_TYPE,
	PREENFM2_NRPN_OPERATOR3_FREQUENCY,
	PREENFM2_NRPN_OPERATOR3_FREQUENCY_FINE_TUNE,

	PREENFM2_NRPN_OPERATOR4_SHAPE,
	PREENFM2_NRPN_OPERATOR4_FREQUENCY_TYPE,
	PREENFM2_NRPN_OPERATOR4_FREQUENCY,
	PREENFM2_NRPN_OPERATOR4_FREQUENCY_FINE_TUNE,

	PREENFM2_NRPN_OPERATOR5_SHAPE,
	PREENFM2_NRPN_OPERATOR5_FREQUENCY_TYPE,
	PREENFM2_NRPN_OPERATOR5_FREQUENCY,
	PREENFM2_NRPN_OPERATOR5_FREQUENCY_FINE_TUNE,

	PREENFM2_NRPN_OPERATOR6_SHAPE,
	PREENFM2_NRPN_OPERATOR6_FREQUENCY_TYPE,
	PREENFM2_NRPN_OPERATOR6_FREQUENCY,
	PREENFM2_NRPN_OPERATOR6_FREQUENCY_FINE_TUNE,

	PREENFM2_NRPN_ENV1_ATTK = 68,
	PREENFM2_NRPN_ENV1_ATTK_LEVEL,
	PREENFM2_NRPN_ENV1_DECAY,
	PREENFM2_NRPN_ENV1_DECAY_LEVEL,
	PREENFM2_NRPN_ENV1_SUSTAIN,
	PREENFM2_NRPN_ENV1_SUSTAIN_LEVEL,
	PREENFM2_NRPN_ENV1_RELEASE,
	PREENFM2_NRPN_ENV1_RELEASE_LEVEL,

	PREENFM2_NRPN_ENV2_ATTK,
	PREENFM2_NRPN_ENV2_ATTK_LEVEL,
	PREENFM2_NRPN_ENV2_DECAY,
	PREENFM2_NRPN_ENV2_DECAY_LEVEL,
	PREENFM2_NRPN_ENV2_SUSTAIN,
	PREENFM2_NRPN_ENV2_SUSTAIN_LEVEL,
	PREENFM2_NRPN_ENV2_RELEASE,
	PREENFM2_NRPN_ENV2_RELEASE_LEVEL,

	PREENFM2_NRPN_ENV3_ATTK,
	PREENFM2_NRPN_ENV3_ATTK_LEVEL,
	PREENFM2_NRPN_ENV3_DECAY,
	PREENFM2_NRPN_ENV3_DECAY_LEVEL,
	PREENFM2_NRPN_ENV3_SUSTAIN,
	PREENFM2_NRPN_ENV3_SUSTAIN_LEVEL,
	PREENFM2_NRPN_ENV3_RELEASE,
	PREENFM2_NRPN_ENV3_RELEASE_LEVEL,

	PREENFM2_NRPN_ENV4_ATTK,
	PREENFM2_NRPN_ENV4_ATTK_LEVEL,
	PREENFM2_NRPN_ENV4_DECAY,
	PREENFM2_NRPN_ENV4_DECAY_LEVEL,
	PREENFM2_NRPN_ENV4_SUSTAIN,
	PREENFM2_NRPN_ENV4_SUSTAIN_LEVEL,
	PREENFM2_NRPN_ENV4_RELEASE,
	PREENFM2_NRPN_ENV4_RELEASE_LEVEL,

	PREENFM2_NRPN_ENV5_ATTK,
	PREENFM2_NRPN_ENV5_ATTK_LEVEL,
	PREENFM2_NRPN_ENV5_DECAY,
	PREENFM2_NRPN_ENV5_DECAY_LEVEL,
	PREENFM2_NRPN_ENV5_SUSTAIN,
	PREENFM2_NRPN_ENV5_SUSTAIN_LEVEL,
	PREENFM2_NRPN_ENV5_RELEASE,
	PREENFM2_NRPN_ENV5_RELEASE_LEVEL,

	PREENFM2_NRPN_ENV6_ATTK,
	PREENFM2_NRPN_ENV6_ATTK_LEVEL,
	PREENFM2_NRPN_ENV6_DECAY,
	PREENFM2_NRPN_ENV6_DECAY_LEVEL,
	PREENFM2_NRPN_ENV6_SUSTAIN,
	PREENFM2_NRPN_ENV6_SUSTAIN_LEVEL,
	PREENFM2_NRPN_ENV6_RELEASE,
	PREENFM2_NRPN_ENV6_RELEASE_LEVEL,

	PREENFM2_NRPN_MTX1_SOURCE = 116,
	PREENFM2_NRPN_MTX1_MULTIPLIER,
	PREENFM2_NRPN_MTX1_DESTINATION1,
    PREENFM2_NRPN_MTX1_DESTINATION2,

	PREENFM2_NRPN_MTX2_SOURCE,
	PREENFM2_NRPN_MTX2_MULTIPLIER,
	PREENFM2_NRPN_MTX2_DESTINATION,
	PREENFM2_NRPN_MTX2_EMPTY,

	PREENFM2_NRPN_MTX3_SOURCE,
	PREENFM2_NRPN_MTX3_MULTIPLIER,
	PREENFM2_NRPN_MTX3_DESTINATION,
	PREENFM2_NRPN_MTX3_EMPTY,

	PREENFM2_NRPN_MTX4_SOURCE,
	PREENFM2_NRPN_MTX4_MULTIPLIER,
	PREENFM2_NRPN_MTX4_DESTINATION,
	PREENFM2_NRPN_MTX4_EMPTY,

	PREENFM2_NRPN_MTX5_SOURCE,
	PREENFM2_NRPN_MTX5_MULTIPLIER,
	PREENFM2_NRPN_MTX5_DESTINATION,
	PREENFM2_NRPN_MTX5_EMPTY,

	PREENFM2_NRPN_MTX6_SOURCE,
	PREENFM2_NRPN_MTX6_MULTIPLIER,
	PREENFM2_NRPN_MTX6_DESTINATION,
	PREENFM2_NRPN_MTX6_EMPTY,

	PREENFM2_NRPN_MTX7_SOURCE,
	PREENFM2_NRPN_MTX7_MULTIPLIER,
	PREENFM2_NRPN_MTX7_DESTINATION,
	PREENFM2_NRPN_MTX7_EMPTY,

	PREENFM2_NRPN_MTX8_SOURCE,
	PREENFM2_NRPN_MTX8_MULTIPLIER,
	PREENFM2_NRPN_MTX8_DESTINATION,
	PREENFM2_NRPN_MTX8_EMPTY,

	PREENFM2_NRPN_MTX9_SOURCE,
	PREENFM2_NRPN_MTX9_MULTIPLIER,
	PREENFM2_NRPN_MTX9_DESTINATION,
	PREENFM2_NRPN_MTX9_EMPTY,

	PREENFM2_NRPN_MTX10_SOURCE,
	PREENFM2_NRPN_MTX10_MULTIPLIER,
	PREENFM2_NRPN_MTX10_DESTINATION,
	PREENFM2_NRPN_MTX10_EMPTY,

	PREENFM2_NRPN_MTX11_SOURCE,
	PREENFM2_NRPN_MTX11_MULTIPLIER,
	PREENFM2_NRPN_MTX11_DESTINATION,
	PREENFM2_NRPN_MTX11_EMPTY,

	PREENFM2_NRPN_MTX12_SOURCE,
	PREENFM2_NRPN_MTX12_MULTIPLIER,
	PREENFM2_NRPN_MTX12_DESTINATION,
	PREENFM2_NRPN_MTX12_EMPTY,

	PREENFM2_NRPN_LFO1_SHAPE = 168,
	PREENFM2_NRPN_LFO1_FREQUENCY,
	PREENFM2_NRPN_LFO1_BIAS,
	PREENFM2_NRPN_LFO1_KSYN,

	PREENFM2_NRPN_LFO2_SHAPE,
	PREENFM2_NRPN_LFO2_FREQUENCY,
	PREENFM2_NRPN_LFO2_BIAS,
	PREENFM2_NRPN_LFO2_KSYN,

	PREENFM2_NRPN_LFO3_SHAPE,
	PREENFM2_NRPN_LFO3_FREQUENCY,
	PREENFM2_NRPN_LFO3_BIAS,
	PREENFM2_NRPN_LFO3_KSYN,


	PREENFM2_NRPN_FREE_ENV1_ATTK = 180,
	PREENFM2_NRPN_FREE_ENV1_DECAY,
	PREENFM2_NRPN_FREE_ENV1_SUSTAIN,
	PREENFM2_NRPN_FREE_ENV1_RELEASE,

	PREENFM2_NRPN_FREE_ENV2_SILENCE = 184,
	PREENFM2_NRPN_FREE_ENV2_ATTK,
	PREENFM2_NRPN_FREE_ENV2_DECAY,
	PREENFM2_NRPN_FREE_ENV2_LOOP,

	PREENFM2_NRPN_STEPSEQ1_BPM = 188,
	PREENFM2_NRPN_STEPSEQ1_GATE,
	PREENFM2_NRPN_STEPSEQ1_UNUSED1,
	PREENFM2_NRPN_STEPSEQ1_UNUSED2,

	PREENFM2_NRPN_STEPSEQ2_BPM = 192,
	PREENFM2_NRPN_STEPSEQ2_GATE,
	PREENFM2_NRPN_STEPSEQ2_UNUSED1,
	PREENFM2_NRPN_STEPSEQ2_UNUSED2,

	PREENFM2_NRPN_LFO_PHASE1 = 196,
	PREENFM2_NRPN_LFO_PHASE2,
	PREENFM2_NRPN_LFO_PHASE3,
	PREENFM2_NRPN_LFO_UNUSED1,

	PREENFM2_NRPN_NOTE1_BEFORE = 200,
	PREENFM2_NRPN_NOTE1_BREAKNOTE,
	PREENFM2_NRPN_NOTE1_AFTER,
	PREENFM2_NRPN_NOTE1_UNUSED1,

	PREENFM2_NRPN_NOTE2_BEFORE = 204,
	PREENFM2_NRPN_NOTE2_BREAKNOTE,
	PREENFM2_NRPN_NOTE2_AFTER,
	PREENFM2_NRPN_NOTE2_UNUSED1,

	PREENFM2_NRPN_GLIDE_TYPE = 216,
	PREENFM2_NRPN_UNISON_SPREAD,
	PREENFM2_NRPN_UNISON_DETUNE,
	PREENFM2_NRPN_VERSION,

	PREENFM2_NRPN_LETTER1 = 228,
	PREENFM2_NRPN_LETTER2,
	PREENFM2_NRPN_LETTER3,
	PREENFM2_NRPN_LETTER4,
	PREENFM2_NRPN_LETTER5,
	PREENFM2_NRPN_LETTER6,
	PREENFM2_NRPN_LETTER7,
	PREENFM2_NRPN_LETTER8,
	PREENFM2_NRPN_LETTER9,
	PREENFM2_NRPN_LETTER10,
	PREENFM2_NRPN_LETTER11,
	PREENFM2_NRPN_LETTER12,

	PREENFM2_NRPN_STEPSEQ1_STEP1 = 256,
	PREENFM2_NRPN_STEPSEQ1_STEP2,
	PREENFM2_NRPN_STEPSEQ1_STEP3,
	PREENFM2_NRPN_STEPSEQ1_STEP4,
	PREENFM2_NRPN_STEPSEQ1_STEP5,
	PREENFM2_NRPN_STEPSEQ1_STEP6,
	PREENFM2_NRPN_STEPSEQ1_STEP7,
	PREENFM2_NRPN_STEPSEQ1_STEP8,
	PREENFM2_NRPN_STEPSEQ1_STEP9,
	PREENFM2_NRPN_STEPSEQ1_STEP10,
	PREENFM2_NRPN_STEPSEQ1_STEP11,
	PREENFM2_NRPN_STEPSEQ1_STEP12,
	PREENFM2_NRPN_STEPSEQ1_STEP13,
	PREENFM2_NRPN_STEPSEQ1_STEP14,
	PREENFM2_NRPN_STEPSEQ1_STEP15,
	PREENFM2_NRPN_STEPSEQ1_STEP16,
	PREENFM2_NRPN_STEPSEQ2_STEP1 = 384,
	PREENFM2_NRPN_STEPSEQ2_STEP2,
	PREENFM2_NRPN_STEPSEQ2_STEP3,
	PREENFM2_NRPN_STEPSEQ2_STEP4,
	PREENFM2_NRPN_STEPSEQ2_STEP5,
	PREENFM2_NRPN_STEPSEQ2_STEP6,
	PREENFM2_NRPN_STEPSEQ2_STEP7,
	PREENFM2_NRPN_STEPSEQ2_STEP8,
	PREENFM2_NRPN_STEPSEQ2_STEP9,
	PREENFM2_NRPN_STEPSEQ2_STEP10,
	PREENFM2_NRPN_STEPSEQ2_STEP11,
	PREENFM2_NRPN_STEPSEQ2_STEP12,
	PREENFM2_NRPN_STEPSEQ2_STEP13,
	PREENFM2_NRPN_STEPSEQ2_STEP14,
	PREENFM2_NRPN_STEPSEQ2_STEP15,
	PREENFM2_NRPN_STEPSEQ2_STEP16,

	// Part of the UI
	PREENFM_NRPN_PFMTYPE = 2044
};

#endif  // PREENNRPN_H_INCLUDED
