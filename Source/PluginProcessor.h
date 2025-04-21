#pragma once

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
    
    //==============================================================================
    juce::String getDebugText() const { return debugText; }
    double getHostBpmOrDefault() const;
    const std::optional<double> getHostBpm() const;

private:
    int time;
    int rate;
    int patternNoteIndex;
    juce::SortedSet<int> pressedKeys;
    int currentNote;
    int lastNoteValue;
    juce::String debugText;
    int patternBaseNote;
    int lastPressedKey;
    juce::Array<int> pattern;
    
    void captureHeldKeys(juce::MidiBuffer& midiMessages);
    int  getOffsetForCurrentBlock(int noteDuration, int numSamples, int time) const;
    bool differentNewKeyIsPressed (int midiBufferSize) const;
    bool shouldOutputNotes() const;
    bool shouldSendCleanupNoteOffMessage() const;
    bool patternIsExhausted() const;
    bool noteSetIsEmpty() const;
    bool noteIsRepeated() const;
    bool shouldMergeRepeatedNotes() const;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ArpAlgoAudioProcessor)
};
