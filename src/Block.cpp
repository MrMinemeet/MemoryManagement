#include "Block.hpp"

#include "Declarations.hpp"
#include "FreeBlock.hpp"

/*
 * The head takes 8 bytes in memory for the typeDescriptor pointer.
 * The rest until the next block is the data part. which depends on the typeDescriptor
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
}

Block::~Block() = default;

/*
 * Returns the effective address of the data of the block.
 * If the block is not marked as "used", then a nullptr is returned
 */
void* Block::getDataPart() {
	if (isFreeBlock()) {
		return nullptr;
	}

	// "this + sizeof(Block)" is the effective getDataPart for the block
	return this + sizeof(Block);
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
	str += "used: true, ";
	str += "totalSize: " + std::to_string(totalSize()) + ", ";
	str += "headerSize: " + std::to_string(headerSize()) + ", ";
	str += "dataSize: " + std::to_string(dataSize());
	str += "}";
	return str;
}


/**
 * Takes a block and checks if it is a FreeBlock. <br>
 * The function checks if the TypeDescriptor points to the body of the block
 * @param blk The body to check
 * @return True if the block is a FreeBlock, otherwise false
 */
bool Block::isFreeBlock() {
	FreeBlock* fb = (FreeBlock*) this;
	return (void*) fb->typeDescriptor == fb->dataPosition();
}
