@echo off
set BASE_DIR=%~dp0

set CMakeGuiPath=%BASE_DIR%..\Programs\Portable\cmake\bin\cmake-gui.exe

if not exist %CMakeGuiPath% (
  echo cmake-gui not found - please make available in:
  echo %CMakeGuiPath%
  pause
  exit 1
)

set BUILD_DIR=%BASE_DIR%build

if not exist %BUILD_DIR% (
  mkdir %BUILD_DIR%
)

cd %BUILD_DIR%
start %CMakeGuiPath% %BASE_DIR%src