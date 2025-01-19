#pragma once

#include <JuceHeader.h>

class MainComponent  : public juce::Component
{
    public:
    //==============================================================================
    MainComponent()
    {
        setSize (1200, 600);
    }
    
    ~MainComponent() override
    {
    }
    
    //==============================================================================
    void paint (juce::Graphics& g) override
    {
        g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));
    }
    
    void resized() override
    {
        addAndMakeVisible(generationMethodsBox);
        generationMethodsBox.setBounds (20, 20, 350, 150);
    }
    
    enum RadioButtonIds
    {
        GenerationMethodsRadioId = 101
    };

    
    private:
    struct GenerationMethodsBox : public juce::GroupComponent
    {
        GenerationMethodsBox (int radioGroupId)
        {
            setText ("Generation Method");
            setColour (juce::GroupComponent::ColourIds::outlineColourId, juce::Colours::white);
            addAndMakeVisible (algorithmButton);
            addAndMakeVisible (algorithmMenu);
            addAndMakeVisible (melodyButton);
            addAndMakeVisible (selectMelodyButton);
            
            algorithmButton .setRadioGroupId(radioGroupId);
            melodyButton    .setRadioGroupId(radioGroupId);
            
            for (auto i = 0; i < algorithmChoices.size(); i ++)
            {
                algorithmMenu.addItem (algorithmChoices[i], i + 1);
            }
            algorithmMenu.setSelectedId(1);
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
        
        juce::ToggleButton  algorithmButton          { "Generate from Algorithm" };
        juce::ToggleButton  melodyButton             { "Generate from Input Melody" };
        juce::ComboBox      algorithmMenu;
        juce::TextButton    selectMelodyButton       { "Select Melody" };
        juce::StringArray   algorithmChoices         {"Algo 1", "Algo 2", "Algo 3", "Algo 4", "Algo 5"};
    };
    
//    GenerationMethodsBox generationMethodsBox {350, 150};
    GenerationMethodsBox generationMethodsBox {GenerationMethodsRadioId};



    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainComponent)
};

//class MainComponent : public juce::Component
//{
//public:
//    MainComponent()
//    {
//        addAndMakeVisible(comboBox);
//        comboBox.addItem("Option 1", 1);
//        comboBox.addItem("Option 2", 2);
//        comboBox.addItem("Option 3", 3);
//
//        addAndMakeVisible(toggleButton);
//        toggleButton.setButtonText("Enable");
//
//        setSize(400, 200);
//    }
//
//    void resized() override
//    {
//        juce::FlexBox flexBox;
//        flexBox.flexDirection = juce::FlexBox::Direction::row;
//        flexBox.justifyContent = juce::FlexBox::JustifyContent::center;
//        flexBox.alignItems = juce::FlexBox::AlignItems::center;
//
//        flexBox.items.add(juce::FlexItem(comboBox).withFlex(1.0));
//        flexBox.items.add(juce::FlexItem(toggleButton).withMargin(juce::FlexItem::Margin(0, 0, 0, 20)));
//
//        flexBox.performLayout(getLocalBounds().reduced(20));
//    }
//
//private:
//    juce::ComboBox comboBox;
//    juce::ToggleButton toggleButton;
//
//    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(MainComponent)
//};
