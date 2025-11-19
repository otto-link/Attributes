add_subdirectory(QSliderX)

if (NOT TARGET highmap)
    set(HIGHMAP_ENABLE_DOCS OFF)
    set(HIGHMAP_ENABLE_EXAMPLES OFF)
    set(HIGHMAP_ENABLE_TESTS OFF)
    add_subdirectory(HighMap)
endif()
