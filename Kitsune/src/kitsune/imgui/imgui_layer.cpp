#include "kitsune_pch.h"

#include "imgui_layer.h"
#include "kitsune/application.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <imconfig.h>
#include <imgui.h>
#include <backends/imgui_impl_glfw.h>
#include <backends/imgui_impl_opengl3.h>

namespace kitsune
{
	ImGuiLayer::ImGuiLayer() :Layer("imgui_layer")
	{
	}

	ImGuiLayer::~ImGuiLayer()
	{
	}

	void ImGuiLayer::on_attach()
	{
		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		ImGuiIO& io = ImGui::GetIO(); (void)io;
		io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
		io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

		// Setup Dear ImGui style
		ImGui::StyleColorsDark();

		GLFWwindow* window = (GLFWwindow*)Application::get().get_window().get_native_window();

		const char* glsl_version = "#version 130";

		ImGui_ImplGlfw_InitForOpenGL(window, true);
		ImGui_ImplOpenGL3_Init(glsl_version);

	}

	void ImGuiLayer::on_detach()
	{
		ImGui_ImplOpenGL3_Shutdown();
		ImGui_ImplGlfw_Shutdown();
		ImGui::DestroyContext();
	}

	void ImGuiLayer::on_update()
	{
		ImGuiIO& io = ImGui::GetIO(); (void)io;
		Application& app = Application::get();
		io.DisplaySize = ImVec2((float)app.get_window().get_width(), (float)app.get_window().get_height());
		float time = (float)glfwGetTime(); 
		io.DeltaTime = (_time > 0.0f) ? (time - _time) : (1.0f / 60.0f); 
		_time = time;

		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		static bool show_demo_window = true;
		ImGui::ShowDemoWindow(&show_demo_window);

		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	}
	void ImGuiLayer::on_event(Event& event)
	{
	}
}