#ifndef KAP_DSP_DELAY_H_
#define KAP_DSP_DELAY_H_

#include "util/Clipping.h"
#include "util/Interpolation.h"
#include "util/Smoothing.h"

#include <juce_core/juce_core.h>

#include <memory>

namespace dsp {

template < class Real >
class Delay
{
public:
  enum class Type
  {
    kDelay = 0,
    kChorus
  };

  Delay( double maxDelayTimeInSeconds ) : mMaxDelayTimeInSeconds{ maxDelayTimeInSeconds } {}

  void setSampleRate( double sampleRate );
  void reset();
  void process(
    Real const* inBuffer,
    int numSamples,
    Real time,
    Real feedback,
    Real type,
    Real wetDry,
    Real const* modulationBuffer,
    Real* outBuffer );

private:
  Real getInterpolatedSample( Real delayTimeInSamples );

  double mMaxDelayTimeInSeconds{ -1. };
  double mSampleRate{ -1. };
  Real mTimeSmoothed{ 0 };
  Real mFeedbackSample{ 0 };
  int mDelayIndex{ 0 };
  size_t mBufferSize{ 0 };
  std::unique_ptr< Real[] > mBuffer{};
};

template < class Real >
void Delay< Real >::setSampleRate( double sampleRate )
{
  mSampleRate = sampleRate;
  mBufferSize = static_cast< size_t >( mSampleRate * mMaxDelayTimeInSeconds );
  mBuffer.reset( new Real[ mBufferSize ] );
  juce::zeromem( mBuffer.get(), mBufferSize * sizeof( Real ) );
};

template < class Real >
void Delay< Real >::reset()
{
  mTimeSmoothed = Real( 0 );
  mBufferSize = 0;
  mBuffer.reset();
}

template < class Real >
void Delay< Real >::process(
  Real const* inBuffer,
  int numSamples,
  Real time,
  Real feedback,
  Real typeParam,
  Real wetDry,
  Real const* modulationBuffer,
  Real* outBuffer )
{
  const Type type = static_cast< Type >( static_cast< int >( typeParam ) );
  const Real wet = wetDry;
  const Real dry = 1 - wetDry;
  const float feedbackMapped =
    ( type == Type::kDelay ) ? juce::jmap< Real >( feedback, Real( 0 ), Real( 1 ), Real( 0 ), Real( 1.2 ) ) : Real( 0 );

  for ( int sample = 0; sample < numSamples; ++sample ) {
    if ( type == Type::kDelay ) {
      mTimeSmoothed = mTimeSmoothed - util::kParameterSmoothingCoeff_Fine< Real > * ( mTimeSmoothed - time );
    } else {
      const Real delayTimeModulation = .003f + util::kParameterSmoothingCoeff_Fine< Real > * modulationBuffer[ sample ];
      mTimeSmoothed =
        mTimeSmoothed - util::kParameterSmoothingCoeff_Fine< Real > * ( mTimeSmoothed - delayTimeModulation );
    }

    const Real delayTimeInSamples = mTimeSmoothed * static_cast< Real >( mSampleRate );
    const Real interpolatedSample = getInterpolatedSample( delayTimeInSamples );

    mBuffer[ mDelayIndex ] = util::clipTanh< Real >( inBuffer[ sample ] + ( mFeedbackSample * feedbackMapped ) );
    mFeedbackSample = interpolatedSample;

    outBuffer[ sample ] = inBuffer[ sample ] * dry + interpolatedSample * wet;
    mDelayIndex = ( mDelayIndex + 1 ) % mBufferSize;
  }
}

template < class Real >
Real Delay< Real >::getInterpolatedSample( Real delayTimeInSamples )
{
  const Real readPosition = ( static_cast< Real >( mDelayIndex ) - delayTimeInSamples < 0 )
    ? static_cast< Real >( mDelayIndex ) - delayTimeInSamples + mBufferSize
    : static_cast< Real >( mDelayIndex ) - delayTimeInSamples;

  Real readPositionInt;
  const Real readPositionPhase = std::modf( readPosition, &readPositionInt );

  const int readHeadX = static_cast< int >( readPositionInt ) == 0 ? static_cast< int >( mBufferSize ) - 1
                                                                   : static_cast< int >( readPositionInt - 1 );

  const int readHeadX_1 = static_cast< int >( readPositionInt ) > static_cast< int >( mBufferSize )
    ? static_cast< int >( readPositionInt ) - static_cast< int >( mBufferSize )
    : static_cast< int >( readPositionInt );

  const Real sampleX = mBuffer[ readHeadX ];
  const Real sampleX_1 = mBuffer[ readHeadX_1 ];

  const Real outSample = util::linearInterpolate( sampleX, sampleX_1, readPositionPhase );
  return outSample;
}

} // namespace dsp

#endif // KAP_DSP_DELAY_H_
