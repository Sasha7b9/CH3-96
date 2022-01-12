@echo off

set make_all=0
set build_all=0

if "%1" equ "make" set make_all=1 & goto MAKING
if "%1" equ "build" set build_all=1 & goto MAKING
if "%1" equ "full" set make_all=1 & set build_all=1 & goto MAKING
goto HINT

:MAKING
if %make_all%==0 goto BUILDING
cd vs_keil
call assembly.bat make
cd ../vs_gui
call assembly.bat make
cd ..

:BUILDING
if %build_all%==0 goto EXIT
cd keil
call assembly.bat build
cd ../vs_keil
call assembly.bat build
cd ../vs_gui
call assembly.bat build
cd ..
goto EXIT

:HINT
echo.
echo Using assembly.bat:
echo                    assembly.bat [make^|build^|full]
echo.
goto EXIT

:EXIT
