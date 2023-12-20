#include "Block.hpp"

#include "Declarations.hpp"

/*
 * Takes 16 bytes in memory
 * 1 byte for the used flag
 * 8 bytes for the typeDescriptor pointer
 * 7 bytes padding
 */
Block::Block(TypeDescriptor* typeDescriptor) {
#if DEBUG
	// Fill memory with 0x02 (for debugging)
	if (typeDescriptor != nullptr) {
		int totalSize = typeDescriptor->totalSize;
		for (int i = 0; i < totalSize + sizeof(Block); ++i) {
			((char*) this)[i] = (char) 0x02;
		}
	}
#endif

	this->typeDescriptor = typeDescriptor;
	this->used = true;
}

Block::~Block() = default;

/*
 * Returns the effective address of the data of the block.
 * If the block is not marked as "used", then a nullptr is returned
 */
void* Block::getDataPart() {
	if (!this->used) {
		return nullptr;
	}

	// "this + sizeof(Block)" is the effective getDataPart for the block
	return this + sizeof (Block);
}

int Block::totalSize() const {
	return typeDescriptor->totalSize + (int) sizeof(Block);
}

int Block::headerSize() {
	return sizeof(Block);
}

int Block::dataSize() const {
	return typeDescriptor->totalSize;
}

std::string Block::ToString() const {
	std::string str = "Block { ";
	if (this->used) {
		str += "used: true, ";
	} else {
		str += "used: false, ";
	}
	str += "totalSize: " + std::to_string(totalSize()) + ", ";
	str += "headerSize: " + std::to_string(headerSize()) + ", ";
	str += "dataSize: " + std::to_string(dataSize());
	str += "}";
	return str;
}
