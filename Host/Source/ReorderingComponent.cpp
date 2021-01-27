/*
* Copyright 2021 Xavier Hosxe
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


#include "ReorderingComponent.h"
#include "pfmPreset.h"


enum {
	PREEN_TYPE_PFM2 = 1,
	PREEN_TYPE_PFM3 = 2
};

// Preset component

PresetComponent::PresetComponent(ReorderingComponent* parent, int n, String name) : Component(name) {
	dragging_ = false;
	dragTarget_ = false;
	presetName_ = name;
	newPosition_ = n;
	oldPosition_ = n;
	swapName_ = "";
	parent_ = parent;
	selected_ = false;
	presetNameModified_ = false;
}

PresetComponent::~PresetComponent() {
};

void PresetComponent::paint(Graphics& g) {
	int x = 3, y = 3, width = proportionOfWidth(1.0f) - 6, height = proportionOfHeight(1.0f) - 6;
	if (swapName_.length() > 0) {
		g.setColour(Colours::lightgreen.brighter());
		g.fillRoundedRectangle(Rectangle<float>(x, y, width, height), 5.0f);

		g.setColour(Colours::black);
		g.drawText(String(newPosition_), x, y, width, height / 2 - 2, Justification::centredBottom);

		g.setColour(Colours::black);
		g.drawText(swapName_, x, y + height / 2 - 2, width, height / 2 + 2, Justification::centredTop);
	}
	else {
		g.setColour(Colour(0xff125368));
		g.fillRect(x, y, width, height);

		g.setColour(Colours::grey);	
		g.drawText(String(newPosition_), x, y, width, height / 2 - 2, Justification::centredBottom);
		//		
		g.setColour(Colours::white);
		g.drawText(presetName_, x, y + height / 2 - 2, width, height / 2 + 2, Justification::centredTop);
	}
}



void PresetComponent::itemDragEnter(const SourceDetails& dragSourceDetails) {
	dragTarget_ = true;
	PresetComponent* sourceComponent = dynamic_cast<PresetComponent*>(dragSourceDetails.sourceComponent.get());
	if (sourceComponent != NULL) {
		swapName_ = dragSourceDetails.sourceComponent->getName();
		sourceComponent->setSwapName(presetName_);
		sourceComponent->repaint();
		repaint();
	}
}

void PresetComponent::itemDragExit(const SourceDetails& dragSourceDetails) {
	dragTarget_ = false;
	PresetComponent* sourceComponent = dynamic_cast<PresetComponent*>(dragSourceDetails.sourceComponent.get());
	if (sourceComponent != NULL) {
		setClearSwapName();
		sourceComponent->setClearSwapName();
		sourceComponent->repaint();
		repaint();
	}
}

void PresetComponent::itemDropped(const SourceDetails& dragSourceDetails) {
	dragTarget_ = false;
	PresetComponent* sourceComponent = dynamic_cast<PresetComponent*>(dragSourceDetails.sourceComponent.get());
	if (sourceComponent != NULL) {
		// Swap order and repaint
		parent_->setNewPosition(getNewPosition(), sourceComponent->getOldPosition());
		parent_->setNewPosition(sourceComponent->getNewPosition(), getOldPosition());
		// Swap PresetComponent number
		int myNumber = newPosition_;
		setNewPosition(sourceComponent->getNewPosition());
		sourceComponent->setNewPosition(myNumber);
		// Clear swap name to display real name
		setClearSwapName();
		sourceComponent->setClearSwapName();
	}
}


bool PresetComponent::isInterestedInDragSource(const SourceDetails& dragSourceDetails) {
	PresetComponent* sourceComponent = dynamic_cast<PresetComponent*>(dragSourceDetails.sourceComponent.get());
	if (sourceComponent != NULL) {
		return sourceComponent->getNewPosition() != newPosition_;
	}
	return false;
}


void PresetComponent::mouseDoubleClick(const MouseEvent& e)  {

	String newName = ReorderingComponent::confirmName("Rename preset",
		"New name for '" + presetName_ + "'", presetName_, 12);

	if (!newName.isEmpty()) {
		presetName_ = newName;
		presetNameModified_ = true;
		repaint();
	}
}

// ReorderingComponent


ReorderingComponent::ReorderingComponent(String folderPath, String bankFileName, MemoryBlock& bankMem) {
	setWantsKeyboardFocus(true);
	addKeyListener(this);

	bankFileName_ = bankFileName;
	folderPath_ = folderPath;
	bankMem_ = new MemoryBlock(bankMem);

	okButton_ = new TextButton("Save Bank");	
	okButton_->addListener(this);
	addAndMakeVisible(okButton_);

	cancelButton_ = new TextButton("Cancel");
	cancelButton_->addListener(this);
	addAndMakeVisible(cancelButton_);

	for (int p = 0; p < 128; p++) {
		FlashSynthParams* paramSource = (FlashSynthParams*)((char*)bankMem.getData() + 1024 * p);
		order_[p] = p;

		paramSource->presetName[12] = '\0';

		preset_[p] = new PresetComponent(this, p, paramSource->presetName);
		addAndMakeVisible(preset_[p]);
	}
	setSize(900, 700);
	dragging_ = false;
}

ReorderingComponent::~ReorderingComponent() {
	delete bankMem_;
}

void ReorderingComponent::paint(Graphics& g) {
	int width = proportionOfWidth(1.0f);
	if (dragging_) {
		g.setColour(Colours::lightgreen.brighter());
		g.drawText("Drop this preset at its new position", 0, 0, width, 25, Justification::centred);
	}
	else {
		g.setColour(Colours::lightgrey.brighter());
		g.drawText("Drag and drop to change positions / Double click to rename", 0, 0, width, 25, Justification::centred);
	}
}

void ReorderingComponent::resized() {
	cancelButton_->setBounds(proportionOfWidth(0.5) - 110, proportionOfHeight(1.0) - 35, 100, 30);
	okButton_->setBounds(proportionOfWidth(0.5) + 10, proportionOfHeight(1.0) - 35, 100, 30);

	float height = (proportionOfHeight(1.0) - 40.0f - 25.0f) / 16.0f;
	float width = proportionOfWidth(1.0) / 8.0f;

	for (int col = 0; col < 8; col++) {
		for (int row = 0; row < 16; row++) {
			int p = order_[col * 16 + row];
			preset_[p]->setBounds(width * col, 25.0f + height * row, width, height);
		}
	}
}

void ReorderingComponent::buttonClicked(Button* buttonThatWasClicked) {
	if (buttonThatWasClicked == cancelButton_) {
		delete getParentComponent();
	}
	else if (buttonThatWasClicked == okButton_) {

		// 
		// Confirm Name : 
		// First find an non existing name
		// Ask user to confirm
		int cpt = 0;
		String bankName;
		bool nameExists = false;
		String bankFullName;

		do {
			bankName = bankFileName_ + (cpt == 0 ? "" : ("_" + String(cpt)));
			bankFullName = folderPath_ + File::getSeparatorString() + bankName + ".bnk";
			File bankTest(bankFullName);
			nameExists = bankTest.exists();
			cpt++;
		} while (nameExists);

		nameExists = false;
		int pfmType = PREEN_TYPE_PFM2;
		do {

			String newBankName = confirmName("Create new bank", "Enter bank name", bankName, 20, true, &pfmType);
			if (newBankName.isEmpty()) {
				return;
			}
			bankFullName = folderPath_ + File::getSeparatorString() + newBankName + ".bnk";
			File bankTest(bankFullName);
			nameExists = bankTest.exists();
			if (nameExists) {
				AlertWindow badNameAlert("Bad name : " + newBankName,
					"A bank with same name already exists.",
					AlertWindow::WarningIcon);
				badNameAlert.addButton("OK", 1);
				badNameAlert.runModalLoop();
			}
		} while (nameExists);

		
		// Reorder + modify some parameters depending on pfm2/pfm3 selected
		MemoryBlock newOrder;

		for (int p = 0; p < 128; p++) {
				
			polishPreset(p, pfmType);

			newOrder.append(((char*)bankMem_->getData() + 1024 * order_[p]), 1024);
		}



		File bankFile(bankFullName);
		bankFile.create();
		bankFile.replaceWithData(newOrder.getData(), newOrder.getSize());


		AlertWindow::showMessageBoxAsync(AlertWindow::InfoIcon,
			TRANS("Bank file Created"),
			TRANS("A bank file has been created here \r\n") +
			bankFullName);

		delete getParentComponent();
	}
}

bool ReorderingComponent::keyPressed(const juce::KeyPress& key, juce::Component* originatingComponent) {
	if (key == KeyPress::returnKey) {
		// simulate OK button
		buttonClicked(okButton_);
		return true;
	}
	return false;
}


void ReorderingComponent::dragOperationStarted(const DragAndDropTarget::SourceDetails&) {
	dragging_ = true;
	repaint();

}
void ReorderingComponent::dragOperationEnded(const DragAndDropTarget::SourceDetails&) {
	dragging_ = false;
	repaint();
}


String ReorderingComponent::confirmName(String title, String text, String previousName, int maxLength, bool askPfmType, int* pfmTypeP) {
	AlertWindow resetWindow(title,
		text,
		AlertWindow::QuestionIcon);

	resetWindow.setSize(600, 400);



	resetWindow.addTextEditor("NewName", previousName);
	TextEditor::LengthAndCharacterRestriction inputFilter(maxLength, String(""));
	resetWindow.getTextEditor("NewName")->setInputFilter(&inputFilter, false);
	resetWindow.getTextEditor("NewName")->setColour(TextEditor::highlightColourId, Colours::orange);
	resetWindow.getTextEditor("NewName")->setColour(TextEditor::backgroundColourId, Colours::darkgrey);

	if (askPfmType) {
		resetWindow.addComboBox("pfmType", StringArray({ "pfm 2", "pfm 3" }), "Preenfm type");
		resetWindow.getComboBoxComponent("pfmType")->setSelectedId(*pfmTypeP);
	}

	resetWindow.addButton("Cancel", 1);
	resetWindow.addButton("OK", 2, KeyPress(KeyPress::returnKey, 0, 0));

	if (resetWindow.runModalLoop() == 2) {
		String newName = resetWindow.getTextEditor("NewName")->getText().trim();
		if (askPfmType && pfmTypeP != nullptr) {
			*pfmTypeP = resetWindow.getComboBoxComponent("pfmType")->getSelectedId();
		}

		if (newName.isEmpty()) {
			AlertWindow badNameAlert("Bad name",
				"Name cannot be empty",
				AlertWindow::WarningIcon);

			badNameAlert.addButton("OK", 1);
			badNameAlert.runModalLoop();
			return "";
		}
		else {
			return newName;
		}
	}
	return "";
}



void ReorderingComponent::polishPreset(int p, int pfmType) {
	FlashSynthParams* paramSource = (FlashSynthParams*)((char*)bankMem_->getData() + 1024 * p);
	if (preset_[p]->isPresetNameModified()) {

		char* newName = preset_[p]->getPresetName();
		int length;
		for (length = 0; length < 12 && newName[length] != '\0'; length++) {
			paramSource->presetName[length] = newName[length];
		}
		for (int c = length; c < 13; c++) {
			paramSource->presetName[c] = '\0';
		}
	}

	// if pfm3 selected and preset is a pfm2 one
	uint32_t version = (uint32_t)(paramSource->engine2.pfm3Version + .1f);

	// Planned version : not yet implemented
	// But let's make the editor compatible right now
	// pfm2 version : 0,2,4,6 etc...
	//    0 = legacy one
	//    2 = with unisons ! (not yet implemented)
	// pfm3 version : 1,3,5
	//    1 = current one

	if (pfmType == PREEN_TYPE_PFM3 && (version & 0x1) == 0) {
		// Set pfm3 version
		paramSource->engine2.pfm3Version = 1.0f;

		// in pfm2 bank playMode was the number of voice
		// More than one voice => poly
		if (paramSource->engine1.playMode > 1.0f) {
			paramSource->engine1.playMode = PLAY_MODE_POLY;
		}
		else {
			paramSource->engine1.playMode = PLAY_MODE_MONO;
		}

		// Old preset, we set unisonSpread and unisonDetune different from 0
		if (paramSource->engine2.unisonSpread == 0.0f && paramSource->engine2.unisonDetune == 0.0f) {
			paramSource->engine2.unisonSpread = 0.5f;
			paramSource->engine2.unisonDetune = 0.12f;
		}
		// Map glide speed to new glideSpeed and glideType
		if (paramSource->engine1.glideSpeed > 0.0f) {
			paramSource->engine2.glideType = GLIDE_TYPE_OVERLAP;
		}
		else {
			paramSource->engine2.glideType = GLIDE_TYPE_OFF;
		}
	}

	// Selected pfm2 for a pfm3 preset
	// pfm2 : playMode is number of voice
	if (pfmType == PREEN_TYPE_PFM2 && (version & 0x1) == 1) {
		// Set pfm2 version
		paramSource->engine2.pfm3Version = 0.0f;

		// Fixe poly Mono depending on pfm3Version :
		// map to new parameters
		// in pfm2 bank playMode was the number of voice
		// poly => 3 voices
		// Mono and unison => 1 voice
		if (paramSource->engine1.playMode == 1.0f) {
			paramSource->engine1.playMode = 3.0f;
		}
		else {
			paramSource->engine1.playMode = 1.0f;
		}
		// Set the rest to 0
		paramSource->engine2.unisonSpread = 0.0f;
		paramSource->engine2.unisonDetune = 0.0f;
		paramSource->engine2.glideType = 0.0f;
		// Tells it's a pfm2 preset
		paramSource->engine2.pfm3Version = 0.0f;
	}
}
