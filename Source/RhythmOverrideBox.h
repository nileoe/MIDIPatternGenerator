/*
  ==============================================================================

    RhythmOverrideBox.h
    Created: 20 Jan 2025 1:23:38pm
    Author:  Lino Perdrix

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
*/
class RhythmOverrideBox  : public juce::GroupComponent
{
public:
    RhythmOverrideBox();
    
    void resized() override;
    
private:
    juce::ToggleButton  customisePatternButton  { "Customise rhythmic patterns to use" };
    juce::TextButton    editRhythmsButton       { "Edit" };
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (RhythmOverrideBox)
};
