project(valueSliders)

set(QTV_DIR ${CMAKE_CURRENT_SOURCE_DIR}/qt-value-slider)

find_package(QT NAMES Qt5 Qt6 REQUIRED COMPONENTS Core)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)
set(CMAKE_AUTOMOC ON)

add_library(${PROJECT_NAME} STATIC
        ${QTV_DIR}/include/doubleslider.hpp
        ${QTV_DIR}/include/intslider.hpp
        ${QTV_DIR}/include/valueslider.hpp
        ${QTV_DIR}/src/doubleslider.cpp
        ${QTV_DIR}/src/intslider.cpp
        ${QTV_DIR}/src/valueslider.cpp
)

target_link_libraries(${PROJECT_NAME} PRIVATE
        Qt::Core
        Qt::Widgets
)

target_include_directories(${PROJECT_NAME} PUBLIC
        ${QTV_DIR}/src/
        ${QTV_DIR}/include/
)