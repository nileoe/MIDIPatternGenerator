/*
  ==============================================================================

    PatternLengthBox.h
    Created: 20 Jan 2025 10:24:52am
    Author:  Lino Perdrix

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "RoundRadioButton.h"

class PatternLengthBox  : public juce::GroupComponent
{
    public:
    PatternLengthBox (int patternRadioGroupId)
    {
        notesLengthRange    = juce::Range<double>{5, 200};
        barsLengthRange     = juce::Range<double>{1, 20};
        secondsLengthRange  = juce::Range<double>{2, 30};
        
        setText ("Pattern Length");
        setColour (juce::GroupComponent::ColourIds::outlineColourId, juce::Colours::white);
        addAndMakeVisible(lengthSlider);
        lengthSlider.setSliderStyle (juce::Slider::LinearHorizontal);
        lengthSlider.setTextBoxStyle (juce::Slider::TextEntryBoxPosition::TextBoxRight,
                                     false,
                                     80,
                                     20);
        addAndMakeVisible (notesOption);
        addAndMakeVisible (barsOption);
        addAndMakeVisible (secondsOption);
        
        notesOption     .setRadioGroupId(patternRadioGroupId);
        barsOption      .setRadioGroupId(patternRadioGroupId);
        secondsOption   .setRadioGroupId(patternRadioGroupId);
        
        notesOption     .onClick = [this] { setSliderUnit (notesLengthRange,    " notes"); };
        barsOption      .onClick = [this] { setSliderUnit (barsLengthRange,     " bars" ); };
        secondsOption   .onClick = [this] { setSliderUnit (secondsLengthRange,  " secs" ); };
        
        notesOption
            .setToggleState (true, juce::NotificationType::sendNotification);
        lengthSlider.setValue (20);
    }

    ~PatternLengthBox() override
    {
    }
    
    void setSliderUnit (juce::Range<double> unitRange, juce::String suffix)
    {
        lengthSlider.setRange(unitRange, 1);
        lengthSlider.setTextValueSuffix(suffix);
        lengthSlider.setSkewFactorFromMidPoint (unitRange.getEnd() / 4);
    }
    
    void resized() override
    {
        juce::Rectangle<int> optionsArea = getLocalBounds().reduced (20);
        juce::Rectangle<int> sliderArea = optionsArea.removeFromTop (optionsArea.getHeight() / 2);
        lengthSlider.setBounds (sliderArea);
        
        juce::FlexBox optionsFb;
        optionsFb.justifyContent = juce::FlexBox::JustifyContent::spaceBetween;
        optionsFb.items.add (juce::FlexItem (notesOption)   .withMinWidth(100).withMinHeight (20));
        optionsFb.items.add (juce::FlexItem (barsOption)    .withMinWidth(100).withMinHeight (20));
        optionsFb.items.add (juce::FlexItem (secondsOption) .withMinWidth(100).withMinHeight (20));
        optionsFb.performLayout(optionsArea);
    }
    
//    void paint (juce::Graphics& g) override
//    {
//    }
    
    private:
    juce::Slider lengthSlider;
    RoundRadioButton    notesOption     { "Notes" },
//    juce::ToggleButton  notesOption     { "Notes" },
                        barsOption      { "Bars" },
                        secondsOption   { "Seconds" };
    juce::Range<double> notesLengthRange,
                        barsLengthRange,
                        secondsLengthRange;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PatternLengthBox)
};
