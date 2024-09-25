add_subdirectory(qt-value-slider)

# add it ony if it has not being added before by any other dependency
if(NOT TARGET nlohmann_json)
    add_subdirectory(json)
endif()