add_subdirectory(QSliderX)

include(qt-value-slider.cmake)

# add it ony if it has not being added before by any other dependency
if(NOT TARGET nlohmann_json)
    add_subdirectory(json)
endif()

if (NOT TARGET highmap)
    set(HIGHMAP_ENABLE_DOCS OFF)
    set(HIGHMAP_ENABLE_EXAMPLES OFF)
    set(HIGHMAP_ENABLE_TESTS OFF)
    add_subdirectory(HighMap)
endif()