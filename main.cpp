#include <iostream>
#include <glad/glad.h>
#include <glfw/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "model.h"
#include "Shader.h"
#include "window.h"
#include "camera.h"

const int WIDTH = 1000;
const int HEIGHT = 800;
const std::string NAME = "Project";

void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);

// Камера
Camera camera(glm::vec3(0.0f, 0.0f, 10.0f));
float lastX = WIDTH / 2.0f;
float lastY = HEIGHT / 2.0f;
bool firstMouse = true;
// Тайминги
float deltaTime = 0.0f;	// время между текущим кадром и последним кадром
float lastFrame = 0.0f;

std::vector<float> triagle = {
    0.5f,  0.5f, 0.0f,  // Top Right
    0.5f, -0.5f, 0.0f,  // Bottom Right
     -0.5f, -0.5f, 0.0f,  // Bottom Left
        -0.5f,  0.5f, 0.0f   // Top Left 
};

std::vector<unsigned int> indices = {  // Note that we start from 0!
       0, 1, 3,  // First Triangle
       1, 2, 3   // Second Triangle
};

int main()
{
    Model model_;
    //Shader cube("D:\\c++\\Learn[OpenGL]\\Learn[OpenGL]\\cube.vs","D:\\c++\\Learn[OpenGL]\\Learn[OpenGL]\\cube.fs");

    init_window();

    GLFWwindow* window = create_window(WIDTH, HEIGHT, NAME.c_str());

    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetScrollCallback(window, scroll_callback);

    loadGlad();
        
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    glEnable(GL_DEPTH_TEST);

    model_.LoadModel("D:\\c++\\Model_reader\\models\\Copper_key.ply");
    Shader cube("D:\\c++\\Model_reader\\cube.vs", "D:\\c++\\Model_reader\\cube.fs");
    
    Attributes at;
   
    glBindVertexArray(at.get_VAO());
    at.set_VBO(model_.vertex);
    at.set_EBO(model_.index);
    
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, (void*)0);
    glEnableVertexAttribArray(0);


    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    glm::vec3 Color;

    while (!glfwWindowShouldClose(window))
    {
        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        // Обработка ввода
        processInput(window,deltaTime,camera);

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // очищаем буфер цвета и буфер глубины

        cube.use();
        float x = 0.5f;
        float z = 0.1f;
        float y = 0.7f;

        cube.setFloat3("Color", glm::vec3(x, y, z));

        // Передаем шейдеру матрицу проекции (поскольку проекционная матрица редко меняется, то нет необходимости делать это для каждого кадра)
        glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)WIDTH / (float)HEIGHT, 0.1f, 1000.0f);
        cube.setMat4("proj", projection);

        // Создаем преобразование камеры/вида
        glm::mat4 view = camera.GetViewMatrix();
        cube.setMat4("view", view);
        glBindVertexArray(at.get_VAO());

        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f) );
        model = glm::scale(model, glm::vec3(0.1));
        model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
        model = glm::rotate(model, glm::radians(180.0f), glm::vec3(0.0f, 0.0f, 1.0f));
        model = glm::rotate(model, glm::radians((float)glfwGetTime() * (float)12), glm::vec3(0.0, 1.0, 0.0));
        cube.setMat4("model", model);

        glDrawElements(GL_TRIANGLES,model_.index.size(),/*indices.size()*/ GL_UNSIGNED_INT, 0);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    at.~Attributes();

    glfwTerminate();
    return 0;
}

// glfw: всякий раз, когда перемещается мышь, вызывается данная callback-функция
void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
    if (firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos; // перевернуто, так как y-координаты идут снизу вверх

    lastX = xpos;
    lastY = ypos;

    camera.ProcessMouseMovement(xoffset, yoffset);
}

// glfw: всякий раз, когда прокручивается колесико мыши, вызывается данная callback-функция
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    camera.ProcessMouseScroll(yoffset);
}