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
    void setIsNewAlgorithmUsed(bool newIsUsed); // no getter (no point)

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
    void updateHeldNotes(juce::MidiBuffer& midiMessages, int& bufferLastPressedKey);
    bool isNewAlgorithmUsed;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ArpAlgoAudioProcessor)
};
