cmake_minimum_required(VERSION 3.10)
project(AStar)
set(CMAKE_CXX_STANDARD 20)
# set(CMAKE_CXX_STANDARD_REQUIRED ON)

file(GLOB_RECURSE MY_SOURCES CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")

add_executable(${PROJECT_NAME} ${MY_SOURCES})

target_include_directories(${PROJECT_NAME} PRIVATE
    "${CMAKE_CURRENT_SOURCE_DIR}/include"
)

find_package(SFML COMPONENTS system window graphics audio CONFIG REQUIRED)
find_package(imgui CONFIG REQUIRED)
find_package(ImGui-SFML CONFIG REQUIRED)

target_link_libraries(${PROJECT_NAME} PRIVATE
    imgui::imgui
    sfml-system 
    sfml-network 
    sfml-graphics 
    sfml-window 
    sfml-audio
    ImGui-SFML::ImGui-SFML
)