@echo off
setlocal enabledelayedexpansion

set OUTPUT=codebase_dump.txt
set ROOT=%~dp0Source\HTTPS

echo Dumping codebase from %ROOT% to %OUTPUT%...
echo. > %OUTPUT%

for /r "%ROOT%" %%F in (*.h *.cpp) do (
    set "FILEPATH=%%F"
    set "RELPATH=!FILEPATH:%ROOT%\=!"
    echo ======================================== >> %OUTPUT%
    echo FILE: !RELPATH! >> %OUTPUT%
    echo ======================================== >> %OUTPUT%
    type "%%F" >> %OUTPUT%
    echo. >> %OUTPUT%
    echo. >> %OUTPUT%
)

echo Done. Output saved to %OUTPUT%
pause
