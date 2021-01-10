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

#include "PreenLookAndFeel.h"


preenfmLookAndFeel::preenfmLookAndFeel() : LookAndFeel_V4() {
	//windowBackground = 0,
	//	widgetBackground,
	//	menuBackground,
	//	outline,
	//	defaultText,
	//	defaultFill,
	//	highlightedText,
	//	highlightedFill,
	//	menuText,
	setUsingNativeAlertWindows(false);
	setColourScheme(
	{ 0xff505050, 0xff303030, 0xff202020,
		0xffa6a6a6, 0xffffffff,
		0xff000000, 0xff000000,
		0xffffffff, 0xffffffff }
	//{ 0xff505050, 0xff424242, 0xff606060,
	//	0xffa6a6a6, 0xffffffff,
	//	0xff21ba90, 0xff000000,
	//	0xffffffff, 0xffffffff }
	);
}



void preenfmLookAndFeel::drawRotarySlider(Graphics& g, int x, int y, int width, int height, float sliderPos,
	const float rotaryStartAngle, const float rotaryEndAngle, Slider& slider)
{
	const auto outline = Colours::grey;
	const auto fill = Colours::lightblue;

	const auto bounds = Rectangle<int>(x, y, width, height).toFloat().reduced(5);

	auto radius = jmin(bounds.getWidth(), bounds.getHeight()) / 2.0f;
	const auto toAngle = rotaryStartAngle + sliderPos * (rotaryEndAngle - rotaryStartAngle);
	auto lineW = jmin(4.0f, radius * 0.5f);
	auto arcRadius = radius - lineW * 0.5f;

	Path backgroundArc;
	backgroundArc.addCentredArc(bounds.getCentreX(),
		bounds.getCentreY(),
		arcRadius,
		arcRadius,
		0.0f,
		rotaryStartAngle,
		rotaryEndAngle,
		true);

	g.setColour(outline);
	g.strokePath(backgroundArc, PathStrokeType(lineW, PathStrokeType::curved, PathStrokeType::butt));

	if (slider.isEnabled())
	{
		Path valueArc;
		valueArc.addCentredArc(bounds.getCentreX(),
			bounds.getCentreY(),
			arcRadius,
			arcRadius,
			0.0f,
			rotaryStartAngle,
			toAngle,
			true);

		g.setColour(fill);
		g.strokePath(valueArc, PathStrokeType(lineW, PathStrokeType::curved, PathStrokeType::butt));

        const juce::Point<float> thumbPoint(bounds.getCentreX() + arcRadius * std::cos(toAngle - float_Pi * 0.5f),
			bounds.getCentreY() + arcRadius * std::sin(toAngle - float_Pi * 0.5f));

		g.setColour(fill);
		g.drawLine(bounds.getCentreX(), bounds.getCentreY(), thumbPoint.getX(), thumbPoint.getY());
	}
}


void preenfmLookAndFeel::drawLinearSlider(Graphics& g, int x, int y, int width, int height,
	float sliderPos,
	float minSliderPos,
	float maxSliderPos,
	const Slider::SliderStyle style, Slider& slider)
{

	const auto outline = Colours::grey;
	const auto fill = Colours::lightblue;


	const auto trackWidth = jmin(4.0f, slider.isHorizontal() ? height * 0.25f : width * 0.25f);

	const juce::Point<float> startPoint(slider.isHorizontal() ? x : x + width * 0.5f,
		slider.isHorizontal() ? y + height * 0.5f : height + y);

	const juce::Point<float> endPoint(slider.isHorizontal() ? width + x : startPoint.x,
		slider.isHorizontal() ? startPoint.y : y);

	Path backgroundTrack;
	backgroundTrack.startNewSubPath(startPoint);
	backgroundTrack.lineTo(endPoint);

	g.setColour(outline);
	g.strokePath(backgroundTrack, PathStrokeType(trackWidth, PathStrokeType::curved, PathStrokeType::butt));

	Path valueTrack;
	juce::Point<float> minPoint, maxPoint;
	juce::Point<float> midPoint = (endPoint + startPoint) / 2;

	const auto kx = slider.isHorizontal() ? sliderPos : (x + width * 0.5f);
	const auto ky = slider.isHorizontal() ? (y + height * 0.5f) : sliderPos;

	minPoint = startPoint;
	maxPoint = { kx, ky };

	valueTrack.startNewSubPath(midPoint);
	valueTrack.lineTo(maxPoint);

	float knobWidth = trackWidth;
	float knobHeight = trackWidth;
	if (slider.isHorizontal()) {
		knobHeight *= 3.0f;
	}
	else {
		knobWidth *= 3.0f;

	}

	g.setColour(fill);
	g.strokePath(valueTrack, PathStrokeType(trackWidth, PathStrokeType::curved, PathStrokeType::butt));
	g.fillRect(Rectangle<float>(knobWidth, knobHeight).withCentre(maxPoint));
}


void preenfmLookAndFeel::drawComboBox(Graphics& g, int width, int height, bool,
	int, int, int, int, ComboBox& box)
{
	const auto cornerSize = box.findParentComponentOfClass<ChoicePropertyComponent>() != nullptr ? 0.0f : 3.0f;
	const Rectangle<int> boxBounds(0, 0, width, height);

	g.setColour(box.findColour(ComboBox::backgroundColourId));
	g.fillRoundedRectangle(boxBounds.toFloat(), cornerSize);

	g.setColour(box.findColour(ComboBox::outlineColourId));
	g.drawRoundedRectangle(boxBounds.toFloat().reduced(0.5f, 0.5f), cornerSize, 1.0f);

	Rectangle<int> arrowZone(width - 18, 0, 15, height);
	Path path;
	path.startNewSubPath(arrowZone.getX() + 3.0f, arrowZone.getCentreY() - 2.0f);
	path.lineTo(static_cast<float> (arrowZone.getCentreX()), arrowZone.getCentreY() + 3.0f);
	path.lineTo(arrowZone.getRight() - 3.0f, arrowZone.getCentreY() - 2.0f);

	g.setColour(box.findColour(ComboBox::arrowColourId).withAlpha((box.isEnabled() ? 0.9f : 0.2f)));
	g.strokePath(path, PathStrokeType(1.5f));
}


Font preenfmLookAndFeel::getComboBoxFont(ComboBox& box)
{
	return Font(jmin(14.0f, box.getHeight() * 0.85f));
}


void preenfmLookAndFeel::positionComboBoxText(ComboBox& box, Label& label)
{
	label.setBounds(1, 1,
		box.getWidth() - 18,
		box.getHeight() - 2);

	label.setFont(getComboBoxFont(box));
}





