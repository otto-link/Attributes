if(ATTR_USE_QT)
    add_subdirectory(qt-value-slider)
endif(ATTR_USE_QT)

# add it ony if it has not being added before by any other dependency
if(NOT TARGET nlohmann_json)
    add_subdirectory(json)
endif()