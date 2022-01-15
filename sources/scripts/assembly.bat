@echo off

if "%1" equ "build" cd keil & call assembly build & cd ../vs_keil & call assembly build & cd ../ThirdParty & call assembly build & cd ../vs_gui & call assembly build & goto EXIT
if "%1" equ "full"  cd keil & call assembly rebuild & cd ../vs_keil & call assembly full & cd ../ThirdParty & call assembly full & cd ../vs_gui & call assembly full & goto EXIT

:HINT
echo.
echo Using assembly.bat:
echo                    assembly.bat [build^|full]
echo.
goto EXIT

:EXIT
