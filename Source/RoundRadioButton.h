/*
  ==============================================================================

    RoundRadioButton.h
    Created: 22 Jan 2025 10:59:57am
    Author:  Lino Perdrix

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
 #pragma once

 #include <JuceHeader.h>

 class RoundRadioButton : public juce::ToggleButton
 {
 public:
     RoundRadioButton(const juce::String& buttonText)
         : juce::ToggleButton(buttonText)
     {
     }

 };


 */
class RoundRadioButton  : public juce::ToggleButton
{
public:
    RoundRadioButton(const juce::String& buttonText, int radioGroupId = -1) : juce::ToggleButton(buttonText)
    {
        setRadioGroupId (radioGroupId);
    }

    ~RoundRadioButton() override
    {
    }


    
    void paint(juce::Graphics& g) override
    {
        auto area = getLocalBounds();
        auto buttonArea = area.reduced(4); // Add some padding
//        auto diameter = juce::jmin(buttonArea.getWidth(), buttonArea.getHeight());
        int diameter = 12;

        // Draw the round button
//        g.setColour(findColour(juce::ToggleButton::ColourIds::tickDisabledColourId).withAlpha(isEnabled() ? 1.0f : 0.5f));
        g.setColour(findColour(juce::ToggleButton::ColourIds::tickDisabledColourId));
        float ellipseY = buttonArea.getY() + (buttonArea.getHeight() - diameter) / 2;
        juce::Rectangle<int> buttonEllipseArea(buttonArea.getX(), ellipseY, diameter, diameter);
//        g.drawEllipse(buttonEllipseArea.reduced(2.0f), 1.5f);
        g.drawEllipse(buttonEllipseArea.toFloat(), 1.5f);
//        g.drawEllipse(buttonArea.toFloat().withSize(diameter, diameter).reduced(2.0f), 1.5f);

        // Draw the dot if the button is selected
        if (getToggleState())
        {
            g.setColour(findColour(juce::ToggleButton::ColourIds::tickColourId));
//            g.fillEllipse(buttonArea.toFloat().withSize(diameter, diameter).reduced(diameter / 3.0f));
            g.fillEllipse(buttonEllipseArea.toFloat().withSize(diameter, diameter).reduced(diameter / 3.0f));
        }

        // Draw the button text
        g.setColour(getLookAndFeel().findColour(juce::ToggleButton::textColourId));
        g.setFont(juce::Font(juce::FontOptions(16.0f)));
        g.drawFittedText(getButtonText(), buttonArea.removeFromRight(buttonArea.getWidth() - diameter - 10), juce::Justification::centredLeft, 1);
    }


    
    
    
    
    
//    void paint(juce::Graphics& g) override
//    {
//        auto area = getLocalBounds();
////        auto buttonArea = area.reduced(4); // Add some padding
//        g.setColour(juce::Colours::red);
////        g.drawRect(buttonArea);
//        g.drawRect(area);
//        
//        int diameter = 17;
//
//        // Draw the round button
//        g.setColour(findColour(juce::ToggleButton::ColourIds::tickDisabledColourId).withAlpha(isEnabled() ? 1.0f : 0.5f));
//        float ellipseX = area.getX() + (area.getWidth()  - diameter) / 2;
//        float ellipseY = area.getY() + (area.getHeight() - diameter) / 2;
////        float ellipseX = buttonArea.getX() + (buttonArea.getWidth()  - diameter) / 2;
////        float ellipseY = buttonArea.getY() + (buttonArea.getHeight() - diameter) / 2;
//        g.drawEllipse(ellipseX, ellipseY, diameter, diameter, 1.5f);
//
////        g.drawEllipse(buttonArea.toFloat().withSize(diameter, diameter).reduced(2.0f), 1.5f);
//        // Draw the dot if the button is selected
//        if (getToggleState())
//        {
//            g.setColour(findColour(juce::ToggleButton::ColourIds::tickColourId));
////            g.fillEllipse(buttonArea.toFloat().withSize(diameter, diameter).reduced(diameter / 3.0f));
//            g.fillEllipse(area.toFloat().withSize(diameter, diameter).reduced(diameter / 3.0f));
//        }
//
//        // Draw the button text
//        g.setColour(getLookAndFeel().findColour(juce::ToggleButton::textColourId));
//        g.setFont(juce::Font(16.0f));
////        g.drawFittedText(getButtonText(), buttonArea.removeFromRight(buttonArea.getWidth() - diameter - 10), juce::Justification::centredLeft, 1);
//        g.drawFittedText(getButtonText(), area.removeFromRight(area.getWidth() - diameter - 10), juce::Justification::centredLeft, 1);
////        g.drawFittedText(getButtonText(), area.removeFromRight(buttonArea.getWidth() - diameter - 10), juce::Justification::centredLeft, 1);
//    }
    void resized() override
    {
        // This method is where you should set the bounds of any child
        // components that your component contains..

    }

private:
//    juce::String buttonText;
//    int radioGroupId;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (RoundRadioButton)
};
