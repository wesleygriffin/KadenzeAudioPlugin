add_subdirectory(dsp)

juce_add_binary_data(ui_assets
    HEADER_NAME ui_assets.h
    NAMESPACE ui
    SOURCES
        assets/kadenze_bg.png
        assets/kadenze_knob.png)

juce_add_plugin(KadenzeAudioPlugin
    # VERSION ...                               # Set this if the plugin version is different to the project version
    # ICON_BIG ...                              # ICON_* arguments specify a path to an image file to use as an icon for the Standalone
    # ICON_SMALL ...
    COMPANY_NAME "Fraktured Labs"               # Specify the name of the plugin's author
    # IS_SYNTH TRUE/FALSE                       # Is this a synth or an effect?
    # NEEDS_MIDI_INPUT TRUE/FALSE               # Does the plugin need midi input?
    # NEEDS_MIDI_OUTPUT TRUE/FALSE              # Does the plugin need midi output?
    # IS_MIDI_EFFECT TRUE/FALSE                 # Is this plugin a MIDI effect?
    # EDITOR_WANTS_KEYBOARD_FOCUS TRUE/FALSE    # Does the editor need keyboard focus?
    COPY_PLUGIN_AFTER_BUILD TRUE                # Should the plugin be installed to a default location after building?
    PLUGIN_MANUFACTURER_CODE Fktd               # A four-character manufacturer id with at least one upper-case character
    PLUGIN_CODE KAdP                            # A unique four-character plugin id with exactly one upper-case character
                                                # GarageBand 10.3 requires the first letter to be upper-case, and the remaining letters to be lower-case
    FORMATS AU VST3 Standalone                  # The formats to build. Other valid formats are: AAX Unity VST AU AUv3
    PRODUCT_NAME "KadenzeAudioPlugin")        # The name of the final executable, which can differ from the target name
juce_generate_juce_header(KadenzeAudioPlugin)
target_sources(KadenzeAudioPlugin
    PRIVATE
        Editor.cpp
        Processor.cpp
        Parameters.cpp
        components/VuMeter.cpp
        managers/PresetManager.cpp
        ui/CenterPanel.cpp
        ui/CenterPanelMenuBar.cpp
        ui/LookAndFeel.cpp
        ui/FxPanel.cpp
        ui/GainPanel.cpp
        ui/MainPanel.cpp
        ui/PanelBase.cpp
        ui/ParameterComboBox.cpp
        ui/ParameterDial.cpp
        ui/TopPanel.cpp)
target_include_directories(KadenzeAudioPlugin PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
target_compile_definitions(KadenzeAudioPlugin
    PUBLIC
        DONT_SET_USING_JUCE_NAMESPACE=1
        JUCE_MODAL_LOOPS_PERMITTED=1
        # JUCE_WEB_BROWSER and JUCE_USE_CURL would be on by default, but you might not need them.
        JUCE_WEB_BROWSER=0  # If you remove this, add `NEEDS_WEB_BROWSER TRUE` to the `juce_add_plugin` call
        JUCE_USE_CURL=0     # If you remove this, add `NEEDS_CURL TRUE` to the `juce_add_plugin` call
        JUCE_VST3_CAN_REPLACE_VST2=0)
target_link_libraries(KadenzeAudioPlugin
    PRIVATE
        dsp
        ui_assets
        juce::juce_audio_utils
    PUBLIC
        juce::juce_recommended_config_flags
        juce::juce_recommended_lto_flags
        juce::juce_recommended_warning_flags)
