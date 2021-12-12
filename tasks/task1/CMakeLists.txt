add_library(${PROJECT_NAME}_task1 SHARED src/trax_packet.cpp)
target_include_directories(${PROJECT_NAME}_task1 PUBLIC include)
target_link_libraries(${PROJECT_NAME}_task1 PUBLIC fmt)

add_executable(${PROJECT_NAME}_task1_test test/main.cpp)
target_link_libraries(${PROJECT_NAME}_task1_test ${PROJECT_NAME}_task1 gtest_main)

include(GoogleTest)
gtest_discover_tests(${PROJECT_NAME}_task1_test)
