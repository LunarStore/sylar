cmake_minimum_required(VERSION 3.1)

project(Lunar)

find_package(yaml-cpp REQUIRED)

find_library(pthread-lib pthread)

include_directories(${YAML_CPP_INCLUDE_DIR})

include_directories(./src)

set(LIB_LIST ${pthread-lib} dl)

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)

set(SRC_LIST
    src/base/log.cc
    src/base/util.cc
    src/base/config.cc
    src/base/thread.cc
    src/base/mutex.cc
    src/base/fiber.cc
    src/base/scheduler.cc
    src/base/iomanager.cc
    src/base/timer.cc
    src/base/fdmanager.cc
    src/base/hook.cc
    src/net/address.cc
    src/net/socket.cc
    src/net/socket.cc
    src/net/stream.cc
    src/net/socketstream.cc
    src/net/bytearray.cc
    src/http/http.cc
    src/http/httpparser.cc
    src/http/httpsession.cc
    src/http/http11_parser.rl.cc
    src/http/httpclient_parser.rl.cc
    src/net/tcpserver.cc
    src/http/httpserver.cc
    src/http/servlet.cc
    src/init/daemon.cc
    src/init/env.cc
    src/init/application.cc
    src/base/worker.cc
    src/init/module.cc
    src/init/library.cc
    src/base/worker.cc)
message(STATUS "-----SRC_LIST:${SRC_LIST}-----LIB_LIST:${LIB_LIST}")
add_compile_options(-std=c++11 -Wall -g)

set (LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)
add_library (lunarLib SHARED ${SRC_LIST})
set_target_properties (lunarLib PROPERTIES OUTPUT_NAME "lunarLib")
target_link_libraries(lunarLib yaml-cpp ${LIB_LIST})

add_executable(test_log tests/test_log.cc ${SRC_LIST})
target_link_libraries(test_log yaml-cpp ${LIB_LIST})

add_executable(test_config tests/test_config.cc ${SRC_LIST})
target_link_libraries(test_config yaml-cpp ${LIB_LIST})

add_executable(test_thread tests/test_thread.cc ${SRC_LIST})
target_link_libraries(test_thread yaml-cpp ${LIB_LIST})

add_executable(test_fiber tests/test_fiber.cc ${SRC_LIST})
target_link_libraries(test_fiber yaml-cpp ${LIB_LIST})

add_executable(test_scheduler tests/test_scheduler.cc ${SRC_LIST})
target_link_libraries(test_scheduler yaml-cpp ${LIB_LIST})

add_executable(test_iomanager tests/test_iomanager.cc ${SRC_LIST})
target_link_libraries(test_iomanager yaml-cpp ${LIB_LIST})

add_executable(test_hook tests/test_hook.cc ${SRC_LIST})
target_link_libraries(test_hook yaml-cpp ${LIB_LIST})

add_executable(test_address tests/test_address.cc ${SRC_LIST})
target_link_libraries(test_address yaml-cpp ${LIB_LIST})

add_executable(test_socket tests/test_socket.cc ${SRC_LIST})
target_link_libraries(test_socket yaml-cpp ${LIB_LIST})

add_executable(test_tcpserver tests/test_tcpserver.cc ${SRC_LIST})
target_link_libraries(test_tcpserver yaml-cpp ${LIB_LIST})

add_executable(test_httpparser tests/test_httpparser.cc ${SRC_LIST})
target_link_libraries(test_httpparser yaml-cpp ${LIB_LIST})

add_executable(test_httpserver tests/test_httpserver.cc ${SRC_LIST})
target_link_libraries(test_httpserver yaml-cpp ${LIB_LIST})

add_executable(test_daemon tests/test_daemon.cc ${SRC_LIST})
target_link_libraries(test_daemon yaml-cpp ${LIB_LIST})

add_executable(test_application tests/test_application.cc ${SRC_LIST})
target_link_libraries(test_application yaml-cpp ${LIB_LIST})