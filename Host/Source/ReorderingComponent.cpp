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
	int x = 2, y = 2, width = proportionOfWidth(1.0f) - 4, height = proportionOfHeight(1.0f) - 1;
	if (swapName_.length() > 0) {
		g.setColour(Colours::lightgreen.brighter());
		g.fillRect(x, y, width, height);

		g.setColour(Colours::black);

		g.drawText(swapName_, x, y, width, height, Justification::centred);
	}
	else {
		g.setColour(Colour(0xff125368));
		g.fillRect(x, y, width, height);

		g.setColour(Colours::lightgrey);	
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
		"New name for '" + presetName_ + "'", presetName_);

	if (!newName.isEmpty()) {
		presetName_ = newName;
		presetNameModified_ = true;
		repaint();
	}
}

// ReorderingComponent


ReorderingComponent::ReorderingComponent(String folderPath, String bankFileName, MemoryBlock& bankMem) {
	bankFileName_ = bankFileName;
	folderPath_ = folderPath;
	bankMem_ = new MemoryBlock(bankMem);

	okButton = new TextButton("Save Bank");
	okButton->addListener(this);
	addAndMakeVisible(okButton);

	cancelButton = new TextButton("Cancel");
	cancelButton->addListener(this);
	addAndMakeVisible(cancelButton);

	for (int p = 0; p < 128; p++) {
		FlashSynthParams* paramSource = (FlashSynthParams*)((char*)bankMem.getData() + 1024 * p);
		order_[p] = p;
		preset[p] = new PresetComponent(this, p, paramSource->presetName);
		addAndMakeVisible(preset[p]);
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
	cancelButton->setBounds(proportionOfWidth(0.5) - 110, proportionOfHeight(1.0) - 35, 100, 30);
	okButton->setBounds(proportionOfWidth(0.5) + 10, proportionOfHeight(1.0) - 35, 100, 30);

	float height = (proportionOfHeight(1.0) - 40.0f - 25.0f) / 16.0f;
	float width = proportionOfWidth(1.0) / 8.0f;

	for (int col = 0; col < 8; col++) {
		for (int row = 0; row < 16; row++) {
			int p = order_[col * 16 + row];
			preset[p]->setBounds(width * col, 25.0f + height * row, width, height);
		}
	}
}

void ReorderingComponent::buttonClicked(Button* buttonThatWasClicked) {
	if (buttonThatWasClicked == cancelButton) {
		delete getParentComponent();
	}
	else if (buttonThatWasClicked == okButton) {
		MemoryBlock newOrder;
		for (int p = 0; p < 128; p++) {
			if (preset[p]->isPresetNameModified()) {
				FlashSynthParams* paramSource = (FlashSynthParams*)((char*)bankMem_->getData() + 1024 * p);
				char* newName = preset[p]->getPresetName();
				int length;
				for (length = length; length < 12 && newName[length] != '\0'; length++) {
					paramSource->presetName[length] = newName[length];
				}
				for (int c = length; c < 13; c++) {
					paramSource->presetName[c] = '\0';
				}
			}

			newOrder.append(((char*)bankMem_->getData() + 1024 * order_[p]), 1024);
		}

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
			String bankFullName = folderPath_ + File::getSeparatorString() + bankName + ".bnk";
			File bankTest(bankFullName);
			nameExists = bankTest.exists();
			cpt++;
		} while (nameExists);

		nameExists = false;
		do {
			String newBankName = confirmName("Create new bank", "Enter bank name", bankName);
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

void ReorderingComponent::dragOperationStarted(const DragAndDropTarget::SourceDetails&) {
	dragging_ = true;
	repaint();

}
void ReorderingComponent::dragOperationEnded(const DragAndDropTarget::SourceDetails&) {
	dragging_ = false;
	repaint();
}


String ReorderingComponent::confirmName(String title, String text, String previousName) {
	AlertWindow resetWindow(title,
		text,
		AlertWindow::QuestionIcon);

	resetWindow.setSize(600, 400);
	resetWindow.addTextEditor("NewName", previousName);
	resetWindow.getTextEditor("NewName")->setColour(TextEditor::highlightColourId, Colours::orange);
	resetWindow.addButton("Cancel", 1);
	resetWindow.addButton("OK", 2);

	if (resetWindow.runModalLoop() == 2) {
		String newName = resetWindow.getTextEditor("NewName")->getText().trim();

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