
/*
 ==============================================================================
 
 SelectedRangeBox.cpp
 Created: 22 Jan 2025 9:17:08am
 Author:  Lino Perdrix
 
 ==============================================================================
 */

#include "SelectedRangeBox.h"

SelectedRangeBox::SelectedRangeBox(NoteSetKeyboard& keyboard, NoteSet& patternNoteSet, bool& settingLowestNoteMode, bool& settingHighestNoteMode)
    : keyboard(keyboard), patternNoteSet(patternNoteSet), settingLowestNoteMode(settingLowestNoteMode), settingHighestNoteMode(settingHighestNoteMode)
{
    setText("Selected Range");
    setColour(juce::GroupComponent::ColourIds::outlineColourId, juce::Colours::white);
    selectedRangeString = "None";
    addAndMakeVisible(selectedRangeLabel);
    selectedRangeLabel.setJustificationType(juce::Justification::centred);
    
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
        AppData::getInstance().log("null pointer in setnote button wft???");
        return;
    }
    
    
    if (setNoteButton == &setLowestNoteButton)
    {
        settingLowestNoteMode = true;
        setLowestNoteButton.setButtonText("Click on the on-screen keyboard to set lowest pattern note");
        setLowestNoteButton.setColour(juce::TextButton::buttonColourId, juce::Colours::firebrick);

        settingHighestNoteMode = false;
        resetButton(&setHighestNoteButton);
    }
    else if (setNoteButton == &setHighestNoteButton)
    {
        settingHighestNoteMode = true;
        setHighestNoteButton.setButtonText("Click on the on-screen keyboard to set highest pattern note");
        setHighestNoteButton.setColour(juce::TextButton::buttonColourId, juce::Colours::firebrick);

        settingLowestNoteMode = false;
        resetButton(&setLowestNoteButton);
    }
}

void SelectedRangeBox::resetButton(juce::TextButton* setNoteButton)
{
    auto& d = AppData::getInstance();
    if (setNoteButton == nullptr)
    {
        d.log ("nullptr button passed to resetButton");
        return;
    }
    juce::String defaultMessage = setNoteButton == &setLowestNoteButton ? "Set lowest note" : "Set highest note";
    setNoteButton->setButtonText(defaultMessage);
    setNoteButton->setColour(juce::TextButton::buttonColourId, juce::Colours::grey);
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

void SelectedRangeBox::changeListenerCallback (juce::ChangeBroadcaster* noteSetKeyboard)
{
    auto& d = AppData::getInstance();
    d.log("selected range box: changed event received");
    if (noteSetKeyboard == nullptr)
    {
        d.log("nullptr received in SelectedRangeBox (from change broadcaster)");
        return;
    }
    if (!(settingLowestNoteMode || settingHighestNoteMode))
    {
        d.log("resetting buttons (note set)");
        resetButton(&setLowestNoteButton);
        resetButton(&setHighestNoteButton);
    }
    else
    {
        d.log("not resetting button: setting note failed, a set note mode is still active");
    }
}

void SelectedRangeBox::updateSelectedRangeText()
{
    selectedRangeLabel.setText ("Currently selected puterange: " + selectedRangeString, juce::NotificationType::dontSendNotification);
}
