#ifndef SYSTEMSOFTWARE_MEMORYMANAGEMENT_FREEBLOCK_HPP
#define SYSTEMSOFTWARE_MEMORYMANAGEMENT_FREEBLOCK_HPP

#include "Block.hpp"
#include <iostream>

/**
 * "A special "Block" that is used to mark free memory.
 * The "rawTypeDescriptor" points to the data part of the block.
 * The data part contains a "objSize" and a pointer to the next free block.
 */
class FreeBlock : public Block {
public:
	FreeBlock(int requestedSize);

	// Additional member function declarations, if needed
	std::string ToString() const override;

	int totalSize() const override;
	int headerSize() const override;
	int dataSize() const override;

	FreeBlock* getNextFree();
	void* getNextFreePointer() const;
	static long getMinFreeBlockSize();
	void setNextFreePointer(void* nextFree);
	void* dataPosition() const;
	void setObjSize(int size);

private:
	int getObjSize() const;
};


#endif//SYSTEMSOFTWARE_MEMORYMANAGEMENT_FREEBLOCK_HPP
