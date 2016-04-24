#!/bin/bash

if [[ $# -ge 1 ]]; then
  export ANDROID_NDK_PATH=$1
  echo "Using android ndk path:"$ANDROID_NDK_PATH
fi

rm -r out
mkdir out
cd out

CMAKE_CMD="cmake -DCMAKE_TOOLCHAIN_FILE=../cmake/android-cmake/android.toolchain.cmake .."

[[ -n $ANDROID_NDK_PATH ]] && CMAKE_CMD="ANDROID_NDK=$ANDROID_NDK_PATH $CMAKE_CMD"

echo $CMAKE_CMD
eval $CMAKE_CMD

make # VERBOSE=1
