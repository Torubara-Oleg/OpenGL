#include <iostream>
#include <glad/glad.h>
#include <glfw/glfw3.h>
#include "model.h"
#include "Shader.h"
#include "window.h"

const int WIDTH = 1000;
const int HEIGHT = 800;
const std::string NAME = "Project";

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
    Model model;
    //Shader cube("D:\\c++\\Learn[OpenGL]\\Learn[OpenGL]\\cube.vs","D:\\c++\\Learn[OpenGL]\\Learn[OpenGL]\\cube.fs");

    init_window();

    GLFWwindow* window = create_window(WIDTH, HEIGHT, NAME.c_str());

    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    loadGlad();
        
    Hello();

    model.LoadModel("D:\\c++\\Model_reader\\models\\Fantasy_Dragon.ply");
    Shader cube("D:\\c++\\Model_reader\\cube.vs", "D:\\c++\\Model_reader\\cube.fs");
    
    Attributes at;
   
    glBindVertexArray(at.get_VAO());
    at.set_VBO(triagle);
    at.set_EBO(indices);
    
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, (void*)0);
    glEnableVertexAttribArray(0);


    while (!glfwWindowShouldClose(window))
    {
        processInput(window);

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        cube.use();
        glBindVertexArray(at.get_VAO());
        //glDrawArrays(GL_TRIANGLES, 0, 3);

        glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}