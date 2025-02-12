#pragma once

#include "./Testing/Tester.h"
#include "./Model/Data/AppData.h"
#include "./Model/Notes/NoteSet.h"
#include <JuceHeader.h>

class ArpAlgoAudioProcessor  : public juce::AudioProcessor
{
public:
    //==============================================================================
    ArpAlgoAudioProcessor();
    ~ArpAlgoAudioProcessor() override;

    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

   #ifndef JucePlugin_PreferredChannelConfigurations
    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;
   #endif

    void processBlock (juce::AudioBuffer<float>&, juce::MidiBuffer&) override;

    //==============================================================================
    juce::AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    //==============================================================================
    const juce::String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect() const override;
    double getTailLengthSeconds() const override;

    //==============================================================================
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const juce::String getProgramName (int index) override;
    void changeProgramName (int index, const juce::String& newName) override;

    //==============================================================================
    void getStateInformation (juce::MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;
    
    // NEW
    void togglePatternWritingMode();
    bool getPatternWritingMode() const;

private:
    int time;
    int rate;
    
    int patternNoteIndex;
    juce::SortedSet<int> heldNotes;
    int currentNote;
    int lastNoteValue;
    
    // NEW
    int lastPressedKey;
    juce::Array<int> pattern;
    bool isWritingPatternModeOn;
//    bool reachedPatternEnd(); // { currentNote >= pattern.size() };
    bool differentNewKeyIsPressed (int bufferLastPressedKey, int midiBufferSize) const;
    bool shouldPatternBeOutputed() const;
    bool shouldSendCleanupNoteOffMessage() const;
    bool patternIsExhausted() const;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ArpAlgoAudioProcessor)
};

/*
 Using getLengthInNotes() to get the target number of notes from the pattern.
 - The last pressed MIDI input key is recorded. Should be displayed on the on-screen keyboard.
 - Pressing a new key DOES restart the pattern, leading to a "new" length-sized pattern to be outputted.
 - Releasing a key stops the output. The user must keep the key pressed to output. However, to generate the output pressing generate just uses the last recorded key press.
*/
