cmake_minimum_required (VERSION 2.8)

project ("categorizer")

file(GLOB sources "src/*.cpp")

add_executable(categorizer ${sources})

target_include_directories(categorizer PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)