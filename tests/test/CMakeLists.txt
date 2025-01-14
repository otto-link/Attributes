add_executable(test_attr main.cpp)
target_link_libraries(test_attr attributes Qt6::Core Qt6::Widgets valueSliders nlohmann_json::nlohmann_json)
