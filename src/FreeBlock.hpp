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

	// Additional member function declarations, if needed
	std::string ToString() const;

	int totalSize() const override;
	int headerSize() const override;
	int dataSize() const override;

	FreeBlock* getNextFree();
	void* getNextFreePointer();
	static long getMinFreeBlockSize();
	void setNextFreePointer(void* nextFree);

private:
	int getObjSize() const;
	void setObjSize(int size);
	void* dataPosition() const;
};


#endif//SYSTEMSOFTWARE_MEMORYMANAGEMENT_FREEBLOCK_HPP
