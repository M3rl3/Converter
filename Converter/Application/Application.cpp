#include "Application.h"
#include "../Global/OpenGL.h"

#include <iostream>
#include <sstream>

Application::Application()
{
    m_Window = new Window();
    m_Timer = new Timer();
    m_GUI = new UI();
}

Application::~Application()
{
}

void Application::Initialize(const char* title, const int width, const int height, bool fullScreen)
{
    // Init GLFW
    if (!glfwInit()) {
        std::cout << "GLFW init failed." << std::endl;
        glfwTerminate();
        return;
    }

    // Fullscreen support based on current monitor
    if (fullScreen) {
        GLFWmonitor* currentMonitor = glfwGetPrimaryMonitor();

        const GLFWvidmode* mode = glfwGetVideoMode(currentMonitor);

        glfwWindowHint(GLFW_RED_BITS, mode->redBits);
        glfwWindowHint(GLFW_GREEN_BITS, mode->greenBits);
        glfwWindowHint(GLFW_BLUE_BITS, mode->blueBits);
        glfwWindowHint(GLFW_REFRESH_RATE, mode->refreshRate);

        m_Window->m_Width = mode->width;
        m_Window->m_Height = mode->height;
        m_Window->m_WindowTitle = title;
        m_Window->m_FullScreen = fullScreen;

        m_Window->m_GlfwWindow = glfwCreateWindow(m_Window->m_Width, m_Window->m_Height, m_Window->m_WindowTitle, currentMonitor, NULL);
    }
    // Otherwise uses the provied size for window
    else {
        m_Window->m_Width = width;
        m_Window->m_Height = height;
        m_Window->m_WindowTitle = title;
        m_Window->m_FullScreen = fullScreen;

        m_Window->m_GlfwWindow = glfwCreateWindow(m_Window->m_Width, m_Window->m_Height, m_Window->m_WindowTitle, NULL, NULL);
    }

    // Check if window was initialized
    if (!m_Window->m_GlfwWindow) {
        std::cout << "Window creation failed." << std::endl;
        glfwTerminate();
        return;
    }

    // Set aspect ratio
    glfwSetWindowAspectRatio(m_Window->m_GlfwWindow, 16, 9);

    // GLFW and GLSL version
    m_Window->m_GlslVersion = "#version 420";
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // keyboard callback
    glfwSetKeyCallback(m_Window->m_GlfwWindow, m_Window->ProcessInput);

    // mouse callback
    glfwSetMouseButtonCallback(m_Window->m_GlfwWindow, m_Window->ProcessMouseInput);

    // capture mouse input
    glfwSetInputMode(m_Window->m_GlfwWindow, GLFW_CURSOR, GLFW_CURSOR_NORMAL);

    // Error callback
    glfwSetErrorCallback(m_Window->ErrorCallback);

    // Bring the window in front
    glfwMakeContextCurrent(m_Window->m_GlfwWindow);

    // Get process address for the app
    if (!gladLoadGLLoader((GLADloadproc)(glfwGetProcAddress))) {
        std::cout << "Error: unable to obtain pocess address." << std::endl;
        return;
    }

    // Initialize UI
    m_GUI->Initialize(m_Window);

    // vertical sync
    glfwSwapInterval(1);
}

void Application::Update(float dt)
{
    memcpy(&(m_Window->m_KeyPressedID[0]), &(m_Window->m_LastKeyPressedID[0]), 255);

    if (m_GUI->m_Render)
    {
        m_GUI->Update(dt);
    }

    // Update current time
    m_Timer->Update();

    // check if update is available
    if (m_Timer->IsUpdateAvailable()) 
    {
        // Increment frame counter
        frameCount++;
    }

    // Get elapsed time 
    deltaTime += m_Timer->GetElapsedTime();

    // Update window title
    if (deltaTime >= 1.f / 30.f)
    {
        // Window title
        std::stringstream ssTitle;

        ssTitle.str("");

        // Gets the GPU that's in use
        const GLubyte* vendor = glGetString(GL_VENDOR);
        const GLubyte* renderer = glGetString(GL_RENDERER);

        // Calculate Frame rate & Frame time
        frameRate = (1.f / deltaTime) * frameCount;
        frameTime = (deltaTime / frameCount) * 1000;

        ssTitle 
            << " Converter v1.0 " 
            << " FPS: " << frameRate
            << " ms: " << frameTime 
            << " GPU: " << renderer;

        // Set window title
        glfwSetWindowTitle(m_Window->m_GlfwWindow, ssTitle.str().c_str());

        // Reset counters
        frameCount = 0;
        deltaTime = 0.f;
    }

    glfwSwapBuffers(m_Window->m_GlfwWindow);
    glfwPollEvents();
}

void Application::Shutdown(void)
{
    m_GUI->Shutdown();
    m_GUI = nullptr;
    delete m_GUI;

    m_Window->Shutdown();
    m_Window = nullptr;
    delete m_Window;

    m_Timer = nullptr;
    delete m_Timer;
}

Window* Application::GetWindow(void)
{
    return m_Window;
}

Timer* Application::GetTimer(void)
{
    return m_Timer;
}