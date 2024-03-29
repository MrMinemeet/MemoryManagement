#ifndef BLOCK_HPP
#define BLOCK_HPP

#include "TypeDescriptor.hpp"
#include <cstdint>
#include <string>

class Block {
private:
	TypeDescriptor* rawTypeDescriptor;

public:
	// Constructor
	Block(TypeDescriptor* typeDescriptor);

	// Additional member function declarations, if needed
	virtual std::string ToString() const;
	bool isFreeBlock() const;
	bool isMarked() const;
	void mark(bool b);

	/**
	* Returns the getDataPart pointer of this block.
	* @return the getDataPart pointer of this block.
	* @return nullptr if this block is free.
	*/
	virtual void* getDataPart() const;
	virtual TypeDescriptor* getTypeDescriptor() const;
	virtual TypeDescriptor* getRawTypeDescriptor() const;
	virtual void setTypeDescriptor(TypeDescriptor* descriptor);
	void* getChildPointer(int offset) const;

	virtual int totalSize() const;
	virtual int headerSize() const;
	virtual int dataSize() const;
};

#endif// BLOCK_HPP