cmake_minimum_required(VERSION 3.30)
project("Template")

file(GLOB SOURCES "src/*.cpp")
file(GLOB SOURCES_ADDITIONAL "src/**/*.cpp")
file(GLOB_RECURSE INCLUDE_CPP "include/**/*.cpp")
file(GLOB_RECURSE INCLUDE_C "include/**/*.c")

# Add "include" sources to avoid "undefined references"
message("${SOURCES}")
message("${INCLUDE_CPP}")
message("${INCLUDE_C}")

add_library(target SHARED ${SOURCES} ${SOURCES_ADDITIONAL} ${INCLUDE_CPP} ${INCLUDE_C})

# target_link_directories(target PRIVATE "E:/DirectX SDK/Lib/x64")
# target_link_libraries(target "d3d11.lib" "xinput.lib" "d3dcompiler.lib")

target_include_directories(target PRIVATE include)

set_property(TARGET target PROPERTY CXX_STANDARD 17)