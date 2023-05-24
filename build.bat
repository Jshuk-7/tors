@echo off

set SRC="tors/src/tors.c"
set INCLUDE_DIR="vendor"

gcc %SRC% -o "build/tors.exe" -I %INCLUDE_DIR%

pause