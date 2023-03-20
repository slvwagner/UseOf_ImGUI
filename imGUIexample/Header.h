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

// opencv dependencies 
#include <opencv2/calib3d.hpp>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include "opencv2/imgcodecs.hpp"

// loading pictures to memory 
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"


// ImGui 
#include "UseImGui.h"

// Common name space for the project
using namespace std;

// Helper function
#include "system.h"


#pragma warning(disable : 4996)