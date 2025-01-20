#pragma once

#include <JuceHeader.h>
#include "GenerationMethodsBox.h"

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
        addAndMakeVisible(generationMethodsBox);
        generationMethodsBox.setBounds (20, 20, 350, 150);
    }
    
    enum RadioButtonIds
    {
        GenerationMethodsRadioId = 101
    };

    
    private:
    GenerationMethodsBox generationMethodsBox {GenerationMethodsRadioId, {"Algo 1", "Algo 2", "Algo 3", "Algo 4", "Algo 5"} };

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainComponent)
};
