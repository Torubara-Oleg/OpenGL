#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "KHR/khrplatform.h"
#include <iostream>
#include <vector>
#include "camera.h"

#define ASSERT(x) if(!(x)) __debugbreak();
#define GL_func(x) GlClearError();\
        x;\
        ASSERT(GLlog(#x,__FILE__,__LINE__));

void GlClearError();

bool GLlog(const char* function, const char* file, int line);

void init_window();

GLFWwindow* create_window(int SCR_WIDTH, int SCR_HEIGHT, const char* name);

void processInput(GLFWwindow* window, float deltaTime, Camera& camera);
// glfw: вс€кий раз, когда измен€ютс€ размеры окна (пользователем или операционной системой), вызываетс€ данна€ callback-функци€
void framebuffer_size_callback(GLFWwindow* window, int width, int height);

int loadGlad();

void DrawMode_Polygon();