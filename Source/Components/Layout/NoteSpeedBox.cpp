/*
  ==============================================================================

    AlgorithmSettingsBox.cpp
    Created: 13 Feb 2025 1:52:32pm
    Author:  Lino Perdrix

  ==============================================================================
*/

#include <JuceHeader.h>
#include "NoteSpeedBox.h"

//==============================================================================
NoteSpeedBox::NoteSpeedBox(ArpAlgoAudioProcessor& p) : processor(p)
{
    setText ("Pattern Speed");
    setColour (juce::GroupComponent::ColourIds::outlineColourId, juce::Colours::white);
    //
    debugBox.setMultiLine (true);
//    addAndMakeVisible (debugBox);
    addAndMakeVisible (bpmLabel);
    addAndMakeVisible (speedMenuLabel);
    addAndMakeVisible (speedMenu);
    
    populateSpeedMenu();
    
    speedMenu.onChange = [this] { handleSpeedMenuChange(); };
    
    startTimer(500);
}
void NoteSpeedBox::handleSpeedMenuChange()
{
    DBG ("app data note speed ratio before: " << AppData::getInstance().getNoteSpeedRatio());
    NoteValue newValue = getSelectedSpeedValue();
    DBG ("new speed shit: " << newValue.getRatioFromBeat());
    DBG ("new speed name: " << newValue.getName());
    AppData::getInstance().setNoteSpeedRatio(newValue.getRatioFromBeat());
    DBG ("app data note speed ratio after: " << AppData::getInstance().getNoteSpeedRatio());
}

void NoteSpeedBox::populateSpeedMenu()
{
    const juce::Array<NoteValue> noteValues = AppData::getInstance().getNoteValues();
    
    speedMenu.addSectionHeading("Straight Values");
    for (auto noteValue : noteValues)
    {
        if (noteValue.isTriplet()) continue;
        speedMenu.addItem(noteValue.getName(), noteValue.getId());
    }
    speedMenu.addSeparator();
    speedMenu.addSectionHeading("Triplet Values");
    for (auto noteValue : noteValues)
    {
        if (!noteValue.isTriplet()) continue;
        speedMenu.addItem(noteValue.getName(), noteValue.getId());
    }
    speedMenu.setSelectedId(4);
}
void NoteSpeedBox::timerCallback()
{
    debugBox.setText(processor.getDebugText());
    const auto bpm = processor.getHostBpmOrDefault();
    juce::String bpmString {"Project BPM: " + juce::String(bpm) };
    bpmLabel.setText(bpmString, juce::NotificationType::dontSendNotification);
}
NoteValue NoteSpeedBox::getSelectedSpeedValue()
{
    int newSpeedValueId = speedMenu.getSelectedId();
    NoteValue newValue;
    auto values = AppData::getInstance().getNoteValues();
    for (auto value: values)
    {
        if (value.getId() == newSpeedValueId)
            newValue = value;
    }
    return newValue;
}

void NoteSpeedBox::log(juce::String dbgText, bool shouldAppendNewline)
{
    debugBox.moveCaretToEnd();
    debugBox.insertTextAtCaret(dbgText);
    if (!shouldAppendNewline)
        return;
    debugBox.insertTextAtCaret("\n");
}

void NoteSpeedBox::changeListenerCallback(juce::ChangeBroadcaster *source)
{
    syncTextWithCurrentAlgorithm();
}

void NoteSpeedBox::syncTextWithCurrentAlgorithm()
{
//    juce::String newAlgorithmName = AppData::getInstance().getSelectedGeneratorName();
//    setText (newAlgorithmName + " settings");
}

void NoteSpeedBox::resized()
{
//    debugBox.setBounds (getLocalBounds().reduced (15));
    using FI = juce::FlexItem;

    juce::Rectangle bounds = getLocalBounds().reduced(20);
    bpmLabel.setBounds (bounds.removeFromTop(bounds.getHeight() / 2));
    juce::Rectangle menuArea = bounds.reduced (0, 10);

    juce::FlexBox menuAreaFb;
    menuAreaFb.justifyContent = juce::FlexBox::JustifyContent::spaceBetween;
    menuAreaFb.items.add (FI(speedMenuLabel).withMinWidth (140.0f).withMinHeight (30.0f));
    menuAreaFb.items.add (FI(speedMenu)     .withMinWidth (170.0f).withMinHeight (30.0f));
    menuAreaFb.performLayout(menuArea);
}
