@echo off

set SRC="tors/src/tors.c"
set DYN_STRING_INCLUDE="vendor/dyn_string/dyn_string/include"
set DYN_ARRAY_INCLUDE="vendor/dyn_array/dyn_array/include"

gcc %SRC% -o "build/tors.exe" -I %DYN_STRING_INCLUDE% -I %DYN_ARRAY_INCLUDE%

pause