#include "PanelBase.h"

#include "Processor.h"

namespace ui {

PanelBase::PanelBase( kap::Processor* processor ) noexcept : mProcessor{ processor } {}

void PanelBase::paint( juce::Graphics& )
{
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