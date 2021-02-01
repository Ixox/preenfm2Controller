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
#include "ReorderingComponent.h"

extern AudioProcessor* JUCE_API JUCE_CALLTYPE createPluginFilter();
extern const uint32 magicXmlNumber = 0x21324356;
extern JUCEApplication* staticMainWindow;



PfmPreset::PfmPreset() {
    reorderingWindow = nullptr;
    processor_ = dynamic_cast<Pfm2AudioProcessor*>(createPluginFilter());
}

void PfmPreset::savePresetsFolder(const File& bankFile) {
    bankFile_ = new File(bankFile);
    bankMemory_.reset();
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
        return ;
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

    AlertWindow::showMessageBoxAsync(AlertWindow::InfoIcon,
        TRANS("Folder Created"),
        TRANS("A folder with all the bank presets has been created here \r\n" +
            parentFolder.getFullPathName()));
}


void PfmPreset::getEditorPatchMemoryBlock(int presetNumber, MemoryBlock& presetMemBlock) {
    // Save each preset of the bank in the folder
    FlashSynthParams* paramSource = (FlashSynthParams*)((char*)bankMemory_.getData() + 1024 * presetNumber);

    updateDefaultValuesForOldPreset(paramSource);

    // PresetName
    paramSource->presetName[12] = 0;
    processor_->setPresetName(String(paramSource->presetName));

    // Send params to processor
    convert(paramSource, PARAM_TO_EDITOR);

    // USER PATTER?

    processor_->getStateInformation(presetMemBlock);
}

/*
 * directions : true from UI processor to pfm param
 *   
 */
