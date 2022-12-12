#ifndef KAP_UTIL_INTERPOLATION_H_
#define KAP_UTIL_INTERPOLATION_H_

namespace util {

template < typename Real >
Real linearInterpolate( Real v0, Real v1, Real t ) noexcept
{
  return ( 1 - t ) * v0 + t * v1;
}

} // namespace util

#endif // KAP_UTIL_INTERPOLATION_H_