#ifndef KAP_UI_GAINPANEL_H_
#define KAP_UI_GAINPANEL_H_

#include "Parameters.h"

#include "ui/MainPanel.h"
#include "ui/PanelBase.h"
#include "ui/ParameterDial.h"
#include "ui/TopPanel.h"

#include <memory>

namespace components {
class VuMeter;
}

namespace ui {

class GainPanel final : public PanelBase
{
public:
  GainPanel( kap::Processor* processor );
  ~GainPanel();

  void setParameter( const kap::Parameters::Parameter& parameter );

  static constexpr int kWidth = 100;
  static constexpr int kHeight = MainPanel::kHeight - TopPanel::kHeight;
  static constexpr int kMeterWidth = 36;

  struct LookAndFeelMethods
  {
    virtual ~LookAndFeelMethods() = default;

    virtual juce::Font getGainPanelLabelFont( GainPanel& ) = 0;
  };

private:
  std::unique_ptr< ParameterDial > mDial;
  std::unique_ptr< juce::Label > mLabel;
  std::unique_ptr< components::VuMeter > mMeter;

  JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR( GainPanel );
};

} // namespace ui

#endif // KAP_UI_GAINPANEL_H_
