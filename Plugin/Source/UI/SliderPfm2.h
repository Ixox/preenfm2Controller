/*
  ==============================================================================

    SliderPfm2.h
    Created: 9 Jul 2014 11:27:53pm
    Author:  Xavier

  ==============================================================================
*/

#ifndef SLIDERPFM2_H_INCLUDED
#define SLIDERPFM2_H_INCLUDED

#include "JuceHeader.h"


class SliderPfm2 : public  Slider
{
public:
	SliderPfm2(const String& componentName) : Slider(componentName) {}
	~SliderPfm2() {}

    void mouseWheelMove (const MouseEvent& e, const MouseWheelDetails& wheel) override
    {
        if (!isEnabled() || !isVisible()) {
            return;
        }
    	if (wheel.deltaY != 0) {
			float y = getValue() + (wheel.deltaY > 0 ? getInterval() : -1 * getInterval() ) * (wheel.isReversed ? -1.0f : 1.0f);

			setValue (y);
    	}
    }

private:

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SliderPfm2)

};



class SliderPfm2Always2Decimals : public  SliderPfm2
{
public:
	SliderPfm2Always2Decimals(const String& componentName) : SliderPfm2(componentName) {}
	~SliderPfm2Always2Decimals(){ }


	String getTextFromValue (double v)
	{
		return String (v, 2) + getTextValueSuffix();
	}
private:

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SliderPfm2Always2Decimals)


};



#endif  // SLIDERPFM2_H_INCLUDED
