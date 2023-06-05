#pragma once
#include <glad/glad.h>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include "shader.hpp"
#include "glm/gtc/type_ptr.hpp"

Shader::Shader(const char* vertexPath, const char* fragmentPath) {
    std::string vertexCode;
    std::string fragmentCode;
    std::ifstream vShaderFile;
    std::ifstream fShaderFile;
    // ensure ifstream objects can throw exceptions:
    vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    try
    {
        // open files
        vShaderFile.open(vertexPath, std::ifstream::in);
        fShaderFile.open(fragmentPath, std::ifstream::in);
        std::stringstream vShaderStream, fShaderStream;
        // read file's buffer contents into streams
        vShaderStream << vShaderFile.rdbuf();
        fShaderStream << fShaderFile.rdbuf();
        // close file handlers
        vShaderFile.close();
        fShaderFile.close();
        // convert stream into string
        vertexCode = vShaderStream.str();
        fragmentCode = fShaderStream.str();
    }
    catch (std::ifstream::failure& e)
    {
        std::cout << "ERROR::SHADER::FILE_NOT_SUCCESSFULLY_READ: " << e.what() << std::endl;
    }
    const char* vShaderCode = vertexCode.c_str();
    const char* fShaderCode = fragmentCode.c_str();
    // 2. compile shaders
    unsigned int vertex, fragment;
    
    vertex = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex, 1, &vShaderCode, NULL);
    glCompileShader(vertex);
    checkCompileErrors(vertex, "VERTEX");
    
    fragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment, 1, &fShaderCode, NULL);
    glCompileShader(fragment);
    checkCompileErrors(fragment, "FRAGMENT");
    // shader Program
    programID = glCreateProgram();
    glAttachShader(programID, vertex);
    glAttachShader(programID, fragment);
    glLinkProgram(programID);
    checkCompileErrors(programID, "PROGRAM");
    // delete the shaders as they're linked into our program now and no longer necessary
    glDeleteShader(vertex);
    glDeleteShader(fragment);

    int numUniforms;
    glGetProgramiv(programID, GL_ACTIVE_UNIFORMS, &numUniforms);

    int maxCharLength;
    glGetProgramiv(programID, GL_ACTIVE_UNIFORM_MAX_LENGTH, &maxCharLength);

    if (numUniforms > 0 && maxCharLength > 0) {
        for (int i = 0; i < numUniforms; ++i) {
            char* charBuffer = (char*)malloc(sizeof(char) * maxCharLength);  // Initialize charBuffer for each uniform
            int length, size;
            GLenum dataType;
            glGetActiveUniform(programID, i, maxCharLength, &length, &size, &dataType, charBuffer);
            GLint varLocation = glGetUniformLocation(programID, charBuffer);
            if (length > 0) {
                std::cout << "Uniform " << charBuffer << " has location " << varLocation << std::endl;
                if (charBuffer != nullptr) uniformLocations[charBuffer] = varLocation;
            }
            free(charBuffer);  // Free the memory allocated for charBuffer after each iteration
        }

    }
}
Shader::~Shader() {
    glUseProgram(0);
    glDeleteProgram(programID);
}

