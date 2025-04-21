#include "PluginEditor.h"


//==============================================================================
ArpAlgoAudioProcessorEditor::ArpAlgoAudioProcessorEditor (ArpAlgoAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    setSize (1200, 500);
    pianoKeyboard.addChangeListener(&selectedRangeBox);
}

ArpAlgoAudioProcessorEditor::~ArpAlgoAudioProcessorEditor()
{
    pianoKeyboard .removeAllChangeListeners();
    PatternSettings::getInstance().getNoteSet().removeAllChangeListeners();
}

void ArpAlgoAudioProcessorEditor::paint (juce::Graphics& g)
{
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));
}

void ArpAlgoAudioProcessorEditor::resized()
{
    juce::Rectangle<int> mainArea = getLocalBounds ();
    juce::Rectangle<int> leftArea = mainArea.removeFromLeft (390);
    
    addAndMakeVisible (generationMethodsBox);
    addAndMakeVisible (noteQuantizationBox);
    addAndMakeVisible (patternLengthBox);
    
    addAndMakeVisible (pianoKeyboard);
    addAndMakeVisible (selectedRangeBox);
    addAndMakeVisible (scaleAndHarmonyBox);
    
    generationMethodsBox.setBounds (leftArea.removeFromTop (190).reduced (20, 10));
    noteQuantizationBox .setBounds (leftArea.removeFromTop (180).reduced (20, 10));
    patternLengthBox    .setBounds (leftArea.reduced (20, 10));
    
    pianoKeyboard       .setBounds (mainArea.removeFromTop (250).reduced (20));
    selectedRangeBox    .setBounds (mainArea.removeFromTop (125) .reduced (20, 5));
    scaleAndHarmonyBox  .setBounds (mainArea.reduced (20, 10));
}
