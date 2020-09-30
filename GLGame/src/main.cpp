#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Event.h"
#include "render/Shader.h"
#include <crtdbg.h>
#include <xutility>

#include "fileio/stb_image.h"
#include "render/VertexArray.h"
#include "render/VertexElementBuffer.h"
#include "Debug.h"
#include "render/Texture.h"

Event<void(int, int, int, int)> KeyPressEvent;
Event<void(int, int)> WindowSizeEvent;

void processKeyboardInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}

void onWindowSizeUpdate(GLFWwindow* window, int width, int height)
{
	WindowSizeEvent.invoke(width, height);
	glViewport(0, 0, width, height);
}

void glOnKeyPress(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	KeyPressEvent.invoke(key, scancode, action, mods);
}


int main()
{
	DebugInit();
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	WindowSizeEvent.Register([](int w, int h) {std::cout << "Screen size changed! " << w << "x" << h << std::endl;});
	KeyPressEvent.Register([](int key, int scancode, int action, int mods)
		{
			std::cout << "Key pressed: " << "Key: " << key << ", Scancode: " << scancode << ", Action: " << action << ", Mods: " << mods << std::endl;
		});
	GLFWwindow* window = glfwCreateWindow(800, 600, "Learn OpenGL", nullptr, nullptr);
	if (window == nullptr)
	{
		std::cout << "GLFW window failed to initialize" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);

	if (!gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress)))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	glViewport(0, 0, 800, 600);
	
	glfwSetFramebufferSizeCallback(window, onWindowSizeUpdate);
	glfwSetKeyCallback(window, glOnKeyPress);

	float vertices[] = {
		// positions          // colors           // texture coords
		 0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // top right
		 0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // bottom right
		-0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // bottom left
		-0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f    // top left 
	};

	unsigned int indices[] = {
		0, 1, 3,
		1, 2, 3
	};

	
	VertexArray vertexArray;
	vertexArray.bind();
	
	VertexElementBuffer vertexElementBuffer;
	vertexElementBuffer.bind();
	vertexElementBuffer.setVertices(vertices, std::size(vertices));
	vertexElementBuffer.setIndices(indices, std::size(indices));
	
	const Shader shader("resources/shaders/vertex.glsl", "resources/shaders/fragment.glsl");
	shader.use();
	

	
	// Position
	glVertexAttribPointer(0, 3, GL_FLOAT, false, 8 * sizeof(float), nullptr);
	glEnableVertexAttribArray(0);

	// Color
	glVertexAttribPointer(1, 3, GL_FLOAT, false, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	// Texture
	glVertexAttribPointer(2, 2, GL_FLOAT, false, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);
	
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	
	const Texture texture("resources/textures/container.jpg");
	texture.load();
	
	const Texture texture2("resources/textures/awesomeface.png");
	texture2.load();

	shader.setInt("texture1", 0);
	shader.setInt("texture2", 1);

	
	while (!glfwWindowShouldClose(window))
	{
		glClearColor(0.2f, 0.3f, 0.3f, 1);
		glClear(GL_COLOR_BUFFER_BIT);

		const float color = (sin(glfwGetTime()) + 1) / 2;
		//const unsigned int vertexColorLocation = glGetUniformLocation(shader.id, "vertexColor");
		
		//shader.setFloat("vertexColor", color);
		
		//glUniform4f(vertexColorLocation, 0, color, 0, 1);
		
		//glDrawArrays(GL_TRIANGLES, 0, 3);
		
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture.getId());
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, texture2.getId());

		
		shader.use();
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		processKeyboardInput(window);

		glfwPollEvents();
		glfwSwapBuffers(window);
	}

	glfwTerminate();
	return 0;
}
