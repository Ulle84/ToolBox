cmake_minimum_required(VERSION 2.8.11)

set (ProjectName ConsoleApplication)

project(${ProjectName})

file(GLOB Sources ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)
source_group("Sources" FILES ${Sources})

file(GLOB Headers ${CMAKE_CURRENT_SOURCE_DIR}/*.h)
source_group("Headers" FILES ${Headers})

file(GLOB Information ${CMAKE_CURRENT_SOURCE_DIR}/*.md)
source_group("Information" FILES ${Information})

set(AllSources
  ${Headers}
  ${Information}
  ${Sources}
)

add_executable(${ProjectName} ${AllSources})

set_target_properties(${ProjectName} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)