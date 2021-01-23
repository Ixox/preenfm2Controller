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

#include "pfmPreset.h"

extern Pfm2AudioProcessor* JUCE_API JUCE_CALLTYPE createPluginFilter();
extern const uint32 magicXmlNumber = 0x21324356;


PfmPreset::PfmPreset() {
    
    //for (int p = 0; p < 128; p++) {
    //    swapAllFloats(p);
    //}

    processor_ = createPluginFilter();
}


void PfmPreset::swapAllFloats(int presetNumber) {
    FlashSynthParams* paramSource = (FlashSynthParams*)((char*)bankMemory_.getData() + 1024 * presetNumber);

    float* floatToSwap = (float*)& paramSource->engine1;

    // We stop at presetName to swape names
    while (floatToSwap < (float*)paramSource->presetName) {
        *floatToSwap = ByteOrder::swap(*floatToSwap);
        floatToSwap++;
    }

    float* fFrom = (float*)&paramSource->engineArp1;

    while (floatToSwap < ((float*)&paramSource->engine2) + 4) {
        *floatToSwap = ByteOrder::swap(*floatToSwap);
        floatToSwap++;
    }
}

void PfmPreset::savePresets(File& bankFile) {
    bankFile_ = new File(bankFile);
    bankFile_->loadFileAsData(bankMemory_);

    String folderPath = bankFile_->getParentDirectory().getFullPathName();
    String folderName = bankFile_->getFileNameWithoutExtension();


    File parentFolder(folderPath + File::getSeparatorString() + folderName);
    if (!parentFolder.exists()) {
        parentFolder.createDirectory();
    }
    else if (!parentFolder.isDirectory()) {
        AlertWindow::showMessageBoxAsync(AlertWindow::WarningIcon,
            TRANS("Error"),
            TRANS("Folder cannot be created for this bank"));
        return;
    }

    for (int p = 0; p < 128; p++) {
        MemoryBlock presetMemBlock;

        getEditorPatchMemoryBlock(p, presetMemBlock);

        FlashSynthParams* paramSource = (FlashSynthParams*)((char*)bankMemory_.getData() + 1024 * p);
        String padNumber = "";
        if (p < 10) {
            padNumber = "00";
        }
        else if (p < 100) {
            padNumber = "0";
        }

        File preset(File::createLegalPathName(parentFolder.getFullPathName() + File::getSeparatorString() + padNumber + String(p)+ "-"+ String(paramSource->presetName).trim() + ".pfm"));

        DBG("savePresets" << String(p) << " name : " << preset.getFullPathName());

        preset.replaceWithData(presetMemBlock.getData(), presetMemBlock.getSize());
    }
}


void PfmPreset::getEditorPatchMemoryBlock(int presetNumber, MemoryBlock& presetMemBlock) {
    // Save each preset of the bank in the folder
    FlashSynthParams* paramSource = (FlashSynthParams*)((char*)bankMemory_.getData() + 1024 * presetNumber);

    updateDefaultValuesForOldPreset(paramSource);

    // PresetName
    paramSource->presetName[12] = 0;
    processor_->setPresetName(String(paramSource->presetName));

    // Send params to processor
    convert(paramSource, false);



    // USER PATTER? 
    // ???

    processor_->getStateInformation(presetMemBlock);
}

/*
 * fillParams : true from UI processor to pfm param
 *   
 */
void PfmPreset::convertParameters(float* values, int nrpnStartParam, int numberOfFloats, bool fillParams) {
    if (!fillParams) {
        for (int n = 0; n < numberOfFloats; n++) {
            processor_->setParameterWithNrpmParamAndRealValue(nrpnStartParam + n, values[n]);
        }
    }
    else {
        for (int n = 0; n < numberOfFloats; n++) {
            values[n] = processor_->getRealValueForPfmBank(nrpnStartParam + n);
        }
    }
}


