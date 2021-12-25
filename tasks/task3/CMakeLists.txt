add_library(${PROJECT_NAME}_task3 STATIC src/mission_context.cpp src/movement_type.cpp src/depth_type.cpp
        src/mission.cpp src/state.cpp src/mission_storage.cpp src/mission_cli.cpp)
target_include_directories(${PROJECT_NAME}_task3 PUBLIC include)
target_link_libraries(${PROJECT_NAME}_task3 PUBLIC fmt nlohmann_json)

add_executable(${PROJECT_NAME}_task3_exec src/main.cpp)
target_link_libraries(${PROJECT_NAME}_task3_exec PRIVATE ${PROJECT_NAME}_task3)
