/*
  ==============================================================================

    DebugEditor.h
    Created: 1 Feb 2025 4:40:13pm
    Author:  Lino Perdrix

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
*/
class DebugEditor  : public juce::Component
{
public:
    DebugEditor();
    ~DebugEditor() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (DebugEditor)
};
