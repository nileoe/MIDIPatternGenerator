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
    RhythmOverrideBox()
    {
        setText ("Rhythm Override");
        setColour (juce::GroupComponent::ColourIds::outlineColourId, juce::Colours::white);
        
        addAndMakeVisible (customisePatternButton);
        addAndMakeVisible (editRhythmsButton);
        customisePatternButton .onClick = [this] { editRhythmsButton.setEnabled (customisePatternButton.getToggleState()); };
        editRhythmsButton.setEnabled (false);
    }

    ~RhythmOverrideBox() override
    {
    }

//    void paint (juce::Graphics& g) override
//    {
//    }

    void resized() override
    {
        juce::Rectangle<int> area = getLocalBounds().reduced (20);
        juce::FlexBox fb;
        fb.justifyContent = juce::FlexBox::JustifyContent::spaceBetween;
        fb.alignItems = juce::FlexBox::AlignItems::center;
        fb.items.add (juce::FlexItem (customisePatternButton).withMinWidth (250).withMinHeight (30));
        fb.items.add (juce::FlexItem (editRhythmsButton)     .withMinWidth (50) .withMinHeight (30));
        fb.performLayout (area);
    }

private:
    juce::ToggleButton  customisePatternButton  { "Customise rhythmic patterns to use" };
    juce::TextButton    editRhythmsButton       { "Edit" };
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (RhythmOverrideBox)
};
