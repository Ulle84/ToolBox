cmake_minimum_required(VERSION 2.8.11)

set(ProjectName QtBuildHelper)

project(${ProjectName})

file(GLOB Sources ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)
source_group("Sources" FILES ${Sources})

file(GLOB Headers ${CMAKE_CURRENT_SOURCE_DIR}/*.h)
source_group("Headers" FILES ${Headers})

set(AllSources
  ${Headers}
  ${Sources}
)

add_executable(${ProjectName} ${AllSources})

target_link_libraries(${ProjectName} ${QtLinkLibraries})

set_target_properties(${ProjectName} PROPERTIES FOLDER ConsoleApplications)