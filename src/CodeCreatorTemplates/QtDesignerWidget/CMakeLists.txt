cmake_minimum_required(VERSION 3.3.2)

set(DLL_NAME QtDesignerWidget)
string(TOUPPER ${DLL_NAME} DLL_NAME_UPPERCASED)

project(${DLL_NAME})

find_package(Qt5Widgets 5.7)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

file(GLOB_RECURSE Headers ${CMAKE_CURRENT_SOURCE_DIR}/*.h)
source_group("Headers" FILES ${Headers})

file(GLOB Sources ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)
source_group("Sources" FILES ${Sources})

file(GLOB UiFiles ${CMAKE_CURRENT_SOURCE_DIR}/*.ui)
source_group("UI Files" FILES ${UiFiles})

file(GLOB Resources ${CMAKE_CURRENT_SOURCE_DIR}/Resources/*.qrc)
source_group("Resources" FILES ${Resources})

file(GLOB JSON ${CMAKE_CURRENT_SOURCE_DIR}/*.json)
file(GLOB MarkDown ${CMAKE_CURRENT_SOURCE_DIR}/*.md)

set(Information
  ${JSON}
  ${MarkDown}
)

source_group("Information" FILES ${Information})

set(AllSources
  ${Headers}
  ${Information}
  ${Resources}
  ${Sources}
  ${UiFiles}
)

include_directories(
  ${CMAKE_CURRENT_SOURCE_DIR}
)

add_library(${DLL_NAME} SHARED ${AllSources})

target_include_directories(${DLL_NAME} PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/API")

set_property(TARGET ${DLL_NAME} APPEND PROPERTY COMPILE_DEFINITIONS
  _USRDLL
  _WINDOWS
)

if(MSVC)
  set_property(TARGET ${DLL_NAME} APPEND PROPERTY COMPILE_FLAGS /MP)
endif(MSVC)

target_link_libraries(${ProjectName} Qt5::Widgets)

set_target_properties(${ProjectName} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)