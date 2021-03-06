#!/bin/sh
# Public domain
# http://unlicense.org/
# Created by Grigore Stefan <g_stefan@yahoo.com>

# On WSL we must build on home folder to keep executable bits on files
WSL_BUILD_PROCESS_PATH=$HOME/SDK/source/xyo-pixel32

export XYO_PATH_REPOSITORY=$HOME/SDK
export XYO_PATH_RELEASE=$HOME/SDK/release
export XYO_PATH_REPOSITORY_LIBRARY=

[ -d $WSL_BUILD_PROCESS_PATH ] || mkdir -p $WSL_BUILD_PROCESS_PATH

[ -d $WSL_BUILD_PROCESS_PATH/include ] || mkdir -p $WSL_BUILD_PROCESS_PATH/include
[ -d $WSL_BUILD_PROCESS_PATH/source ] || mkdir -p $WSL_BUILD_PROCESS_PATH/source
[ -d $WSL_BUILD_PROCESS_PATH/util ] || mkdir -p $WSL_BUILD_PROCESS_PATH/util
[ -d $WSL_BUILD_PROCESS_PATH/port ] || mkdir -p $WSL_BUILD_PROCESS_PATH/port
[ -d $WSL_BUILD_PROCESS_PATH/release ] || mkdir -p $WSL_BUILD_PROCESS_PATH/release

cp -rfu ./include/* $WSL_BUILD_PROCESS_PATH/include/
cp -rfu ./source/* $WSL_BUILD_PROCESS_PATH/source/
cp -rfu ./util/* $WSL_BUILD_PROCESS_PATH/util/
cp -rfu ./port/build.ubuntu*.sh $WSL_BUILD_PROCESS_PATH/port/
cp -rfu ./release/*.csv $WSL_BUILD_PROCESS_PATH/release/

WSL_POPD=$PWD
cd $WSL_BUILD_PROCESS_PATH

chmod -R -x+X include
chmod -R -x+X source
chmod -R -x+X util

/bin/sh -- ./port/build.ubuntu.sh $1
RETV=$?

cd $WSL_POPD

if [ "$1" = "clean" ]; then
	rm -rf $WSL_BUILD_PROCESS_PATH
fi

if [ "$1" = "release" ]; then
	[ -d ./release ] || mkdir -p ./release 
	cp -rfu $WSL_BUILD_PROCESS_PATH/release/*.7z ./release/
	cp -rfu $WSL_BUILD_PROCESS_PATH/release/*.csv ./release/
fi

if [ "$RETV" = "1" ]; then
	exit 1
fi
exit 0
