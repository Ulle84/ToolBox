cmake_minimum_required(VERSION 3.3.2)

set(PROJECT_NAME CodeCleaner)
set(EXE_TYPE Console)

include(../CMake/QtExe.cmake)

#cmake_minimum_required(VERSION 2.8.11)
#
#set (PROJECT_NAME CodeCleaner)
#
#project(${PROJECT_NAME})
#
#find_package(Qt5Core 5.7)
#
#
#file(GLOB Headers ${CMAKE_CURRENT_SOURCE_DIR}/*.h)
#source_group("Headers" FILES ${Headers})
#
#file(GLOB Sources ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)
#source_group("Sources" FILES ${Sources})
#source_group("Sources" FILES ${Sources})
#
#file(GLOB Information ${CMAKE_CURRENT_SOURCE_DIR}/*.md)
#source_group("Information" FILES ${Information})
#
#set(AllSources
#  ${Headers}
#  ${Information}
#  ${Sources}
#)
#
#add_executable(${PROJECT_NAME} ${AllSources})
#
#target_link_libraries(${PROJECT_NAME}
#  Qt5::Core
#  Shared
#)
#
#set_target_properties(${PROJECT_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)