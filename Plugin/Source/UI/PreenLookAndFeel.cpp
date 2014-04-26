/*
  ==============================================================================

    PreenLookAndFeel.cpp
    Created: 8 Apr 2014 9:23:51pm
    Author:  xhosxe

  ==============================================================================
 */

#include "PreenLookAndFeel.h"
#include "OTF/exoFont.h"

static Colour createBaseColourPFM2 (Colour buttonColour,
		bool hasKeyboardFocus,
		bool isMouseOverButton,
		bool isButtonDown) noexcept {

	const float sat = hasKeyboardFocus ? 1.3f : 0.9f;
	const Colour baseColour (buttonColour.withMultipliedSaturation (sat));

	if (isButtonDown)
		return baseColour.contrasting (0.2f);
	if (isMouseOverButton)
		return baseColour.contrasting (0.1f);

	return baseColour;
}


preenfmLookAndFeel::preenfmLookAndFeel() : LookAndFeel_V3() {
	exoFont = Typeface::createSystemTypefaceFor(exoFont::exoregular_otf, exoFont::exoregular_otfSize);
}

Typeface::Ptr preenfmLookAndFeel::getTypefaceForFont(const Font &) {
	return exoFont;
}

void preenfmLookAndFeel::drawLinearSliderBackground (Graphics& g, int x, int y, int width, int height,
		float /*sliderPos*/,
		float /*minSliderPos*/,
		float /*maxSliderPos*/,
		const Slider::SliderStyle /*style*/, Slider& slider)
{
	const float sliderRadius = 2.0f; // (float) (getSliderThumbRadius (slider) - 2);

	const Colour trackColour (slider.findColour (Slider::trackColourId));
	const Colour gradCol1 (trackColour.overlaidWith (Colours::black.withAlpha (slider.isEnabled() ? 0.25f : 0.13f)));
	const Colour gradCol2 (trackColour.overlaidWith (Colour (0x14000000)));
	Path indent;

	if (slider.isHorizontal())
	{
		const float iy = y + height * 0.5f - sliderRadius * 0.5f;
		const float ih = sliderRadius;

		indent.addRoundedRectangle (x - sliderRadius * 0.5f, iy,
				width + sliderRadius, ih,
				5.0f);
	}
	else
	{
		const float ix = x + width * 0.5f - sliderRadius * 0.5f;
		const float iw = sliderRadius;

		g.setGradientFill (ColourGradient (gradCol1, ix, 0.0f,
				gradCol2, ix + iw, 0.0f, false));

		indent.addRoundedRectangle (ix, y - sliderRadius * 0.5f,
				iw, height + sliderRadius,
				5.0f);
	}

	//	    g.fillPath (indent);
	if (slider.isEnabled()) {
        g.setColour (Colours::darkgrey);
	} else {
        g.setColour (Colour (0x80808080));
	}
	g.strokePath (indent, PathStrokeType (0.5f));
}


void preenfmLookAndFeel::drawLinearSliderThumb (Graphics& g, int x, int y, int width, int height,
		float sliderPos, float minSliderPos, float maxSliderPos,
		const Slider::SliderStyle style, Slider& slider) 				{

	if (!slider.isEnabled()) {
		return;
	}

	const float sliderRadius = (float) (getSliderThumbRadius (slider) - 2);

	Colour knobColour (createBaseColourPFM2 (slider.findColour (Slider::thumbColourId),
			slider.hasKeyboardFocus (false) && slider.isEnabled(),
			slider.isMouseOverOrDragging() && slider.isEnabled(),
			slider.isMouseButtonDown() && slider.isEnabled()));

	const float outlineThickness = slider.isEnabled() ? 0.8f : 0.3f;

	if (style == Slider::LinearHorizontal || style == Slider::LinearVertical)
	{
		float kx, ky;

		if (style == Slider::LinearVertical)
		{
			kx = x + width * 0.5f;
			ky = sliderPos;
		}
		else
		{
			kx = sliderPos;
			ky = y + height * 0.5f;
		}

		//	        drawGlassSphere (g,
		//	                         kx - sliderRadius,
		//	                         ky - sliderRadius,
		//	                         sliderRadius * 2.0f,
		//	                         knobColour, outlineThickness);
		if (slider.isEnabled()) {
			g.setColour(knobColour);
			g.fillRect( kx - sliderRadius + 3,  ky - sliderRadius, sliderRadius*2 - 6, sliderRadius*2);
			g.setColour(Colours::grey);
		} else {
			g.setColour (Colour (0x80808080));
		}
		g.drawRect( kx - sliderRadius + 3,  ky - sliderRadius, sliderRadius*2 - 6, sliderRadius*2);
	}
	else
	{
		LookAndFeel_V2::drawLinearSliderThumb (g, x, y, width, height,
				sliderPos, minSliderPos, maxSliderPos,
				style, slider);
	}
				}

