################################################################################
# QtDll
# Created by Ulrich Belitz in Februrary 2017
################################################################################

project(${PROJECT_NAME})

set(CMAKE_INCLUDE_CURRENT_DIR ON)

file(GLOB_RECURSE Headers ${CMAKE_CURRENT_SOURCE_DIR}/*.h)
source_group("Headers" FILES ${Headers})

if(NOT EXISTS ${CMAKE_CURRENT_BINARY_DIR}/generated.cpp)
  file(WRITE ${CMAKE_CURRENT_BINARY_DIR}/generated.cpp "/* file is generated automatically - changes will be overwritten */")
endif()

file(GLOB Sources ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)
list(APPEND Sources ${CMAKE_CURRENT_BINARY_DIR}/generated.cpp)
source_group("Sources" FILES ${Sources})


file(GLOB WinResources ${CMAKE_CURRENT_SOURCE_DIR}/*.rc)

set(Resources
  ${WinResources}
)

source_group("Resources" FILES ${Resources})

file(GLOB Forms ${CMAKE_CURRENT_SOURCE_DIR}/*.ui)
source_group("Forms" FILES ${Forms})

file(GLOB Information ${CMAKE_CURRENT_SOURCE_DIR}/*.json)
source_group("Information" FILES ${Information})

set(AllSources
  ${Headers}
  ${Sources}
  ${Resources}
  ${Forms}
  ${Information}
)

add_library(${PROJECT_NAME} SHARED ${AllSources})

target_link_libraries(${PROJECT_NAME}
  Shared
  ${QtLinkLibraries}
  ${RequiredLibraries}
)

add_dependencies(${PROJECT_NAME} QtBuildHelper)

string(TOUPPER ${PROJECT_NAME} PROJECT_NAME_UPPERCASED)
set_property(TARGET ${PROJECT_NAME} APPEND PROPERTY COMPILE_DEFINITIONS
  ${PROJECT_NAME_UPPERCASED}_EXPORT
  _USRDLL
  _WINDOWS
)

target_include_directories(${PROJECT_NAME} PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/API")

set_target_properties(${PROJECT_NAME} PROPERTIES FOLDER Widgets)

add_custom_command(TARGET ${PROJECT_NAME} PRE_BUILD COMMAND QtBuildHelper.exe ARGS -id ${CMAKE_CURRENT_SOURCE_DIR} -ed ${CMAKE_CURRENT_SOURCE_DIR}/Resources/Templates -od ${CMAKE_CURRENT_BINARY_DIR} -qbd ${QtBinDir} -qid ${QtIncludeDir} WORKING_DIRECTORY ${QtBuilderWorkingDir})