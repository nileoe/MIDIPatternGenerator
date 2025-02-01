/*
 ==============================================================================
 
 RoundRadioButton.cpp
 Created: 22 Jan 2025 10:59:57am
 Author:  Lino Perdrix
 
 ==============================================================================
 */

#include "RoundRadioButton.h"

RoundRadioButton::RoundRadioButton(const juce::String& buttonText, int radioGroupId) : juce::ToggleButton(buttonText)
{
    setRadioGroupId (radioGroupId);
}

void RoundRadioButton::paint(juce::Graphics& g)
{
    auto area = getLocalBounds();
    auto buttonArea = area.reduced(4);
    int diameter = 12;
    
    g.setColour(findColour(juce::ToggleButton::ColourIds::tickDisabledColourId));
    float ellipseY = buttonArea.getY() + (buttonArea.getHeight() - diameter) / 2;
    juce::Rectangle<int> buttonEllipseArea(buttonArea.getX(), ellipseY, diameter, diameter);
    g.drawEllipse(buttonEllipseArea.toFloat(), 1.5f);
    
    if (getToggleState())
    {
        g.setColour(findColour(juce::ToggleButton::ColourIds::tickColourId));
        g.fillEllipse(buttonEllipseArea.toFloat().withSize(diameter, diameter).reduced(diameter / 3.0f));
    }
    
    g.setColour(getLookAndFeel().findColour(juce::ToggleButton::textColourId));
    g.setFont(juce::Font(juce::FontOptions(16.0f)));
    g.drawFittedText(getButtonText(), buttonArea.removeFromRight(buttonArea.getWidth() - diameter - 10), juce::Justification::centredLeft, 1);
}
