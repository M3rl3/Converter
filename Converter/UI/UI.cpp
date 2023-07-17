#include "UI.h"

#include "../imgui/imgui.h"
#include "../imgui/imgui_impl_glfw.h"
#include "../imgui/imgui_impl_opengl3.h"

UI::UI() : m_Render(true)
{
}

UI::~UI()
{
}

void UI::Initialize(Window* window)
{
    // Init dear ImGUI	
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();

    // Setup Platform/Renderer bindings
    ImGui_ImplGlfw_InitForOpenGL(window->m_GlfwWindow, true);
    ImGui_ImplOpenGL3_Init(window->m_GlslVersion);

    // dark theme
    ImGui::StyleColorsDark();		
}

void UI::Update(float dt)
{
    // Start a new frame
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    ImGui::Begin("ass");
    ImGui::End();

    // Render imgui stuff to screen
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void UI::Shutdown()
{
    ImGui_ImplGlfw_Shutdown();
    ImGui_ImplOpenGL3_Shutdown();
    ImGui::DestroyContext();
}