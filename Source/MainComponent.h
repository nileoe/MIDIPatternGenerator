#pragma once

#include <JuceHeader.h>
#include "GenerationMethodsBox.h"
#include "PatternLengthBox.h"

class MainComponent  : public juce::Component
{
    public:
    //==============================================================================
    MainComponent()
    {
        setSize (1200, 600);
    }
    
    ~MainComponent() override
    {
    }
    
    //==============================================================================
    void paint (juce::Graphics& g) override
    {
        g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));
    }
    
    void resized() override
    {
        addAndMakeVisible (generationMethodsBox);
        addAndMakeVisible (patternLengthBox);
        
        juce::Rectangle<int> mainArea = getLocalBounds ();
        juce::Rectangle<int> leftArea = mainArea.removeFromLeft (390);
        
        generationMethodsBox.setBounds (leftArea.removeFromTop (190).reduced (20));
        patternLengthBox    .setBounds (leftArea.removeFromTop (150).reduced (20));
    }
    
    enum RadioButtonIds
    {
        GenerationMethodsRadioId = 101,
        PatternLengthRadioId
    };

    
    private:
    GenerationMethodsBox generationMethodsBox {GenerationMethodsRadioId, {"Algo 1", "Algo 2", "Algo 3", "Algo 4", "Algo 5"} };
    PatternLengthBox patternLengthBox { PatternLengthRadioId };

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainComponent)
};
