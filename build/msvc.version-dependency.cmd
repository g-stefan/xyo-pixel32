@echo off
rem Public domain
rem http://unlicense.org/
rem Created by Grigore Stefan <g_stefan@yahoo.com>

echo -^> version-dependency xyo-pixel32

xyo-cc --bump-version-minor-if-version-dependency xyo-pixel32
