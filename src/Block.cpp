#include "Block.hpp"


/*
 * Takes 8 bytes in memory
 * 1 byte for the used flag
 * 4 bytes for the size
 * 3 bytes padding/alignment
 */
Block::Block(uint size) {
	this->used = false;
	this->size = size;
}

Block::~Block() = default;

void* Block::data() {
	if (!this->used) {
		return nullptr;
	}
	return &this[0] + 1;
}

std::string Block::ToString() const {
	std::string str = "Block {";
	if ((this->used)) {
		str += "used: true, ";
	} else {
		str += "used: false, ";
	}
	str += "size: " + std::to_string(this->size);
	str += "}";
	return str;
}
