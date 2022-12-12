#include "PanelBase.h"

#include "Processor.h"

namespace ui {

PanelBase::PanelBase( kap::Processor* processor ) noexcept : mProcessor{ processor } {}

void PanelBase::paint( juce::Graphics& g )
{
  g.setColour( juce::Colours::darkgrey );
  g.fillAll();

  g.setColour( juce::Colours::whitesmoke );
  g.drawRoundedRectangle( 0, 0, static_cast< float >( getWidth() ), static_cast< float >( getHeight() ), 4, 2 );
}

void PanelBase::mouseEnter( const juce::MouseEvent& )
{
  repaint();
}

void PanelBase::mouseExit( const juce::MouseEvent& )
{
  repaint();
}

} // namespace ui