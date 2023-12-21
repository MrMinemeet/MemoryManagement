#ifndef SYSTEMSOFTWARE_MEMORYMANAGEMENT_FREEBLOCK_HPP
#define SYSTEMSOFTWARE_MEMORYMANAGEMENT_FREEBLOCK_HPP

#include "Block.hpp"

/**
 * "A special "Block" that is used to mark free memory.
 * The "typeDescriptor" points to the data part of the block.
 * The data part contains a "objSize" and a pointer to the next free block.
 */
class FreeBlock : public Block {
public:
	FreeBlock(int requestedSize);
	std::string ToString() const;
	int totalSize() const;
	static int headerSize();
	int dataSize() const;
	FreeBlock* getNextFree();
	void* getNextFreePointer();
	static long getMinFreeBlockSize();
	void setNextFreePointer(void* nextFree);
	void setObjSize(int size);
	void* dataPosition() const;

private:
	int getObjSize() const;
};


#endif//SYSTEMSOFTWARE_MEMORYMANAGEMENT_FREEBLOCK_HPP
