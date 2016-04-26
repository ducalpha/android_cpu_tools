#!/bin/bash

if [[ $# -ge 1 ]]; then
  export ANDROID_NDK_PATH=$1
  echo "Using android ndk path:"$ANDROID_NDK_PATH
fi

OUT_DIR=out
[[ ! -d $OUT_DIR ]] && mkdir $OUT_DIR
cd $OUT_DIR

# Use android 16 (4.1) which covers most of devices
CMAKE_CMD="cmake -GNinja -DCMAKE_TOOLCHAIN_FILE=../cmake/android-cmake/android.toolchain.cmake -DANDROID_NATIVE_API_LEVEL=android-16"

[[ -n $ANDROID_NDK_PATH ]] && CMAKE_CMD="$CMAKE_CMD -DANDROID_NDK=$ANDROID_NDK_PATH .."

echo $CMAKE_CMD
eval $CMAKE_CMD

# make -j4 # VERBOSE=1
ninja
