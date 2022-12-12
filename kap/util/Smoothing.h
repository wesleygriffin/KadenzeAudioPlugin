#ifndef KAP_UTIL_SMOOTHING_H_
#define KAP_UTIL_SMOOTHING_H_

namespace util {

template < class Real >
constexpr Real kParameterSmoothingCoeff_Generic = Real( 0.04 );

template < class Real >
constexpr Real kParameterSmoothingCoeff_Fine = Real( 0.002 );

template < class Real >
constexpr Real kMeterSmoothingCoeff = Real( 0.2 );

} // namespace util

#endif // KAP_UTIL_SMOOTHING_H_
