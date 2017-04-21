################################################################################
# CMake file for using Qt
# Created by Ulrich Belitz in Februrary 2017
################################################################################

################################################################################
# Checking prerequisites
################################################################################
if (NOT DEFINED OutputDirDebug)
  message(FATAL_ERROR "OutputDirDebug not defined")
endif()

if (NOT DEFINED OutputDirRelease)
  message(FATAL_ERROR "OutputDirRelease not defined")
endif()

################################################################################
# Setting Qt Version
################################################################################
set(QtVersion 5.5.1)
message(STATUS "using Qt version: ${QtVersion}")

################################################################################
# Test if Qt5Core can be found - raise fatal error if not found
################################################################################
string(SUBSTRING ${QtVersion} 0 3 QtVersionShort)
set(QtDir "C:/Qt/Qt${QtVersion}/${QtVersionShort}/msvc2013")

if(CMAKE_SIZEOF_VOID_P EQUAL 8)
  set(QtDir "${QtDir}_64")
endif()

set (CMAKE_PREFIX_PATH ${QtDir})

find_package(Qt5Core ${QT_VERSION})
  
if ("${Qt5Core_DIR}" STREQUAL "Qt5Core_DIR-NOTFOUND")
  message(FATAL_ERROR "Qt5Core package not found")
endif()

set(QtBinDir "${Qt5Core_DIR}/../../../bin/")
set(QtIncludeDir "${QtDir}/include/")
set(QtDesignerPluginsDir "${QtDir}/plugins/designer/")

# ToDo prepare one list of packages and generate package and link names automatically

################################################################################
# Find Qt packages
################################################################################
set(QtPackages
  Qt5Core
  Qt5Gui
  Qt5UiTools
  Qt5Widgets
  Qt5Test
  Qt5WebKitWidgets
  Qt5Sensors
  Qt5Positioning
  Qt5Quick
  Qt5Qml
  Qt5Network
  Qt5Multimedia
  Qt5MultimediaWidgets
  Qt5WebChannel
  Qt5Sql
  Qt5PrintSupport
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
  Qt5::WebKitWidgets
  Qt5::Sensors
  Qt5::Positioning
  Qt5::Quick
  Qt5::Qml
  Qt5::Network
  Qt5::Multimedia
  Qt5::MultimediaWidgets
  Qt5::WebChannel
  Qt5::Sql
  Qt5::PrintSupport
)

################################################################################
# Install Dlls
################################################################################
list(REMOVE_ITEM QtPackages Qt5UiTools) # package exist, but no correspoinding DLL

set(QtDlls
  ${QtPackages}
  Qt5Designer
  Qt5DesignerComponents
  Qt5WebKit
  Qt5OpenGl
)

foreach(QtDll ${QtDlls})
  file(INSTALL ${QtBinDir}${QtDll}.dll DESTINATION ${OutputDirRelease})  
  file(INSTALL ${QtBinDir}${QtDll}d.dll DESTINATION ${OutputDirDebug})  
  file(INSTALL ${QtBinDir}${QtDll}d.pdb DESTINATION ${OutputDirDebug})  
endforeach()

set(AdditionalDlls
  icudt54
  icuin54
  icuuc54
)

foreach(AdditionalDll ${AdditionalDlls})
  file(INSTALL ${QtBinDir}${AdditionalDll}.dll DESTINATION ${OutputDirRelease})  
  file(INSTALL ${QtBinDir}${AdditionalDll}.dll DESTINATION ${OutputDirDebug})
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
  get_filename_component(QtPluginDir "${OutputDirRelease}/../plugins/${QtPlugin}.dll" PATH)
  file(INSTALL ${QtPluginsPath}${QtPlugin}.dll DESTINATION ${QtPluginDir})  
  file(INSTALL ${QtPluginsPath}${QtPlugin}d.dll DESTINATION ${QtPluginDir})  
  file(INSTALL ${QtPluginsPath}${QtPlugin}d.pdb DESTINATION ${QtPluginDir})  
endforeach()

################################################################################
# Write config files
################################################################################
set(QtConfFiles
  ${OutputDirDebug}/qt.conf
  ${OutputDirRelease}/qt.conf
)

foreach(QtConfFile ${QtConfFiles})
  if(NOT EXISTS ${QtConfFile})
    file(WRITE ${QtConfFile} "[Paths]\nPrefix=..")
  endif()
endforeach()