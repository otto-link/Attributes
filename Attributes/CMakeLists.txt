project(attributes)

# Qt6
set(CMAKE_AUTOMOC ON)

# --- sources GUI headers need to be added in add_executable, otherwise the moc
# won't parse them
file(GLOB_RECURSE ATTR_GUI_INCLUDES
     ${CMAKE_CURRENT_SOURCE_DIR}/include/attributes/*.hpp)

file(GLOB_RECURSE ATTR_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp)

add_library(${PROJECT_NAME} STATIC ${ATTR_SOURCES} ${ATTR_GUI_INCLUDES})

set(ATTR_INCLUDE
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${CMAKE_CURRENT_SOURCE_DIR}/../external/qt-value-slider/include PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/../external/json/include)

target_include_directories(${PROJECT_NAME} PUBLIC ${ATTR_INCLUDE})

# --- Link libraries
target_link_libraries(
  ${PROJECT_NAME}
  spdlog::spdlog
  nlohmann_json::nlohmann_json
  Qt6::Core
  Qt6::Widgets
  valueSliders
  highmap)
