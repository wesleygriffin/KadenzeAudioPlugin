#ifndef KAP_UI_TOPPANEL_H_
#define KAP_UI_TOPPANEL_H_

#include "ui/MainPanel.h"
#include "ui/PanelBase.h"

namespace ui {

class TopPanel final : public PanelBase
{
public:
  TopPanel( kap::Processor* processor );

  void paint( juce::Graphics& g ) override;

  struct LookAndFeelMethods
  {
    virtual ~LookAndFeelMethods() = default;

    virtual juce::Font getTopPanelTextFont( TopPanel& ) = 0;
    virtual juce::Colour getTopPanelTextColour( TopPanel& ) = 0;
  };

  static constexpr int kWidth = MainPanel::kWidth;
  static constexpr int kHeight = 45;
  static constexpr int kPresetButtonWidth = 55;
  static constexpr int kPresetButtonHeight = 25;
  static constexpr int kPresetComboBoxWidth = 200;
  static constexpr int kPresetComboBoxHeight = kPresetButtonHeight;
  static constexpr int kLabelWidth = 220;

private:
  std::unique_ptr< juce::TextButton > mInitPresetButton;
  std::unique_ptr< juce::TextButton > mSavePresetButton;
  std::unique_ptr< juce::TextButton > mSaveAsPresetButton;
  std::unique_ptr< juce::ComboBox > mPresetComboBox;

  void updatePresetComboBox();
  void displaySaveAsPopup();

  JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR( TopPanel );
};

} // namespace ui

#endif // KAP_UI_TOPPANEL_H_
