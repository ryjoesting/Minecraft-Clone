#pragma once
#include <glm/glm.hpp>
#include <iostream>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

enum BlockID { GRASS, DIRT, GRAVEL, COBBLESTONE, OAK_LOG, OAK_PLANKS };

class Block {
private:
	BlockID ID;
	json JSON;
	float Vertices[180];
	glm::vec3 Position;

	void GetJSONFromFile(std::string filepath);

public:
	Block(BlockID id, glm::vec3 position);


};