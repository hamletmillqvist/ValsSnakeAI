cmake_minimum_required(VERSION 3.20.0)

project(VSAI VERSION 0.1)

set(CMAKE_CXX_STANDARD )
set(CMAKE_CSS_STANDARD_REQUIRED ON)

add_subdirectory(source)
target_include_directories(vsai_exe PUBLIC ${PROJECT_SOURCE_DIR}/include)
set_target_properties(vsai_exe PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/out/bin)
