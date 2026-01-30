cmake_minimum_required(VERSION 3.10)
project(MatrixCalcTool LANGUAGES C)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -O3 -g -fPIC -Wall -Wextra")

include_directories(include)

find_package(Python3 REQUIRED COMPONENTS Development)

add_library(matrix_core SHARED src/matrix.c)
target_link_libraries(matrix_core m)

add_library(mtools_wrapper MODULE wrapper/mtools_wrapper.c)
target_include_directories(mtools_wrapper PRIVATE ${Python3_INCLUDE_DIRS})
target_link_libraries(mtools_wrapper PRIVATE matrix_core Python3::Python)

set_target_properties(mtools_wrapper PROPERTIES PREFIX "" OUTPUT_NAME "MTools")

add_executable(matrix_tool src/main.c)
target_link_libraries(matrix_tool matrix_core m)

add_executable(unittest test/test_matrix.c test/test_main.c)
target_link_libraries(unittest matrix_core m)