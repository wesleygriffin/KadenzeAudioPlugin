#ifndef KAP_DSP_GAIN_H_
#define KAP_DSP_GAIN_H_

#include <juce_core/juce_core.h>

namespace dsp {

template < class Real >
class Gain
{
public:
  void process( Real const* inBuffer, int numSamples, Real gain, Real* outBuffer );

private:
};

template < class Real >
void Gain< Real >::process( Real const* inBuffer, int numSamples, Real gain, Real* outBuffer )
{
  const float gainMapped = juce::Decibels::decibelsToGain< Real >( juce::jmap< Real >( gain, 0, 1, -24, 24 ), -24 );
  for ( int sample = 0; sample < numSamples; ++sample ) {
    outBuffer[ sample ] = inBuffer[ sample ] * gainMapped;
  }
}

} // namespace dsp

#endif // KAP_DSP_GAIN_H_