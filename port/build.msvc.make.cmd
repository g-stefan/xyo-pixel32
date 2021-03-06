@echo off
rem Public domain
rem http://unlicense.org/
rem Created by Grigore Stefan <g_stefan@yahoo.com>

set ACTION=%1
if "%1" == "" set ACTION=make

echo -^> %ACTION% xyo-pixel32

goto StepX
:cmdX
%*
if errorlevel 1 goto cmdXError
goto :eof
:cmdXError
echo "Error: %ACTION%"
exit 1
:StepX

call :cmdX file-to-cs --touch=source/xyo-pixel32-license.cpp --file-in=source/license-dependency-libpng.txt --file-out=source/license-dependency-libpng.src --is-string-direct
call :cmdX file-to-cs --touch=source/xyo-pixel32-license.cpp --file-in=source/license-dependency-zlib.txt --file-out=source/license-dependency-zlib.src --is-string-direct
call :cmdX xyo-cc --mode=%ACTION% @util/xyo-pixel32.static.compile
call :cmdX xyo-cc --mode=%ACTION% @util/xyo-pixel32.dynamic.compile
