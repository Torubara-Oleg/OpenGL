#ifndef SHADER_H
#define SHADER_H

#include <glad/glad.h> // подключаем glad для активации всех заголовочных файлов OpenGL
#include "glm/glm.hpp"
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <unordered_map>

class Shader
{
public:
    unsigned int ID;

    mutable std::unordered_map<std::string, GLint> Uniform_cache; /*делает переменные в константной среде изменяемыми, например в const методах 
                                                                  сама map нужна для храненения кеша Uniform переменных шейдерной программы*/
    // Конструктор генерирует шейдер на лету
    Shader(const char* vertexPath, const char* fragmentPath)
    {
        // Этап №1: Получение исходного кода вершинного/фрагментного шейдера из переменной filePath
        std::string vertexCode;
        std::string fragmentCode;
        std::ifstream vShaderFile;
        std::ifstream fShaderFile;

        // Убеждаемся, что объекты ifstream могут выбросить исключение
        vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
        fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
        try
        {
            // Открываем файлы
            vShaderFile.open(vertexPath);
            fShaderFile.open(fragmentPath);
            std::stringstream vShaderStream, fShaderStream;

            // Считываем содержимое файловых буферов в потоки 
            vShaderStream << vShaderFile.rdbuf();
            fShaderStream << fShaderFile.rdbuf();

            // Закрываем файлы
            vShaderFile.close();
            fShaderFile.close();

            // Конвертируем данные из потока в строковые переменные
            vertexCode = vShaderStream.str();
            fragmentCode = fShaderStream.str();
        }
        catch (std::ifstream::failure& e)
        {
            std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
        }
        const char* vShaderCode = vertexCode.c_str();
        const char* fShaderCode = fragmentCode.c_str();

        // Этап №2: Компилируем шейдеры
        unsigned int vertex, fragment;

        // Вершинный шейдер
        vertex = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vertex, 1, &vShaderCode, NULL);
        glCompileShader(vertex);
        checkCompileErrors(vertex, "VERTEX");

        // Фрагментный шейдер
        fragment = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fragment, 1, &fShaderCode, NULL);
        glCompileShader(fragment);
        checkCompileErrors(fragment, "FRAGMENT");

        // Шейдерная программа
        ID = glCreateProgram();
        glAttachShader(ID, vertex);
        glAttachShader(ID, fragment);
        glLinkProgram(ID);
        checkCompileErrors(ID, "PROGRAM");

        // После того, как мы связали шейдеры с нашей программой, удаляем их, так как они нам больше не нужны
        glDeleteShader(vertex);
        glDeleteShader(fragment);
    }

    // Активация шейдера
    void use()
    {
        glUseProgram(ID);
    }

    // Полезные uniform-функции
    void setBool(const std::string& name, bool value) const
    {
        glUniform1i(getUniformLocation(name), (int)value);
    }
    void setInt(const std::string& name, int value) const
    {
        glUniform1i(getUniformLocation(name), value);
    }
    void setFloat(const std::string& name, float value) const
    {
        glUniform1f(getUniformLocation(name), value);
    }
    void setFloat3(const std::string& name, glm::vec3 val) const
    {
        glUniform3f(getUniformLocation(name), val.x, val.y, val.z);
    }

    void setMat4(const std::string& name, const glm::mat4& mat) const
    {
        glUniformMatrix4fv(getUniformLocation(name), 1, GL_FALSE, &mat[0][0]);
    }

private:
    // Полезные функции для проверки ошибок компиляции/связывания шейдеров
    void checkCompileErrors(unsigned int shader, std::string type)
    {
        int success;
        char infoLog[1024];
        if (type != "PROGRAM")
        {
            glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
            if (!success)
            {
                glGetShaderInfoLog(shader, 1024, NULL, infoLog);
                std::cout << "ERROR::SHADER_COMPILATION_ERROR of type: " << type << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
            }
        }
        else
        {
            glGetProgramiv(shader, GL_LINK_STATUS, &success);
            if (!success)
            {
                glGetProgramInfoLog(shader, 1024, NULL, infoLog);
                std::cout << "ERROR::PROGRAM_LINKING_ERROR of type: " << type << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
            }
        }
    }

    GLint getUniformLocation(const std::string& name) const //выполняет кеширование Uniform переменных(их адресов)
    {
        if (Uniform_cache.find(name) != Uniform_cache.end())
        {
            return Uniform_cache[name];
        }

        GLint location = glGetUniformLocation(ID, name.c_str());
        Uniform_cache[name] = location;
        return location;
    }
};
#endif