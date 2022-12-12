#ifndef KAP_UI_MAINPANEL_H_
#define KAP_UI_MAINPANEL_H_

#include "ui/PanelBase.h"

#include <memory>

namespace ui {

class CenterPanel;
class GainPanel;
class TopPanel;

class MainPanel final : public PanelBase
{
public:
  MainPanel( kap::Processor* processor );
  ~MainPanel();

  static constexpr int kWidth = 750;
  static constexpr int kHeight = 300;

private:
  std::unique_ptr< TopPanel > mTopPanel;
  std::unique_ptr< GainPanel > mInputGainPanel;
  std::unique_ptr< GainPanel > mOutputGainPanel;
  std::unique_ptr< CenterPanel > mCenterPanel;

  JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR( MainPanel );
};

} // namespace ui

#endif // KAP_UI_MAINPANEL_H_
