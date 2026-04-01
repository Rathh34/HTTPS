@echo off
setlocal enabledelayedexpansion

set OUTPUT=%~dp0codebase_dump.txt
set ROOT=%~dp0Source\HTTPS

echo Searching in: %ROOT%
echo Output to: %OUTPUT%

if not exist "%ROOT%" (
    echo ERROR: Folder not found: %ROOT%
    echo Make sure this .bat is in the same folder as HTTPS.uproject
    pause
    exit /b 1
)

echo. > "%OUTPUT%"

set COUNT=0
for /r "%ROOT%" %%F in (*.h *.cpp) do (
    set /a COUNT+=1
    set "FILEPATH=%%F"
    set "RELPATH=!FILEPATH:%ROOT%\=!"
    echo ======================================== >> "%OUTPUT%"
    echo FILE: !RELPATH! >> "%OUTPUT%"
    echo ======================================== >> "%OUTPUT%"
    type "%%F" >> "%OUTPUT%"
    echo. >> "%OUTPUT%"
    echo. >> "%OUTPUT%"
)

echo Found and dumped %COUNT% files.
echo Done. Output saved to %OUTPUT%
pause
