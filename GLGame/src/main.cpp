#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Event.h"
#include "render/Shader.h"
#include <crtdbg.h>
#include <xutility>

#include "render/VertexArray.h"
#include "render/VertexElementBuffer.h"
#include "Debug.h"
#include "glm/detail/func_trigonometric.hpp"

#include "glm/detail/type_mat.hpp"
#include "glm/detail/type_vec.hpp"
#include "glm/gtx/transform.hpp"
#include "glm/gtc/type_ptr.hpp"

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
	-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
	 0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
	-0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

	-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	-0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	 0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	 0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
	 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
	 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

	-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	-0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
	-0.5f,  0.5f, -0.5f,  0.0f, 1.0f
	};

	unsigned int indices[] = {
		0, 1, 3,
		1, 2, 3
	};

	glm::vec3 cubePositions[] = {
		glm::vec3(0.0f,  0.0f,  0.0f),
		glm::vec3(2.0f,  5.0f, -15.0f),
		glm::vec3(-1.5f, -2.2f, -2.5f),
		glm::vec3(-3.8f, -2.0f, -12.3f),
		glm::vec3(2.4f, -0.4f, -3.5f),
		glm::vec3(-1.7f,  3.0f, -7.5f),
		glm::vec3(1.3f, -2.0f, -2.5f),
		glm::vec3(1.5f,  2.0f, -2.5f),
		glm::vec3(1.5f,  0.2f, -1.5f),
		glm::vec3(-1.3f,  1.0f, -1.5f)
	};


	const VertexArray vertexArray;
	vertexArray.bind();
	
	VertexElementBuffer vertexElementBuffer;
	vertexElementBuffer.bind();
	vertexElementBuffer.setVertices(vertices, std::size(vertices));
	vertexElementBuffer.setIndices(indices, std::size(indices));
	
	const Shader shader("resources/shaders/vertex.glsl", "resources/shaders/fragment.glsl");
	shader.use();
	
	glEnable(GL_DEPTH_TEST);
	
	// Position
	glVertexAttribPointer(0, 3, GL_FLOAT, false, 5 * sizeof(float), nullptr);
	glEnableVertexAttribArray(0);

	// Texture
	glVertexAttribPointer(1, 2, GL_FLOAT, false, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	
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
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		processKeyboardInput(window);

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture.getId());
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, texture2.getId());

		shader.use();

		glm::mat4 view = glm::mat4(1.0f);
		view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));

		glm::mat4 projection;
		projection = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f);

		shader.setMat4("projection", projection);
		shader.setMat4("view", view);

		for (int i = 0; i < 10; i++)
		{
			const float angle = 20.0f * (i == 0 ? 1 : i) * glfwGetTime();

			glm::mat4 model = glm::mat4(1.0f);
			model = glm::translate(model, cubePositions[i]);
			model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
			shader.setMat4("model", model);

			//glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
			glDrawArrays(GL_TRIANGLES, 0, 36);
			
		}
		

		glfwPollEvents();
		glfwSwapBuffers(window);
	}

	glfwTerminate();
	return 0;
}
