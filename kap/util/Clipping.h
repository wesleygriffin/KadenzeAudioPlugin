#ifndef KAP_UTIL_CLIPPING_H_
#define KAP_UTIL_CLIPPING_H_

namespace util {

template < class Real >
Real clipTanh( Real x )
{
  return x * ( Real( 27 ) + x * x ) / ( Real( 27 ) + Real( 9 ) * x * x );
}

} // namespace util

#endif // KAP_UTIL_CLIPPING_H_
