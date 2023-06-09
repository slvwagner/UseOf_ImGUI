﻿# Version
cmake_minimum_required (VERSION 3.8)
# source
add_executable (imGUIexample "imGUIexample.cpp" "UseImGui.cpp" "UseImGui.h"   "system.h" "Header.h" "Enum.h" )

message("************************************")
message("vcpkg root = ${CMAKE_MSVC_RUNTIME_LIBRARY}")
message("************************************\n")


# Install Logos/icons
message("************************************")
message("Image source = ${CMAKE_CURRENT_SOURCE_DIR}/Picts/wagnius.png")
message("Image destiantion = ${CMAKE_CURRENT_BINARY_DIR}/picts/wagnius.png")
message("************************************\n************************************")

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/picts/wagnius.png  DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/picts)

# pthread
find_package(PThreads4W REQUIRED)
target_link_libraries(imGUIexample PRIVATE PThreads4W::PThreads4W)

# ImGui dependecies 
find_package(glad CONFIG REQUIRED)
target_link_libraries(imGUIexample PRIVATE glad::glad)

find_package(glfw3 CONFIG REQUIRED)
target_link_libraries(imGUIexample PRIVATE glfw)

find_package(imgui CONFIG REQUIRED)
target_link_libraries(imGUIexample PRIVATE imgui::imgui)

# Eigen 
find_package(Eigen3 CONFIG REQUIRED)
target_link_libraries(imGUIexample PRIVATE Eigen3::Eigen) 

# OpenCV
find_package(OpenCV CONFIG REQUIRED)
target_link_libraries(imGUIexample PRIVATE opencv_calib3d)
target_link_libraries(imGUIexample PRIVATE opencv_core)
target_link_libraries(imGUIexample PRIVATE opencv_dnn)
target_link_libraries(imGUIexample PRIVATE opencv_features2d)
target_link_libraries(imGUIexample PRIVATE opencv_flann)
target_link_libraries(imGUIexample PRIVATE opencv_highgui)
target_link_libraries(imGUIexample PRIVATE opencv_imgcodecs)
target_link_libraries(imGUIexample PRIVATE opencv_imgproc)
target_link_libraries(imGUIexample PRIVATE opencv_ml)
target_link_libraries(imGUIexample PRIVATE opencv_objdetect)
target_link_libraries(imGUIexample PRIVATE opencv_photo)
target_link_libraries(imGUIexample PRIVATE opencv_stitching)
target_link_libraries(imGUIexample PRIVATE opencv_video)
target_link_libraries(imGUIexample PRIVATE opencv_videoio)

# openGL
find_package(OpenGL REQUIRED)
target_link_libraries(imGUIexample PRIVATE OpenGL::GL)
find_package(FreeGLUT CONFIG REQUIRED)
target_link_libraries(imGUIexample PRIVATE $<IF:$<TARGET_EXISTS:FreeGLUT::freeglut>,FreeGLUT::freeglut,FreeGLUT::freeglut_static>)

find_package(FFMPEG REQUIRED)
target_include_directories(imGUIexample PRIVATE ${FFMPEG_INCLUDE_DIRS})
target_link_directories(imGUIexample PRIVATE ${FFMPEG_LIBRARY_DIRS})
target_link_libraries(imGUIexample PRIVATE ${FFMPEG_LIBRARIES})

# load pict to ram 
find_package(Stb REQUIRED)
target_include_directories(imGUIexample PRIVATE ${Stb_INCLUDE_DIR})

# imPlot
find_package(implot CONFIG REQUIRED)
target_link_libraries(imGUIexample PRIVATE implot::implot)

