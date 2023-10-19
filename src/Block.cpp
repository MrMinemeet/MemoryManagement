#include "Block.hpp"

Block::Block(int size) {
	this->used = false;
	this->size = size;
}

Block::~Block() {

}
std::string Block::ToString() {
	std::string str = "HEAP INFO:\n";
	str += "Used: " + std::to_string(this->used) + "\n";
	str += "Size: " + std::to_string(this->size) + "\n";
	return str;
}
