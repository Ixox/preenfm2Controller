/*
  ==============================================================================

    PreenLookAndFeel.h
    Created: 8 Apr 2014 9:23:51pm
    Author:  xhosxe

  ==============================================================================
*/

#ifndef PREENLOOKANDFEEL_H_INCLUDED
#define PREENLOOKANDFEEL_H_INCLUDED

#include "JuceHeader.h"

class preenfmLookAndFeel : public LookAndFeel_V4 {
public:
	preenfmLookAndFeel();
	void drawRotarySlider(Graphics& g, int x, int y, int width, int height, float sliderPos,
		const float rotaryStartAngle, const float rotaryEndAngle, Slider& slider);

	void drawLinearSlider(Graphics& g, int x, int y, int width, int height,
		float sliderPos,
		float minSliderPos,
		float maxSliderPos,
		const Slider::SliderStyle style, Slider& slider);

	void drawComboBox(Graphics& g, int width, int height, bool,
		int, int, int, int, ComboBox& box);


	Font getComboBoxFont(ComboBox& box);
	void positionComboBoxText(ComboBox& box, Label& label);

private:
};



#endif  // PREENLOOKANDFEEL_H_INCLUDED
