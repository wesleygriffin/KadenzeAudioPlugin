#ifndef KAP_DSP_GAIN_H_
#define KAP_DSP_GAIN_H_

#include "util/Smoothing.h"

#include <juce_core/juce_core.h>

namespace dsp {

template < class Real >
class Gain
{
public:
  void process( Real const* inBuffer, int numSamples, Real gain, Real* outBuffer );

  float getMeterLevel() const { return ( juce::Decibels::decibelsToGain( mOutputSmoothed ) ); }

private:
  float mGainSmoothed{ 0.f };
  float mOutputSmoothed{ 0.f };
};

template < class Real >
void Gain< Real >::process( Real const* inBuffer, int numSamples, Real gain, Real* outBuffer )
{
  const float gainMapped = juce::Decibels::decibelsToGain< Real >( juce::jmap< Real >( gain, 0, 1, -24, 24 ), -24 );
  mGainSmoothed = mGainSmoothed - util::kParameterSmoothingCoeff_Generic< float > * ( mGainSmoothed - gainMapped );

  for ( int sample = 0; sample < numSamples; ++sample ) {
    outBuffer[ sample ] = inBuffer[ sample ] * mGainSmoothed;
  }

  float absOutput = std::abs( outBuffer[ 0 ] );
  mOutputSmoothed = util::kMeterSmoothingCoeff< float > * ( mOutputSmoothed - absOutput ) + absOutput;
}

} // namespace dsp

#endif // KAP_DSP_GAIN_H_