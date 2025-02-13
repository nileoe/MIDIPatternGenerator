#include "PluginEditor.h"
// #include "PluginProcessor.h"


//==============================================================================
ArpAlgoAudioProcessorEditor::ArpAlgoAudioProcessorEditor (ArpAlgoAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    startTimer(300);
    setSize (1200, 600);
//    DebugWindow& debugWindow = AppData::getInstance().getDebugWindow();
    // debugWindow.setVisible (true); // TODO something
    
    generationMethodsBox.addChangeListener(&algorithmSettingsBox);
    pianoKeyboard.addChangeListener(&selectedRangeBox);
    patternWritingButton.onClick = [this] { handleStartPatternRecordingPress(); };
}

ArpAlgoAudioProcessorEditor::~ArpAlgoAudioProcessorEditor()
{
    pianoKeyboard .removeAllChangeListeners();
    PatternSettings::getInstance().getNoteSet().removeAllChangeListeners();
//    audioProcessor.patternNoteSet.removeAllChangeListeners(); TODO remove
}

//void ArpAlgoAudioProcessorEditor::changeListenerCallback(juce::ChangeBroadcaster *source)
void ArpAlgoAudioProcessorEditor::timerCallback()
{
    if (audioProcessor.getPatternWritingMode()) // processor recording mode is ON
    {
        // Turning ON OR doing nothing
        if (!patternRecordingModeIsOn)
        {
            patternRecordingModeIsOn = true;
            setRecordButtonState(true);
            DBG ("new state: mode is ON!");
        }
    }
    else // processor recording mode is OFF
    {
        // Turning OFF, OR doing nothing
        if (patternRecordingModeIsOn)
        {
            patternRecordingModeIsOn = false;
            setRecordButtonState(false);
            DBG ("new state: mode is OFF!");
        }
    }
}

void ArpAlgoAudioProcessorEditor::paint (juce::Graphics& g)
{
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));
}

void ArpAlgoAudioProcessorEditor::setRecordButtonState(bool newState)
{
    if (newState)
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

void ArpAlgoAudioProcessorEditor::handleStartPatternRecordingPress()
{
    audioProcessor.togglePatternWritingMode();
    
    setRecordButtonState(patternRecordingModeIsOn);
    
//    if (audioProcessor.getPatternWritingMode())
//    {
//        patternWritingButton.setButtonText ("Recording pattern...");
//        patternWritingButton.setColour (juce::TextButton::buttonColourId, juce::Colours::orange);
//    }
//    else
//    {
//        patternWritingButton.setButtonText ("Start Pattern Recording");
//        juce::Colour defaultButtonBackgroundColour = juce::LookAndFeel::getDefaultLookAndFeel().findColour(juce::TextButton::buttonColourId);
//        patternWritingButton.setColour(juce::TextButton::buttonColourId, defaultButtonBackgroundColour);
//    }
}

void ArpAlgoAudioProcessorEditor::resized()
{
    juce::Rectangle<int> mainArea = getLocalBounds ();
    juce::Rectangle<int> leftArea = mainArea.removeFromLeft (390);
    
    addAndMakeVisible (generationMethodsBox);
    addAndMakeVisible (algorithmSettingsBox);
    addAndMakeVisible (patternLengthBox);
//    addAndMakeVisible (rhythmOverrideBox);
    
    addAndMakeVisible (pianoKeyboard);
    addAndMakeVisible (selectedRangeBox);
    addAndMakeVisible (scaleAndHarmonyBox);
    addAndMakeVisible (patternWritingButton);
    
    generationMethodsBox.setBounds (leftArea.removeFromTop (190).reduced (20));
    algorithmSettingsBox.setBounds (leftArea.removeFromTop (240).reduced (20));
    patternLengthBox    .setBounds (leftArea.reduced (20));
//    patternLengthBox    .setBounds (leftArea.removeFromTop (150).reduced (20));
//    rhythmOverrideBox   .setBounds (leftArea.reduced (20));
//    closeButton         .setBounds (leftArea.reduced(50, 30));
    
    pianoKeyboard       .setBounds (mainArea.removeFromTop (250).reduced (20));
    selectedRangeBox    .setBounds (mainArea.removeFromTop (70) .reduced (20, 5));
    scaleAndHarmonyBox  .setBounds (mainArea.removeFromTop (160).reduced (20, 10));
    patternWritingButton.setBounds (mainArea.reduced(50, 30));
    
    //        Tester::testNoteSetAndScale();
}
