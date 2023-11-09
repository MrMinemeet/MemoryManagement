#include "Block.hpp"


Block::Block(int size) {
	this->used = false;
	this->size = size;
}

Block::~Block() = default;

void* Block::data() {
	if (!this->used) {
		return nullptr;
	}
	return &this[0]+1;
}

std::string Block::ToString() {
	std::string str = "Block {";
	str += "used: " + std::to_string(this->used) + ", ";
	str += "size: " + std::to_string(this->size);
	str += "}";
	return str;
}

