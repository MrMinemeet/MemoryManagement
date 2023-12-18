//
// Created by mrminemeet on 18.12.23.
//

#include "FreeBlock.hpp"
#include "Declarations.hpp"
#include <iostream>

FreeBlock::FreeBlock(int requestedSize) : Block(typeDescriptor) {
	int actualSize = requestedSize + sizeof(FreeBlock);
#if DEBUG
	// Fill memory with 0x01 (to mark as free)
	for (int i = 0; i < actualSize; ++i) {
		((char*) this)[i] = (char) 0x01;
	}
#endif

	this->used = false;
	// typeDescriptor is a pointer to the data part of the free block
	this->typeDescriptor = (TypeDescriptor*) dataPosition();
	// Size of the data part of the whole free block
	*(int*) dataPosition() = sizeof(FreeBlock) + requestedSize;
	// Pointer to the next free block
	*(void**) getNextFreePointer() = nullptr;
}

/**
 * Returns the data part of the block
 */
void* FreeBlock::dataPosition() const {
	return (void*) (this + sizeof(FreeBlock));
}
/**
 * At first position of data part, there is a integer value which is the size of the object
 */
int FreeBlock::getObjSize() const {
	return *(int*) dataPosition();
}
/**
 * At second position of data part, there is a pointer to the next free block
 */
void* FreeBlock::getNextFreePointer() {
	return (char*) dataPosition() + sizeof(int);
}

FreeBlock* FreeBlock::getNextFree() {
	return *(FreeBlock**) getNextFreePointer();
}

std::string FreeBlock::ToString() {
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
