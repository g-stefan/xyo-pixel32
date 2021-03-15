#!/bin/sh
# Public domain
# http://unlicense.org/
# Created by Grigore Stefan <g_stefan@yahoo.com>

echo "-> analyze xyo-pixel32"

cmdX(){
	echo "-> $@"
	if ! "$@" ; then
		echo "Error: $@"
		exit 1
	fi
}

cmdX scan-build ./build/ubuntu.make.sh
