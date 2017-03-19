cmake_minimum_required(VERSION 3.3.2)

set(EXPERIMENT_ELEMENT_NAME ExperimentElementTemplate)
set(CATALOG_NAME CatalogName)
set(DLL_NAME ${CATALOG_NAME}_${EXPERIMENT_ELEMENT_NAME})

project(Catalog${DLL_NAME})
include(omicron_config)
include(omicron_defines)

find_package(Qt4)
set(CMAKE_AUTOMOC ON)

file(GLOB_RECURSE Headers ${CMAKE_CURRENT_SOURCE_DIR}/*.h)
list(REMOVE_ITEM Headers ${CMAKE_CURRENT_SOURCE_DIR}/resource.h)
source_group("Headers" FILES ${Headers})

file(GLOB Sources ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)
source_group("Sources" FILES ${Sources})

set(Resources
  ${CMAKE_CURRENT_BINARY_DIR}/${EXPERIMENT_ELEMENT_NAME}.rc
  ${CMAKE_CURRENT_BINARY_DIR}/Version.h
  ${CMAKE_CURRENT_SOURCE_DIR}/resource.h
)
source_group("Resources" FILES ${Resources})

set(AllSources
  ${Sources}
  ${Resources}
  ${Headers}
)

include_directories(
  ${CMAKE_CURRENT_SOURCE_DIR}
  ${CMAKE_CURRENT_SOURCE_DIR}/API
  ${CMAKE_CURRENT_BINARY_DIR}
  ${OMICRON_ICUSTATION_INCL_SYSINCL_PATH}
)

add_library(${DLL_NAME} SHARED ${AllSources})

target_include_directories(${DLL_NAME} PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/API")

target_link_libraries(${CATALOG_NAME}_${EXPERIMENT_ELEMENT_NAME}
  Base
  CatalogManager
  Exp
  Instr
  Script
)

omicron_configure_file(${DLL_NAME} ${CMAKE_CURRENT_SOURCE_DIR}/Version.h.template ${CMAKE_CURRENT_BINARY_DIR}/Version.h)
omicron_configure_file(${DLL_NAME} ${CMAKE_CURRENT_SOURCE_DIR}/${EXPERIMENT_ELEMENT_NAME}.rc.template ${CMAKE_CURRENT_BINARY_DIR}/${EXPERIMENT_ELEMENT_NAME}.rc)

string(TOUPPER ${EXPERIMENT_ELEMENT_NAME} EXPERIMENT_ELEMENT_NAME_UPPER)
set_property(TARGET ${DLL_NAME} APPEND PROPERTY COMPILE_DEFINITIONS
  CATALOG_${EXPERIMENT_ELEMENT_NAME_UPPER}_EXPORT
  _USRDLL
  _WINDOWS
)

if(MSVC)
set_property(TARGET ${DLL_NAME} APPEND PROPERTY COMPILE_FLAGS 
  /MP
)
endif(MSVC)

set_target_properties (${DLL_NAME} PROPERTIES FOLDER Catalog${CATALOG_NAME})
set_property(TARGET ${DLL_NAME} PROPERTY PROJECT_LABEL "${EXPERIMENT_ELEMENT_NAME}")
set_target_properties(${DLL_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CataloguesFolder} RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CataloguesFolder} RUNTIME_OUTPUT_DIRECTORY_RELWITHDEBINFO ${CataloguesFolder} RUNTIME_OUTPUT_DIRECTORY_MINSIZEREL ${CataloguesFolder})

