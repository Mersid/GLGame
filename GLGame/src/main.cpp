#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "event/EventBus.h"
#include "eventbus/EventBusThree.h"
#include "eventbus/EventBusTwo.h"
#include "events/KeyPressEvent.h"
#include "render/Shader.h"
#include "fileio/stb_image.h"

EventBus eventBus;
EventBusTwo<void(int, int, int, int)> eventBusTwo;
EventBusThree<void(int, int, int, int)> event_bus_three;
EventBusThree<void(GLFWwindow* window, int width, int height)> windowSizeUpdate;

void processKeyboardInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}

void onWindowSizeUpdate(GLFWwindow* window, int width, int height)
{
	//std::cout << "Frame buffer size changed: " << width << "x" << height << std::endl;
	windowSizeUpdate.Invoke(window, width, height);
	glViewport(0, 0, width, height);
}

void glOnKeyPress(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	KeyPressEvent e(key, scancode, action, mods);
	eventBus.Fire(e);

	event_bus_three.Invoke(key, scancode, action, mods);
	
	
}

void test(int a, int b, int c, int d)
{
	std::cout << "Hello world" << a << std::endl;
}

int main()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	event_bus_three.Register([](int a, int b, int c, int d) {std::cout << "Hello: " << a << std::endl;});
	event_bus_three.Register([](int a, int b, int c, int d) {std::cout << "Bai: " << a << std::endl;});
	windowSizeUpdate.Register([](GLFWwindow* wwindow, int width, int height) {std::cout << "Frame buffer size changed: " << width << "x" << height << std::endl;});
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

	unsigned int vao;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	unsigned int vbo;
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	unsigned int ebo;
	glGenBuffers(1, &ebo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);


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

	int width;
	int height;
	int channels;
	unsigned char* data = stbi_load("resources/textures/container.jpg", &width, &height, &channels, 0);

	unsigned int texture;
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE, texture);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
	glGenerateMipmap(texture);

	stbi_image_free(data);

	
	
	while (!glfwWindowShouldClose(window))
	{
		glClearColor(0.2f, 0.3f, 0.3f, 1);
		glClear(GL_COLOR_BUFFER_BIT);

		const float color = (sin(glfwGetTime()) + 1) / 2;
		//const unsigned int vertexColorLocation = glGetUniformLocation(shader.id, "vertexColor");
		shader.use();
		//shader.setFloat("vertexColor", color);
		
		//glUniform4f(vertexColorLocation, 0, color, 0, 1);
		
		//glDrawArrays(GL_TRIANGLES, 0, 3);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		processKeyboardInput(window);

		glfwPollEvents();
		glfwSwapBuffers(window);
	}

	glfwTerminate();
	return 0;
}
