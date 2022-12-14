#include "Parameters.h"

#include <functional>

namespace kap {

Parameters::Parameter const Parameters::kInputGain{
  "InputGain",
  "Input Gain",
  std::hash< std::string >{}( "InputGain" ) };
Parameters::Parameter const Parameters::kOutputGain{
  "OutputGain",
  "Output Gain",
  std::hash< std::string >{}( "OputputGain" ) };
Parameters::Parameter const Parameters::kType{ "DelayType", "Type", std::hash< std::string >{}( "DelayType" ) };
Parameters::Parameter const Parameters::kDryWet{
  "DelayDryWet",
  "Dry Wet",
  std::hash< std::string >{}( "DelayDryWet" ) };
Parameters::Parameter const Parameters::kDelayTime{
  "DelayTime",
  "Delay Time",
  std::hash< std::string >{}( "DelayTime" ) };
Parameters::Parameter const Parameters::kFeedback{
  "DelayFeedback",
  "Feedback",
  std::hash< std::string >{}( "DelayFeedback" ) };
Parameters::Parameter const Parameters::kModRate{
  "ModulationRate",
  "Mod Rate",
  std::hash< std::string >{}( "ModulationRate" ) };
Parameters::Parameter const Parameters::kModDepth{
  "ModulationDepth",
  "Mod Depth",
  std::hash< std::string >{}( "ModulationDepth" ) };

} // namespace kap