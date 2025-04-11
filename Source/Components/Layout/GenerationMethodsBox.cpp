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

void GenerationMethodsBox::resized()
{
    juce::Rectangle bounds = getLocalBounds().reduced(20);
    algorithmLabel.setBounds(bounds.removeFromTop(bounds.getHeight() / 2));
    algorithmMenu.setBounds(bounds.reduced(0, 15));
//    juce::Rectangle<int> algoDropdownArea = getLocalBounds().reduced (20);
//    juce::Rectangle<int> labelArea = algoDropdownArea.removeFromTop(algoDropdownArea.getHeight() / 2); // todo try smaller value
//    juce::FlexBox algoOptionFb;
//    algoOptionFb.justifyContent = juce::FlexBox::JustifyContent::spaceBetween;
//    algoOptionFb.alignItems = juce::FlexBox::AlignItems::center;
////    algoOptionFb.items.add (juce::FlexItem (algorithmButton).withMinWidth (210.0f).withMinHeight (20.0f));
//    algoOptionFb.items.add (juce::FlexItem (algorithmMenu)  .withMinWidth (100.0f).withMinHeight (30.0f));
//    algoOptionFb.performLayout(algoDropdownArea);
//    
//    juce::FlexBox melodyOptionFb;
//    melodyOptionFb.justifyContent = juce::FlexBox::JustifyContent::spaceBetween;
//    melodyOptionFb.alignItems = juce::FlexBox::AlignItems::center;
////    melodyOptionFb.items.add (juce::FlexItem (melodyButton)        .withMinWidth (210.0f).withMinHeight (20.0f));
////    melodyOptionFb.items.add (juce::FlexItem (selectMelodyButton)  .withMinWidth (100.0f).withMinHeight (30.0f));
}
