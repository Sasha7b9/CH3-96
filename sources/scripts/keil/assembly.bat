@echo off

set _COMPILER_=c:\Keil_v5\UV4\UV4
set _PROJECT_=..\..\Panel\Panel.uvprojx

rem 1, если требуется очистка
set isClean=0

rem 1, если требуется сборка
set isBuild=0

rem 1, если требуется загрузка
set isLoad=0

if "%1" equ "build"   set isBuild=1 &                  goto CHECK_ON_LOAD
if "%1" equ "rebuild" set isClean=1 & set isBuild=1 &  goto CHECK_ON_LOAD
if "%1" equ "load"    set isLoad=1 &                   goto LOADING
goto HINT

rem Проверка на то, нужно ли загружать (второй параметр - "load")
:CHECK_ON_LOAD
if "%2" equ "load" set isLoad=1

:CLEANING
if %isClean%==0 goto BUILDING
echo Cleaning ...
%_COMPILER_% -c %_PROJECT_% -j0

:BUILDING
if %isBuild%==0 goto LOADING
echo Building ...
%_COMPILER_% -b %_PROJECT_% -j0 -o Panel.out
if %ERRORLEVEL%==0 goto LOADING
echo ERROR!!! Build failed !!!
type ..\..\Panel\Panel.out

:LOADING
if %isLoad%==0 goto EXIT
echo Loading ...
%_COMPILER_% -f %_PROJECT_% -j0 -o Panel.out
if %ERRORLEVEL%==0 goto EXIT
echo Error loading firmware to device
type ..\..\Panel\Panel.out

goto EXIT


:HINT
echo.
echo Using assembly.bat:
echo                    assembly.bat build
echo                    assembly.bat rebuild
echo                    assembly.bat load
echo                    assembly.bat build load
echo                    assembly.bat rebuild load
echo.
goto EXIT

:EXIT
