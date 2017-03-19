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
  file(INSTALL ${QtBinDir}${QtDll}.dll DESTINATION ${OutputDirRelease})  
  file(INSTALL ${QtBinDir}${QtDll}d.dll DESTINATION ${OutputDirDebug})  
  file(INSTALL ${QtBinDir}${QtDll}d.pdb DESTINATION ${OutputDirDebug})  
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