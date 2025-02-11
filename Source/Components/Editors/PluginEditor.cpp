#include "PluginEditor.h"
// #include "PluginProcessor.h"


//==============================================================================
ArpAlgoAudioProcessorEditor::ArpAlgoAudioProcessorEditor (ArpAlgoAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    setSize (1200, 600);
//    DebugWindow& debugWindow = AppData::getInstance().getDebugWindow();
    // debugWindow.setVisible (true); // TODO something
    pianoKeyboard.addChangeListener(&selectedRangeBox);
//    p.patternNoteSet.addChangeListener(&pianoKeyboard); // TODO Remove
    patternWritingButton.onClick = [this] { handleStartPatternRecordingPress(); };
}

ArpAlgoAudioProcessorEditor::~ArpAlgoAudioProcessorEditor()
{
    pianoKeyboard .removeAllChangeListeners();
    PatternSettings::getInstance().getNoteSet().removeAllChangeListeners();
//    audioProcessor.patternNoteSet.removeAllChangeListeners(); TODO remove
}

//==============================================================================
void ArpAlgoAudioProcessorEditor::paint (juce::Graphics& g)
{
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));
}

void ArpAlgoAudioProcessorEditor::handleStartPatternRecordingPress()
{
    audioProcessor.togglePatternWritingMode();
    if (audioProcessor.getPatternWritingMode())
    {
        patternWritingButton.setButtonText ("Recording pattern...");
        patternWritingButton.setColour (juce::TextButton::buttonColourId, juce::Colours::orange);
    }
    else
    {
        patternWritingButton.setButtonText ("Start Pattern Recording");
        juce::Colour defaultButtonBackgroundColour = juce::LookAndFeel::getDefaultLookAndFeel().findColour(juce::TextButton::buttonColourId);
        patternWritingButton.setColour(juce::TextButton::buttonColourId, defaultButtonBackgroundColour);
    }
}

void ArpAlgoAudioProcessorEditor::resized()
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
        addAndMakeVisible (patternWritingButton);

        generationMethodsBox.setBounds (leftArea.removeFromTop (190).reduced (20));
        patternLengthBox    .setBounds (leftArea.removeFromTop (150).reduced (20));
        rhythmOverrideBox   .setBounds (leftArea.removeFromTop (150).reduced (20));
        closeButton         .setBounds (leftArea.reduced(50, 30));

        pianoKeyboard       .setBounds (mainArea.removeFromTop (250).reduced (20));
        selectedRangeBox    .setBounds (mainArea.removeFromTop (70) .reduced (20, 5));
        scaleAndHarmonyBox  .setBounds (mainArea.removeFromTop (160).reduced (20, 10));
        patternWritingButton.setBounds (mainArea.reduced(50, 30));
        
//        Tester::testNoteSetAndScale();
}
