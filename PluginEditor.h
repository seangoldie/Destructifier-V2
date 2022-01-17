#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

//==============================================================================

class DestructifierV2AudioProcessorEditor  : public juce::AudioProcessorEditor, public juce::Slider::Listener, public juce::Button::Listener
{
public:
    DestructifierV2AudioProcessorEditor (DestructifierV2AudioProcessor&);
    ~DestructifierV2AudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;
    void sliderValueChanged(juce::Slider *slider) override;
    void buttonClicked(juce::Button *button) override;
    void setColors(int mode);

private:
    juce::Slider knob;
    juce::TextButton mode;
    juce::Font font;

    DestructifierV2AudioProcessor& audioProcessor;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (DestructifierV2AudioProcessorEditor)
};
