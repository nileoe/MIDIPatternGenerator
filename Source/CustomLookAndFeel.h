/*
  ==============================================================================

    CustomLookAndFeel.h
    Created: 22 Jan 2025 12:16:59pm
    Author:  Lino Perdrix

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
*/
class CustomLookAndFeel  : public juce::LookAndFeel_V4
{
public:
    CustomLookAndFeel()
    {
        corner
    }

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (CustomLookAndFeel)
};
