#pragma once
#include <glm/glm.hpp>
class Cube {
private:
	glm::vec3 position;
	GLuint VAO, VBO, EBO;
public:
	Cube(glm::vec3 position);
	~Cube();
	GLuint getVAO() const;
	GLuint getVBO() const;
	GLuint getEBO() const;
};