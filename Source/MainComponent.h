#pragma once

#include <JuceHeader.h>
#include "GenerationMethodsBox.h"
#include "PatternLengthBox.h"
#include "RhythmOverrideBox.h"
#include "ClickableMidiKeyboard.h"
#include "SelectedRangeBox.h"
#include "ScaleAndHarmonyBox.h"
#include "AppData.h"
#include "Scale.h"
#include "Tester.h"

class MainComponent  : public juce::Component
{
    public:
    MainComponent()
    {
        setSize (1200, 600);
    }
    
    ~MainComponent() override
    {
    }
    
    void paint (juce::Graphics& g) override
    {
        g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));
    }
    
    void resized() override
    {
        juce::Rectangle<int> mainArea = getLocalBounds ();
        juce::Rectangle<int> leftArea = mainArea.removeFromLeft (390);
        
        addAndMakeVisible (generationMethodsBox);
        addAndMakeVisible (patternLengthBox);
        addAndMakeVisible (rhythmOverrideBox);
        addAndMakeVisible (closeButton);
        
        addAndMakeVisible (pianoKeyboard);
        addAndMakeVisible (selectedRangeBox);
        addAndMakeVisible (scaleAndHarmonyBox);
        addAndMakeVisible (generateButton);

        generationMethodsBox.setBounds (leftArea.removeFromTop (190).reduced (20));
        patternLengthBox    .setBounds (leftArea.removeFromTop (150).reduced (20));
        rhythmOverrideBox   .setBounds (leftArea.removeFromTop (150).reduced (20));
        closeButton         .setBounds (leftArea.reduced(50, 30));

        pianoKeyboard       .setBounds (mainArea.removeFromTop (250).reduced (20));
        selectedRangeBox    .setBounds (mainArea.removeFromTop (70) .reduced (20, 10));
        scaleAndHarmonyBox  .setBounds (mainArea.removeFromTop (160).reduced (20, 10));
        generateButton      .setBounds (mainArea.reduced(50, 30));
        
//        Tester::testNoteSetAndScale();
    }
    
    enum RadioButtonIds
    {
        GenerationMethodsRadioId = 101,
        PatternLengthRadioId,
        ScaleHarmonyRadioId,
    };

    
    private:
    GenerationMethodsBox    generationMethodsBox    { GenerationMethodsRadioId };
    PatternLengthBox        patternLengthBox        { PatternLengthRadioId };
    RhythmOverrideBox       rhythmOverrideBox;
    
    juce::MidiKeyboardState keyboardState;
    ClickableMidiKeyboard   pianoKeyboard           { keyboardState, 24, 83 };
    SelectedRangeBox        selectedRangeBox        { keyboardState };
    ScaleAndHarmonyBox      scaleAndHarmonyBox      { ScaleHarmonyRadioId };
    
    juce::TextButton        closeButton             { "Close" },
                            generateButton          { "Generate Pattern" };

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainComponent)
};
