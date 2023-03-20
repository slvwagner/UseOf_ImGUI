// imGUIexample.cpp : Defines the entry point for the application.
//
#include "Header.h"
using namespace cv;

// initialize a video capture object(`s)
VideoCapture vid_capture0(cam0);
VideoCapture vid_capture1(cam1);


/// <summary>
/// set web cam settings
/// </summary>
void videoSettings() {
	vid_capture0.set(cv::CAP_PROP_FRAME_WIDTH, frameWidth);
	vid_capture0.set(cv::CAP_PROP_FRAME_HEIGHT, frameHeight);
	vid_capture1.set(cv::CAP_PROP_FRAME_WIDTH, frameWidth);
	vid_capture1.set(cv::CAP_PROP_FRAME_HEIGHT, frameHeight);
}

/// <summary>
/// load a singl frame
/// </summary>
void loadFrame() {

	// Video frames
	Mat frame0, frame1;

	//show video 
	// Check if the camera was opened successfully
	if (!(vid_capture0.isOpened() && vid_capture1.isOpened()))
	{
		std::cout << "Error opening camera" << std::endl;
	}
	// set correct resolution accoring to camer typ
	vid_capture0.read(frame0);
	vid_capture1.read(frame1);
}

/// <summary>
/// 2. Part of the class to create an ImGui object
/// </summary>
class CustomImGui : public UseImGui {
public:

	void loadImage(char const* fileNamePath) {
		int image_width = 0;
		int image_height = 0;
		unsigned char* image_data = stbi_load(fileNamePath, &image_width, &image_height, NULL, 4);
		if (image_data != NULL) {
			glGenTextures(1, &my_image_texture);
			glBindTexture(GL_TEXTURE_2D, my_image_texture);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image_width, image_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image_data);
			stbi_image_free(image_data);
			my_image_width = image_width;
			my_image_height = image_height;
		}
	}

	virtual void Update() override {

		// Webcam frames
		loadFrame();

		// Show Image in Gui
		ImGui::Begin("OpenGL Texture Text");
		ImGui::Text("pointer = %p", my_image_texture);
		ImGui::Text("size = %d x %d", my_image_width, my_image_height);
		ImGui::Image((void*)(intptr_t)my_image_texture, ImVec2(my_image_width, my_image_height));
		ImGui::End();

		// render your GUI
		static float f = 0.0f;
		static int counter = 0;
		ImGui::Begin("CustomImGui Hello, world!");              // Create a window called "Hello, world!" and append into it.
		ImGui::Text("This is some useful text.");               // Display some text (you can use a format strings too)
		ImGui::SliderFloat("float", &f, 0.0f, 1.0f);            // Edit 1 float using a slider from 0.0f to 1.0f
		bool clear_color_changed = ImGui::ColorEdit3("clear color", (float*)clear_color); // Edit 3 floats representing a color
		if (ImGui::Button("Button"))                            // Buttons return true when clicked (most widgets return true when edited/activated)
			counter++;
		ImGui::SameLine();
		ImGui::Text("counter = %d", counter);
		ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
		ImGui::End();

		if (clear_color_changed) {
			change_clear_color(clear_color[0], clear_color[1], clear_color[2]);
		}
	}

private:
	float clear_color[3] = { .0f, .0f, .0f };
	void change_clear_color(float r, float g, float b) {
		glClearColor(r, g, b, 1.00f);
	}
	// Image Data 
	int my_image_width = 0;
	int my_image_height = 0;
	GLuint my_image_texture = 0;
};


/// <summary>
/// Testing ImGui 
/// show Pictures
/// </summary>
/// <returns></returns>
int main()
{
	// Setup window
	if (!glfwInit())
		return 1;

	// GL 3.0 + GLSL 130
	const char *glsl_version = "#version 130";
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
	//glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);  // 3.2+ only
	//glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);            // 3.0+ only

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
	// Load image to display just once
	myimgui.loadImage("D:/src_D/UseOf_ImGUI/imGUIexample/Picts/logo weiss marine blau.png");

	//Set Webcam settings
	videoSettings();

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
	destroyAllWindows();

	return 0;
}
