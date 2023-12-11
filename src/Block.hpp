#ifndef BLOCK_HPP
#define BLOCK_HPP

#include "TypeDescriptor.hpp"
#include <string>

class Block {
public:
	// Heap
	TypeDescriptor* typeDescriptor;
	bool used;
	uint dataSize;

	// GC
	/*
	bool marked;
	Block* left;
	Block* right;
	*/
	Block(uint dataSize);// Constructor declaration
	~Block();		 // Destructor declaration

	// Additional member function declarations, if needed
	std::string ToString() const;

	/**
	* Returns the data pointer of this block.
	* @return the data pointer of this block.
	* @return nullptr if this block is free.
	*/
	void* data();
};

#endif// BLOCK_HPP