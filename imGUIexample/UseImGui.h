
// Included 

#pragma once

#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <fstream>
#include <iostream>
#include <cstdlib>

#include <array>
#include <vector>
#include <list>
#include <map>
#include <stack>

#include <algorithm>
#include <math.h>
#include <random>


class UseImGui {
public:
  void Init(GLFWwindow* window, const char* glsl_version);
  void NewFrame();
  virtual void Update();
  void Render();
  void Shutdown();
};