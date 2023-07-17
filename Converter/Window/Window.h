#pragma once

#include "../Global/OpenGL.h"

#include <iostream>

// Class holding the window object and its size
class Window {
public:
	// Constructor
	Window();

	// Destructor
	~Window();

	// The main window
	GLFWwindow* m_GlfwWindow;

	// Window width
	int m_Width;

	// Window height
	int m_Height;

	// Fullscreen toggle
	bool m_FullScreen;

	// Window title
	const char* m_WindowTitle;

	// GLSL Version
	const char* m_GlslVersion;

	// boolean arrays for handling keyboard input
	bool m_KeyPressedID[255];
	bool m_LastKeyPressedID[255];

	bool* GetKeyPressedArray();

	bool IsKeyHeldDown(unsigned char key);
	bool IsKeyPressed(unsigned char key);
	bool IsKeyReleased(unsigned char key);

	// keyboard callback
	static void ProcessInput(GLFWwindow* window, int key, int scancode, int action, int mods);

	// mouse callback
	static void ProcessMouseInput(GLFWwindow* window, int button, int action, int mods);

	// If something goes wrong
	static void ErrorCallback(int error, const char* description);

	void Shutdown(void);
};