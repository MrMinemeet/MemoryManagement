#ifndef BLOCK_HPP
#define BLOCK_HPP

#include "TypeDescriptor.hpp"
#include <string>

class Block {
private:
	TypeDescriptor* typeDescriptor;

public:

	// GC
	/*
	bool marked;
	Block* left;
	Block* right;
	*/

	// Constructor
	Block(TypeDescriptor* typeDescriptor);

	// Additional member function declarations, if needed
	virtual std::string ToString() const;
	bool isFreeBlock() const;
	bool isMarked() const;

	/**
	* Returns the getDataPart pointer of this block.
	* @return the getDataPart pointer of this block.
	* @return nullptr if this block is free.
	*/
	virtual void* getDataPart() const;
	virtual TypeDescriptor* getTypeDescriptor() const;
	virtual void setTypeDescriptor(TypeDescriptor* descriptor);

	virtual int totalSize() const;
	virtual int headerSize() const;
	virtual int dataSize() const;
};

#endif// BLOCK_HPP