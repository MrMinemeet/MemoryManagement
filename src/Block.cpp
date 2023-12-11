#include "Block.hpp"


/*
 * Takes 8 bytes in memory
 * 1 byte for the used flag
 * 4 bytes for the dataSize
 * 8 bytes for the typeDescriptor pointer
 * 3 bytes padding
 */
Block::Block(uint dataSize) {
	this->used = false;
	this->dataSize = dataSize;
	this->typeDescriptor = nullptr;
}

Block::~Block() = default;

/*
 * Returns the effective address of the data of the block.
 * If the block is not marked as "used", then a nullptr is returned
 */
void* Block::data() {
	if (!this->used) {
		return nullptr;
	}

	// "this + 1" is the effective data for the block
	return this + 1;
}

std::string Block::ToString() const {
	std::string str = "Block { ";
	if (this->used) {
		str += "used: true, ";
	} else {
		str += "used: false, ";
	}
	str += "dataSize: " + std::to_string(this->dataSize);
	str += " }";
	return str;
}
