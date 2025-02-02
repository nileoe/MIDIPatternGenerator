#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "GenerationMethodsBox.h"
#include "PatternLengthBox.h"
#include "RhythmOverrideBox.h"
#include "NoteSetKeyboard.h"
#include "SelectedRangeBox.h"
#include "ScaleAndHarmonyBox.h"
#include "AppData.h"
#include "Scale.h"
#include "Tester.h"
#include "DebugWindow.h"

class ArpAlgoAudioProcessorEditor  : public juce::AudioProcessorEditor
{
public:
    ArpAlgoAudioProcessorEditor (ArpAlgoAudioProcessor&);
    ~ArpAlgoAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;
    
    enum RadioButtonIds // TODO private?
    {
        GenerationMethodsRadioId = 101,
        PatternLengthRadioId,
        ScaleHarmonyRadioId,
    };

private:
    ArpAlgoAudioProcessor& audioProcessor;
    
    juce::MidiKeyboardState keyboardState;
    NoteSetKeyboard   pianoKeyboard { keyboardState, 36, 95, audioProcessor.patternNoteSet, settingLowestNoteMode, settingHighestNoteMode };
    
    bool settingLowestNoteMode  = false;
    bool settingHighestNoteMode = false;

    GenerationMethodsBox    generationMethodsBox    { GenerationMethodsRadioId };
    PatternLengthBox        patternLengthBox        { PatternLengthRadioId };
    RhythmOverrideBox       rhythmOverrideBox;
    ScaleAndHarmonyBox      scaleAndHarmonyBox      { ScaleHarmonyRadioId, audioProcessor.patternNoteSet };
    SelectedRangeBox        selectedRangeBox        { pianoKeyboard, audioProcessor.patternNoteSet, settingLowestNoteMode, settingHighestNoteMode };

    juce::TextButton closeButton    { "Close" };
    juce::TextButton generateButton { "Generate Pattern" };

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ArpAlgoAudioProcessorEditor)
};
