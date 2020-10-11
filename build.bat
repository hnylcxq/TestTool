@echo off

set OUTPUT=%CD%

if /I "%1" EQU "all" (
    nmake -nologo clean
    nmake -nologo all
) else if /I "%1" EQU "clean" (
    nmake -nologo clean
)

echo build complete