void preenfmLookAndFeel::drawButtonBackground (Graphics& g, Button& button, const Colour& backgroundColour,
		bool isMouseOverButton, bool isButtonDown)
{
	if (!button.isEnabled()) {
		return;
	}

	Colour baseColour (backgroundColour.withMultipliedSaturation (button.hasKeyboardFocus (true) ? 1.3f : 0.9f)
			.withMultipliedAlpha (button.isEnabled() ? 0.9f : 0.5f));

	if (isButtonDown || isMouseOverButton)
		baseColour = baseColour.contrasting (isButtonDown ? 0.2f : 0.1f);

	const bool flatOnLeft   = button.isConnectedOnLeft();
	const bool flatOnRight  = button.isConnectedOnRight();
	const bool flatOnTop    = button.isConnectedOnTop();
	const bool flatOnBottom = button.isConnectedOnBottom();

	const float width  = button.getWidth() - 1.0f;
	const float height = button.getHeight() - 1.0f;

	if (width > 0 && height > 0)
	{
		const float cornerSize = 4.0f;

		Path outline;
		outline.addRoundedRectangle (0.5f, 0.5f, width, height, cornerSize, cornerSize,
				! (flatOnLeft  || flatOnTop),
				! (flatOnRight || flatOnTop),
				! (flatOnLeft  || flatOnBottom),
				! (flatOnRight || flatOnBottom));


		const float mainBrightness = baseColour.getBrightness();
		const float mainAlpha = baseColour.getFloatAlpha();

		g.setColour (baseColour);
		g.fillPath (outline);
		g.setColour (Colours::black.withAlpha (0.4f * mainAlpha));
		g.strokePath (outline, PathStrokeType (1.0f));
	}
}


void preenfmLookAndFeel::drawRotarySlider (Graphics& g, int x, int y, int width, int height, float sliderPos,
		const float rotaryStartAngle, const float rotaryEndAngle, Slider& slider)
{

	const float radius = jmin (width / 2, height / 2) - 2.0f;
	const float centreX = x + width * 0.5f;
	const float centreY = y + height * 0.5f;
	const float rx = centreX - radius;
	const float ry = centreY - radius;
	const float rw = radius * 2.0f;
	const float angle = rotaryStartAngle + sliderPos * (rotaryEndAngle - rotaryStartAngle);
	const bool isMouseOver = slider.isMouseOverOrDragging() && slider.isEnabled();

	if (radius > 12.0f)
	{
        const float thickness = 0.75f;
		if (slider.isEnabled()) {
			g.setColour (slider.findColour (Slider::rotarySliderFillColourId).withAlpha (isMouseOver ? 1.0f : 0.7f));

            Path filledArc;
		    if (slider.getMinimum() >= 0) {
	            filledArc.addPieSegment (rx, ry, rw, rw, rotaryStartAngle, angle, thickness);
	            g.fillPath (filledArc);
		    } else {

                filledArc.addPieSegment (rx, ry, rw, rw, 0, (sliderPos - 0.5) * (rotaryEndAngle - rotaryStartAngle), thickness);
                g.fillPath (filledArc);
		    }

            float innerRadius = 1;
            if (isMouseOver ) {
                innerRadius = 2;
            }
            Path p;
            p.addTriangle (-innerRadius, 0.0f,
                    0.0f, -radius * thickness * 1.1f,
                    innerRadius, 0.0f);

            //              p.addEllipse (-innerRadius, -innerRadius, innerRadius * 2.0f, innerRadius * 2.0f);

            g.fillPath (p, AffineTransform::rotation (angle).translated (centreX, centreY));
            g.setColour (slider.findColour (Slider::rotarySliderOutlineColourId));
		} else {
            g.setColour (Colour (0x80808080));
		}

		Path outlineArc;
		outlineArc.addPieSegment (rx, ry, rw, rw, rotaryStartAngle, rotaryEndAngle, thickness);
		outlineArc.closeSubPath();

		g.strokePath (outlineArc, PathStrokeType (slider.isEnabled() ?  1.2f : 0.3f));
	}
	else
	{
		if (slider.isEnabled())
			g.setColour (slider.findColour (Slider::rotarySliderFillColourId).withAlpha (isMouseOver ? 1.0f : 0.7f));
		else
			g.setColour (Colour (0x80808080));

		Path p;
		p.addEllipse (-0.4f * rw, -0.4f * rw, rw * 0.8f, rw * 0.8f);
		PathStrokeType (rw * 0.1f).createStrokedPath (p, p);

		p.addLineSegment (Line<float> (0.0f, 0.0f, 0.0f, -radius), rw * 0.2f);

		g.fillPath (p, AffineTransform::rotation (angle).translated (centreX, centreY));
	}
}

