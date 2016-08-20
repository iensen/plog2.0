cmake_minimum_required(VERSION 3.3)
project(plog)
#project(clingo)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

file(GLOB_RECURSE PLOG_SOURCES
        clingo/liblp/src/*.cpp
        clingo/libclingo/src/*.cc
        clingo/libgringo/src/*.cc
        clingo/libclasp/src/*.cpp
        clingo/libprogram_opts/src/*.cpp
        clingo/libreify/src/*.cc
        libgroundplog/src/*.cpp
        plogapp/src/*.cpp
        libplog/*.cpp
        )


file(GLOB_RECURSE CLINGO_SOURCES
        clingo/liblp/src/*.cpp
        clingo/libclingo/src/*.cc
        clingo/libgringo/src/*.cc
        clingo/libclasp/src/*.cpp
        clingo/libprogram_opts/src/*.cpp
        clingo/libreify/src/*.cc
        clingo/libclasp/src/*.cpp
        clingo/app/clingo/src/*.cc
        clingo/app/clingo/src/*.cpp
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
include_directories(/usr/include/python2.7)


#link_directories(clingo/build/release/)


#set(SOURCE_FILES main.cpp clingo/app/plog/src/main.cpp clingo/app/plog/src/plog_app.cpp clingo/app/plog/src/plog_app.h clingo/app/plog/src/groundplog/grndplog_app.cpp clingo/app/plog/src/groundplog/grndplog_app.h)
set(PLOG_SOURCE_FILES plogapp/src/main.cpp  libgroundplog/groundplog/program.h libgroundplog/groundplog/groundplog_facade.h libgroundplog/groundplog/solver_strategies.h libgroundplog/groundplog/shared_context.h libgroundplog/groundplog/program_types.h libgroundplog/groundplog/rule_utils.h libgroundplog/groundplog/solver_types.h libplog/plog/plog.h libgroundplog/src/shared_context.cpp libgroundplog/src/groundplog_facade.cpp libgroundplog/src/solver_strategies.cpp)
set(CLINGO_SOURCE_FILES clingo/app/clingo/src/main.cc )

#set(SOURCE_FILES plogapp/src/main.cpp)

#TARGET_LINK_LIBRARIES(plog ${PROJECT_SOURCE_DIR}/clingo/build/release/liblp.a)
#TARGET_LINK_LIBRARIES(plog ${PROJECT_SOURCE_DIR}/clingo/build/release/libgringo.a)
#TARGET_LINK_LIBRARIES(plog ${PROJECT_SOURCE_DIR}/clingo/build/release/libclingo.a)
#TARGET_LINK_LIBRARIES(plog ${PROJECT_SOURCE_DIR}/clingo/build/release/libreify.a)
##TARGET_LINK_LIBRARIES(plog ${PROJECT_SOURCE_DIR}/clingo/build/release/libclasp.a)
#TARGET_LINK_LIBRARIES(plog ${PROJECT_SOURCE_DIR}/clingo/build/release/libprogram_opts.a)

add_definitions(-DWITH_THREADS=1)
add_definitions(-DWITH_PYTHON)






add_executable(clingo ${CLINGO_SOURCE_FILES} ${CLINGO_SOURCES})
TARGET_LINK_LIBRARIES(clingo lua python2.7 tbb pthread dl)

add_executable(plog ${PLOG_SOURCE_FILES} ${PLOG_SOURCES})
TARGET_LINK_LIBRARIES(plog lua python2.7 tbb pthread dl)
