@echo off
set BASE_DIR=%~dp0

rem echo Checking prerequisites...
rem 
rem where cmake-gui >NUL 2>&1
rem if NOT %errorlevel% EQU 0 (
rem   echo cmake-gui not found, please install cmake and add it to the default path
rem   pause
rem   exit 1
rem )
rem echo   cmake-gui found

set BUILD_DIR=%BASE_DIR%build

echo Building Tools in %BUILD_DIR%

if not exist %BUILD_DIR% (
  mkdir %BUILD_DIR%
)

cd %BUILD_DIR%
start ..\..\PortablePrograms\cmake\bin\cmake-gui.exe %BASE_DIR%/src