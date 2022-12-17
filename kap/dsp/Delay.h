#ifndef DSP_DELAY_H_
#define DSP_DELAY_H_

#include <memory>

namespace dsp {

template < typename Real >
class Delay
{
public:
  Delay( double maxDelayTimeInSeconds ) : mMaxDelayTimeInSeconds{ maxDelayTimeInSeconds } {}

  void setSampleRate( double sampleRate );
  void reset();
  void process(
    Real const* inBuffer,
    int numSamples,
    Real time,
    Real feedback,
    Real smoothingCoefficient,
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

extern Delay< float > fDelay;
extern Delay< double > dDelay;

} // namespace dsp

#endif // DSP_DELAY_H_
