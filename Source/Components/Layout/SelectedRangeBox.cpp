
/*
 ==============================================================================
 
 SelectedRangeBox.cpp
 Created: 22 Jan 2025 9:17:08am
 Author:  Lino Perdrix
 
 ==============================================================================
 */

#include "SelectedRangeBox.h"

SelectedRangeBox::SelectedRangeBox(NoteSetKeyboard& keyboard, bool& settingLowestNoteMode, bool& settingHighestNoteMode)
    : keyboard(keyboard), settingLowestNoteMode(settingLowestNoteMode), settingHighestNoteMode(settingHighestNoteMode)
{
    setText("Selected Range");
    setColour(juce::GroupComponent::ColourIds::outlineColourId, juce::Colours::white);
    selectedRangeString = "None";
    addAndMakeVisible(selectedRangeLabel);
    selectedRangeLabel.setJustificationType(juce::Justification::centredRight);
    
    setLowestNoteButton.onClick = [this]
    {
        toggleButton( & setLowestNoteButton);
    };
    setHighestNoteButton.onClick = [this]
    {
        toggleButton( & setHighestNoteButton);
    };
    
    addAndMakeVisible(setLowestNoteButton);
    addAndMakeVisible(setHighestNoteButton);
}


void SelectedRangeBox::toggleButton(juce::TextButton* setNoteButton)
{
    if (setNoteButton == nullptr)
    {
        DBG ("null pointer in setnote button wft???");
        return;
    }
    
    
    if (setNoteButton == &setLowestNoteButton)
    {
        settingLowestNoteMode = true;
        setLowestNoteButton.setButtonText("Click on-screen keyboard...");
        setLowestNoteButton.setColour(juce::TextButton::buttonColourId, juce::Colours::grey);

        settingHighestNoteMode = false;
        resetButton(&setHighestNoteButton);
    }
    else if (setNoteButton == &setHighestNoteButton)
    {
        settingHighestNoteMode = true;
        setHighestNoteButton.setButtonText("Click on-screen keyboard...");
        setHighestNoteButton.setColour(juce::TextButton::buttonColourId, juce::Colours::grey);

        settingLowestNoteMode = false;
        resetButton(&setLowestNoteButton);
    }
}

void SelectedRangeBox::resetButton(juce::TextButton* setNoteButton)
{
    if (setNoteButton == nullptr)
    {
        DBG ("nullptr button passed to resetButton");
        return;
    }
    juce::String defaultMessage = setNoteButton == &setLowestNoteButton ? "Set lowest note" : "Set highest note";
    setNoteButton->setButtonText(defaultMessage);
    juce::Colour defaultButtonBackgroundColour = juce::LookAndFeel::getDefaultLookAndFeel().findColour(juce::TextButton::buttonColourId);
    setNoteButton->setColour(juce::TextButton::buttonColourId, defaultButtonBackgroundColour);
}

void SelectedRangeBox::resized()
{
    using FI = juce::FlexItem;
    updateSelectedRangeText();
    
    juce::FlexBox buttonsFb;
    buttonsFb.alignItems = juce::FlexBox::AlignItems::center;
    buttonsFb.items.add (FI (setLowestNoteButton) .withMinWidth (200).withMinHeight (40));
    buttonsFb.items.add (FI (setHighestNoteButton).withMinWidth (200).withMinHeight (40).withMargin (FI::Margin(0, 0, 0, 10)));
    
    juce::FlexBox mainFb;
    mainFb.justifyContent = juce::FlexBox::JustifyContent::spaceBetween;
    mainFb.alignItems = juce::FlexBox::AlignItems::center;
    mainFb.items.add (FI (buttonsFb)            .withMinWidth (200).withMinHeight (50).withMargin (FI::Margin(0, 0, 0, 20)));
    mainFb.items.add (FI (selectedRangeLabel)   .withMinWidth (300).withMinHeight (55).withMargin (FI::Margin(0, 20, 0, 0)));

    mainFb.performLayout(getLocalBounds());
}

void SelectedRangeBox::changeListenerCallback (juce::ChangeBroadcaster* noteSetKeyboard)
{
    DBG ("selected range box: changed event received");
    if (noteSetKeyboard == nullptr)
    {
        DBG ("nullptr received in SelectedRangeBox (from change broadcaster)");
        return;
    }
    if (!(settingLowestNoteMode || settingHighestNoteMode))
    {
        DBG ("resetting buttons (note set)");
        resetButton(&setLowestNoteButton);
        resetButton(&setHighestNoteButton);
        updateSelectedRangeText();
    }
    else
    {
        DBG ("not resetting button: setting note failed, a set note mode is still active");
    }
}

void SelectedRangeBox::updateSelectedRangeText()
{
    auto& noteSet = PatternSettings::getInstance().getNoteSet();
    const juce::String lowestNoteName  = juce::MidiMessage::getMidiNoteName(noteSet.getLowestNote(),  true, true, 0);
    const juce::String highestNoteName = juce::MidiMessage::getMidiNoteName(noteSet.getHighestNote(), true, true, 0);
    selectedRangeString = lowestNoteName + " - " + highestNoteName;
    selectedRangeLabel.setText ("Currently selected range: " + selectedRangeString, juce::NotificationType::dontSendNotification);
}
