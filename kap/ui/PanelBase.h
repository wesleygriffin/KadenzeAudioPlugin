#ifndef KAP_UI_PANELBASE_H_
#define KAP_UI_PANELBASE_H_

#include "ui/LookAndFeel.h"

#include <juce_gui_basics/juce_gui_basics.h>

namespace kap {
class Processor;
}

namespace ui {

class PanelBase : public juce::Component
{
public:
  PanelBase( kap::Processor* processor ) noexcept;
  virtual ~PanelBase() = default;

  void paint( juce::Graphics& g ) override;

  void mouseEnter( const juce::MouseEvent& event ) override;
  void mouseExit( const juce::MouseEvent& event ) override;

protected:
  kap::Processor* mProcessor;

  JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR( PanelBase );
};

} // namespace ui

#endif // KAP_UI_PANELBASE_H_
