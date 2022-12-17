#ifndef DSP_CLIPPING_H_
#define DSP_CLIPPING_H_

namespace dsp::clipping {

template < typename Real >
Real tanh( Real x )
{
  return x * ( Real{ 27 } + x * x ) / ( Real{ 27 } + Real{ 9 } * x * x );
}

} // namespace dsp::clipping

#endif // DSP_CLIPPING_H_
