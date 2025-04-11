/*
 ==============================================================================
 
 GenerationMethodsBox.cpp
 Created: 20 Jan 2025 9:58:15am
 Author:  Lino Perdrix
 
 ==============================================================================
 */

#include "GenerationMethodsBox.h"

GenerationMethodsBox::GenerationMethodsBox (int radioGroupId, ArpAlgoAudioProcessor& processor) : audioProcessor(processor)
{
    setText ("Generation Method");
    setColour (juce::GroupComponent::ColourIds::outlineColourId, juce::Colours::white);
    
    addAndMakeVisible (algorithmMenu);
    addAndMakeVisible (algorithmLabel);
    addAndMakeVisible (allowOffKeyNotesButton);
    
    allowOffKeyNotesButton.setButtonText ("Allow off-key notes");
    allowOffKeyNotesButton.setTooltip("When enabled, the pattern will include all input notes, even those that are outside of the selected scale and range.");
    allowOffKeyNotesButton.onClick = [this] { handleOffKeyButtonChange(); };
    
    auto& data = AppData::getInstance();
    const juce::Array<GenerationAlgorithm*>& algorithms = data.getGenerationAlgorithms();
    for (auto* algo : algorithms)
    {
        algorithmMenu.addItem(algo->getName(), algo->getId());
    }
    
    algorithmMenu.setSelectedId(algorithms.getFirst()->getId());
    algorithmMenu.onChange = [this] { handleAlgorithmChange(); };
}

void GenerationMethodsBox::handleOffKeyButtonChange()
{
    bool newState = allowOffKeyNotesButton.getToggleState();
    PatternSettings::getInstance().setAllowOffKeyInput(newState);
}

void GenerationMethodsBox::handleAlgorithmChange()
{
    auto& data = AppData::getInstance();
    int newAlgoId = algorithmMenu.getSelectedId();
    data.setSelectedAlgorithmId(newAlgoId);
    sendChangeMessage();
    auto description = data.getSelectedGenerator()->getDescription();
    algorithmMenu.setTooltip(description);
}

void GenerationMethodsBox::resized()
{
    juce::Rectangle bottomRowArea = getLocalBounds().reduced(20);
    juce::Rectangle topRowArea = bottomRowArea.removeFromTop(bottomRowArea.getHeight() / 2);

    algorithmLabel.setBounds(topRowArea.removeFromLeft(topRowArea.getWidth() / 2));
    allowOffKeyNotesButton.setBounds(topRowArea);
    
    algorithmMenu.setBounds(bottomRowArea.reduced(0, 15));
}
