cmake_minimum_required(VERSION 3.3.2)

set(EXPERIMENT_ELEMENT_NAME ExperimentElementTemplate)
set(CATALOG_NAME CatalogName)
set(DLL_NAME ${CATALOG_NAME}_${EXPERIMENT_ELEMENT_NAME}Gui)

project(Catalog${DLL_NAME})
include(omicron_config)
include(omicron_defines)

find_package(Qt4)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)

file(GLOB_RECURSE Headers ${CMAKE_CURRENT_SOURCE_DIR}/*.h)
list(REMOVE_ITEM Headers ${CMAKE_CURRENT_SOURCE_DIR}/resource.h)
source_group("Headers" FILES ${Headers})

file(GLOB Sources ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)
source_group("Sources" FILES ${Sources})

file(GLOB UiFiles ${CMAKE_CURRENT_SOURCE_DIR}/*.ui)
source_group("UI Files" FILES ${UiFiles})

set(Resources
  ${CMAKE_CURRENT_BINARY_DIR}/${EXPERIMENT_ELEMENT_NAME}Gui.rc
  ${EXPERIMENT_ELEMENT_NAME}Gui.rc.template
  resource.h
  ${CMAKE_CURRENT_BINARY_DIR}/Version.h
  Version.h.template
)
source_group("Resource Files" FILES ${Resources})

# TODO uncomment and change section if required
#set(TextDefinitions
#  ${CMAKE_BINARY_DIR}/TextDefinitions/TextDefinitions_Catalog${DLL_NAME}.h
#)
#source_group("TextDefinitions" FILES ${TextDefinitions})


set(AllSources
  ${Sources}
  ${Headers}
  ${Resources}
  ${TextDefinitions}
  ${UiFiles}
)

include_directories(
  ${CMAKE_CURRENT_SOURCE_DIR}
  ${CMAKE_CURRENT_BINARY_DIR}
  ${OMICRON_GLOBAL_INCLUDE_DIRECTORY}
  ${CMAKE_BINARY_DIR}/TextDefinitions
  ${CMAKE_CURRENT_BINARY_DIR}
  ${OMICRON_ICUSTATION_INCL_SYSINCL_PATH}
)

add_library(${DLL_NAME} SHARED ${AllSources})

omicron_configure_file(${DLL_NAME} ${CMAKE_CURRENT_SOURCE_DIR}/Version.h.template ${CMAKE_CURRENT_BINARY_DIR}/Version.h)

omicron_configure_file(${DLL_NAME} ${CMAKE_CURRENT_SOURCE_DIR}/${EXPERIMENT_ELEMENT_NAME}Gui.rc.template ${CMAKE_CURRENT_BINARY_DIR}/${EXPERIMENT_ELEMENT_NAME}Gui.rc)

target_link_libraries(${DLL_NAME}
  Base
  CatalogManager
  Gui_Collection
  Gui_Utilities
  QtCore
  QtGui
  Gui_Special
)

string(TOUPPER ${EXPERIMENT_ELEMENT_NAME} EXPERIMENT_ELEMENT_NAME_UPPER)
set_property(TARGET ${DLL_NAME} APPEND PROPERTY COMPILE_DEFINITIONS
  CATALOG_${EXPERIMENT_ELEMENT_NAME_UPPER}GUI_EXPORT
  QT_DLL
  _USRDLL
  _WINDOWS
)

if(MSVC)
set_property(TARGET ${DLL_NAME} APPEND PROPERTY COMPILE_FLAGS 
  /MP
)
endif(MSVC)

set_target_properties (${DLL_NAME} PROPERTIES FOLDER Catalog${CATALOG_NAME})
set_property(TARGET ${DLL_NAME} PROPERTY PROJECT_LABEL "${EXPERIMENT_ELEMENT_NAME}Gui")
set_property(TARGET ${DLL_NAME} PROPERTY VS_KEYWORD "Qt4VSv1.0")
set_target_properties(${DLL_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CataloguesFolder} RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CataloguesFolder} RUNTIME_OUTPUT_DIRECTORY_RELWITHDEBINFO ${CataloguesFolder} RUNTIME_OUTPUT_DIRECTORY_MINSIZEREL ${CataloguesFolder})
