#include "Window.h"

Window::Window() :
	m_GlfwWindow(nullptr),
	m_Width(NULL),
	m_Height(NULL),
	m_FullScreen(false),
	m_WindowTitle(""),
	m_GlslVersion("")
{
	for (size_t i = 0; i < 255; i++) 
	{
		m_KeyPressedID[i] = false;
		m_LastKeyPressedID[i] = false;
	}
}

Window::~Window() 
{
}

bool* Window::GetKeyPressedArray()
{
	return m_KeyPressedID;
}

bool Window::IsKeyHeldDown(unsigned char key)
{
	return m_LastKeyPressedID[key] && m_KeyPressedID[key];
}

bool Window::IsKeyPressed(unsigned char key)
{
	return !m_LastKeyPressedID[key] && m_KeyPressedID[key];
}

bool Window::IsKeyReleased(unsigned char key)
{
	return m_LastKeyPressedID[key] && !m_KeyPressedID[key];
}

// keyboard callback
void Window::ProcessInput(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	Window* altWindow = static_cast<Window*>(glfwGetWindowUserPointer(window));

	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) 
	{
		glfwSetWindowShouldClose(window, GLFW_TRUE);
	}

	if (key > 0 && key < 255) 
	{
		if (action == GLFW_PRESS) 
		{
			altWindow->m_KeyPressedID[key] = true;
		}
		else if (action == GLFW_RELEASE) 
		{
			altWindow->m_KeyPressedID[key] = false;
		}
	}
}

// mouse callback
void Window::ProcessMouseInput(GLFWwindow* window, int button, int action, int mods)
{
	if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
	{

	}

	if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_PRESS)
	{

	}

	if (button == GLFW_MOUSE_BUTTON_MIDDLE && action == GLFW_PRESS)
	{

	}
}

// If something goes wrong
void Window::ErrorCallback(int error, const char* description)
{
	fprintf(stderr, "Error: %s\n", description);
}

void Window::Shutdown(void)
{
	// Shutdown the window and GLFW
	glfwDestroyWindow(m_GlfwWindow);
	glfwTerminate();

	// Delete the pointer
	m_GlfwWindow = nullptr;
	delete m_GlfwWindow;
}