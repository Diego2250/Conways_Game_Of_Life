cmake_minimum_required(VERSION 3.25)
project(Conways_Game_of_Life)

set(CMAKE_CXX_STANDARD 20)
set(SDL2_INCLUDE_DIR C:/Users/DIEAL/OneDrive/Documents/SDL2-2.28.1/include)
set(SDL2_LIB_DIR C:/Users/DIEAL/OneDrive/Documents/SDL2-2.28.1/lib/x64)

include_directories(${SDL2_INCLUDE_DIR})
link_directories(${SDL2_LIB_DIR})

add_executable(Conways_Game_of_Life src/main.cpp)

target_link_libraries(${PROJECT_NAME} SDL2main SDL2)