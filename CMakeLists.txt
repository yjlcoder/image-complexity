CMAKE_MINIMUM_REQUIRED(VERSION 3.10)
project("image-complexity")

SET(SRCS src/main.cpp)

add_executable(${PROJECT_NAME} ${SRCS})

include_directories(dependencies/include)
find_package(OpenCV REQUIRED PATHS dependencies/)
target_link_directories(${PROJECT_NAME} PUBLIC dependencies/lib/)
target_link_libraries(${PROJECT_NAME} opencv_core opencv_calib3d opencv_dnn opencv_features2d opencv_flann opencv_highgui opencv_imgcodecs)
