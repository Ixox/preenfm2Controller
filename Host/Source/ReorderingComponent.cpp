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
	name_ = name;
	number_ = n;
	swapName_ = "";
	parent_ = parent;
}

PresetComponent::~PresetComponent() {
};


void PresetComponent::paint(Graphics& g) {
	int x = 2, y = 2, width = proportionOfWidth(1.0f) - 2, height = proportionOfHeight(1.0f) - 2;
	Colour fillColour1 = Colour(0xff125368), fillColour2 = Colour(0xff083543);
	if (swapName_.length() > 0) {
		g.setColour(Colours::white);
		g.fillRect(x, y, width, height);

		g.setColour(Colours::black);

		g.drawText(swapName_, x, y, width, height, Justification::centred);
	}
	else {
		g.setColour(fillColour1);
		g.fillRect(x, y, width, height);

		g.setColour(Colours::white);
		g.drawText(getName(), x, y, width, height, Justification::centred);
	}
}



void PresetComponent::itemDragEnter(const SourceDetails& dragSourceDetails) {
	dragTarget_ = true;
	PresetComponent* sourceComponent = dynamic_cast<PresetComponent*>(dragSourceDetails.sourceComponent.get());
	if (sourceComponent != NULL) {
		swapName_ = dragSourceDetails.sourceComponent->getName();
		sourceComponent->setSwapName(name_);
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
		// Swap PresetComponent number
		int myNumber = number_;
		setNumber(sourceComponent->getNumber());
		sourceComponent->setNumber(myNumber);
		// Clear swap name to display real name
		setClearSwapName();
		sourceComponent->setClearSwapName();

		// Swap order and repaint
		parent_->swap(number_, sourceComponent->getNumber());
	}
}


bool PresetComponent::isInterestedInDragSource(const SourceDetails& dragSourceDetails) {
	PresetComponent* sourceComponent = dynamic_cast<PresetComponent*>(dragSourceDetails.sourceComponent.get());
	if (sourceComponent != NULL) {
		return sourceComponent->getNumber() != number_;
	}
	return false;
}




// ReorderingComponent


ReorderingComponent::ReorderingComponent(String bankFileName, MemoryBlock& bankMem) {
	bankFileName_ = bankFileName;
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
	setSize(800, 600);
	dragging_ = false;
}

ReorderingComponent::~ReorderingComponent() {
	delete bankMem_;
}

void ReorderingComponent::paint(Graphics& g) {
	if (dragging_) {
		g.setColour(Colours::darkgrey);
		g.fillRect(0, 0, proportionOfWidth(1.0f), proportionOfHeight(1.0));
	}
}

void ReorderingComponent::resized() {
	cancelButton->setBounds(proportionOfWidth(0.5) - 110, proportionOfHeight(1.0) - 35, 100, 30);
	okButton->setBounds(proportionOfWidth(0.5) + 10, proportionOfHeight(1.0) - 35, 100, 30);

	float height = (proportionOfHeight(1.0) - 40.0f) / 16.0f;
	float width = proportionOfWidth(1.0) / 8.0f;

	for (int col = 0; col < 8; col++) {
		for (int row = 0; row < 16; row++) {
			int p = order_[col * 16 + row];
			preset[p]->setBounds(width * col, height * row, width, height);
		}
	}
}

void ReorderingComponent::buttonClicked(Button* buttonThatWasClicked) {
	if (buttonThatWasClicked == cancelButton) {
		delete getParentComponent();
	}
	else if (buttonThatWasClicked == okButton) {
		File bankFile(bankFileName_);
		bankFile.create();
		bankFile.replaceWithData(bankMem_->getData(), bankMem_->getSize());

		AlertWindow::showMessageBoxAsync(AlertWindow::InfoIcon,
			TRANS("Bank file Created"),
			TRANS("A bank file has been created here \r\n") +
			bankFileName_);

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


