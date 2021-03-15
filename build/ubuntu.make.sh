#!/bin/sh
# Public domain
# http://unlicense.org/
# Created by Grigore Stefan <g_stefan@yahoo.com>

ACTION=$1
if [ "$ACTION" = "" ]; then
	ACTION=make
fi

echo "-> $ACTION xyo-pixel32"

cmdX(){
	if ! "$@" ; then
		echo "Error: $ACTION"
		exit 1
	fi
}

cmdX file-to-cs --touch=source/xyo-pixel32-license.cpp --file-in=source/license-dependency-libpng.txt --file-out=source/license-dependency-libpng.src --is-string-direct
cmdX file-to-cs --touch=source/xyo-pixel32-license.cpp --file-in=source/license-dependency-zlib.txt --file-out=source/license-dependency-zlib.src --is-string-direct
cmdX xyo-cc --mode=$ACTION @build/source/xyo-pixel32.static.compile.unix
cmdX xyo-cc --mode=$ACTION @build/source/xyo-pixel32.dynamic.compile
