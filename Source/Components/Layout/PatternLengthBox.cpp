/*
 ==============================================================================
 
 PatternLengthBox.h
 Created: 20 Jan 2025 10:24:52am
 Author:  Lino Perdrix
 
 ==============================================================================
 */

#include "PatternLengthBox.h"

PatternLengthBox::PatternLengthBox (int patternRadioGroupId)
{
    notesLengthRange    = juce::Range<double>{5, 200};
    barsLengthRange     = juce::Range<double>{1, 20};
    secondsLengthRange  = juce::Range<double>{2, 30};
    
    setText ("Pattern Maximum Length");
    setColour (juce::GroupComponent::ColourIds::outlineColourId, juce::Colours::white);
    addAndMakeVisible(lengthSlider);
    lengthSlider.setSliderStyle (juce::Slider::LinearHorizontal);
    lengthSlider.setTextBoxStyle (juce::Slider::TextEntryBoxPosition::TextBoxRight,
                                  false,
                                  80,
                                  20);
    lengthSlider.setTooltip("Maximum pattern length in your chosen unit. Set the slider to the maximum value to allow for a pattern of infinite length.");
    addAndMakeVisible (notesOption);
    addAndMakeVisible (barsOption);
    addAndMakeVisible (secondsOption);
    
    notesOption     .setRadioGroupId(patternRadioGroupId);
    barsOption      .setRadioGroupId(patternRadioGroupId);
    secondsOption   .setRadioGroupId(patternRadioGroupId);
    
    notesOption     .onClick = [this] { handleUnitChange (notesLengthRange,    "notes"); };
    barsOption      .onClick = [this] { handleUnitChange (barsLengthRange,     "bars" ); };
    secondsOption   .onClick = [this] { handleUnitChange (secondsLengthRange,  "secs" ); };
    
    notesOption
        .setToggleState (true, juce::NotificationType::sendNotification);
    
    lengthSlider.onValueChange = [this] { handleLengthValueChange(); };
    
    lengthSlider.setValue (20);
}

void PatternLengthBox::handleLengthValueChange()
{
    auto& patternSettings = PatternSettings::getInstance();
    patternSettings.setLength(lengthSlider.getValue());
    if (isMaxLengthValueSelected())
    {
        patternSettings.setInfinitePattern(true);
        lengthSlider
            .setColour(juce::Slider::ColourIds::textBoxTextColourId,
                       juce::Colours::lightgrey);
        lengthSlider
            .setColour(juce::Slider::ColourIds::textBoxBackgroundColourId,
                       juce::Colours::grey);
    }
    else
    {
        patternSettings.setInfinitePattern(false);
        lengthSlider
            .setColour(juce::Slider::ColourIds::textBoxTextColourId,
                       getLookAndFeel()
                       .findColour (juce::Slider::textBoxTextColourId));
        lengthSlider
            .setColour(juce::Slider::ColourIds::textBoxBackgroundColourId,
                       getLookAndFeel()
                       .findColour (juce::Slider::textBoxBackgroundColourId));
        
    }
}

void PatternLengthBox::handleUnitChange(juce::Range<double> unitRange, juce::String unitName)
{
    setSliderUnit(unitRange, " " + unitName);
    PatternSettings::getInstance().setLengthUnit(unitName);
    // In case the value for the previous unit exceeds the range of the new unit, update the
    // length with the updated range
    handleLengthValueChange();
}

void PatternLengthBox::setSliderUnit (juce::Range<double> unitRange, juce::String sliderSuffix)
{
    lengthSlider.setRange(unitRange, 1);
    lengthSlider.setTextValueSuffix(sliderSuffix);
    lengthSlider.setSkewFactorFromMidPoint (unitRange.getEnd() / 4);
}
bool PatternLengthBox::isMaxLengthValueSelected() const
{
    DBG ("IS max value selected? end value is " << lengthSlider.getRange().getEnd() << ", actual value is " << lengthSlider.getValue());
    return lengthSlider.getRange().getEnd() == lengthSlider.getValue();
}

void PatternLengthBox::resized()
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
