cmake_minimum_required(VERSION 3.28)
project(GraphAlko)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_program(MEMORYCHECK_COMMAND valgrind)
set(MEMORYCHECK_COMMAND_OPTIONS "--trace-children=yes --leak-check=full")


add_compile_options(-fsanitize=address -fsanitize=undefined -g)
add_link_options(-fsanitize=address -fsanitize=undefined -g)


add_library(AllGraph INTERFACE)
target_include_directories(AllGraph INTERFACE ${CMAKE_CURRENT_BINARY_DIR}/headers/)
target_include_directories(AllGraph INTERFACE ${CMAKE_CURRENT_BINARY_DIR}/headers/VisitorsHeaders)
target_include_directories(AllGraph INTERFACE ${CMAKE_CURRENT_BINARY_DIR}/tpp/)

add_library(BaseGraph INTERFACE)
target_sources(BaseGraph INTERFACE /headers/VisitorsHeaders/Visitors.hpp /headers/Edges.hpp /headers/Graph.hpp
        /headers/GraphStorage.hpp /headers/iterators.hpp)
target_include_directories(BaseGraph INTERFACE /tpp/)

add_library(FlowGraph INTERFACE)
target_sources(FlowGraph INTERFACE headers/VisitorsHeaders/FlowVisitors.hpp)
target_link_libraries(FlowGraph INTERFACE BaseGraph)

add_library(LCAGraph INTERFACE)
target_sources(LCAGraph INTERFACE headers/VisitorsHeaders/LCAVisitors.hpp)
target_link_libraries(LCAGraph INTERFACE BaseGraph)

add_library(ShortestPathGraph INTERFACE)
target_sources(ShortestPathGraph INTERFACE headers/VisitorsHeaders/LCAVisitors.hpp)
target_link_libraries(ShortestPathGraph INTERFACE BaseGraph)





add_executable(Test test.cpp)
target_link_libraries(Test PUBLIC AllGraph)



find_package(Doxygen REQUIRED)
set(DOXYFILE_IN ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile.in)

set(DOXYFILE_OUT ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile)

configure_file(${DOXYFILE_IN} ${DOXYFILE_OUT} @ONLY)

add_custom_target(doc_doxygen ALL
        COMMAND ${DOXYGEN_EXECUTABLE} ${DOXYFILE_OUT}
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
        COMMENT "Generating API documentation with Doxygen"
        VERBATIM)

