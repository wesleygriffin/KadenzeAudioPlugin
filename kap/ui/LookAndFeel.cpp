#include "LookAndFeel.h"

#include "ui_assets.h"

namespace ui {

const juce::Colour LookAndFeel::kColor1 = juce::Colour( 105, 105, 105 );
const juce::Colour LookAndFeel::kColor2 = juce::Colour( 0, 0, 0 ).withAlpha( 0.f );
const juce::Colour LookAndFeel::kColor3 = juce::Colour( 0, 0, 0 ).withAlpha( .3f );
const juce::Colour LookAndFeel::kColor4 = juce::Colour( 0, 0, 0 ).withAlpha( .6f );
const juce::Colour LookAndFeel::kColor5 = juce::Colour( 105, 105, 105 ).withAlpha( .3f );
const juce::Colour LookAndFeel::kColor6 = juce::Colour( 0, 0, 0 ).withAlpha( .8f );
const juce::Colour LookAndFeel::kColor7 = juce::Colour( 125, 125, 125 );
const juce::Colour LookAndFeel::kColor8 = juce::Colour( 192, 192, 192 );

const juce::Font LookAndFeel::kFont1( "Arial", 12.f, juce::Font::bold );
const juce::Font LookAndFeel::kFont2( "Arial", 22.f, juce::Font::bold );
const juce::Font LookAndFeel::kFont3( "Arial", 48.f, juce::Font::bold );

const float LookAndFeel::kCornerSize = 6.f;

LookAndFeel::LookAndFeel()
: mSliderImage{ juce::ImageCache::getFromMemory( ui::kadenze_knob_png, ui::kadenze_knob_pngSize ) }
{
  setColour( juce::ComboBox::ColourIds::backgroundColourId, kColor3 );
  setColour( juce::ComboBox::ColourIds::outlineColourId, kColor2 );
  setColour( juce::ComboBox::ColourIds::arrowColourId, kColor1 );
  setColour( juce::ComboBox::ColourIds::textColourId, kColor8 );

  setColour( juce::TextButton::ColourIds::buttonColourId, kColor1 );
  setColour( juce::TextButton::ColourIds::textColourOnId, kColor8 );
  setColour( juce::TextButton::ColourIds::textColourOffId, kColor8 );

  setColour( juce::Label::ColourIds::backgroundColourId, kColor3 );
  setColour( juce::Label::ColourIds::textColourId, kColor8 );
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
    fillColor = kColor6;
  } else if ( isMouseOverButton ) {
    fillColor = kColor3;
  } else {
    fillColor = kColor4;
  }

  const juce::Rectangle< float > bounds = button.getLocalBounds().toFloat().reduced( .5f, .5f );
  g.setColour( fillColor );
  g.fillRoundedRectangle( bounds.reduced( 1 ), kCornerSize );
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
  const juce::Rectangle< int > boxBounds( 0, 0, width, height );

  g.setColour( kColor3 );
  g.fillRoundedRectangle( boxBounds.toFloat(), kCornerSize / 2.f );

  juce::Rectangle< int > arrow( width - 30, 0, 20, height );
  juce::Path path;
  path.startNewSubPath( arrow.toFloat().getX() + 3.f, arrow.toFloat().getCentreY() - 2.f );
  path.lineTo( arrow.toFloat().getCentreX(), arrow.toFloat().getCentreY() + 3.f );
  path.lineTo( arrow.toFloat().getRight() - 3.f, arrow.toFloat().getCentreY() - 2.f );

  g.setColour( comboBox.findColour( juce::ComboBox::arrowColourId ).withAlpha( comboBox.isEnabled() ? .9f : .2f ) );
  g.strokePath( path, juce::PathStrokeType( 2.f ) );
}

void LookAndFeel::drawRotarySlider(
  juce::Graphics& g,
  int x,
  int y,
  int width,
  int height,
  float sliderPosProportional,
  float,
  float,
  juce::Slider& )
{
  const int imageWidth = mSliderImage.getWidth();
  const int imageHeight = mSliderImage.getHeight();
  const int numFrames = imageHeight / imageWidth;
  const int frameIndex = static_cast< int >( std::ceil( sliderPosProportional * ( numFrames - 1 ) ) );
  const float radius = juce::jmin( width * .5f, height * .5f );
  const float centerX = x + width * .5f;
  const float centerY = y + height * .5f;
  const int rx = static_cast< int >( centerX - radius );
  const int ry = static_cast< int >( centerY - radius );
  const int r2 = static_cast< int >( radius * 2 );

  // the image is numframes * width high, so each "actual" image frame is width x width in size
  g.drawImage( mSliderImage, rx, ry, r2, r2, 0, frameIndex * imageWidth, imageWidth, imageWidth );
}

void LookAndFeel::drawLabel( juce::Graphics& g, juce::Label& label )
{
  const juce::Rectangle< float > bounds = label.getLocalBounds().toFloat().reduced( kCornerSize );
  g.setColour( label.findColour( juce::Label::backgroundColourId ) );
  g.fillRoundedRectangle( bounds, kCornerSize );

  if ( !label.isBeingEdited() ) {
    auto alpha = label.isEnabled() ? 1.0f : 0.5f;
    const juce::Font font( getLabelFont( label ) );

    g.setColour( label.findColour( juce::Label::textColourId ).withMultipliedAlpha( alpha ) );
    g.setFont( font );

    auto textArea = getLabelBorderSize( label ).subtractedFrom( label.getLocalBounds() );

    g.drawFittedText(
      label.getText(),
      textArea,
      label.getJustificationType(),
      juce::jmax( 1, (int) ( (float) textArea.getHeight() / font.getHeight() ) ),
      label.getMinimumHorizontalScale() );

    g.setColour( label.findColour( juce::Label::outlineColourId ).withMultipliedAlpha( alpha ) );
  } else if ( label.isEnabled() ) {
    g.setColour( label.findColour( juce::Label::outlineColourId ) );
  }

  g.drawRect( label.getLocalBounds() );
}

} // namespace ui