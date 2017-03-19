cmake_minimum_required(VERSION 2.8.11)

set(PROJECT_NAME ClassAnalyzer)

project(${PROJECT_NAME})

find_package(Qt5Widgets 5.7)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

file(GLOB Headers ${CMAKE_CURRENT_SOURCE_DIR}/*.h)
source_group("Headers" FILES ${Headers})

file(GLOB Sources ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)
source_group("Sources" FILES ${Sources})

file(GLOB Resources ${CMAKE_CURRENT_SOURCE_DIR}/*.qrc)
source_group("Resources" FILES ${Resources})

file(GLOB UiFiles ${CMAKE_CURRENT_SOURCE_DIR}/*.ui)
source_group("UI Files" FILES ${UiFiles})

file(GLOB Information ${CMAKE_CURRENT_SOURCE_DIR}/*.md)
source_group("Information" FILES ${Information})

set(AllSources
  ${Headers}
  ${Sources}
  ${Resources}
  ${UiFiles}
  ${Information}  
)

add_executable(${PROJECT_NAME} WIN32 ${AllSources})

target_link_libraries(${PROJECT_NAME} Qt5::Widgets)

set_target_properties(${PROJECT_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)