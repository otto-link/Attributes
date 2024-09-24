add_executable(test_attributes_widget main.cpp)
target_link_libraries(test_attributes_widget attributes Qt6::Core Qt6::Widgets valueSliders nlohmann_json::nlohmann_json)
