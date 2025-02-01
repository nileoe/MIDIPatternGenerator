/*
  ==============================================================================

    SelectedRangeBox.h
    Created: 22 Jan 2025 9:17:08am
    Author:  Lino Perdrix

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
*/
class SelectedRangeBox  : public juce::GroupComponent
{
public:
    SelectedRangeBox(juce::MidiKeyboardState& keyboardState);
    void resized() override;

private:
    juce::MidiKeyboardState& keyboardState;
    juce::String selectedRangeString;
    juce::Label selectedRangeLabel;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SelectedRangeBox)
};

