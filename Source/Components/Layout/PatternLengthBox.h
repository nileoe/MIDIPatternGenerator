/*
  ==============================================================================

    PatternLengthBox.h
    Created: 20 Jan 2025 10:24:52am
    Author:  Lino Perdrix

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "../UI/RoundRadioButton.h"
#include "../../Model/Data/PatternSettings.h"

class PatternLengthBox  : public juce::GroupComponent
{
    public:
    PatternLengthBox (int patternRadioGroupId);
    
    void resized() override;
    
    
    private:
    void handleUnitChange(juce::Range<double> unitRange, juce::String unitName);
    void handleLengthValueChange();
    bool isMaxLengthValueSelected() const;
    void setSliderUnit (juce::Range<double> unitRange, juce::String sliderSuffix);

    juce::Slider lengthSlider;
    RoundRadioButton    notesOption     { "Notes" },
                        barsOption      { "Bars" },
                        secondsOption   { "Seconds" };
    juce::Range<double> notesLengthRange,
                        barsLengthRange,
                        secondsLengthRange;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PatternLengthBox)
};
