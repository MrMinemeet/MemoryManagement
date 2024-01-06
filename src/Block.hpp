#ifndef BLOCK_HPP
#define BLOCK_HPP

#include "TypeDescriptor.hpp"
#include <string>

class Block {
public:
	// Heap
	TypeDescriptor* typeDescriptor;

	// GC
	/*
	bool marked;
	Block* left;
	Block* right;
	*/

	// Constructor
	Block(TypeDescriptor* typeDescriptor);

	// Additional member function declarations, if needed
	std::string ToString() const;
	bool isFreeBlock() const;

	/**
	* Returns the getDataPart pointer of this block.
	* @return the getDataPart pointer of this block.
	* @return nullptr if this block is free.
	*/
	virtual void* getDataPart() const;

	virtual int totalSize() const;
	virtual int headerSize() const;
	virtual int dataSize() const;
};

#endif// BLOCK_HPP