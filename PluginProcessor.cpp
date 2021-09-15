/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
DestructifierV2AudioProcessor::DestructifierV2AudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  juce::AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", juce::AudioChannelSet::stereo(), true)
                     #endif
                       )
#endif
{
}

DestructifierV2AudioProcessor::~DestructifierV2AudioProcessor()
{
}

//==============================================================================
const juce::String DestructifierV2AudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool DestructifierV2AudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool DestructifierV2AudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool DestructifierV2AudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double DestructifierV2AudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int DestructifierV2AudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int DestructifierV2AudioProcessor::getCurrentProgram()
{
    return 0;
}

void DestructifierV2AudioProcessor::setCurrentProgram (int index)
{
}

const juce::String DestructifierV2AudioProcessor::getProgramName (int index)
{
    return {};
}

void DestructifierV2AudioProcessor::changeProgramName (int index, const juce::String& newName)
{
}

//==============================================================================
void DestructifierV2AudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // Use this method as the place to do any pre-playback
    // initialisation that you need..
}

void DestructifierV2AudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool DestructifierV2AudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    juce::ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    // Some plugin hosts, such as certain GarageBand versions, will only
    // load plugins that support stereo bus layouts.
    if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif

void DestructifierV2AudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    juce::ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());
    short int p;
    int ratio = 20;
    float knee = 0.25f;
    float threshold;

    for (int channel = 0; channel < totalNumInputChannels; ++channel)
    {
        auto* channelData = buffer.getWritePointer (channel);
        for (int sample = 0; sample < buffer.getNumSamples(); ++sample)
        {
            p = channelData[sample]/abs(channelData[sample]);
            threshold = amount/100.0f;
            switch (mode)
            {
                case 0: // OD
                    channelData[sample] += channelData[sample] * (amount/10);
                    break;
                case 1: // Fuzz
                    channelData[sample] *= pow(2,(amount/10));
                    break;
                case 2: // Bad compression
                    threshold = (1-threshold);
                    if (abs(channelData[sample]) >= threshold - knee && abs(channelData[sample]) <= threshold + knee)
                    {
                        channelData[sample] = p * ((abs(channelData[sample] - threshold)/ratio) + threshold);
                    }
                    break;
                case 3: // Hard clipping
                    threshold = (1-threshold);
                    if (abs(channelData[sample]) >= (threshold))
                    {
                        channelData[sample] = channelData[sample] / abs(channelData[sample]) * (threshold);
                    }
                    break;
                case 4: // Up-compression
                    if (abs(channelData[sample]) <= threshold)
                    {
                        channelData[sample] += p * (threshold - (abs(channelData[sample])/ratio));
                    }
                        break;
                default:
                    break;
            }
            if (channelData[sample] >= 1.0f)
                channelData[sample] = 1.0f;
            else if (channelData[sample] <= -1.0f)
                channelData[sample] = -1.0f;
        }
    }
}

//==============================================================================
bool DestructifierV2AudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* DestructifierV2AudioProcessor::createEditor()
{
    return new DestructifierV2AudioProcessorEditor (*this);
}

//==============================================================================
void DestructifierV2AudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    destData.reset();
    state.prevAmount = amount;
    state.prevMode = mode;
    destData.append(&state, sizeof(state));
}

void DestructifierV2AudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    const stateStruct* newData = reinterpret_cast<const stateStruct*>(data);
    stateStruct prevState = newData[0];
    state = prevState;
    amount = state.prevAmount;
    mode = state.prevMode;
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new DestructifierV2AudioProcessor();
}
