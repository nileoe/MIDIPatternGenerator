
/*
 ==============================================================================
 
 SelectedRangeBox.cpp
 Created: 22 Jan 2025 9:17:08am
 Author:  Lino Perdrix
 
 ==============================================================================
 */

#include "SelectedRangeBox.h"

SelectedRangeBox::SelectedRangeBox(juce::MidiKeyboardState& keyboardState) : keyboardState(keyboardState)
{
    setText ("Selected Range");
    setColour (juce::GroupComponent::ColourIds::outlineColourId, juce::Colours::white);
    selectedRangeString = "None";
    addAndMakeVisible (selectedRangeLabel);
    selectedRangeLabel.setJustificationType(juce::Justification::centred);
}

void SelectedRangeBox::resized()
{
    selectedRangeLabel
        .setText ("Currently selected range: " + selectedRangeString,
                  juce::NotificationType::dontSendNotification);
    
    selectedRangeLabel.setSize(200, 50);
    selectedRangeLabel.setCentrePosition (getLocalBounds().getCentre());
}
