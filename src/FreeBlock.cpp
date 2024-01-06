//
// Created by mrminemeet on 18.12.23.
//

#include "FreeBlock.hpp"
#include "Declarations.hpp"
#include <iostream>

/*
 * Takes 20 bytes in memory:
 * - 8 bytes for the typeDescriptor pointer (Actual head)
 * - 4 bytes for the size of the data part (Data Part)
 * - 8 bytes for the pointer to the next free block (Data Part)
 * The rest of the data part until the next block is not used for anything specifically at the moment and just sits around.
 */
FreeBlock::FreeBlock(int requestedSize) : Block(nullptr) {// Explicitly null here, and set further below. Otherwise, the debug info would overwrite it.

	int actualSize = requestedSize + (int) sizeof(FreeBlock);
#if DEBUG
	// Fill memory with 0x01 (to mark as free)
	for (int i = 0; i < actualSize; ++i) {
		((char*) this)[i] = (char) 0x01;
	}
#endif

	// typeDescriptor is a pointer to the data part of the free block
	this->typeDescriptor = (TypeDescriptor*) dataPosition();
	// Size of the data part of the whole free block
	this->setObjSize(actualSize);
	// Pointer to the next free block, which is nullptr per default
	setNextFreePointer(nullptr);
}

/**
 * Returns the data part of the block
 */
void* FreeBlock::dataPosition() const {
	return (void*) ((char*) this + sizeof(FreeBlock));
}
/**
 * At first position of data part, there is a integer value which is the size of the object
 */
int FreeBlock::getObjSize() const {
	return *(int*) dataPosition();
}
void FreeBlock::setObjSize(int size) {
#if DEBUG
	std::cout << "Setting objSize of (" << this << ") to (" << size << ")" << std::endl;
#endif
	*((int*) dataPosition()) = size;
}

/**
 * At second position of data part, there is a pointer to the next free block
 */
void* FreeBlock::getNextFreePointer() {
	return (char*) dataPosition() + sizeof(int);
}
void FreeBlock::setNextFreePointer(void* nextFree) {
#if DEBUG
	std::cout << "Setting next free pointer of (" << this << ") to (" << nextFree << ")" << std::endl;
#endif
	char* tmp = ((char*) dataPosition()) + sizeof(int);
	// Set the address in tmp to nextFree
	*(void**) tmp = nextFree;
}

/**
 * @return nullptr if this is the last free block
 */
FreeBlock* FreeBlock::getNextFree() {
	return *(FreeBlock**) getNextFreePointer();
}

std::string FreeBlock::ToString() const {
	std::string str = "FreeBlock { ";
	str += "totalSize: " + std::to_string(totalSize()) + ", ";
	str += "headerSize: " + std::to_string(headerSize()) + ", ";
	str += "dataSize: " + std::to_string(dataSize());
	str += " }";
	return str;
}
int FreeBlock::totalSize() const {
	return getObjSize();
}
int FreeBlock::headerSize() {
	return sizeof(FreeBlock);
}
int FreeBlock::dataSize() const {
	return totalSize() - headerSize();
}

/**
 * At the time of creating this method (20.12.2023 - 09:58), the size is 28 byte
 * @return the minimum size of a free block with objSize and next-pointer
 */
long FreeBlock::getMinFreeBlockSize() {
	return sizeof(FreeBlock) + sizeof(int) + sizeof(char*);
}