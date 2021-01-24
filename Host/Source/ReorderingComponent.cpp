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

ReorderingComponent::ReorderingComponent() {

	okButton = new TextButton("OK");
	okButton->addListener(this);
	addAndMakeVisible(okButton);
	cancelButton = new TextButton("Cancel");
	cancelButton->addListener(this);
	addAndMakeVisible(cancelButton);

	for (int p = 0; p < 128; p++) {
		preset[p] = new PresetComponent("Preset #" + String(p));
		addAndMakeVisible(preset[p]);
	}


	setSize(800, 600);
}

ReorderingComponent::~ReorderingComponent() {

}

//void ReorderingComponent::paint(Graphics& g) {
//
//}

void ReorderingComponent::resized() {
	cancelButton->setBounds(proportionOfWidth(0.5) - 110, proportionOfHeight(1.0) - 35, 100 , 30);
	okButton->setBounds(proportionOfWidth(0.5) + 10, proportionOfHeight(1.0) - 35, 100, 30);

	float height = (proportionOfHeight(1.0) - 40.0f) / 16.0f;
	float width = proportionOfWidth(1.0) / 8.0f;

	for (int col = 0; col < 8; col++) {
		for (int row = 0; row < 16; row++) {
			int p = col * 16 + row;
			preset[p]->setBounds(width * col, height * row, width, height);
		}
	}



}

void ReorderingComponent::buttonClicked(Button* buttonThatWasClicked) {
	if (buttonThatWasClicked == cancelButton) {
	}
	else if (buttonThatWasClicked == okButton) {
	}
}


// Preset component

PresetComponent::PresetComponent(String name) : TextButton(name) {

}

PresetComponent::~PresetComponent() {
};


void PresetComponent::itemDropped(const SourceDetails& dragSourceDetails) {

}

bool PresetComponent::isInterestedInDragSource(const SourceDetails& dragSourceDetails) {
	return false;
}


void PresetComponent::dragOperationStarted(const DragAndDropTarget::SourceDetails&) {

}
void PresetComponent::dragOperationEnded(const DragAndDropTarget::SourceDetails&) {

}
