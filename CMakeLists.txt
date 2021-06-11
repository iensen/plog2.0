# Run cmake DBUILD_TESTS=1 . to build tests.
# Run cmake . to build the actual P-log executable.
# If you need to switch between the two modes, make sure to 
# remove CmakeCache.txt file between runs.

cmake_minimum_required(VERSION 3.3)
#set(BUILD_TESTS 1)
if(BUILD_TESTS)
project(tests)
else()
project(plog)
endif(BUILD_TESTS)

set(CMAKE_BUILD_TYPE Release)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -O3")
#set(CMAKE_BUILD_TYPE Debug)
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -pg")
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

get_filename_component(full_path_Plog_cpp ${CMAKE_CURRENT_SOURCE_DIR}/oldplog/Plog.cpp ABSOLUTE)
list(REMOVE_ITEM OLD_PLOG_SOURCES "${full_path_Plog_cpp}")




file(GLOB_RECURSE CLINGO_SOURCES
        clingo/liblp/src/*.cpp
        clingo/libclingo/src/*.cc
        clingo/libgringo/src/*.cc
        clingo/clasp/src/*.cpp
        clingo/clasp/app/clasp_app.cpp
        clingo/clasp/libpotassco/src/*.cpp
        clingo/libreify/src/*.cc
        clingo/libclasp/src/*.cpp
        clingo/app/clingo/src/*.cpp
        clingo/app/clingo/src/clingo_app.cc
        )


file(GLOB_RECURSE TEST_SOURCES
          test/*.cpp
        )


include_directories(clingo/clasp)
include_directories(clingo/clasp/app)
include_directories(clingo/clasp/libpotassco)
include_directories(clingo/liblp)
include_directories(clingo/libclingo)
include_directories(clingo/libgringo)
include_directories(clingo/libgringo/src)
include_directories(clingo/libprogram_opts)
include_directories(clingo/libreify)
include_directories(libgroundplog)
include_directories(libplog)
include_directories(oldplog)

set(CLINGO_MAIN_FILE  clingo/app/clingo/src/main.cc libgroundplog/groundplog/state.h)
set(PLOG_MAIN_FILE    plogapp/src/main.cpp libgroundplog/src/state.cpp)
set(OLDPLOG_MAIN_FILE    oldplog/Plog.cpp)
set(EXAMPLE_MAIN_FILE clingo/examples/cpp/groundobs.cpp)

#add_executable(clingo1 ${CLINGO_MAIN_FILE} ${CLINGO_SOURCES})
#TARGET_LINK_LIBRARIES(clingo1  pthread dl)

if(BUILD_TESTS)
add_executable(tests   ${OLD_PLOG_SOURCES} ${TEST_SOURCES} ${PLOG_SOURCES} ${CLINGO_SOURCES}   test/utils.h)
TARGET_LINK_LIBRARIES(tests  gtest pthread)
else()
add_executable(plog2  ${PLOG_SOURCES} ${CLINGO_SOURCES} ${PLOG_MAIN_FILE})
TARGET_LINK_LIBRARIES(plog2  pthread)
endif(BUILD_TESTS)

#add_executable(ex ${EXAMPLE_MAIN_FILE} ${CLINGO_SOURCES})
#TARGET_LINK_LIBRARIES(ex   pthread dl)

#add_executable(wplog ${OLD_PLOG_SOURCES} ${OLDPLOG_MAIN_FILE})


