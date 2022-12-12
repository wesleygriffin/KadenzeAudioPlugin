#include "LookAndFeel.h"

namespace ui {

const juce::Colour LookAndFeel::kColor1 = juce::Colour( 105, 105, 105 );
const juce::Colour LookAndFeel::kColor2 = juce::Colour( 0, 0, 0 ).withAlpha( 0.f );
const juce::Colour LookAndFeel::kColor3 = juce::Colour( 0, 0, 0 ).withAlpha( .3f );
const juce::Colour LookAndFeel::kColor4 = juce::Colour( 0, 0, 0 ).withAlpha( .6f );
const juce::Colour LookAndFeel::kColor5 = juce::Colour( 105, 105, 105 ).withAlpha( .3f );
const juce::Colour LookAndFeel::kColor6 = juce::Colour( 0, 0, 0 ).withAlpha( .8f );
const juce::Colour LookAndFeel::kColor7 = juce::Colour( 125, 125, 125 );

const juce::Font LookAndFeel::kFont1( "Arial", 12.f, juce::Font::bold );
const juce::Font LookAndFeel::kFont2( "Arial", 22.f, juce::Font::bold );
const juce::Font LookAndFeel::kFont3( "Arial", 48.f, juce::Font::bold );

LookAndFeel::LookAndFeel()
{
  setColour( juce::ComboBox::ColourIds::backgroundColourId, kColor3 );
  setColour( juce::ComboBox::ColourIds::outlineColourId, kColor2 );
  setColour( juce::ComboBox::ColourIds::arrowColourId, kColor1 );
  setColour( juce::ComboBox::ColourIds::textColourId, kColor1 );

  setColour( juce::TextButton::ColourIds::buttonColourId, kColor1 );
  setColour( juce::TextButton::ColourIds::textColourOnId, kColor1 );
  setColour( juce::TextButton::ColourIds::textColourOffId, kColor1 );
}

void LookAndFeel::drawButtonBackground(
  juce::Graphics& g,
  juce::Button& button,
  const juce::Colour&,
  bool isMouseOverButton,
  bool isButtonDown )
{
  juce::Colour fillColor;
  if ( isButtonDown ) {
    fillColor = kColor5;
  } else if ( isMouseOverButton ) {
    fillColor = kColor3;
  }

  const float cornerSize = 6.f;
  const juce::Rectangle< float > bounds = button.getLocalBounds().toFloat().reduced( .5f, .5f );
  g.setColour( fillColor );
  g.fillRoundedRectangle( bounds.reduced( 1 ), cornerSize );
}

void LookAndFeel::drawPopupMenuItem(
  juce::Graphics& g,
  const juce::Rectangle< int >& area,
  bool,
  bool,
  bool isHighlighted,
  bool isTicked,
  bool,
  const juce::String& text,
  const juce::String&,
  const juce::Drawable*,
  const juce::Colour* )
{
  juce::Rectangle< int > r( area );

  g.setColour( isHighlighted ? kColor5 : kColor4 );
  g.fillRect( r.getX(), r.getY(), r.getWidth(), r.getHeight() - 1 );

  g.setColour( isTicked ? kColor7 : kColor1 );
  g.setFont( kFont1 );
  r.setLeft( 10 );
  r.setY( 1 );
  g.drawFittedText( text, r, juce::Justification::left, 1 );
}

void LookAndFeel::drawComboBox(
  juce::Graphics& g,
  int width,
  int height,
  bool,
  int,
  int,
  int,
  int,
  juce::ComboBox& comboBox )
{
  const float cornerSize = 3.f;
  const juce::Rectangle< int > boxBounds( 0, 0, width, height );

  g.setColour( kColor3 );
  g.fillRoundedRectangle( boxBounds.toFloat(), cornerSize );

  juce::Rectangle< int > arrow( width - 30, 0, 20, height );
  juce::Path path;
  path.startNewSubPath( arrow.toFloat().getX() + 3.f, arrow.toFloat().getCentreY() - 2.f );
  path.lineTo( arrow.toFloat().getCentreX(), arrow.toFloat().getCentreY() + 3.f );
  path.lineTo( arrow.toFloat().getRight() - 3.f, arrow.toFloat().getCentreY() - 2.f );

  g.setColour( comboBox.findColour( juce::ComboBox::arrowColourId ).withAlpha( comboBox.isEnabled() ? .9f : .2f ) );
  g.strokePath( path, juce::PathStrokeType( 2.f ) );
}

} // namespace ui