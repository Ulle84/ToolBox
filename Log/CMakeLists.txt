cmake_minimum_required(VERSION 3.2)

set(ProjectName Log)

project(${ProjectName})

file(GLOB Headers ${CMAKE_CURRENT_SOURCE_DIR}/*.h ${CMAKE_CURRENT_SOURCE_DIR}/API/*.h)

source_group("Headers" FILES ${Headers})

file(GLOB_RECURSE Sources ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)
source_group("Sources" FILES ${Sources})

set(AllFiles
  ${Sources}
  ${Headers}
)

include_directories(
  ${CMAKE_CURRENT_SOURCE_DIR}
  ${CMAKE_CURRENT_SOURCE_DIR}/API
  ${OMICRON_ICUSTATION_INCL_SYSINCL_PATH}
)

add_library(${ProjectName} SHARED ${AllFiles})

target_include_directories(${ProjectName} PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/API")

target_link_libraries(${ProjectName}
  Base
  Comms
  QtCore
)

set_property(TARGET ${ProjectName} APPEND PROPERTY COMPILE_DEFINITIONS
  LOG_EXPORT
  _USRDLL
  _WINDOWS
)
