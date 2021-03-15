@echo off
rem Public domain
rem http://unlicense.org/
rem Created by Grigore Stefan <g_stefan@yahoo.com>

echo -^> sign xyo-pixel32

pushd output
for /r %%i in (*.dll) do call grigore-stefan.sign "XYO" "%%i"
for /r %%i in (*.exe) do call grigore-stefan.sign "XYO" "%%i"
popd
