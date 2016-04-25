#!/bin/bash

if [[ $# -ge 1 ]]; then
  export ANDROID_NDK_PATH=$1
  echo "Using android ndk path:"$ANDROID_NDK_PATH
fi

mkdir out
cd out

# Use android 21 (5.0) which covers most of devices
CMAKE_CMD="cmake -DCMAKE_TOOLCHAIN_FILE=../cmake/android-cmake/android.toolchain.cmake -DANDROID_NATIVE_API_LEVEL=android-21"

[[ -n $ANDROID_NDK_PATH ]] && CMAKE_CMD="$CMAKE_CMD -DANDROID_NDK=$ANDROID_NDK_PATH .."

echo $CMAKE_CMD
eval $CMAKE_CMD

make  VERBOSE=1