void Shader::checkCompileErrors(unsigned int shader, std::string type) {
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
void Shader::cacheUniformLocations() {
    GLint numUniforms = 0;
    glGetProgramiv(programID, GL_ACTIVE_UNIFORMS, &numUniforms);

    for (int i = 0; i < numUniforms; ++i)
    {
        constexpr int maxNameLength = 256;
        char uniformName[maxNameLength];
        GLsizei length = 0;
        GLint size = 0;
        GLenum type = GL_NONE;

        glGetActiveUniform(programID, i, maxNameLength, &length, &size, &type, uniformName);
        GLint location = glGetUniformLocation(programID, uniformName);

        uniformLocations[uniformName] = location;
    }
}

void Shader::bind()
{
    glUseProgram(programID);
}
void Shader::unbind() {
    glUseProgram(0);
}

GLint Shader::findLocation(const char* varName) {
    auto locationIt = uniformLocations.find(varName);
    if (locationIt != uniformLocations.end()) {
        return locationIt->second;
    }
    else {
        throw std::runtime_error("Error: varName location not found in Shader::findLocation");
    }
}

void Shader::uploadVec4(const char* varName, const glm::vec4& vec4) {
    GLint location = findLocation(varName);
    if (location >= 0) {
        glUniform4fv(location, 1, glm::value_ptr(vec4));
    }
    else {
        std::cout << "Location was invalid\n";
    }
}
void Shader::uploadVec3(const char* varName, const glm::vec3& vec3) {
    GLint location = findLocation(varName);
    if (location >= 0) {
        glUniform3fv(location, 1, glm::value_ptr(vec3));
    }
    else {
        std::cout << "Location was invalid\n";
    }
}
void Shader::uploadVec2(const char* varName, const glm::vec2& vec2) {
    GLint location = findLocation(varName);
    if (location >= 0) {
        glUniform2fv(location, 1, glm::value_ptr(vec2));
    }
    else {
        std::cout << "Location was invalid\n";
    }
}

void Shader::uploadIVec4(const char* varName, const glm::ivec4& ivec4) {
    GLint location = findLocation(varName);
    if (location >= 0) {
        glUniform4iv(location, 1, glm::value_ptr(ivec4));
    }
    else {
        std::cout << "Location was invalid\n";
    }
}
void Shader::uploadIVec3(const char* varName, const glm::ivec3& ivec3) {
    GLint location = findLocation(varName);
    if (location >= 0) {
        glUniform3iv(location, 1, glm::value_ptr(ivec3));
    }
    else {
        std::cout << "Location was invalid\n";
    }
}
void Shader::uploadIVec2(const char* varName, const glm::ivec2& ivec2) {
    GLint location = findLocation(varName);
    if (location >= 0) {
        glUniform2iv(location, 1, glm::value_ptr(ivec2));
    }
    else {
        std::cout << "Location was invalid\n";
    }
}

void Shader::uploadFloat(const char* varName, float value) {
    int location = findLocation(varName);
    if (location >= 0) glUniform1f(location, value); else std::cout << "Location was invalid\n";
}
void Shader::uploadInt(const char* varName, int value) {
    GLint location = findLocation(varName);
    if (location >= 0) {
        glUniform1i(location, value);
    }
    else {
        std::cout << "Location was invalid\n";
    }
}
void Shader::uploadIntArray(const char* varName, int length, const int* array) {
    GLint location = findLocation(varName);
    if (location >= 0) {
        glUniform1iv(location, length, array);
    }
    else {
        std::cout << "Location was invalid\n";
    }
}
void Shader::uploadUInt(const char* varName, unsigned int value) {
    GLint location = findLocation(varName);
    if (location >= 0) {
        glUniform1ui(location, value);
    }
    else {
        std::cout << "Location was invalid\n";
    }
}
void Shader::uploadBool(const char* varName, bool value) {
    GLint location = findLocation(varName);
    if (location >= 0) {
        glUniform1i(location, static_cast<int>(value));
    }
    else {
        std::cout << "Location was invalid\n";
    }
}

void Shader::uploadMat4(const char* varName, const glm::mat4& mat4) {
    GLint location = findLocation(varName);
    if (location >= 0) {
        glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(mat4));
    }
    else {
        std::cout << "Location was invalid\n";
    }
}
void Shader::uploadMat3(const char* varName, const glm::mat3& mat3) {
    GLint location = findLocation(varName);
    if (location >= 0) {
        glUniformMatrix3fv(location, 1, GL_FALSE, glm::value_ptr(mat3));
    }
    else {
        std::cout << "Location was invalid\n";
    }
}
unsigned int Shader::getProgramID() const {
    return programID;
}