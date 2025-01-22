/*
  ==============================================================================

    ScaleAndHarmonyBox.h
    Created: 22 Jan 2025 10:40:42am
    Author:  Lino Perdrix

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "RoundRadioButton.h"

//==============================================================================
/*
*/
class ScaleAndHarmonyBox  : public juce::GroupComponent
{
public:
    ScaleAndHarmonyBox(int scaleHarmonyRadioId)
    {
        setText ("Scale and Harmony");
        setColour (juce::GroupComponent::ColourIds::outlineColourId, juce::Colours::white);
        
        addAndMakeVisible(useHarmonyRadioButton);
        addAndMakeVisible(useScaleRadioButton);
        
        addAndMakeVisible(strictModeTickbox);
        
        addAndMakeVisible(useCustomScaleTickbox);
        addAndMakeVisible(scaleRootMenu);
        addAndMakeVisible(scaleNameMenu);
        addAndMakeVisible(customScaleButton);
        
        useHarmonyRadioButton   .setName("useHarmony");
        useScaleRadioButton     .setName("useScale");

        useHarmonyRadioButton   .setRadioGroupId(scaleHarmonyRadioId);
        useScaleRadioButton     .setRadioGroupId(scaleHarmonyRadioId);
        
        useHarmonyRadioButton   .setToggleState (true, juce::NotificationType::sendNotification);
    }

    void resized() override
    {
        using FI = juce::FlexItem;
        juce::Rectangle<int> scaleArea = getLocalBounds().reduced (20);
        juce::Rectangle<int> harmonyArea = scaleArea.removeFromTop (scaleArea.getHeight() / 2);
    
        juce::FlexBox harmonyFb;
        harmonyFb.justifyContent = juce::FlexBox::JustifyContent::spaceBetween;
        harmonyFb.items.add (FI(useHarmonyRadioButton)  .withMinWidth (500.0f).withMinHeight (20.0f));
        harmonyFb.items .add (FI(strictModeTickbox)     .withMinWidth (200.0f).withMinHeight (20.0f));
        harmonyFb.performLayout(harmonyArea);
        
        juce::FlexBox scaleFb;
        scaleFb.justifyContent = juce::FlexBox::JustifyContent::spaceBetween;
        scaleFb.alignItems = juce::FlexBox::AlignItems::center;
        scaleFb.items.add (FI(useScaleRadioButton)      .withMinWidth (130.0f).withMinHeight (30.0f));
        scaleFb.items.add (FI(scaleRootMenu)            .withMinWidth (70.0f) .withMinHeight (30.0f).withMargin (FI::Margin(0, 10, 0, 0)));
        scaleFb.items.add (FI(scaleNameMenu)            .withMinWidth (250.0f).withMinHeight (30.0f));
        
        juce:: FlexBox customScaleFb;
        customScaleFb.justifyContent = juce::FlexBox::JustifyContent::flexEnd;
        customScaleFb.alignItems = juce::FlexBox::AlignItems::center;
        customScaleFb.items.add (FI(useCustomScaleTickbox)    .withMinWidth (30.0f) .withMinHeight (30.0f));
        customScaleFb.items.add (FI(customScaleButton)        .withMinWidth (150.0f).withMinHeight (30.0f));
        
        scaleFb.items.add (FI(customScaleFb).withFlex(1.0f)   .withMinWidth (200.0f));
        scaleFb.performLayout (scaleArea);
    }

private:
    RoundRadioButton    useHarmonyRadioButton       { "Use existing harmony to set available pitches" },
                        useScaleRadioButton         { "Choose scale" };
    
    juce::ToggleButton  strictModeTickbox           { "Strict mode" };
    
    juce::ToggleButton  useCustomScaleTickbox;
    juce::ComboBox      scaleRootMenu,
                        scaleNameMenu;
    juce::TextButton    customScaleButton           { "Use custom scale" };
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ScaleAndHarmonyBox)
};
