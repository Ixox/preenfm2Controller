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

	bool isUsingNativeAlertWindows() { return false;  }

};



#endif  // PREENLOOKANDFEEL_H_INCLUDED
