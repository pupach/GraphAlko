cmake_minimum_required(VERSION 3.28)
project(GraphAlko)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_program( MEMORYCHECK_COMMAND valgrind )
set( MEMORYCHECK_COMMAND_OPTIONS "--trace-children=yes --leak-check=full" )

# Убираем флаг -std=c++20, так как стандарт уже задаётся через CMAKE_CXX_STANDARD
add_compile_options(-fsanitize=address -fsanitize=undefined -g)
add_link_options(-fsanitize=address -fsanitize=undefined -g)

# Создаём header-only библиотеку для Graph
add_library(Graph INTERFACE)
target_include_directories(Graph INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/headers/)

add_library(FlowGraph INTERFACE)
target_include_directories(FlowGraph INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/headers/)

# Целевая исполняемая программа meow
add_executable(meow main.cpp)
target_include_directories(meow PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/tpp/)
target_link_libraries(meow PUBLIC Graph)

# Целевая исполняемая программа Test
add_executable(Test test.cpp)
target_include_directories(Test PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/tpp/)
target_include_directories(Test PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/tests/)
target_include_directories(Test PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/headers/VisitorsHeaders)
target_link_libraries(Test PUBLIC Graph)