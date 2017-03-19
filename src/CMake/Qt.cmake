################################################################################
# CMake file for using Qt
# Created by Ulrich Belitz in Februrary 2017
################################################################################

################################################################################
# Checking prerequisites
################################################################################
if (NOT DEFINED OutputDir)
  message(FATAL_ERROR "OutputDir not defined")
endif()

################################################################################
# Setting Qt Version
################################################################################
set(QtVersion 5.8.0)
message(STATUS "using Qt version: ${QtVersion}")

################################################################################
# Test if Qt5Core can be found - raise fatal error if not found
################################################################################
string(SUBSTRING ${QtVersion} 0 3 QtVersionShort)
set(QtDir "C:/Qt/Qt${QtVersion}/${QtVersionShort}/msvc2013")
set (CMAKE_PREFIX_PATH ${QtDir})

find_package(Qt5Core ${QT_VERSION})
  
if ("${Qt5Core_DIR}" STREQUAL "Qt5Core_DIR-NOTFOUND")
  message(FATAL_ERROR "Qt5Core package not found")
endif()

set(QtBinDir "${Qt5Core_DIR}/../../../bin/")
set(QtIncludeDir "${QtDir}/include/")
set(QtDesignerPluginsDir "${QtDir}/plugins/designer/")

################################################################################
# Find Qt packages
################################################################################
set(QtPackages
  Qt5Core
  Qt5Gui
  Qt5UiTools
  Qt5Widgets
  Qt5Test
)

foreach(QtPackage ${QtPackages})
  find_package(${QtPackage} ${QT_VERSION})  
endforeach()

################################################################################
# Set QtLinkLibaries
################################################################################
set(QtLinkLibraries
  Qt5::Core
  Qt5::Gui
  Qt5::UiTools
  Qt5::Widgets
  Qt5::Test
)

################################################################################
# Install Dlls
################################################################################
list(REMOVE_ITEM QtPackages Qt5UiTools) # package exist, but no correspoinding DLL

set(QtDlls
  ${QtPackages}
  Qt5Designer
  Qt5DesignerComponents
)

foreach(QtDll ${QtDlls})
  file(INSTALL ${QtBinDir}${QtDll}.dll DESTINATION ${OutputDir})  
endforeach()

################################################################################
# Install plugins
################################################################################
set(QtPluginsPath ${QtBinDir}../plugins/)

set(QtPlugins
  bearer/qgenericbearer
  bearer/qnativewifibearer
  iconengines/qsvgicon
  imageformats/qgif
  imageformats/qicns
  imageformats/qico
  imageformats/qjpeg
  imageformats/qsvg
  imageformats/qtga
  imageformats/qtiff
  imageformats/qwbmp
  imageformats/qwebp
  platforms/qwindows
  platforms/qminimal
  printsupport/windowsprintersupport
  sqldrivers/qsqlite
  sqldrivers/qsqlmysql
  sqldrivers/qsqlodbc
  sqldrivers/qsqlpsql
  platforms/qwindows
)

foreach(QtPlugin ${QtPlugins})
  get_filename_component(QtPluginReleaseDir "${OutputDir}/../plugins/${QtPlugin}.dll" PATH)
  file(INSTALL ${QtPluginsPath}${QtPlugin}.dll DESTINATION ${QtPluginReleaseDir})  
endforeach()

################################################################################
# Write config file
################################################################################
set(QtConfFile ${OutputDir}/qt.conf)

if(NOT EXISTS ${QtConfFile})
  file(WRITE ${QtConfFile} "[Paths]\nPrefix=..")
endif()