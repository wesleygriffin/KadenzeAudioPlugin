add_library(dsp STATIC)
target_sources(dsp PRIVATE Delay.cpp Gain.cpp Lfo.cpp)
target_include_directories(dsp PUBLIC dsp)
set_target_properties(dsp PROPERTIES
    POSITION_INDEPENDENT_CODE TRUE
    VISIBILITY_INLINES_HIDDEN TRUE
    C_VISIBILITY_PRESET hidden
    CXX_VISIBILITY_PRESET hidden)