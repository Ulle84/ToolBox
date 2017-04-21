cmake_minimum_required(VERSION 3.3.2)

set(PROJECT_NAME Shared)

string(TOUPPER ${PROJECT_NAME} PROJECT_NAME_UPPERCASED)

project(${PROJECT_NAME})

file(GLOB_RECURSE Headers ${CMAKE_CURRENT_SOURCE_DIR}/*.h)
source_group("Headers" FILES ${Headers})

file(GLOB Sources ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)
source_group("Sources" FILES ${Sources})

set(Resources ${CMAKE_CURRENT_SOURCE_DIR}/${PROJECT_NAME}.rc)
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

add_library(${PROJECT_NAME} SHARED ${AllSources})

target_include_directories(${PROJECT_NAME} PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/API")

set_property(TARGET ${PROJECT_NAME} APPEND PROPERTY COMPILE_DEFINITIONS
  ${PROJECT_NAME_UPPERCASED}_EXPORT
  _USRDLL
  _WINDOWS
)

if(MSVC)
  set_property(TARGET ${PROJECT_NAME} APPEND PROPERTY COMPILE_FLAGS /MP)
endif(MSVC)

target_link_libraries(${PROJECT_NAME}
  Qt5::Core
  Qt5::Gui
  Qt5::Widgets
)