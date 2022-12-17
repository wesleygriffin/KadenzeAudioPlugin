#ifndef KAP_SMOOTHING_H_
#define KAP_SMOOTHING_H_

namespace kap {

template < typename Real >
constexpr Real kParameterSmoothingCoeff_Generic = Real{ 0.04 };

template < typename Real >
constexpr Real kParameterSmoothingCoeff_Fine = Real{ 0.002 };

template < typename Real >
constexpr Real kMeterSmoothingCoeff = Real{ 0.2 };

} // namespace dsp

#endif // KAP_SMOOTHING_H_
