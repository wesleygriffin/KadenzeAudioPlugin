#include "VuMeter.h"

#include "ui/LookAndFeel.h"

#include "util/Smoothing.h"

#include "Parameters.h"
#include "Processor.h"

namespace components {

VuMeter::VuMeter( kap::Processor* processor, int numChannels )
: mProcessor{ processor }, mNumChannels{ numChannels }, mLevels( mNumChannels, 0.f )
{}

void VuMeter::paint( juce::Graphics& g )
{
  const int meterWidth = getWidth() / mNumChannels + 2;

  g.setColour( ui::LookAndFeel::kColor6 );
  for ( int i = 0; i < mNumChannels; ++i ) {
    g.setColour( juce::Colour( 125, 125, 75 * i ) );
    g.fillRect( i * ( meterWidth * 2 ), 0, meterWidth, getHeight() );
  }

  std::vector< float > fills( mLevels.size() );
  std::transform( mLevels.begin(), mLevels.end(), fills.begin(), [ & ]( float level ) {
    return getHeight() - ( getHeight() * level );
  } );

  g.setColour( ui::LookAndFeel::kColor7 );
  for ( int i = 0; i < mNumChannels; ++i ) {
    g.fillRect( i * ( meterWidth * 2 ), static_cast< int >( fills[ i ] ), meterWidth, getHeight() );
  }
}

void VuMeter::timerCallback()
{
  for ( int i = 0; i < mNumChannels; ++i ) {
    const float newLevel = mGainCallback( i );
    if ( newLevel > mLevels[ i ] ) {
      mLevels[ i ] = newLevel;
    } else {
      mLevels[ i ] = util::kMeterSmoothingCoeff< float > * ( mLevels[ i ] - newLevel ) * newLevel;
    }

    JUCE_UNDENORMALISE( mLevels[ i ] )
    if ( mLevels[ i ] > 0.f ) repaint();
  }
}

void VuMeter::setGainCallback( std::function< float( int ) > callback )
{
  mGainCallback = std::move( callback );
  startTimer( 15 );
}

} // namespace components