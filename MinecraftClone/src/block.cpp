#include <cstdio>
#include <iostream>
#include "rapidjson/document.h" 
#include "rapidjson/filereadstream.h" 
#include "rapidjson/rapidjson.h"
#include "block.hpp"
#include "glfw/glfw3.h"
#include "vendor/stb_image/stb_image.h"

Block::Block(BlockID id, glm::vec3 position) : ID(id), Position(position) {
	rapidjson::Document doc;
	switch (id)
	{
	case GRASS:
		doc.Parse()
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
rapidjson::Document Block::ReadJSON(std::string filepath) {
    FILE* fp = fopen(filepath.c_str(), "rb");
    if (!fp) {
        std::cerr << "Error: unable to open file"
            << std::endl;
        return NULL;
    }

    char readBuffer[1024];
    rapidjson::FileReadStream is(fp, readBuffer,
        sizeof(readBuffer));

    // Parse the JSON document 
    rapidjson::Document doc;
    doc.ParseStream(is);

    // Check if the document is valid 
    if (doc.HasParseError()) {
        std::cerr << "Error: failed to parse JSON document"
            << std::endl;
        fclose(fp);
        return NULL;
    }

    // Close the file 
    fclose(fp);
}