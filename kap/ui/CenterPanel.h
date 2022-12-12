#ifndef KAP_UI_CENTERPANEL_H_
#define KAP_UI_CENTERPANEL_H_

#include "ui/GainPanel.h"
#include "ui/MainPanel.h"
#include "ui/PanelBase.h"

#include <memory>

namespace ui {

class CenterPanelMenuBar;
class FxPanel;

class CenterPanel final : public PanelBase
{
public:
  CenterPanel( kap::Processor* processor );
  ~CenterPanel();

  static constexpr int kWidth = MainPanel::kWidth - ( GainPanel::kWidth * 2 );
  static constexpr int kHeight = GainPanel::kHeight;

private:
  std::unique_ptr< CenterPanelMenuBar > mMenuBar;
  std::unique_ptr< FxPanel > mFxPanel;

  JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR( CenterPanel );
};

} // namespace ui

#endif // KAP_UI_CENTERPANEL_H_
