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


class PresetComponent;

class ReorderingComponent : public Component,
    public DragAndDropContainer,
    public Button::Listener {
public:
    ReorderingComponent(String bankFileName, MemoryBlock& bankMem);
    ~ReorderingComponent() override;


    void resized() override;
    void paint(Graphics& g) override;
    void buttonClicked(Button* buttonThatWasClicked) override;

    // source
    void dragOperationStarted(const DragAndDropTarget::SourceDetails&) override;
    void dragOperationEnded(const DragAndDropTarget::SourceDetails&) override;

    void swap(int p1, int p2) {
        int oldP1 = order_[p1];
        order_[p1] = order_[p2];
        order_[p2] = oldP1;
        resized();
        repaint();
    }

private:
    int order_[128];
    bool dragging_;
    String bankFileName_;
    MemoryBlock* bankMem_;
    ScopedPointer<TextButton> okButton;
    ScopedPointer<TextButton> cancelButton;
    ScopedPointer<PresetComponent> preset[128];
};


class PresetComponent : public Component,
    public DragAndDropTarget
{
public:
    PresetComponent(ReorderingComponent* parent, int number, String name);
    ~PresetComponent() override;


    // Target
    void itemDropped(const SourceDetails& dragSourceDetails) override;
    bool isInterestedInDragSource(const SourceDetails& dragSourceDetails) override;
    void itemDragEnter(const SourceDetails& dragSourceDetails) override;
    void itemDragExit(const SourceDetails& dragSourceDetails) override;


    // Component
    void paint(Graphics& g) override;

    void mouseDrag(const MouseEvent& e) override
    {
        DragAndDropContainer::findParentDragContainerFor(this)->startDragging(number_, this);
    }

    void setSwapName(String swapName) {
        swapName_ = swapName;
    }

    void setClearSwapName() {
        swapName_.clear();
    }
    
    int getNumber() { return number_; }
    void setNumber(int n) { number_ = n;  }


private:
    bool dragging_;
    bool dragTarget_;
    String name_;
    String swapName_;
    int number_;
    ReorderingComponent* parent_;
};



