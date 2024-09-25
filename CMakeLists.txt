cmake_minimum_required(VERSION 3.10)
project(attributes-root VERSION 0.0.0)

set(ATTRIBUTES_ENABLE_TESTS ON)

set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/bin)

if(CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
  # MSVC compiler options
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4 /Od")
else()
  # GNU compiler options
  set(CMAKE_CXX_FLAGS
      "${CMAKE_CXX_FLAGS} -g -Wall -Wextra -Wno-dangling-reference -O3 -pthread"
  )
endif()

set(CMAKE_CXX_STANDARD 20)

# ---  dependenciesù
find_package(spdlog REQUIRED)
find_package(Qt6 REQUIRED COMPONENTS Core Widgets)

add_subdirectory(external)
add_subdirectory(Attributes)

if(ATTRIBUTES_ENABLE_TESTS)
  add_subdirectory(tests)
endif()
