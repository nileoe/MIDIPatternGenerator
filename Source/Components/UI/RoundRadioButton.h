/*
  ==============================================================================

    RoundRadioButton.h
    Created: 22 Jan 2025 10:59:57am
    Author:  Lino Perdrix

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

class RoundRadioButton  : public juce::ToggleButton
{
public:
    RoundRadioButton(const juce::String& buttonText, int radioGroupId = -1);
    void paint(juce::Graphics& g) override;
    
    private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (RoundRadioButton)
};
