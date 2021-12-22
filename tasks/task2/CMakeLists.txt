add_library(${PROJECT_NAME}_task2 INTERFACE)
target_include_directories(${PROJECT_NAME}_task2 INTERFACE include)

add_executable(${PROJECT_NAME}_task2_test test/main.cpp)
target_link_libraries(${PROJECT_NAME}_task2_test ${PROJECT_NAME}_task2 gtest_main)

include(GoogleTest)
gtest_discover_tests(${PROJECT_NAME}_task2_test)
