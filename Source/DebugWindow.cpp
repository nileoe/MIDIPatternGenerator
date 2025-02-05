/*
  ==============================================================================

    DebugEditor.cpp
    Created: 1 Feb 2025 4:40:13pm
    Author:  Lino Perdrix

  ==============================================================================
*/

#include <JuceHeader.h>
#include "DebugWindow.h"

DebugWindow::DebugWindow(juce::String name,
                         juce::Colour bgColour,
                         int windowButtons,
                         bool addToDesktop) : juce::DocumentWindow(name,
                                                                   bgColour,
                                                                   windowButtons,
                                                                   addToDesktop)
{
    setSize (400, 1200);
    debugBox.setMultiLine(true);
    // addAndMakeVisible (&debugBox); // NO
    setContentOwned(&debugBox, false);
}

void DebugWindow::log(juce::String dbgText, bool shouldAppendNewline)
{
    debugBox.moveCaretToEnd();
    debugBox.insertTextAtCaret(dbgText);
    if (!shouldAppendNewline)
        return;
    debugBox.insertTextAtCaret("\n");
}

void DebugWindow::paint (juce::Graphics& g)
{
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));   // clear the background

    g.setColour (juce::Colours::grey);
    g.drawRect (getLocalBounds(), 1);   // draw an outline around the component

}

void DebugWindow::resized()
{
    debugBox.setBounds (getLocalBounds());
}
