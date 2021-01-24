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



#pragma once


#include <stdint.h>
#include "JuceHeader.h"


class PresetComponent : public TextButton,
    public DragAndDropContainer,
    public DragAndDropTarget {
public:
    PresetComponent(String name);
    ~PresetComponent() override;

    void itemDropped(const SourceDetails& dragSourceDetails) override;
    bool isInterestedInDragSource(const SourceDetails& dragSourceDetails) override;

    void dragOperationStarted(const DragAndDropTarget::SourceDetails&) override;
    void dragOperationEnded(const DragAndDropTarget::SourceDetails&) override;


};

class ReorderingComponent : public Component,
    public Button::Listener {
public:
    ReorderingComponent();
    ~ReorderingComponent() override;


//    void paint(Graphics& g) override;
    void resized() override;
    void buttonClicked(Button* buttonThatWasClicked) override;


private:
    ScopedPointer<TextButton> okButton;
    ScopedPointer<TextButton> cancelButton;
    ScopedPointer<PresetComponent> preset[128];
};


