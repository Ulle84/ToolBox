cmake_minimum_required(VERSION 3.3.2)

set(DLL_NAME Template)
string(TOUPPER ${DLL_NAME} DLL_NAME_UPPERCASED)

project(${DLL_NAME})

file(GLOB_RECURSE Headers ${CMAKE_CURRENT_SOURCE_DIR}/*.h)
source_group("Headers" FILES ${Headers})

file(GLOB Sources ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)
source_group("Sources" FILES ${Sources})

set(Resources ${CMAKE_CURRENT_SOURCE_DIR}/${DLL_NAME}.rc)
source_group("Resources" FILES ${Resources})

set(AllSources
  ${Sources}
  ${Headers}
  ${Resources}
)

include_directories(
  ${CMAKE_CURRENT_SOURCE_DIR}
  ${CMAKE_CURRENT_SOURCE_DIR}/API
)

add_library(${DLL_NAME} SHARED ${AllSources})

target_include_directories(${DLL_NAME} PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/API")

set_property(TARGET ${DLL_NAME} APPEND PROPERTY COMPILE_DEFINITIONS
  ${DLL_NAME_UPPERCASED}_EXPORT
  _USRDLL
  _WINDOWS
)

if(MSVC)
  set_property(TARGET ${DLL_NAME} APPEND PROPERTY COMPILE_FLAGS /MP)
endif(MSVC)

set_target_properties(${ProjectName} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)