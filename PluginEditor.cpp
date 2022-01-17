#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
DestructifierV2AudioProcessorEditor::DestructifierV2AudioProcessorEditor (DestructifierV2AudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    knob.setSliderStyle(juce::Slider::SliderStyle::RotaryVerticalDrag);
    knob.setColour(juce::Slider::rotarySliderFillColourId, juce::Colours::orange);
    knob.setColour(juce::Slider::rotarySliderOutlineColourId, juce::Colours::darkgrey);
    knob.setColour(juce::Slider::thumbColourId, juce::Colours::orange);

    knob.setTextBoxStyle(juce::Slider::NoTextBox, true, 0, 0);
    knob.setRange(0.0f, 100.0f, 0.01f);
    knob.setValue(0.0f);
    knob.addListener(this);
    addAndMakeVisible(knob);
    
    mode.Component::setColour(juce::TextButton::textColourOnId, juce::Colours::grey);
    mode.Component::setColour(juce::TextButton::textColourOffId, juce::Colours::white);
    mode.addListener(this);
    mode.setColour(juce::TextButton::buttonColourId, juce::Colours::orange);
    addAndMakeVisible(mode);
    
    font.setTypefaceName("Futura");
    
    setSize (300, 300);
    setResizable(false, false); // Comment out if resizeable is desired
}

DestructifierV2AudioProcessorEditor::~DestructifierV2AudioProcessorEditor()
{
}

//==============================================================================
void DestructifierV2AudioProcessorEditor::paint (juce::Graphics& g)
{
    g.fillAll(juce::Colours::black);
    g.setColour(juce::Colours::white);
    g.setFont(font);
    
    g.setFont(16.0f);
    g.drawText("COW ELVIS DSP", getWidth()/2-100, getHeight()/2-175, 200, 100, juce::Justification::centred);
    g.setFont(32.0f);
    g.drawText("DESTRUCTIFIER", getWidth()/2-100, getHeight()/2-150, 200, 100, juce::Justification::centred);
    g.setFont(16.0f);
    g.drawText("FLAVOR",getWidth()/2-100, getHeight()/2+70, 200, 100, juce::Justification::centred);
}

void DestructifierV2AudioProcessorEditor::resized()
{
    knob.setBounds(getWidth()/2-85, getHeight()/2-85, 170, 170);
    mode.setBounds(getWidth()/2-13, getHeight()/2+80, 26, 26);

    knob.setValue(audioProcessor.amount);
    
    if (audioProcessor.mode == 0)
    {
        knob.setColour(juce::Slider::rotarySliderFillColourId, juce::Colours::gold);
        knob.setColour(juce::Slider::thumbColourId, juce::Colours::gold);
        mode.setColour(juce::TextButton::buttonColourId, juce::Colours::gold);
    }
    else if (audioProcessor.mode == 1)
    {
        knob.setColour(juce::Slider::rotarySliderFillColourId, juce::Colours::indianred);
        knob.setColour(juce::Slider::thumbColourId, juce::Colours::indianred);
        mode.setColour(juce::TextButton::buttonColourId, juce::Colours::indianred);
    }
    else if (audioProcessor.mode == 2)
    {
        knob.setColour(juce::Slider::rotarySliderFillColourId, juce::Colours::springgreen);
        knob.setColour(juce::Slider::thumbColourId, juce::Colours::springgreen);
        mode.setColour(juce::TextButton::buttonColourId, juce::Colours::springgreen);
    }
    else if (audioProcessor.mode == 3)
    {
        knob.setColour(juce::Slider::rotarySliderFillColourId, juce::Colours::mediumpurple);
        knob.setColour(juce::Slider::thumbColourId, juce::Colours::mediumpurple);
        mode.setColour(juce::TextButton::buttonColourId, juce::Colours::mediumpurple);
    }
    else if (audioProcessor.mode == 4)
    {
        knob.setColour(juce::Slider::rotarySliderFillColourId, juce::Colours::skyblue);
        knob.setColour(juce::Slider::thumbColourId, juce::Colours::skyblue);
        mode.setColour(juce::TextButton::buttonColourId, juce::Colours::skyblue);
    }
}

void DestructifierV2AudioProcessorEditor::sliderValueChanged(juce::Slider *slider)
{
    audioProcessor.amount = slider->getValue();
}

void DestructifierV2AudioProcessorEditor::buttonClicked(juce::Button *button)
{
    if (audioProcessor.mode == 0)
    {
        audioProcessor.mode = 1;
        knob.setColour(juce::Slider::rotarySliderFillColourId, juce::Colours::indianred);
        knob.setColour(juce::Slider::thumbColourId, juce::Colours::indianred);
        mode.setColour(juce::TextButton::buttonColourId, juce::Colours::indianred);
    }
    else if (audioProcessor.mode == 1)
    {
        audioProcessor.mode = 2;
        knob.setColour(juce::Slider::rotarySliderFillColourId, juce::Colours::springgreen);
        knob.setColour(juce::Slider::thumbColourId, juce::Colours::springgreen);
        mode.setColour(juce::TextButton::buttonColourId, juce::Colours::springgreen);
    }
    else if (audioProcessor.mode == 2)
    {
        audioProcessor.mode = 3;
        knob.setColour(juce::Slider::rotarySliderFillColourId, juce::Colours::mediumpurple);
        knob.setColour(juce::Slider::thumbColourId, juce::Colours::mediumpurple);
        mode.setColour(juce::TextButton::buttonColourId, juce::Colours::mediumpurple);
    }
    else if (audioProcessor.mode == 3)
    {
        audioProcessor.mode = 4;
        knob.setColour(juce::Slider::rotarySliderFillColourId, juce::Colours::skyblue);
        knob.setColour(juce::Slider::thumbColourId, juce::Colours::skyblue);
        mode.setColour(juce::TextButton::buttonColourId, juce::Colours::skyblue);
    }
    else if (audioProcessor.mode == 4)
    {
        audioProcessor.mode = 0;
        knob.setColour(juce::Slider::rotarySliderFillColourId, juce::Colours::gold);
        knob.setColour(juce::Slider::thumbColourId, juce::Colours::gold);
        mode.setColour(juce::TextButton::buttonColourId, juce::Colours::gold);
    }
}
