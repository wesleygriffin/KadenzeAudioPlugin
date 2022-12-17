#ifndef KAP_UI_LOOKANDFEEL_H_
#define KAP_UI_LOOKANDFEEL_H_

#include "ui/FxPanel.h"
#include "ui/GainPanel.h"
#include "ui/TopPanel.h"

#include <juce_gui_basics/juce_gui_basics.h>

namespace ui {

class LookAndFeel : public juce::LookAndFeel_V4,
                    public FxPanel::LookAndFeelMethods,
                    public GainPanel::LookAndFeelMethods,
                    public TopPanel::LookAndFeelMethods
{
public:
  static LookAndFeel* getInstance();

  virtual ~LookAndFeel() = default;

  juce::Colour getFxPanelTextColour( FxPanel& ) override { return mColor4; }
  juce::Font getFxPanelTextFont( FxPanel& ) override { return mFont3; }
  juce::Font getFxPanelDialFont( FxPanel& ) override { return mFont1; }

  juce::Font getGainPanelLabelFont( GainPanel& ) override { return mFont1; }

  juce::Colour getTopPanelTextColour( TopPanel& ) override { return mColor1; }
  juce::Font getTopPanelTextFont( TopPanel& ) override { return mFont2; }

  juce::Font getTextButtonFont( juce::TextButton&, int ) override { return mFont1; }

  void drawButtonBackground( juce::Graphics&, juce::Button&, const juce::Colour&, bool, bool ) override;

  juce::Font getLabelFont( juce::Label& ) override { return mFont1; }

  void drawPopupMenuItem(
    juce::Graphics&,
    const juce::Rectangle< int >&,
    bool,
    bool,
    bool,
    bool,
    bool,
    const juce::String&,
    const juce::String&,
    const juce::Drawable*,
    const juce::Colour* ) override;

  void drawComboBox( juce::Graphics&, int, int, bool, int, int, int, int, juce::ComboBox& ) override;

  void drawRotarySlider( juce::Graphics&, int, int, int, int, float, float, float, juce::Slider& ) override;

  void drawLabel( juce::Graphics&, juce::Label& ) override;

private:
  LookAndFeel();

  juce::Colour mColor1;
  juce::Colour mColor2;
  juce::Colour mColor3;
  juce::Colour mColor4;
  juce::Colour mColor5;
  juce::Colour mColor6;
  juce::Colour mColor7;
  juce::Colour mColor8;
  juce::Font mFont1;
  juce::Font mFont2;
  juce::Font mFont3;
  juce::Image mSliderImage;

  static const float kCornerSize;

  JUCE_DECLARE_WEAK_REFERENCEABLE( LookAndFeel )
  JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR( LookAndFeel )
};

} // namespace ui

#endif // KAP_UI_LOOKANDFEEL_H_