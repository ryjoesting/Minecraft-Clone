#include <fstream>
#include <iostream>
#include "block.hpp"
#include "glfw/glfw3.h"
#include "vendor/stb_image/stb_image.h"
#include "nlohmann/json.hpp"

Block::Block(BlockID id, glm::vec3 position) : ID(id), Position(position) {
	
	switch (id)
	{
	case GRASS:
		GetJSONFromFile("src/resources/models/block/grass_block.json");
		std::cout << JSON["textures"]["top"] << std::endl;
		break;
	case DIRT:
		break;
	case GRAVEL:
		break;
	case COBBLESTONE:
		break;
	case OAK_LOG:
		break;
	case OAK_PLANKS:
		break;
	default:
		break;
	}
}

void Block::GetJSONFromFile(std::string filepath) {
	std::ifstream f(filepath);
	if (f) { std::cout << "Filepath found for " << filepath << std::endl; }
	else { throw new std::exception("JSON filepath not found"); }
	json data = json::parse(f);
	JSON = data;
}
