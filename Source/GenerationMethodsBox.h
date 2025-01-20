/*
  ==============================================================================

    GenerationMethodsBox.h
    Created: 20 Jan 2025 9:58:15am
    Author:  Lino Perdrix

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

class GenerationMethodsBox  : public juce::GroupComponent
{
    public:
    GenerationMethodsBox (int radioGroupId, juce::StringArray algorithmChoices)
    {
        setText ("Generation Method");
        setColour (juce::GroupComponent::ColourIds::outlineColourId, juce::Colours::white);
        
        addAndMakeVisible (algorithmButton);
        addAndMakeVisible (algorithmMenu);
        addAndMakeVisible (melodyButton);
        addAndMakeVisible (selectMelodyButton);
        
        algorithmButton .setRadioGroupId(radioGroupId);
        melodyButton    .setRadioGroupId(radioGroupId);
        
        algorithmButton.setName ("algo");
        melodyButton   .setName ("melody");
        selectMelodyButton.setEnabled (false);
        algorithmButton
            .setToggleState (true, juce::NotificationType::dontSendNotification);

        algorithmButton .onClick = [this] { algorithmMenu.     setEnabled (algorithmButton.getState()); };
        melodyButton    .onClick = [this] { selectMelodyButton.setEnabled (melodyButton.   getState()); };

        for (auto i = 0; i < algorithmChoices.size(); i ++)
        {
            algorithmMenu.addItem (algorithmChoices[i], i + 1);
        }
        algorithmMenu.setSelectedId(1);
    }
    
    ~GenerationMethodsBox() override
    {
    }
    
    void updateToggleState (juce::ToggleButton* button)
    {
        bool state = button->getToggleState();
        auto stateString = state ? "on" : "off";
        std::cout << button->getName() << " is " << stateString << std::endl;
    }
    
    void resized() override
    {
        juce::Rectangle<int> optionsArea = getLocalBounds().reduced(20);
        juce::Rectangle<int> algoOptionArea = optionsArea.removeFromTop(optionsArea.getHeight() / 2);
        juce::FlexBox algoOptionFb;
        algoOptionFb.justifyContent = juce::FlexBox::JustifyContent::spaceBetween;
        algoOptionFb.alignItems = juce::FlexBox::AlignItems::center;
        algoOptionFb.items.add (juce::FlexItem (algorithmButton).withMinWidth(210.f).withMinHeight (20.f));
        algoOptionFb.items.add (juce::FlexItem (algorithmMenu)  .withMinWidth(100.f).withMinHeight (30.f));
        algoOptionFb.performLayout(algoOptionArea);
        
        juce::FlexBox melodyOptionFb;
        melodyOptionFb.justifyContent = juce::FlexBox::JustifyContent::spaceBetween;
        melodyOptionFb.alignItems = juce::FlexBox::AlignItems::center;
        melodyOptionFb.items.add (juce::FlexItem (melodyButton)        .withMinWidth(210.f).withMinHeight (20.f));
        melodyOptionFb.items.add (juce::FlexItem (selectMelodyButton)  .withMinWidth(100.f).withMinHeight (30.f));
        melodyOptionFb.performLayout(optionsArea);
    }
    
//    void paint (juce::Graphics& g) override
//    {
        //        g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));   // clear the background
        //        g.setColour (juce::Colours::grey);
        //        g.drawRect (getLocalBounds(), 1);   // draw an outline around the component
        //        g.setColour (juce::Colours::white);
        //        g.setFont (juce::FontOptions (14.0f));
        //        g.drawText ("GenerationMethodsBox", getLocalBounds(),
        //                    juce::Justification::centred, true);   // draw some placeholder text
//    }
    private:
    juce::ToggleButton  algorithmButton          { "Generate from Algorithm" };
    juce::ToggleButton  melodyButton             { "Generate from Input Melody" };
    juce::ComboBox      algorithmMenu;
    juce::TextButton    selectMelodyButton       { "Select Melody" };
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (GenerationMethodsBox)
};
