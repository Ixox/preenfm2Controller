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
    public Button::Listener,
    public KeyListener
{
public:
    ReorderingComponent(String folderPath, String bankFileName, MemoryBlock& bankMem);
    ~ReorderingComponent() override;


    void resized() override;
    void paint(Graphics& g) override;
    void buttonClicked(Button* buttonThatWasClicked) override;
    bool keyPressed(const juce::KeyPress& key, juce::Component* originatingComponent) override; 
    // source
    void dragOperationStarted(const DragAndDropTarget::SourceDetails&) override;
    void dragOperationEnded(const DragAndDropTarget::SourceDetails&) override;

    void setNewPosition(int position, int presetNumber) {
        order_[position] = presetNumber;
        resized();
        repaint();
    }

    static String confirmName(String title, String text, String previousName, int maxLength, bool pfmType = false, int* type = nullptr);

    void polishPreset(int p, int pfmType);

private:
    int order_[128];
    bool dragging_;
    String bankFileName_;
    String folderPath_;
    MemoryBlock* bankMem_;
    ScopedPointer<TextButton> okButton_;
    ScopedPointer<TextButton> cancelButton_;
    ScopedPointer<PresetComponent> preset_[128];
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
        DragAndDropContainer::findParentDragContainerFor(this)->startDragging(newPosition_, this);
    }

    void mouseDoubleClick(const MouseEvent& e) override;

    void setSwapName(String swapName) {
        swapName_ = swapName;
    }

    void setClearSwapName() {
        swapName_.clear();
    }
    
    int getNewPosition() { return newPosition_; }
    void setNewPosition(int n) { newPosition_ = n;  }
    int getOldPosition() { return oldPosition_; }
    
    char* getPresetName() { return presetName_.getCharPointer().getAddress(); }
    bool isPresetNameModified() { return presetNameModified_;  }

private:
    bool dragging_;
    bool dragTarget_;
    bool selected_;
    String presetName_;
    String swapName_;
    bool presetNameModified_;
    int newPosition_;
    int oldPosition_;
    ReorderingComponent* parent_;
};
