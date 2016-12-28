cmake_minimum_required(VERSION 3.3)
project(plog)
#project(clingo)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Wall")

file(GLOB_RECURSE PLOG_SOURCES
        libgroundplog/src/*.cpp
        plogapp/src/plog_app.cpp
        libplog/src/*.cpp
        libplog/src/*.cc
        plogapp/src/groundplog/groundplog_app.cpp
        )

file(GLOB_RECURSE OLD_PLOG_SOURCES
        oldplog/*.cpp
        )





file(GLOB_RECURSE CLINGO_SOURCES
        clingo/liblp/src/*.cpp
        clingo/libclingo/src/*.cc
        clingo/libgringo/src/*.cc
        clingo/libclasp/src/*.cpp
        clingo/libprogram_opts/src/*.cpp
        clingo/libreify/src/*.cc
        clingo/libclasp/src/*.cpp
        clingo/app/clingo/src/*.cpp
        clingo/app/clingo/src/clingo_app.cc
        )


file(GLOB_RECURSE TEST_SOURCES
          test/tests.cpp
        )


include_directories(clingo/libclasp)
include_directories(clingo/liblp)
include_directories(clingo/libclingo)
include_directories(clingo/libgringo)
include_directories(clingo/libgringo/src)
include_directories(clingo/libprogram_opts)
include_directories(clingo/libreify)
include_directories(libgroundplog)
include_directories(libplog)
include_directories(oldplog)
include_directories(/usr/include/python2.7)



set(CLINGO_MAIN_FILE  clingo/app/clingo/src/main.cc)
set(PLOG_MAIN_FILE    plogapp/src/main.cpp)
set(EXAMPLE_MAIN_FILE clingo/examples/cpp/groundobs.cpp)

add_definitions(-DWITH_THREADS=1)
add_definitions(-DWITH_PYTHON)



add_executable(clingo ${CLINGO_MAIN_FILE} ${CLINGO_SOURCES})
TARGET_LINK_LIBRARIES(clingo  python2.7 tbb pthread dl)

add_executable(plog1  ${PLOG_SOURCES} ${CLINGO_SOURCES} ${PLOG_MAIN_FILE})
TARGET_LINK_LIBRARIES(plog1  python2.7 tbb pthread dl)

add_executable(ex ${EXAMPLE_MAIN_FILE} ${CLINGO_SOURCES})
TARGET_LINK_LIBRARIES(ex  python2.7 tbb pthread dl)

add_executable(tests   ${OLD_PLOG_SOURCES} ${TEST_SOURCES} ${PLOG_SOURCES} ${CLINGO_SOURCES}   test/utils.h)
TARGET_LINK_LIBRARIES(tests  python2.7 tbb dl gtest pthread )
