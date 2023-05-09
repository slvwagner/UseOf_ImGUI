// StereoCamCalibration.h: Includedatei für Include-Standardsystemdateien
// oder projektspezifische Includedateien.

#pragma once

// C++
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <unordered_map>
#include <chrono>
#include <direct.h>
#include <stdio.h>
#include <stdlib.h>
#include <filesystem>
#include <Windows.h>
#include <thread>  
#include <mutex>    
#include <algorithm>
#include <math.h>
#include <random>

// Includes for ImGui
#pragma once
#define IMGUI_DEFINE_MATH_OPERATORS

//ImGui
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

//imPlot
#include <implot.h>
#include <implot_internal.h>

// openGL
#include <glad/glad.h>
#include <GLFW/glfw3.h>

// system
#include <fstream>
#include <iostream>
#include <cstdlib>

// data typ`s
#include <array>
#include <vector>
#include <list>
#include <map>
#include <stack>

// ffmpeg
extern "C" {
#include <libavcodec/avcodec.h>
#include <libavformat/avformat.h>
#include <libswscale/swscale.h>
}

// opencv dependencies 
#include <opencv2/opencv.hpp>
#include <opencv2/calib3d.hpp>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include "opencv2/imgcodecs.hpp"

// Common name space for the project
using namespace std;

// loading pictures to memory 
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

//Enums
#include "Enum.h"

// Helper function
#include "system.h"

// ImGui 
#include "UseImGui.h"

#pragma warning(disable : 4996)