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
    
    addAndMakeVisible (algorithmButton);
    addAndMakeVisible (algorithmMenu);
    addAndMakeVisible (melodyButton);
    addAndMakeVisible (selectMelodyButton);
    
    algorithmButton .setRadioGroupId(radioGroupId);
    melodyButton    .setRadioGroupId(radioGroupId);
    
    algorithmButton.setName ("algo");
    melodyButton   .setName ("melody");
    selectMelodyButton.setEnabled (false);
    algorithmButton
        .setToggleState (true, juce::NotificationType::dontSendNotification);
    
    algorithmButton .onClick = [this] { algorithmMenu     .setEnabled (algorithmButton.getState()); };
    melodyButton    .onClick = [this] { selectMelodyButton.setEnabled (melodyButton   .getState()); };
    
    auto& data = AppData::getInstance();
    const juce::Array<GenerationAlgorithm*>& algorithms = data.getGenerationAlgorithms();
    for (auto* algo : algorithms)
    {
        algorithmMenu.addItem(algo->getName(), algo->getId());
    }
    
    algorithmMenu.setSelectedId(algorithms.getFirst()->getId());
    
    algorithmMenu.onChange = [this] { handleAlgorithmChange(); };
}

void GenerationMethodsBox::handleAlgorithmChange()
{
    int newAlgoId = algorithmMenu.getSelectedId();
    DBG ("Generation box: setting new algorithm selected id to " << newAlgoId << ", processor newAlgorithmWasChosen to TRUE.");
    AppData::getInstance().setSelectedAlgorithmId(newAlgoId);
    sendChangeMessage();
}

void GenerationMethodsBox::updateToggleState (juce::ToggleButton* button)
{
    // TODO unused
    bool state = button->getToggleState();
    auto stateString = state ? "on" : "off";
    std::cout << button->getName() << " is " << stateString << std::endl;
}

void GenerationMethodsBox::resized()
{
    juce::Rectangle<int> optionsArea = getLocalBounds().reduced (20);
    juce::Rectangle<int> algoOptionArea = optionsArea.removeFromTop(optionsArea.getHeight() / 2);
    juce::FlexBox algoOptionFb;
    algoOptionFb.justifyContent = juce::FlexBox::JustifyContent::spaceBetween;
    algoOptionFb.alignItems = juce::FlexBox::AlignItems::center;
    algoOptionFb.items.add (juce::FlexItem (algorithmButton).withMinWidth (210.0f).withMinHeight (20.0f));
    algoOptionFb.items.add (juce::FlexItem (algorithmMenu)  .withMinWidth (100.0f).withMinHeight (30.0f));
    algoOptionFb.performLayout(algoOptionArea);
    
    juce::FlexBox melodyOptionFb;
    melodyOptionFb.justifyContent = juce::FlexBox::JustifyContent::spaceBetween;
    melodyOptionFb.alignItems = juce::FlexBox::AlignItems::center;
    melodyOptionFb.items.add (juce::FlexItem (melodyButton)        .withMinWidth (210.0f).withMinHeight (20.0f));
    melodyOptionFb.items.add (juce::FlexItem (selectMelodyButton)  .withMinWidth (100.0f).withMinHeight (30.0f));
}
