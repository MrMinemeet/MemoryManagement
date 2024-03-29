#include "FreeBlock.hpp"
#include "Declarations.hpp"

/*
 * Takes 20 bytes in memory:
 * - 8 bytes for the rawTypeDescriptor pointer (Actual head)
 * - 4 bytes for the size of the data part (Data Part)
 * - 8 bytes for the pointer to the next free block (Data Part)
 * The rest of the data part until the next block is not used for anything specifically and just sits around until the free block is (partially) allocated.
 */
FreeBlock::FreeBlock(int requestedSize) : Block(nullptr) {// Explicitly null here, and set further below. Otherwise, the debug info would overwrite it.
	int actualSize = requestedSize + (int) sizeof(FreeBlock);

	// rawTypeDescriptor is a pointer to the data part of the free block
	this->setTypeDescriptor((TypeDescriptor*) ((char*) this + sizeof(FreeBlock)));
	// Size of the data part of the whole free block
	this->setObjSize(actualSize);
	// Pointer to the next free block, which is nullptr per default
	setNextFreePointer(nullptr);
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
void* FreeBlock::getNextFreePointer() const {
	void* dataPos = dataPosition();
	return (char*) dataPos + sizeof(int);
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
	FreeBlock* nextFree = *(FreeBlock**) getNextFreePointer();
	return nextFree;
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
int FreeBlock::headerSize() const {
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
void* FreeBlock::dataPosition() const {
	return (void*) ((char*) this + sizeof(FreeBlock));
}
