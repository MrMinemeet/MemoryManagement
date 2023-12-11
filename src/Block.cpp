#include "Block.hpp"


/*
 * Takes 8 bytes in memory
 * 1 byte for the used flag
 * 4 bytes for the dataSize
 * 8 bytes for the typeDescriptor pointer
 * 3 bytes padding
 */
Block::Block(TypeDescriptor* typeDescriptor) {
	this->used = false;
	this->typeDescriptor = typeDescriptor;
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

int Block::totalSize() const {
	return typeDescriptor->totalSize;
}

int Block::headerSize() {
	return sizeof(Block);
}

int Block::dataSize() const {
	return totalSize() - headerSize();
}

std::string Block::ToString() const {
	std::string str = "Block { ";
	if (this->used) {
		str += "used: true, ";
	} else {
		str += "used: false, ";
	}
	str += "totalSize: " + std::to_string(totalSize()) + ", ";
	str += "headerSize: " + std::to_string(headerSize()) + ",";
	str += "dataSize: " + std::to_string(dataSize());
	str += "}";
	return str;
}

Block* Block::createFreeBlock(int position, int size) {
	char* pos = (char*) position + sizeof(TypeDescriptor);
	Block* freeBlk = (Block*) pos;

}
