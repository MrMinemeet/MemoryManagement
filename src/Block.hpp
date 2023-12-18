#ifndef BLOCK_HPP
#define BLOCK_HPP

#include "TypeDescriptor.hpp"
#include <string>

class Block {
public:
	// Heap
	TypeDescriptor* typeDescriptor;
	bool used;

	// GC
	/*
	bool marked;
	Block* left;
	Block* right;
	*/

	// Constructor declaration
	Block(TypeDescriptor* typeDescriptor);
	// Destructor declaration
	~Block();

	// Additional member function declarations, if needed
	std::string ToString() const;

	/**
	* Returns the getDataPart pointer of this block.
	* @return the getDataPart pointer of this block.
	* @return nullptr if this block is free.
	*/
	void* getDataPart();

	int totalSize() const;
	static int headerSize();
	int dataSize() const;
};

#endif// BLOCK_HPP