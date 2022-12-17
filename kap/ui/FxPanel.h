#ifndef KAP_UI_FXPANEL_H_
#define KAP_UI_FXPANEL_H_

#include "ui/CenterPanel.h"
#include "ui/CenterPanelMenuBar.h"
#include "ui/PanelBase.h"

#include <memory>
#include <vector>

namespace ui {

class ParameterDial;

class FxPanel final : public PanelBase, public juce::ComboBox::Listener
{
public:
  enum class Style
  {
    kDelay = 0,
    kChorus
  };

  FxPanel( kap::Processor* processor );

  void setStyle( Style style );

  void paint( juce::Graphics& g ) override;

  void comboBoxChanged( juce::ComboBox* comboBoxThatHasChanged ) override;

  static constexpr int kWidth = CenterPanel::kWidth;
  static constexpr int kHeight = CenterPanel::kHeight - CenterPanelMenuBar::kHeight;

  struct LookAndFeelMethods
  {
    virtual ~LookAndFeelMethods() = default;

    virtual juce::Font getFxPanelTextFont( FxPanel& ) = 0;
    virtual juce::Colour getFxPanelTextColour( FxPanel& ) = 0;
    virtual juce::Font getFxPanelDialFont( FxPanel& ) = 0;
  };

private:
  Style mStyle{ Style::kDelay };

  std::vector< std::unique_ptr< ParameterDial > > mDials;
  std::vector< std::unique_ptr< juce::Label > > mLabels;

  void addDial( const kap::Parameters::Parameter& parameter, int x, int y );

  JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR( FxPanel );
};

} // namespace ui

#endif // KAP_UI_FXPANEL_H_
