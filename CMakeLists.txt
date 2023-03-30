cmake_minimum_required(VERSION 3.0.0)
project(ProjectUI VERSION 0.1.0)

include(CTest)
enable_testing()

add_executable(ProjectUI main.cpp)

add_subdirectory(external/raylib)
# add_subdirectory(Function)
add_subdirectory(UI)

target_include_directories(${PROJECT_NAME} 
    PUBLIC external/raylib/src
    PUBLIC UI
    # PUBLIC Function
)

link_directories(${PROJECT_NAME} 
    PRIVATE external/raylib/src
    # PRIVATE func
    PRIVATE UI
)

target_link_libraries(${PROJECT_NAME} 
    raylib
    # func
    ui
)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ..)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)