#!/bin/bash

# Download opencv
if [ -d "opencv" ]; then
  echo "Opencv folder exists. Skip downloading."
else
  echo "Download opencv-3.4.12 sources."
  git clone https://github.com/opencv/opencv --branch 3.4.12 --depth 1
fi

# Build opencv
if [ -d "opencv/build" ]; then
  echo "opencv/build folder exists. Skip building."
else
  echo "Build opencv."
  mkdir -p opencv/build
  pushd opencv/build
  cmake -D WITH_FFMPEG=ON \
        -D CMAKE_INSTALL_PREFIX=../../dependencies \
        -D BUILD_opencv_java=OFF \
        -D BUILD_opencv_python=OFF \
        -D CMAKE_BUILD_TYPE=Release \
        -D BUILD_EXAMPLES=OFF \
        -D BUILD_DOCS=OFF \
        -D BUILD_PERF_TESTS=OFF \
        -D BUILD_TESTS=OFF ..
  make -j7
  make install
  popd
fi

# Build this project
mkdir -p build
cd build
cmake -D CMAKE_BUILD_TYPE=Release ..
make -j8