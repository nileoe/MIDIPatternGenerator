#pragma once

//#include "AppData.h"
#include "NoteSet.h"
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
    
    // public attributes relevant to the plugin's or generated pattern choices state
    NoteSet patternNoteSet;

private:
    //==============================================================================
    juce::SortedSet<int> heldNotes;
    int currentNote;
    int lastNoteValue;
    int time;
    int rate;

    
    // TODO REMOVE (should be in algorithm when implemented)
    juce::Array<int> getActualNotes()
    {
        jassert(!heldNotes.isEmpty());
        const int lowestHeldNote = heldNotes.getFirst();
        juce::Array<int> actualNotes;
        
        for (const int note : patternNoteSet.getNotesIndices())
        {
            if (note >= lowestHeldNote)
            {
                actualNotes.add(note);
            }
        }
        return actualNotes;
    }

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ArpAlgoAudioProcessor)
};
