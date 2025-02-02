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
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    ArpAlgoAudioProcessor& audioProcessor;
    
    GenerationMethodsBox    generationMethodsBox    { GenerationMethodsRadioId };
    PatternLengthBox        patternLengthBox        { PatternLengthRadioId };
    RhythmOverrideBox       rhythmOverrideBox;
    ScaleAndHarmonyBox      scaleAndHarmonyBox      { ScaleHarmonyRadioId };
    SelectedRangeBox        selectedRangeBox        { pianoKeyboard, audioProcessor.patternNoteSet };
    
    juce::TextButton closeButton    { "Close" };
    juce::TextButton generateButton { "Generate Pattern" };

    juce::MidiKeyboardState keyboardState;
    NoteSetKeyboard   pianoKeyboard { keyboardState, 24, 83, audioProcessor.patternNoteSet };
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ArpAlgoAudioProcessorEditor)
};
