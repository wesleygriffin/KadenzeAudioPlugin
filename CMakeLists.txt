cmake_minimum_required(VERSION 3.24.0)
project(juce-sandbox VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(JUCE_BUILD_EXTRAS OFF)
set(JUCE_BUILD_EXAMPLES OFF)
add_subdirectory(JUCE)

#add_subdirectory(src)
add_subdirectory(kap)