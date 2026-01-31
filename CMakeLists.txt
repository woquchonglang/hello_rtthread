cmake_minimum_required(VERSION 3.24)

set(CMAKE_EXPORT_COMPILE_COMMANDS TRUE)
set(CMAKE_PROJECT_NAME hello_rtthread)

include(bsp/gcc-arm-none-eabi.cmake)

project(${CMAKE_PROJECT_NAME})

enable_language(C CXX ASM)

add_compile_options($<$<C_COMPILER_ID:GNU>:-fdiagnostics-color=always>)
add_compile_options($<$<CXX_COMPILER_ID:GNU>:-fdiagnostics-color=always>)

add_executable(${CMAKE_PROJECT_NAME})

# bsp
add_subdirectory(bsp/cmake/stm32cubemx)
list(REMOVE_ITEM CMAKE_C_IMPLICIT_LINK_LIBRARIES ob)
target_link_libraries(${CMAKE_PROJECT_NAME} stm32cubemx)

# rtthread
add_library(rtthread STATIC)
file(GLOB_RECURSE SRCFILES "rtthread-nano/rt-thread/src/*.c"
  "rtthread-nano/rt-thread/libcpu/arm/cortex-m4/context_gcc.S"
  "rtthread-nano/rt-thread/libcpu/arm/cortex-m4/cpuport.c")
target_sources(rtthread PRIVATE ${SRCFILES})
target_include_directories(rtthread PUBLIC "rtthread-nano/rt-thread/include" "src/config")
target_compile_options(rtthread PRIVATE -Wno-unused-variable)
target_link_libraries(${CMAKE_PROJECT_NAME} rtthread)

# user
file(GLOB_RECURSE SRCFILES "src/*.cpp" "src/*.c")
target_sources(${CMAKE_PROJECT_NAME} PRIVATE ${SRCFILES})

target_include_directories(${CMAKE_PROJECT_NAME} PUBLIC "src")
