#include "Header.h"

class UseImGui {
public:
  void Init(GLFWwindow* window, const char* glsl_version);
  void NewFrame();
  virtual void Update();
  void Render();
  void Shutdown();
};

/// <summary>
/// 2. Part of the class to create an ImGui object
/// </summary>
class CustomImGui : public UseImGui {
public:

	/// <summary>
	/// load Image only once to GPU memory 
	/// </summary>
	/// <param name="fileNamePath"></param>
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

	/// <summary>
	/// Custom update 
	/// </summary>
	virtual void Update() override {

		// Webcam frames
		loadFrame();
		BindCVMat2GLTexture(frame0, imageTexture_cam0);
		BindCVMat2GLTexture(frame1, imageTexture_cam1);
		frame0.release();
		frame1.release();

		// Show video cam0
		ImGui::Begin("cam0");
		ImGui::Text("pointer = %p", imageTexture_cam0);
		ImGui::Text("size = %d x %d", frameWidth, frameHeight);
		ImGui::Image((void*)(intptr_t)imageTexture_cam0, ImVec2(frameWidth, frameHeight));
		ImGui::End();

		// Show video cam1
		ImGui::Begin("cam1");
		ImGui::Text("pointer = %p", imageTexture_cam1);
		ImGui::Text("size = %d x %d", frameWidth, frameHeight);
		ImGui::Image((void*)(intptr_t)imageTexture_cam1, ImVec2(frameWidth, frameHeight));
		ImGui::End();

		// Show Image in Gui
		ImGui::Begin("OpenGL Texture Text");
		ImGui::Text("pointer = %p", my_image_texture);
		ImGui::Text("size = %d x %d", my_image_width, my_image_height);
		ImGui::Image((void*)(intptr_t)my_image_texture, ImVec2(my_image_width, my_image_height));
		ImGui::End();

		//ImPlot::ShowDemoWindow();
		/*
		// ImPlot example
		double   bar_data[4] = {1,2,2.5,15};
		ImGui::Begin("My Window");
		if (ImPlot::BeginPlot("My Plot")) {
			ImPlot::PlotBars("My Bar Plot", bar_data, 4);
			ImPlot::EndPlot();
		}
		ImGui::End();
		*/

		// CustomImGui Hello, world! 
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

		// Generate samples and plot them
		float samples[100];
		for (int n = 0; n < 100; n++)
			samples[n] = sinf(n * 0.2f + ImGui::GetTime() * 2.5f);
		ImGui::PlotLines("Samples", samples, 100);

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
