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
    SelectedRangeBox(juce::MidiKeyboardState& keyboardState) : keyboardState(keyboardState)
    {
        setText ("Selected Range");
        setColour (juce::GroupComponent::ColourIds::outlineColourId, juce::Colours::white);
        selectedRangeString = "None";
        addAndMakeVisible (selectedRangeLabel);
        selectedRangeLabel.setJustificationType(juce::Justification::centred);
    }

    ~SelectedRangeBox() override
    {
    }

    void resized() override
    {
        selectedRangeLabel
            .setText ("Currently selected range: " + selectedRangeString,
                      juce::NotificationType::dontSendNotification);
        
        selectedRangeLabel.setSize(200, 50);
        selectedRangeLabel.setCentrePosition (getLocalBounds().getCentre());
    }

private:
    juce::MidiKeyboardState& keyboardState;
    juce::String selectedRangeString;
    juce::Label selectedRangeLabel;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SelectedRangeBox)
};
