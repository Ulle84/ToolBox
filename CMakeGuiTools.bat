@echo off
set BASE_DIR=%~dp0

echo Checking prerequisites...

where cmake-gui >NUL 2>&1
if NOT %errorlevel% EQU 0 (
  echo cmake-gui not found, please install cmake and add it to the default path
  pause
  exit 1
)
echo   cmake-gui found

set BUILD_DIR=%BASE_DIR%build

echo Building Tools in %BUILD_DIR%

if not exist %BUILD_DIR% (
  mkdir %BUILD_DIR%
)

cd %BUILD_DIR%
start cmake-gui %BASE_DIR%/src