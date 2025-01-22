/*
  ==============================================================================

    ScaleAndHarmonyBox.h
    Created: 22 Jan 2025 10:40:42am
    Author:  Lino Perdrix

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
*/
class ScaleAndHarmonyBox  : public juce::GroupComponent
{
public:
    ScaleAndHarmonyBox()
    {
        setText ("Scale and Harmony");
        setColour (juce::GroupComponent::ColourIds::outlineColourId, juce::Colours::white);
    }

    ~ScaleAndHarmonyBox() override
    {
    }

    void resized() override
    {
    }

private:
    juce::ToggleButton useHarmonyButton     { "Use existing harmony to set available pitches" };
    juce::ToggleButton chooseScaleButton    { "Choose scale" };
//    juce::ToggleButton chooseScaleButton    { "Choose scale" };
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ScaleAndHarmonyBox)
};
