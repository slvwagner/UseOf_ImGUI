
// Included 

#pragma once
#define IMGUI_DEFINE_MATH_OPERATORS
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

// c
#include <algorithm>
#include <math.h>
#include <random>

// ffmpeg
extern "C" {
#include <libavcodec/avcodec.h>
#include <libavformat/avformat.h>
#include <libswscale/swscale.h>
}


class UseImGui {
public:
  void Init(GLFWwindow* window, const char* glsl_version);
  void NewFrame();
  virtual void Update();
  void Render();
  void Shutdown();
};