cmake_minimum_required(VERSION 3.3)
project(plog)
#project(clingo)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Wall")

file(GLOB_RECURSE PLOG_SOURCES
        clingo/liblp/src/*.cpp
        clingo/libclingo/src/*.cc
        clingo/libgringo/src/*.cc
        clingo/libgringo/src/input/nongroundgrammar/*.cc
        clingo/libclasp/src/*.cpp
        clingo/libprogram_opts/src/*.cpp
        clingo/libreify/src/*.cc
        libgroundplog/src/*.cpp
        plogapp/src/*.cpp
        plogapp/src/*.cc
        libplog/*.cpp
        libplog/*.cc
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
set(PLOG_SOURCE_FILES plogapp/src/main.cpp  libgroundplog/groundplog/program.h libgroundplog/groundplog/groundplog_facade.h libgroundplog/groundplog/solver_strategies.h libgroundplog/groundplog/program_types.h libgroundplog/groundplog/rule_utils.h libgroundplog/groundplog/solver_types.h libplog/plog/plog.h  libgroundplog/src/groundplog_options.cpp libgroundplog/src/groundplog_facade.cpp libgroundplog/src/solver_strategies.cpp libgroundplog/groundplog/solve_algorithms.h libgroundplog/src/program.cpp libgroundplog/src/rule_utils.cpp libgroundplog/src/solve_algorithms.cpp libgroundplog/src/program_types.cpp libplog/src/plogparser.cpp libplog/src/program.cpp libplog/src/plogoutput.cpp libplog/src/programbuilder.cpp libplog/src/term.cpp libplog/src/attributedeclaration.cpp libplog/src/sortdefinition.cpp libplog/src/literal.cpp libplog/src/statement.cpp libplog/src/probability.cpp libplog/src/grprogamobs.cpp libplog/src/utils.cpp libgroundplog/groundplog/solvingres.h libgroundplog/src/dependency_graph.cpp libgroundplog/src/interpretation.cpp libgroundplog/groundplog/interpretation.h)
set(CLINGO_SOURCE_FILES    clingo/app/clingo/src/main.cc  clingo/app/clingo/src/clingo_app.cc libplog/plog/input/sortdefinition.h libplog/plog/input/attributedeclaration.h libplog/plog/literal.h clingo/examples/cpp/control.cpp libplog/plog/grprogramobs.h clingo/examples/cpp/groundobs.cpp libplog/plog/input/utils.h libgroundplog/src/attribute_selection_heuristic.cpp libgroundplog/groundplog/attribute_selection_heuristic.h libgroundplog/src/value_selection_heuristic.cpp libgroundplog/groundplog/value_selection_heuristic.h)
set(EXAMPLE clingo/examples/cpp/groundobs.cpp)

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
TARGET_LINK_LIBRARIES(clingo  python2.7 tbb pthread dl)

add_executable(plog1 ${PLOG_SOURCE_FILES} ${PLOG_SOURCES} libplog/src/sortexpression.cpp libplog/plog/sortexpression.h libgroundplog/groundplog/solvingres.h libgroundplog/src/interpretation.cpp libgroundplog/groundplog/interpretation.h)
TARGET_LINK_LIBRARIES(plog1  python2.7 tbb pthread dl)

add_executable(ex ${EXAMPLE} ${CLINGO_SOURCES})
TARGET_LINK_LIBRARIES(ex  python2.7 tbb pthread dl)
