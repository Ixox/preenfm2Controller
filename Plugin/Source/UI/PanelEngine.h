/*
  ==============================================================================

  This is an automatically generated GUI class created by the Projucer!

  Be careful when adding custom code to these files, as only the code within
  the "//[xyz]" and "//[/xyz]" sections will be retained when the file is loaded
  and re-saved.

  Created with Projucer version: 6.0.7

  ------------------------------------------------------------------------------

  The Projucer is part of the JUCE library.
  Copyright (c) 2020 - Raw Material Software Limited.

  ==============================================================================
*/

#pragma once

//[Headers]     -- You can add your own extra header files here --

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

#include "JuceHeader.h"
#include "Enveloppe.h"
#include "PanelOfComponents.h"

#define NUMBER_OF_OPERATORS 6
#define NUMBER_OF_IM 6
#define NUMBER_OF_MIX 6
#define NUMBER_OF_ALGO 28

//[/Headers]



//==============================================================================
/**
                                                                    //[Comments]
	An auto-generated component, created by the Introjucer.

	Describe your class and how it works here!
                                                                    //[/Comments]
*/
class PanelEngine  : public Component,
                     public Slider::Listener,
                     public Button::Listener,
                     public ComboBox::Listener,
                     public PanelOfComponents
{
public:
    //==============================================================================
    PanelEngine ();
    ~PanelEngine() override;

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.
	void buttonClicked(Button* buttonThatWasClicked) override;
	void sliderDragStarted(Slider* slider)	override;
	void sliderDragEnded(Slider* slider) override;
	void sliderValueChanged(Slider* sliderThatWasMoved) override;
	void sliderValueChanged(Slider* sliderThatWasMoved, bool fromPluginUI);
	void comboBoxChanged(ComboBox* comboBoxThatHasChanged) override;
	void comboBoxChanged(ComboBox* comboBoxThatHasChanged, bool fromPluginUI);
	void newAlgo(int algoNumber);
	void resizeAlgoDrawableImage();
	// Panel of parameters
	void buildParameters() override;
	void updateSliderFromParameter_hook(Slider* slider) override;
	void updateComboFromParameter_hook(ComboBox* combo) override;
	void updateUIEnveloppe(String paramName) override;
	bool containsThisParameterAsEnveloppe(String name) override;
	void setPfmType(int type) override;
	void enableComponent(Component* comp, bool enable);
	void hideComponent(Component* comp, bool enable);
    //[/UserMethods]

    void paint (juce::Graphics& g) override;
    void resized() override;



private:
    //[UserVariables]   -- You can add your own custom variables in this section.
	ScopedPointer<Enveloppe> enveloppe[NUMBER_OF_OPERATORS];
	ScopedPointer<TextButton> envCopyButton, envPasteButton;
	int envToCopy, envSelected;
	ScopedPointer<TextButton> enveloppeButton[NUMBER_OF_OPERATORS];
	ScopedPointer<Slider> mixKnob[NUMBER_OF_MIX];
	ScopedPointer<Slider> panKnob[NUMBER_OF_MIX];
	ScopedPointer<Label> mixLabel[NUMBER_OF_MIX];
	ScopedPointer<Label> IMLabel;
	ScopedPointer<Label> IMVelocityLabel;
	ScopedPointer<Label> IMNumber[NUMBER_OF_IM];
	ScopedPointer<Slider> IMKnob[NUMBER_OF_IM];
	ScopedPointer<Slider> IMVelocityKnob[NUMBER_OF_IM];
	ScopedPointer<Label> algoChooserLabel;
	ScopedPointer<Slider> algoChooser;
	ScopedPointer<DrawableImage> algoDrawableImage;
	Image algoImages[NUMBER_OF_ALGO];
	ScopedPointer<Label> velocityLabel;
	ScopedPointer<Slider> velocity;
	ScopedPointer<Label> voicesLabel;
	ScopedPointer<Slider> voices;
	ScopedPointer<ComboBox> playModePfm3;
	ScopedPointer<ComboBox> playModePfm2;
	ScopedPointer<Label> glideLabel;
	ScopedPointer<Slider> glide;
	ScopedPointer<Label> glideTypeLabel;
	ScopedPointer<ComboBox> glideType;

	ScopedPointer<Label> unisonSpreadLabel;
	ScopedPointer<Slider> unisonSpread;
	ScopedPointer<Label> unisonDetuneLabel;
	ScopedPointer<Slider> unisonDetune;

	ScopedPointer<Label> opShapeLabel;
	ScopedPointer<ComboBox> opShape[NUMBER_OF_OPERATORS];

	ScopedPointer<Label> opFrequencyTypeLabel;
	ScopedPointer<ComboBox> opFrequencyType[NUMBER_OF_OPERATORS];

	ScopedPointer<Label> opFrequencyLabel;
	ScopedPointer<Slider> opFrequency[NUMBER_OF_OPERATORS];

	ScopedPointer<Label> opFrequencyFineTuneLabel;
	ScopedPointer<Slider> opFrequencyFineTune[NUMBER_OF_OPERATORS];

	MidiBuffer* eventsToAdd;
    //[/UserVariables]

    //==============================================================================
    std::unique_ptr<juce::GroupComponent> operatorGroup;
    std::unique_ptr<juce::GroupComponent> mixerGroup;
    std::unique_ptr<juce::GroupComponent> imGroup;


    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PanelEngine)
};

//[EndFile] You can add extra defines here...
struct AlgoInformation {
	unsigned char osc;
	unsigned char im;
	unsigned char mix;
};
//[/EndFile]

