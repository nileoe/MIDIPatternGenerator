/*
  ==============================================================================

    AlgorithmSettingsBox.cpp
    Created: 13 Feb 2025 1:52:32pm
    Author:  Lino Perdrix

  ==============================================================================
*/

#include <JuceHeader.h>
#include "AlgorithmSettingsBox.h"

//==============================================================================
AlgorithmSettingsBox::AlgorithmSettingsBox(ArpAlgoAudioProcessor& p) : processor(p)
{
    setText ("Algorithm Settings");
    setColour (juce::GroupComponent::ColourIds::outlineColourId, juce::Colours::white);
    //
    debugBox.setMultiLine (true);
    addAndMakeVisible (debugBox);
    startTimer(500);
}
void AlgorithmSettingsBox::timerCallback()
{
    debugBox.setText(processor.getDebugText());
}

void AlgorithmSettingsBox::log(juce::String dbgText, bool shouldAppendNewline)
{
    debugBox.moveCaretToEnd();
    debugBox.insertTextAtCaret(dbgText);
    if (!shouldAppendNewline)
        return;
    debugBox.insertTextAtCaret("\n");
}



void AlgorithmSettingsBox::changeListenerCallback(juce::ChangeBroadcaster *source)
{
    syncTextWithCurrentAlgorithm();
}

void AlgorithmSettingsBox::syncTextWithCurrentAlgorithm()
{
//    juce::String newAlgorithmName = AppData::getInstance().getSelectedGeneratorName();
//    setText (newAlgorithmName + " settings");
}

void AlgorithmSettingsBox::resized()
{
    debugBox.setBounds (getLocalBounds());
}
