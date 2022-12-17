#include "Delay.h"
#include "Clipping.h"

#include <cmath>
#include <cstring> // std::memset

namespace dsp {

template < typename Real >
void Delay< Real >::setSampleRate( double sampleRate )
{
  mSampleRate = sampleRate;
  mBufferSize = static_cast< size_t >( mSampleRate * mMaxDelayTimeInSeconds );
  mBuffer.reset( new Real[ mBufferSize ] );
  std::memset( mBuffer.get(), 0, mBufferSize * sizeof( Real ) );
};

template < typename Real >
void Delay< Real >::reset()
{
  mTimeSmoothed = Real( 0 );
  mBufferSize = 0;
  mBuffer.reset();
}

template < typename Real >
void Delay< Real >::process(
  Real const* inBuffer,
  int numSamples,
  Real time,
  Real feedback,
  Real smoothingCoefficient,
  Real wetDry,
  Real const* modulationBuffer,
  Real* outBuffer )
{
  for ( int sample = 0; sample < numSamples; ++sample ) {
    mTimeSmoothed = mTimeSmoothed + ( modulationBuffer ? modulationBuffer[ sample ] : Real{ 0 } )
      - smoothingCoefficient * ( mTimeSmoothed - time );

    const Real delayTimeInSamples = mTimeSmoothed * static_cast< Real >( mSampleRate );
    const Real interpolatedSample = getInterpolatedSample( delayTimeInSamples );

    mBuffer[ mDelayIndex ] = clipping::tanh< Real >( inBuffer[ sample ] + ( mFeedbackSample * feedback ) );
    mFeedbackSample = interpolatedSample;

    outBuffer[ sample ] = inBuffer[ sample ] * ( Real{ 1 } - wetDry ) + interpolatedSample * wetDry;
    mDelayIndex = ( mDelayIndex + 1 ) % mBufferSize;
  }
}

template < typename Real >
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

  const Real outSample = std::lerp( sampleX, sampleX_1, readPositionPhase );
  return outSample;
}

template class Delay< float >;
template class Delay< double >;

} // namespace dsp