void PfmPreset::updateDefaultValuesForOldPreset(FlashSynthParams* params) {
    // Comes from pfm firmware

    // Initialized not initialize params in memory
    if (params->engineArp1.BPM < 10) {
        params->engineArp1.clock = 0;
        params->engineArp1.BPM = 90;
        params->engineArp1.octave = 1;
        params->engineArp2.pattern = 2;
        params->engineArp2.division = 12;
        params->engineArp2.duration = 14;
        params->engineArp2.latche = 0;
    }

    if (params->effect.type == 0.0f && params->effect.param1 == 0.0f && params->effect.param2 == 0.0f && params->effect.param3 == 0.0f) {
        params->effect.param1 = 0.5f;
        params->effect.param2 = 0.5f;
        params->effect.param3 = 1.0f;
    }

    if (params->midiNote1Curve.breakNote == 0.0f && params->midiNote1Curve.curveAfter == 0.0f && params->midiNote1Curve.curveBefore == 0.0f) {
        // Default compatibility value
        // FLAT 0 +Lin
        params->midiNote1Curve.curveAfter = 1;
    }
    if (params->midiNote2Curve.breakNote == 0.0f && params->midiNote2Curve.curveAfter == 0.0f && params->midiNote2Curve.curveBefore == 0.0f) {
        // Default compatibility value
        // FLAT 0 +Lin
        params->midiNote2Curve.curveBefore = 4;
        params->midiNote2Curve.curveAfter = 1;
        params->midiNote2Curve.breakNote = 60;
    }
}


void PfmPreset::saveBank(File& presetFolder) {
    
    if (!presetFolder.isDirectory() ) {
        AlertWindow::showMessageBox(AlertWindow::WarningIcon,
            TRANS("Wrong folder"),
            TRANS("Not a folder !!!"));
        return;
    }


    String fullPathName = presetFolder.getFullPathName();
    String fileName = presetFolder.getFileName();

    File parentFolder = presetFolder.getParentDirectory();

    Array<File> presetFiles = presetFolder.findChildFiles(File::findFiles, false);
    presetFiles.sort();

    if (presetFiles.size() == 0) {
        AlertWindow::showMessageBox(AlertWindow::WarningIcon,
            TRANS("Wrong folder"),
            TRANS("No preset file (*.pfm) in this folder"));
        return;
    }

    int cpt = 0;
    String bankName;
    bool nameExists = false;
    do {
        bankName = parentFolder.getFullPathName() + File::getSeparatorString() + fileName + ".bnk" + (cpt == 0 ? "" : String(cpt));
        File bankTest(bankName);
        nameExists = bankTest.exists();
        cpt++;
    } while (nameExists);

    File bankFile(bankName);
    bankFile.create();

    MemoryBlock bankMemory;
    MemoryBlock presetMemory(1024, 0);
    cpt = 0;
    FlashSynthParams params;
    MemoryBlock fileMemory;

    for (File presetFile : presetFiles) {
        // bankFile.appendText(presetFile.getFileName() + "\r\n");
        fileMemory.reset();
        presetFile.loadFileAsData(fileMemory);

        // If not Patch continue !!
        if (!((int)fileMemory.getData()) == magicXmlNumber) {
            continue;
        }


        processor_->setStateInformation(fileMemory.getData(), fileMemory.getSize());

        char* presetName = processor_->getPresetName().getCharPointer().getAddress();
        for (int c = 0; c < 12; c++) {
            params.presetName[c] = presetName[c];
        }

        convert(&params, true);

        presetMemory.copyFrom(&params, 0, sizeof(FlashSynthParams));
        bankMemory.append(presetMemory.getData(), presetMemory.getSize());

        cpt++;
        if (cpt == 128) {
            break;
        }
    }
    
    char* newName = "Empty\0\0\0\0\0\0\0";
    for (int n = 0; n < 12; n++) {
        params.presetName[n] = newName[n];
    }
    presetMemory.copyFrom(&params, 0, sizeof(FlashSynthParams));

    for (int p = cpt; p < 128; p++) {
        bankMemory.append(presetMemory.getData(), presetMemory.getSize());
    }
    bankFile.replaceWithData(bankMemory.getData(), bankMemory.getSize());
}



