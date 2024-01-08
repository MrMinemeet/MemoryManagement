#include "Block.hpp"

#include "FreeBlock.hpp"

/*
 * The head takes 8 bytes in memory for the typeDescriptor pointer.
 * The rest depends on if it is a used or free block
 */
Block::Block(TypeDescriptor* typeDescriptor) {
	this->typeDescriptor = typeDescriptor;
}

std::string Block::ToString() const {
	std::string str = "Block { ";
	if (isFreeBlock()) {
		str += "used: false, ";
	} else {
		str += "used: true, ";
	}
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
bool Block::isFreeBlock() const {
	FreeBlock* fb = (FreeBlock*) this;
	return (void*) fb->typeDescriptor == fb->dataPosition();
}
void* Block::getDataPart() const {
	// "this + sizeof(Block)" is the effective getDataPart for the block
	return (void*) (this + headerSize());
}

int Block::totalSize() const {
	return typeDescriptor->totalSize + headerSize();
}
int Block::headerSize() const {
	return sizeof(Block);
}
int Block::dataSize() const {
	return typeDescriptor->totalSize;
}
