cmake_minimum_required(VERSION 3.3.2)

set(ProjectName Shared)

set(FolderName Shared)

set(RequiredLibraries
  SharedResources
)

include(../CMake/QtLibrary.cmake)

#string(TOUPPER ${ProjectName} ProjectName_UPPERCASED)
#
#project(${ProjectName})
#
#file(GLOB_RECURSE Headers ${CMAKE_CURRENT_SOURCE_DIR}/*.h)
#source_group("Headers" FILES ${Headers})
#
#file(GLOB Sources ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)
#source_group("Sources" FILES ${Sources})
#
#set(Resources ${CMAKE_CURRENT_SOURCE_DIR}/${ProjectName}.rc)
#source_group("Resources" FILES ${Resources})
#
#set(AllSources
#  ${Sources}
#  ${Headers}
#  ${Resources}
#)
#
#include_directories(
#  ${CMAKE_CURRENT_SOURCE_DIR}
#  ${CMAKE_CURRENT_SOURCE_DIR}/API
#)
#
#add_library(${ProjectName} SHARED ${AllSources})
#
#target_include_directories(${ProjectName} PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/API")
#
#set_property(TARGET ${ProjectName} APPEND PROPERTY COMPILE_DEFINITIONS
#  ${ProjectName_UPPERCASED}_EXPORT
#  _USRDLL
#  _WINDOWS
#)
#
#if(MSVC)
#  set_property(TARGET ${ProjectName} APPEND PROPERTY COMPILE_FLAGS /MP)
#endif(MSVC)
#
#target_link_libraries(${ProjectName}
#  SharedResources
#  ${QtLinkLibraries}
#)
#
#set_target_properties(${ProjectName} PROPERTIES FOLDER Miscellaneous)