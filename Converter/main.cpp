#include "Global/OpenGL.h"
#include "Application/Application.h"

// main entry point
int main(int argc, char** argv) 
{
	Application application;

	application.Initialize("Converter", 1366, 768, false);

	while (!glfwWindowShouldClose(application.GetWindow()->m_GlfwWindow)) 
	{
		application.Update(application.GetTimer()->GetDeltaTime());
	}

	application.Shutdown();
}