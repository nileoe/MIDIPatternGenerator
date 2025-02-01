
/*
 ==============================================================================
 
 SelectedRangeBox.cpp
 Created: 22 Jan 2025 9:17:08am
 Author:  Lino Perdrix
 
 ==============================================================================
 */

#include "SelectedRangeBox.h"

SelectedRangeBox::SelectedRangeBox(juce::MidiKeyboardState& keyboardState, int& patternLowestNote, int& patternHighestNote) : keyboardState(keyboardState), patternLowestNote(patternLowestNote), patternHighestNote(patternHighestNote)
{
    setText ("Selected Range");
    setColour (juce::GroupComponent::ColourIds::outlineColourId, juce::Colours::white);
    selectedRangeString = "None";
    addAndMakeVisible (selectedRangeLabel);
    selectedRangeLabel.setJustificationType(juce::Justification::centred);
    
    setLowestNoteButton.onClick  = [this] { toggleButton(&setLowestNoteButton); };
    setHighestNoteButton.onClick = [this] { toggleButton(&setHighestNoteButton); };
    
    addAndMakeVisible (setLowestNoteButton);
    addAndMakeVisible (setHighestNoteButton);
}

void SelectedRangeBox::toggleButton(juce::TextButton* setNoteButton)
{
    AppData::getInstance().dbg("fuck yeaaaaaaaaaaaaaaaaa");
    if (setNoteButton == nullptr)
        return;
    bool isOn = setNoteButton->getToggleState();
    if (isOn)
    {
        setNoteButton->setButtonText(activeButtonMessage);
        setNoteButton->setColour(juce::TextButton::buttonOnColourId, juce::Colours::firebrick);
    }
    else
    {
        if (setNoteButton == &setLowestNoteButton)
        {
            setNoteButton->setButtonText("Set lowest note");
            setNoteButton->setColour(juce::TextButton::buttonOnColourId, juce::Colours::grey);
        }
        else if (setNoteButton == &setLowestNoteButton)
        {
            setNoteButton->setButtonText("Set lowest note");
            setNoteButton->setColour(juce::TextButton::buttonOnColourId, juce::Colours::grey);
        }
    }
}

void SelectedRangeBox::resized()
{
    using FI = juce::FlexItem;
    updateSelectedRangeText();
    
    juce::FlexBox buttonsFb;
    buttonsFb.alignItems = juce::FlexBox::AlignItems::center;
    buttonsFb.items.add (FI (setLowestNoteButton) .withMinWidth (150).withMinHeight (25));
    buttonsFb.items.add (FI (setHighestNoteButton).withMinWidth (150).withMinHeight (25).withMargin (FI::Margin(0, 0, 0, 10)));
    
    juce::FlexBox mainFb;
    mainFb.justifyContent = juce::FlexBox::JustifyContent::spaceBetween;
    mainFb.alignItems = juce::FlexBox::AlignItems::center;
    mainFb.items.add (FI (buttonsFb)            .withMinWidth (200).withMinHeight (25).withMargin (FI::Margin(0, 0, 0, 20)));
    mainFb.items.add (FI (selectedRangeLabel)   .withMinWidth (200).withMinHeight (30).withMargin (FI::Margin(0, 20, 0, 0)));

    mainFb.performLayout(getLocalBounds());
}

void SelectedRangeBox::updateSelectedRangeText()
{
    selectedRangeLabel.setText ("Currently selected range: " + selectedRangeString, juce::NotificationType::dontSendNotification);
}
