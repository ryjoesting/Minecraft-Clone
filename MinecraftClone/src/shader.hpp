#pragma once
#include <glad/glad.h>
#include <unordered_map>
#include <iostream>
#include "glm/glm.hpp"

class Shader {
private:
    unsigned int programID;
    std::unordered_map<std::string, int> uniformLocations;
    void checkCompileErrors(unsigned int shader, std::string type);
    void cacheUniformLocations();
    GLint findLocation(const char* varName);

public:
    Shader(const char* vertexPath, const char* fragmentPath);
    ~Shader();
    // activate the shader
    void bind();
    void unbind();
    
    // utility uniform functions
    void uploadVec4(const char* varName, const glm::vec4& vec4);
    void uploadVec3(const char* varName, const glm::vec3& vec3);
    void uploadVec2(const char* varName, const glm::vec2& vec2);
    void uploadIVec4(const char* varName, const glm::ivec4& ivec4);
    void uploadIVec3(const char* varName, const glm::ivec3& ivec3);
    void uploadIVec2(const char* varName, const glm::ivec2& ivec2);
    void uploadFloat(const char* varName, float value);
    void uploadInt(const char* varName, int value);
    void uploadIntArray(const char* varName, int length, const int* array);
    void uploadUInt(const char* varName, unsigned int value);
    void uploadBool(const char* varName, bool value);

    void uploadMat4(const char* varName, const glm::mat4& mat4);
    void uploadMat3(const char* varName, const glm::mat3& mat3);
    unsigned int getProgramID() const;
};