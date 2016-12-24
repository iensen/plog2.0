cmake_minimum_required(VERSION 2.8)


project(Plog CXX)

include_directories(".")



add_executable(plog
    Plog.cpp
    AnswerSet.cpp
    Attribute.cpp
    Formula.cpp
    GroundLiteral.cpp
    GroundProgram.cpp
    GroundRule.cpp
    GroundTerm.cpp
    Grounder.cpp
    Literal.cpp
    Parse.cpp
    Program.cpp
    Query.cpp
    RandomRule.cpp
    Rule.cpp
    Sort.cpp
    State.cpp
    TermTree.cpp
    TrEngine.cpp
    Variable.cpp
    global.cpp
    pgEngine.cpp
)


install(TARGETS plog DESTINATION bin)
