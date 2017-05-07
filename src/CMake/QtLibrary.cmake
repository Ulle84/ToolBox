################################################################################
# QtDll
# Created by Ulrich Belitz in Februrary 2017
################################################################################

project(${ProjectName})

set(CMAKE_INCLUDE_CURRENT_DIR ON)

file(GLOB_RECURSE Headers ${CMAKE_CURRENT_SOURCE_DIR}/*.h)
source_group("Headers" FILES ${Headers})

if(NOT EXISTS ${CMAKE_CURRENT_BINARY_DIR}/generated.cpp)
  file(WRITE ${CMAKE_CURRENT_BINARY_DIR}/generated.cpp "/* file is generated automatically - changes will be overwritten */")
endif()

file(GLOB_RECURSE Sources ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)
list(APPEND Sources ${CMAKE_CURRENT_BINARY_DIR}/generated.cpp)
source_group("Sources" FILES ${Sources})


file(GLOB_RECURSE WinResources ${CMAKE_CURRENT_SOURCE_DIR}/*.rc)
file(GLOB_RECURSE QtResources ${CMAKE_CURRENT_SOURCE_DIR}/*.qrc)

set(Resources
  ${WinResources}
  ${QtResources}
)

source_group("Resources" FILES ${Resources})

file(GLOB_RECURSE Forms ${CMAKE_CURRENT_SOURCE_DIR}/*.ui)
source_group("Forms" FILES ${Forms})

file(GLOB_RECURSE Configuration ${CMAKE_CURRENT_SOURCE_DIR}/*.xml)
source_group("Configuration" FILES ${Configuration})

file(GLOB_RECURSE StyleSheets ${CMAKE_CURRENT_SOURCE_DIR}/*.css)
source_group("StyleSheets" FILES ${StyleSheets})

set(AllSources
  ${Headers}
  ${Sources}
  ${Resources}
  ${Forms}
  ${Configuration}
  ${StyleSheets}
)

add_library(${ProjectName} SHARED ${AllSources})

target_link_libraries(${ProjectName}
  ${QtLinkLibraries}
  ${RequiredLibraries}
)

add_dependencies(${ProjectName} QtBuildHelper)

string(TOUPPER ${ProjectName} ProjectNameUppercased)
set_property(TARGET ${ProjectName} APPEND PROPERTY COMPILE_DEFINITIONS
  ${ProjectNameUppercased}_EXPORT
  _USRDLL
  _WINDOWS
)

target_include_directories(${ProjectName} PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/API")

if ("${FolderName}" STREQUAL  "")
  set(FolderName Widgets)
endif()

set_target_properties(${ProjectName} PROPERTIES FOLDER ${FolderName})

add_custom_command(TARGET ${ProjectName} PRE_BUILD COMMAND QtBuildHelper.exe ARGS -id ${CMAKE_CURRENT_SOURCE_DIR} -ed ${CMAKE_CURRENT_SOURCE_DIR}/Resources/Templates -od ${CMAKE_CURRENT_BINARY_DIR} -qbd ${QtBinDir} -qid ${QtIncludeDir} WORKING_DIRECTORY ${QtBuilderWorkingDir})