void PfmPreset::convert(FlashSynthParams* paramSource, bool fillParam) {
    // engine 1
    convertParameters((float*)&paramSource->engine1, PREENFM2_NRPN_ALGO, 4, fillParam);

    // Then there's a difference between NRPN and flash memory for IMs and Velo IMs
    convertParameters((float*)&paramSource->flashEngineIm1.modulationIndex1, PREENFM2_NRPN_IM1, 1, fillParam);
    convertParameters((float*)&paramSource->flashEngineVeloIm1.modulationIndexVelo1, PREENFM2_NRPN_IM1_VELOCITY, 1, fillParam);
    convertParameters((float*)&paramSource->flashEngineIm1.modulationIndex2, PREENFM2_NRPN_IM2, 1, fillParam);
    convertParameters((float*)&paramSource->flashEngineVeloIm1.modulationIndexVelo2, PREENFM2_NRPN_IM2_VELOCITY, 1, fillParam);

    convertParameters((float*)&paramSource->flashEngineIm1.modulationIndex3, PREENFM2_NRPN_IM3, 1, fillParam);
    convertParameters((float*)&paramSource->flashEngineVeloIm1.modulationIndexVelo3, PREENFM2_NRPN_IM3_VELOCITY, 1, fillParam);
    convertParameters((float*)&paramSource->flashEngineIm1.modulationIndex4, PREENFM2_NRPN_IM4, 1, fillParam);
    convertParameters((float*)&paramSource->flashEngineVeloIm1.modulationIndexVelo4, PREENFM2_NRPN_IM4_VELOCITY, 1, fillParam);

    convertParameters((float*)&paramSource->flashEngineIm2.modulationIndex5, PREENFM2_NRPN_IM5, 1, fillParam);
    convertParameters((float*)&paramSource->flashEngineVeloIm2.modulationIndexVelo5, PREENFM2_NRPN_IM5_VELOCITY, 1, fillParam);
    convertParameters((float*)&paramSource->flashEngineIm2.modulationIndex6, PREENFM2_NRPN_IM6, 1, fillParam);
    convertParameters((float*)&paramSource->flashEngineVeloIm2.modulationIndexVelo6, PREENFM2_NRPN_IM6_VELOCITY, 1, fillParam);

    // Mix 
    convertParameters((float*)&paramSource->engineMix1, PREENFM2_NRPN_MIX1, 4 * 3, fillParam);

    // Arp
    convertParameters((float*)&paramSource->engineArp1, PREENFM2_NRPN_ARP_CLOCK, 4 * 2, fillParam);

    // Filter
    convertParameters((float*)&paramSource->effect, PREENFM2_NRPN_FILTER_TYPE, 4, fillParam);

    // Operator (Shape + env1 + env2) * 6
    convertParameters((float*)&paramSource->osc1, PREENFM2_NRPN_OPERATOR1_SHAPE, 4 * 18, fillParam);

    // Matrix
    convertParameters((float*)&paramSource->matrixRowState1, PREENFM2_NRPN_MTX1_SOURCE, 4 * 12, fillParam);

    // Lfo Osc1, 2 3 + env1 + env2 + seq + seq2
    convertParameters((float*)&paramSource->lfoOsc1, PREENFM2_NRPN_LFO1_SHAPE, 4 * (3 + 1 + 1 + 1 + 1), fillParam);

    //  Lfo Phases
    convertParameters((float*)&paramSource->lfoPhases, PREENFM2_NRPN_LFO_PHASE1, 4, fillParam);

    // Midi note curve    
    convertParameters((float*)&paramSource->midiNote1Curve, PREENFM2_NRPN_NOTE1_BEFORE, 4 * 2, fillParam);

    // Arp User Pattern
// ????    convertParameters((float*)&paramSource->engineArpUserPatterns, PREENFM2_NRPN_ARP_PATTERN, 4, false);

    if (!fillParam) {
        for (int n = 0; n < 16; n++) {
            processor_->setParameterWithNrpmParamAndRealValue(PREENFM2_NRPN_STEPSEQ1_STEP1 + n, paramSource->lfoSteps1.steps[n]);
        }
        for (int n = 0; n < 16; n++) {
            processor_->setParameterWithNrpmParamAndRealValue(PREENFM2_NRPN_STEPSEQ2_STEP1 + n, paramSource->lfoSteps2.steps[n]);
        }
    }
    else {
        for (int n = 0; n < 16; n++) {
            paramSource->lfoSteps1.steps[n] = processor_->getRealValueForPfmBank(PREENFM2_NRPN_STEPSEQ1_STEP1 + n);
        }
        for (int n = 0; n < 16; n++) {
            paramSource->lfoSteps2.steps[n] = processor_->getRealValueForPfmBank(PREENFM2_NRPN_STEPSEQ2_STEP1 + n);
        }
    }

}
