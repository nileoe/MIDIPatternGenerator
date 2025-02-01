/*
  ==============================================================================

    DebugEditor.h
    Created: 1 Feb 2025 4:40:13pm
    Author:  Lino Perdrix

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

class DebugWindow  : public juce::DocumentWindow
{
public:
    DebugWindow(juce::String name = "Debug",
                juce::Colour bgColour = juce::Colours::darkgrey,
                int windowButtons = juce::DocumentWindow::TitleBarButtons::allButtons,
                bool addToDesktop = true
                );

    void paint (juce::Graphics&) override;
    void resized() override;
    void log(juce::String);

private:
    juce::TextEditor debugBox;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (DebugWindow)
};
