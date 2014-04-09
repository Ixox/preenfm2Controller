/*
  ==============================================================================

    PreenLookAndFeel.h
    Created: 8 Apr 2014 9:23:51pm
    Author:  xhosxe

  ==============================================================================
*/

#ifndef PREENLOOKANDFEEL_H_INCLUDED
#define PREENLOOKANDFEEL_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"

class preenfmLookAndFeel : public LookAndFeel_V3 {
public:
	preenfmLookAndFeel();

	Typeface::Ptr getTypefaceForFont(const Font &) override;

	void drawLinearSliderBackground (Graphics& g, int x, int y, int width, int height,
	                                                 float /*sliderPos*/,
	                                                 float /*minSliderPos*/,
	                                                 float /*maxSliderPos*/,
	                                                 const Slider::SliderStyle /*style*/, Slider& slider) override;
	void drawLinearSliderThumb (Graphics& g, int x, int y, int width, int height,
	                                            float sliderPos, float minSliderPos, float maxSliderPos,
	                                            const Slider::SliderStyle style, Slider& slider) override;

	void drawButtonBackground (Graphics& g, Button& button, const Colour& backgroundColour,
	                                           bool isMouseOverButton, bool isButtonDown) override;

	void drawRotarySlider (Graphics& g, int x, int y, int width, int height, float sliderPos,
	                                       const float rotaryStartAngle, const float rotaryEndAngle, Slider& slider) override;


private:
	Typeface::Ptr exoFont;
};



#endif  // PREENLOOKANDFEEL_H_INCLUDED
