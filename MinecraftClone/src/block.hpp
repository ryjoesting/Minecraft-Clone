#pragma once

enum BlockID { GRASS, DIRT, GRAVEL, COBBLESTONE, OAK_LOG, OAK_PLANKS };

class Block {
private:
	float vertices[180];
public:
	Block(BlockID id);


};