void PfmPreset::convertParameters(float* values, int nrpnStartParam, int numberOfFloats, ConvertDirectionEnum direction) {
    if (direction == PARAM_TO_EDITOR) {
        for (int n = 0; n < numberOfFloats; n++) {
            processor_->setParameterWithNrpmParamAndRealValue(nrpnStartParam + n, values[n]);
        }
    }
    else {
        // EDITOR_TO_PARAM
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


void PfmPreset::savePfmBankFile(const File& presetFolder) {
    
    if (!presetFolder.isDirectory() ) {
        return ;
    }


    String fullPathName = presetFolder.getFullPathName();
    File parentFolder = presetFolder.getParentDirectory();

    Array<File> presetFiles = presetFolder.findChildFiles(File::findFiles, false);
    presetFiles.sort();

    if (presetFiles.size() == 0) {
        return;
    }

    MemoryBlock bankMemory;
    MemoryBlock presetMemory(1024, 0);
    int cpt = 0;
    FlashSynthParams params;
    MemoryBlock fileMemory;

    for (File presetFile : presetFiles) {
        // bankFile.appendText(presetFile.getFileName() + "\r\n");
        fileMemory.reset();
        presetFile.loadFileAsData(fileMemory);

        // If not Patch continue !!
        if (!((long)fileMemory.getData()) == magicXmlNumber) {
            continue;
        }


        processor_->setStateInformation(fileMemory.getData(), fileMemory.getSize(), false);

        char* presetName = processor_->getPresetName().getCharPointer().getAddress();
        for (int c = 0; c < 12; c++) {
            params.presetName[c] = presetName[c];
        }

        convert(&params, EDITOR_TO_PARAM);

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

    // complete number of presets to 128
    for (int p = cpt; p < 128; p++) {
        bankMemory.append(presetMemory.getData(), presetMemory.getSize());
    }

    // Bank is ready we can ask for reprdering
    reorderBank(parentFolder.getFullPathName(), presetFolder.getFileName(), bankMemory);

    return ;
}



void PfmPreset::convert(FlashSynthParams* paramSource, ConvertDirectionEnum direction) {

    // Init pfmType
    if (direction == PARAM_TO_EDITOR) {
        int version = (int)paramSource->engine2.pfm3Version + .01f;
        processor_->setPfmType(((version & 0x1) == 0) ? 1 : 2);
        processor_->setParameterWithNrpmParamAndRealValue(PREENFM_NRPN_PFMTYPE, ((version & 0x1) == 0) ? 0.0f : 1.0f);
    }

    // engine 1
    convertParameters((float*)&paramSource->engine1, PREENFM2_NRPN_ALGO, 4, direction);

    // engine 2
    convertParameters((float*)&paramSource->engine2, PREENFM2_NRPN_GLIDE_TYPE, 4, direction);

    // Then there's a difference between NRPN and flash memory for IMs and Velo IMs
    convertParameters((float*)&paramSource->flashEngineIm1.modulationIndex1, PREENFM2_NRPN_IM1, 1, direction);
    convertParameters((float*)&paramSource->flashEngineVeloIm1.modulationIndexVelo1, PREENFM2_NRPN_IM1_VELOCITY, 1, direction);
    convertParameters((float*)&paramSource->flashEngineIm1.modulationIndex2, PREENFM2_NRPN_IM2, 1, direction);
    convertParameters((float*)&paramSource->flashEngineVeloIm1.modulationIndexVelo2, PREENFM2_NRPN_IM2_VELOCITY, 1, direction);

    convertParameters((float*)&paramSource->flashEngineIm1.modulationIndex3, PREENFM2_NRPN_IM3, 1, direction);
    convertParameters((float*)&paramSource->flashEngineVeloIm1.modulationIndexVelo3, PREENFM2_NRPN_IM3_VELOCITY, 1, direction);
    convertParameters((float*)&paramSource->flashEngineIm1.modulationIndex4, PREENFM2_NRPN_IM4, 1, direction);
    convertParameters((float*)&paramSource->flashEngineVeloIm1.modulationIndexVelo4, PREENFM2_NRPN_IM4_VELOCITY, 1, direction);

    convertParameters((float*)&paramSource->flashEngineIm2.modulationIndex5, PREENFM2_NRPN_IM5, 1, direction);
    convertParameters((float*)&paramSource->flashEngineVeloIm2.modulationIndexVelo5, PREENFM2_NRPN_IM5_VELOCITY, 1, direction);
    convertParameters((float*)&paramSource->flashEngineIm2.modulationIndex6, PREENFM2_NRPN_IM6, 1, direction);
    convertParameters((float*)&paramSource->flashEngineVeloIm2.modulationIndexVelo6, PREENFM2_NRPN_IM6_VELOCITY, 1, direction);

    // Mix 
    convertParameters((float*)&paramSource->engineMix1, PREENFM2_NRPN_MIX1, 4 * 3, direction);

    // Arp
    convertParameters((float*)&paramSource->engineArp1, PREENFM2_NRPN_ARP_CLOCK, 4 * 2, direction);

    // Filter
    convertParameters((float*)&paramSource->effect, PREENFM2_NRPN_FILTER_TYPE, 4, direction);

    // Operator (Shape + env1 + env2) * 6
    convertParameters((float*)&paramSource->osc1, PREENFM2_NRPN_OPERATOR1_SHAPE, 4 * 18, direction);

    // Matrix
    convertParameters((float*)&paramSource->matrixRowState1, PREENFM2_NRPN_MTX1_SOURCE, 4 * 12, direction);

    // Lfo Osc1, 2 3 + env1 + env2 + seq + seq2
    convertParameters((float*)&paramSource->lfoOsc1, PREENFM2_NRPN_LFO1_SHAPE, 4 * (3 + 1 + 1 + 1 + 1), direction);

    //  Lfo Phases
    convertParameters((float*)&paramSource->lfoPhases, PREENFM2_NRPN_LFO_PHASE1, 4, direction);

    // Midi note curve    
    convertParameters((float*)&paramSource->midiNote1Curve, PREENFM2_NRPN_NOTE1_BEFORE, 4 * 2, direction);

    // Arp User Pattern
// ????    convertParameters((float*)&paramSource->engineArpUserPatterns, PREENFM2_NRPN_ARP_PATTERN, 4, false);

    if (direction == PARAM_TO_EDITOR) {
        for (int n = 0; n < 16; n++) {
            processor_->setParameterWithNrpmParamAndRealValue(PREENFM2_NRPN_STEPSEQ1_STEP1 + n, paramSource->lfoSteps1.steps[n]);
        }
        for (int n = 0; n < 16; n++) {
            processor_->setParameterWithNrpmParamAndRealValue(PREENFM2_NRPN_STEPSEQ2_STEP1 + n, paramSource->lfoSteps2.steps[n]);
        }
    }
    else {
        // EDITOR_TO_PARAM
        for (int n = 0; n < 16; n++) {
            paramSource->lfoSteps1.steps[n] = processor_->getRealValueForPfmBank(PREENFM2_NRPN_STEPSEQ1_STEP1 + n);
        }
        for (int n = 0; n < 16; n++) {
            paramSource->lfoSteps2.steps[n] = processor_->getRealValueForPfmBank(PREENFM2_NRPN_STEPSEQ2_STEP1 + n);
        }
    }
}

void PfmPreset::organizeBank(const File& bankFile) {
    MemoryBlock bankMemory;
    bankFile.loadFileAsData(bankMemory);
    reorderBank(bankFile.getParentDirectory().getFullPathName(), bankFile.getFileNameWithoutExtension(), bankMemory);
}


void PfmPreset::reorderBank(String folderPath, String bankFileName, MemoryBlock& bankMem) {
    reorderingWindow = new DocumentWindow("Organize your presets", Colour::fromRGB(0, 0, 0), 0);
    reorderingWindow->setContentOwned(new ReorderingComponent(folderPath, bankFileName, bankMem), true);
    Rectangle<int> screen = Desktop::getInstance().getDisplays().displays[0].totalArea;
    reorderingWindow->centreWithSize(reorderingWindow->getWidth(), reorderingWindow->getHeight());
    reorderingWindow->setVisible(true);
}
