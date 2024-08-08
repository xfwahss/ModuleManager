cmake_minimum_required(VERSION 3.26)
project("ModuleManager")
set(CMAKE_EXPORT_COMPILE_COMMANDS ON) # 生成compile_commands.json文件
set(CMAKE_CXX_STANDARD 17)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/bin)
set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR}/lib)
set( CMAKE_BUILD_TYPE "Debug" )

add_library(basesample SHARED module/src/BaseSample.cc)

add_executable(test test/TestManager.cc)
target_include_directories(test PUBLIC include)