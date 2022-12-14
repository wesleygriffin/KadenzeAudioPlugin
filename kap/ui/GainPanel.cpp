#include "GainPanel.h"

#include "components/VuMeter.h"

#include "ui/LookAndFeel.h"

#include "Processor.h"

namespace ui {

GainPanel::GainPanel( kap::Processor* processor )
: PanelBase{ processor }, mMeter{ new components::VuMeter{ processor } }
{
  setSize( kWidth, kHeight );
}

GainPanel::~GainPanel() = default;

void GainPanel::setParameter( const kap::Parameters::Parameter& parameter )
{
  mDial.reset( new ParameterDial{ mProcessor->getValueTreeState(), parameter } );
  mDial->setBounds(
    static_cast< int >( ( getWidth() * .5f ) - ( ParameterDial::kTotalWidth * .5f ) ),
    static_cast< int >( ( getHeight() * .2f ) - ( ParameterDial::kDialHeight * .5f ) ),
    ParameterDial::kTotalWidth,
    ParameterDial::kDialHeight );
  addAndMakeVisible( mDial.get() );

  mLabel.reset( new juce::Label( parameter.name + "Label", parameter.name ) );
  mLabel->setFont( LookAndFeel::kFont1 );
  mLabel->setJustificationType( juce::Justification::centred );
  mLabel->setBounds(
    static_cast< int >( ( getWidth() * .5f ) - ( ParameterDial::kTotalWidth * .5f ) ),
    static_cast< int >( ( getHeight() * .2f ) + ( ParameterDial::kDialHeight * .35f ) ),
    ParameterDial::kTotalWidth,
    ParameterDial::kLabelHeight );
  addAndMakeVisible( mLabel.get() );

  mMeter->setBounds(
    static_cast< int >( ( getWidth() * .5f ) - ( kMeterWidth * .5f ) ),
    static_cast< int >( getHeight() * .45f ),
    kMeterWidth,
    static_cast< int >( getHeight() * .5f ) );
  mMeter->setGainCallback( [ & ]( int channel ) {
    if ( parameter == kap::Parameters::kInputGain ) {
      return mProcessor->getInputMeterLevel( channel );
    } else {
      return mProcessor->getOutputMeterLevel( channel );
    }
  } );
  addAndMakeVisible( mMeter.get() );
}

} // namespace ui