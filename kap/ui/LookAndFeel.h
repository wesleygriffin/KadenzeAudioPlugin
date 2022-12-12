#ifndef KAP_UI_LOOKANDFEEL_H_
#define KAP_UI_LOOKANDFEEL_H_

#include <juce_gui_basics/juce_gui_basics.h>

namespace ui {

class LookAndFeel : public juce::LookAndFeel_V4
{
public:
  static const juce::Colour kColor1;
  static const juce::Colour kColor2;
  static const juce::Colour kColor3;
  static const juce::Colour kColor4;
  static const juce::Colour kColor5;
  static const juce::Colour kColor6;
  static const juce::Colour kColor7;

  static const juce::Font kFont1;
  static const juce::Font kFont2;
  static const juce::Font kFont3;

  LookAndFeel();
  virtual ~LookAndFeel() = default;

  juce::Font getTextButtonFont( juce::TextButton&, int ) override { return kFont1; }

  void drawButtonBackground( juce::Graphics&, juce::Button&, const juce::Colour&, bool, bool ) override;

  juce::Font getLabelFont( juce::Label& ) override { return kFont1; }

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
};

} // namespace ui

#endif // KAP_UI_LOOKANDFEEL_H_