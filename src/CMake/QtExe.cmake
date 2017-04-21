################################################################################
# Template QtExe
# Created by Ulrich Belitz in Februrary 2017
################################################################################

project(${PROJECT_NAME})

set(CMAKE_INCLUDE_CURRENT_DIR ON)

file(GLOB Headers ${CMAKE_CURRENT_SOURCE_DIR}/*.h)
source_group("Headers" FILES ${Headers})

if(NOT EXISTS ${CMAKE_CURRENT_BINARY_DIR}/generated.cpp)
  file(WRITE ${CMAKE_CURRENT_BINARY_DIR}/generated.cpp "/* file is generated automatically - changes will be overwritten */")
endif()

file(GLOB Sources ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)
list(APPEND Sources ${CMAKE_CURRENT_BINARY_DIR}/generated.cpp)
source_group("Sources" FILES ${Sources})

file(GLOB QtResources ${CMAKE_CURRENT_SOURCE_DIR}/Resources/*.qrc)
file(GLOB WinResources ${CMAKE_CURRENT_SOURCE_DIR}/Resources/*.rc)

set(Resources
  ${QtResources}
  ${WinResources}
)

source_group("Resources" FILES ${Resources})

file(GLOB Forms ${CMAKE_CURRENT_SOURCE_DIR}/*.ui)
source_group("Forms" FILES ${Forms})

file(GLOB Information ${CMAKE_CURRENT_SOURCE_DIR}/*.md)
source_group("Information" FILES ${Information})

set(AllSources
  ${Generated}
  ${Headers}
  ${Sources}
  ${Resources}
  ${Forms}
  ${Information}
)

if ("${EXE_TYPE}" STREQUAL  "Console")
  add_executable(${PROJECT_NAME} ${AllSources})
else()
  add_executable(${PROJECT_NAME} WIN32 ${AllSources})
endif()

target_link_libraries(${PROJECT_NAME}
  Shared
  ${QtLinkLibraries}
  ${RequiredLibraries}
)

add_dependencies(${PROJECT_NAME} QtBuildHelper)

add_custom_command(TARGET ${PROJECT_NAME} PRE_BUILD COMMAND QtBuildHelper.exe ARGS -id ${CMAKE_CURRENT_SOURCE_DIR} -ed ${CMAKE_CURRENT_SOURCE_DIR}/Resources/Templates -od ${CMAKE_CURRENT_BINARY_DIR} -qbd ${QtBinDir} -qid ${QtIncludeDir} WORKING_DIRECTORY ${QtBuilderWorkingDir})