// imGUIexample.cpp : Defines the entry point for the application.
//
#include "Header.h"

/// <summary>
/// Testing ImGui 
/// show Pictures
/// </summary>
/// <returns>returns 0 if normal shutdown</returns>
int main()
{
	// Print working directory 
	cout << getwd();
	
	// Setup window
	if (!glfwInit())
		return 1;

	// GL 3.0 + GLSL 130
	const char *glsl_version = "#version 130";
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);  // 3.2+ only
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);            // 3.0+ only

	// Create window with graphics context
	GLFWwindow *window = glfwCreateWindow(1280, 720, "Dear ImGui - Example", NULL, NULL);
	if (window == NULL)
		return 1;
	glfwMakeContextCurrent(window);
	glfwSwapInterval(1); // Enable vsync

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))  // tie window context to glad's opengl funcs
		throw("Unable to context to OpenGL");

	int screen_width, screen_height;
	glfwGetFramebufferSize(window, &screen_width, &screen_height);
	glViewport(0, 0, screen_width, screen_height);

	// Create GUI object
	CustomImGui myimgui;
	myimgui.Init(window, glsl_version);
	// Load image just once 
	myimgui.loadImage("picts/wagnius.png");

	//Setting up Webcam 
	videoSettings();
	loadFrame(); // single frame needed to calculate GPU memory allocation

	// setting up OpenGL (Allocate GPU memory)
	initTexture(frame0, imageTexture_cam0);
	initTexture(frame1, imageTexture_cam1);
	// releas frames is needed before loading new frame within the .Update() method
	frame0.release(); 
	frame1.release();

	// ImGui update
	while (!glfwWindowShouldClose(window)) {
		glfwPollEvents();
		glClear(GL_COLOR_BUFFER_BIT);
		myimgui.NewFrame();
		myimgui.Update();
		myimgui.Render();
		glfwSwapBuffers(window);
	}
	myimgui.Shutdown();

	// reles webcams 
	vid_capture0.release();
	vid_capture0.release();

	// No problems to run the code 
	return 0;
}
