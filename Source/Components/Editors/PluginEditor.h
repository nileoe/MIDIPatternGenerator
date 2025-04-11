#pragma once

#include "../../PluginProcessor.h"
#include "../Layout/GenerationMethodsBox.h"
#include "../Layout/PatternLengthBox.h"
#include "../Layout/RhythmOverrideBox.h"
#include "../Layout/SelectedRangeBox.h"
#include "../Layout/ScaleAndHarmonyBox.h"
#include "../Layout/NoteSpeedBox.h"
#include "../MIDI/NoteSetKeyboard.h"
#include "../../Model/Data/AppData.h"
#include "../../Model/Notes/Scale.h"
#include "../../Model/Data/PatternSettings.h"
#include <JuceHeader.h>

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
    
    void handleStartPatternRecordingPress();
    void setRecordButtonState (bool newState);

    juce::MidiKeyboardState keyboardState;
    NoteSetKeyboard   pianoKeyboard { keyboardState, 36, 95, settingLowestNoteMode, settingHighestNoteMode };
    
    bool settingLowestNoteMode  = false;
    bool settingHighestNoteMode = false;
    bool patternRecordingModeIsOn = false;

    GenerationMethodsBox    generationMethodsBox    { GenerationMethodsRadioId, audioProcessor };
    PatternLengthBox        patternLengthBox        { PatternLengthRadioId };
    RhythmOverrideBox       rhythmOverrideBox;
    ScaleAndHarmonyBox      scaleAndHarmonyBox      { ScaleHarmonyRadioId };
    SelectedRangeBox        selectedRangeBox        { pianoKeyboard, settingLowestNoteMode, settingHighestNoteMode };
    NoteSpeedBox    algorithmSettingsBox    { audioProcessor };

//    juce::TextButton patternWritingButton           { "Start Pattern Recording" };

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ArpAlgoAudioProcessorEditor)
};
