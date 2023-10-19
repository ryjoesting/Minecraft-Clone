#pragma once
#include <glm/glm.hpp>
#include <rapidjson/document.h>
#include <iostream>
enum BlockID { GRASS, DIRT, GRAVEL, COBBLESTONE, OAK_LOG, OAK_PLANKS };

class Block {
private:
	BlockID ID;
	float Vertices[180];
	glm::vec3 Position;

	rapidjson::Document ReadJSON(std::string filepath);
public:
	Block(BlockID id, glm::vec3 position);


};