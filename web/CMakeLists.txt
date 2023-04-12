cmake_minimum_required(VERSION 3.1)

project(Web)

find_package(yaml-cpp REQUIRED)

find_library(pthread-lib pthread)

include_directories(${YAML_CPP_INCLUDE_DIR})
include_directories (~/Lunar/src)

set(LIB_LIST ${pthread-lib} dl)
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR})
set (SRC_LIST ${PROJECT_SOURCE_DIR}/index.cc)
add_compile_options(-std=c++11 -Wall -g)

find_library(TESTFUNC_LIB lunarLib HINTS ~/Lunar/lib)



add_executable (main ${SRC_LIST})
target_link_libraries(main yaml-cpp ${LIB_LIST} ${TESTFUNC_LIB})

add_library (out SHARED ${SRC_LIST})

set_target_properties (out PROPERTIES OUTPUT_NAME "webLib")
target_link_libraries(out yaml-cpp ${LIB_LIST} ${TESTFUNC_LIB})
set (LIBRARY_OUTPUT_PATH ~/Lunar/bin/module)