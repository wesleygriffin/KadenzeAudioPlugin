#include "VuMeter.h"

#include "ui/LookAndFeel.h"

#include "util/Smoothing.h"

#include "Parameters.h"
#include "Processor.h"

namespace components {

VuMeter::VuMeter( kap::Processor* processor ) : mProcessor{ processor }, mLevels{ 0.f, 0.f } {}

void VuMeter::paint( juce::Graphics& g )
{
  const float meterHeight = static_cast< float >( getHeight() );
  const float meterWidth = getWidth() / ( numChannels() + 1.f );

  g.setColour( ui::LookAndFeel::kColor6 );
  g.fillRect( 0.f, 0.f, meterWidth, meterHeight );
  g.fillRect( meterWidth * 1.5f, 0.f, meterWidth, meterHeight );

  decltype( mLevels ) fills;
  fills[ 0 ] = std::max( 0.f, meterHeight - ( meterHeight * mLevels[ 0 ] ) );
  fills[ 1 ] = std::max( 0.f, meterHeight - ( meterHeight * mLevels[ 1 ] ) );

  g.setColour( ui::LookAndFeel::kColor7 );
  g.fillRect( 0.f, fills[ 0 ], meterWidth, meterHeight );
  g.fillRect( meterWidth * 1.5f, fills[ 1 ], meterWidth, meterHeight );
}

void VuMeter::timerCallback()
{
  decltype( mLevels ) newLevels;
  newLevels[ 0 ] = mGainCallback( 0 );
  newLevels[ 1 ] = mGainCallback( 1 );

  mLevels[ 0 ] = ( newLevels[ 0 ] > mLevels[ 0 ] )
    ? newLevels[ 0 ]
    : util::kMeterSmoothingCoeff< float > * ( mLevels[ 0 ] - newLevels[ 0 ] ) + newLevels[ 0 ];
  mLevels[ 1 ] = ( newLevels[ 1 ] > mLevels[ 1 ] )
    ? newLevels[ 1 ]
    : util::kMeterSmoothingCoeff< float > * ( mLevels[ 1 ] - newLevels[ 1 ] ) + newLevels[ 1 ];

  JUCE_UNDENORMALISE( mLevels[ 0 ] )
  JUCE_UNDENORMALISE( mLevels[ 1 ] )

  if ( mLevels[ 0 ] > 0.f || mLevels[ 1 ] > 0.f ) repaint();
}

void VuMeter::setGainCallback( std::function< float( int ) > callback )
{
  mGainCallback = std::move( callback );
  startTimer( 15 );
}

} // namespace components