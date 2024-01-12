#include "Block.hpp"

#include "FreeBlock.hpp"

/*
 * The head takes 8 bytes in memory for the rawTypeDescriptor pointer.
 * Somehow still uses 16 bytes when using "sizeof(Block)".
 * The rest depends on if it is a used or free block
 */
Block::Block(TypeDescriptor* typeDescriptor) {
	this->rawTypeDescriptor = typeDescriptor;
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
	FreeBlock fbA = *fb;
	TypeDescriptor* td = fb->getTypeDescriptor();
	void* dataPart = fb->getDataPart();
	return (void*) fb->getTypeDescriptor() == fb->dataPosition();
}
void* Block::getDataPart() const {
	// "this + sizeof(Block)" is the effective getDataPart for the block
	return (void*) ((char*) this + headerSize());
}

int Block::totalSize() const {
	return getTypeDescriptor()->totalSize + headerSize();
}
int Block::headerSize() const {
	return sizeof(Block);
}
int Block::dataSize() const {
	return getTypeDescriptor()->totalSize;
}

/**
 * Checks for the Mark-Bit in the type descriptor.
 * @return  If the LSB is 1 it is marked and true is returned., otherwise returns false
 */
bool Block::isMarked() const {
	// Check if the lsb is a 1 or a 0
	ulong maskedAddress = ((uintptr_t) rawTypeDescriptor & 1);
	return maskedAddress == 1;
}

/**
 * Getter which does not include the Mark bit, which is stored in the type descriptor
 * @return The sanitized TypeDescriptor pointer
 */
TypeDescriptor* Block::getTypeDescriptor() const {
	// Remove the LSB from the rawTypeDescriptor pointer
	// TODO: Do this in a nice way
	return (TypeDescriptor*) (((uintptr_t) rawTypeDescriptor >> 1) << 1);
}

/**
 * Returns the typeDescriptor as stored in the block.
 * This will include the Mark bit! Be careful when using this function.
 * @return The raw type descriptor
 */
TypeDescriptor* Block::getRawTypeDescriptor() const {
	return rawTypeDescriptor;
}

/**
 * Sets the passed value as the new type descriptor
 * @param descriptor The new type descriptor
 */
void Block::setTypeDescriptor(TypeDescriptor* descriptor) {
	rawTypeDescriptor = descriptor;
}

/**
 * Marks the block by setting the LSB of the type descriptor to 1
 */
void Block::mark(bool b) {
	// Set the LSB to 1
	if (b)
		rawTypeDescriptor = (TypeDescriptor*) ((uintptr_t) rawTypeDescriptor | 1);
	else
		rawTypeDescriptor = (TypeDescriptor*) (((uintptr_t) rawTypeDescriptor >> 1) << 1);
}

/**
 * Returns the pointer to the child at the given offset.
 * @param offset The offset of the child
 * @return The pointer to the child
 */
void* Block::getChildPointer(int offset) const {
	return (char*) getDataPart() + offset;
}
