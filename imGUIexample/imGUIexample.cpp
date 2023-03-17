// imGUIexample.cpp : Defines the entry point for the application.
//

#include <windows.h>
#include "UseImGui.h"
#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include <imgui.h>


// opencv dependencies 
#include <opencv2/calib3d.hpp>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include "opencv2/imgcodecs.hpp"

using namespace std;
using namespace cv;

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"


// Simple helper function to load an image into a OpenGL texture with common settings
bool LoadTextureFromFile(const char* filename, GLuint* out_texture, int* out_width, int* out_height)
{
	// Load from file
	int image_width = 0;
	int image_height = 0;
	unsigned char* image_data = stbi_load(filename, &image_width, &image_height, NULL, 4);
	if (image_data == NULL)
		return false;

	// Create a OpenGL texture identifier
	GLuint image_texture;
	glGenTextures(1, &image_texture);
	glBindTexture(GL_TEXTURE_2D, image_texture);

	// Setup filtering parameters for display
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE); // This is required on WebGL for non power-of-two textures
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE); // Same

	// Upload pixels into texture
#if defined(GL_UNPACK_ROW_LENGTH) && !defined(__EMSCRIPTEN__)
	glPixelStorei(GL_UNPACK_ROW_LENGTH, 0);
#endif
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image_width, image_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image_data);
	stbi_image_free(image_data);

	*out_texture = image_texture;
	*out_width = image_width;
	*out_height = image_height;

	return true;
}



class CustomImGui : public UseImGui {
public:
	virtual void Update() override {

		int my_image_width = 0;
		int my_image_height = 0;
		GLuint my_image_texture = 0;
		//bool ret = LoadTextureFromFile("C:\\Users\\slvwa\\OneDrive\\Desktop\\CV_pic_2023.jpg", &my_image_texture, &my_image_width, &my_image_height);
		bool ret = LoadTextureFromFile("C:/Users/slvwa/OneDrive/Desktop/CV_pic_2023.jpg", &my_image_texture, &my_image_width, &my_image_height);
		IM_ASSERT(ret);

		ImGui::Begin("OpenGL Texture Text");
		ImGui::Text("pointer = %p", my_image_texture);
		ImGui::Text("size = %d x %d", my_image_width, my_image_height);
		ImGui::Image((void*)(intptr_t)my_image_texture, ImVec2(my_image_width, my_image_height));
		ImGui::End();
		/*
		// Load image using stb_image library
		const string fileNamePath = "C:\\Users\\slvwa\\OneDrive\\Desktop\\CV_pic_2023.jpg";
		int width, height, num_channels;
		unsigned char* image_data = stbi_load(const CHAR(fileNamePath), &width, &height, &num_channels, 0);

		// Create OpenGL texture object
		GLuint texture_id;
		glGenTextures(1, &texture_id);
		glBindTexture(GL_TEXTURE_2D, texture_id);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image_data);
		glGenerateMipmap(GL_TEXTURE_2D);

		// Create window
		ImGui::Begin("Image Window");
		ImVec2 texture_size(width, height);
		ImGui::Image(reinterpret_cast<void*>(texture_id), texture_size);
		ImGui::End();
		*/

		/*
		// Load the image using OpenCV
		Mat image = cv::imread("C:/Users/slvwa/OneDrive/Desktop/CV_pic_2023.jpg", cv::COLOR_BGR2RGB);
		//resize(image, image, Size(500,700));
		//imshow("Pict", image);
		//waitKey(1);

		//int width = image.cols;
		//int height = image.rows;
		//int channels = image.channels();
		//std::cout << "\n" << "width" << width;
		//std::cout << "\n" << "height" << height;
		//std::cout << "\n" << "channels" << channels;

		std::vector<unsigned char> imgData;
		imgData.assign(image.datastart, image.dataend);

		unsigned char* data = &imgData[0];

		// Display the image using ImGui
		ImGui::Begin("Image Viewer");
		ImGui::Image((void*)&data, ImVec2(width/3, height/3));
		ImGui::End();
		*/

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
};



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

	CustomImGui myimgui;
	myimgui.Init(window, glsl_version);
	while (!glfwWindowShouldClose(window)) {
		glfwPollEvents();

		glClear(GL_COLOR_BUFFER_BIT);
		myimgui.NewFrame();
		myimgui.Update();
		myimgui.Render();
		glfwSwapBuffers(window);

	}
	myimgui.Shutdown();

	return 0;
}
