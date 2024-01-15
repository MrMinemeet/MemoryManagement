#ifndef HEAP_HPP
#define HEAP_HPP

#include "Block.hpp"
#include "Declarations.hpp"
#include "UsedBlock.hpp"
#include <string>
#include <unordered_map>

#include "FreeBlock.hpp"
#include "TypeDescriptor.hpp"
#include <cstdint>
#include <iomanip>
#include <iostream>
#include <list>
#include <sstream>

class Heap {
private:
	// TODO: Adjust heap to 32 KiB for the final submission
	const int HEAP_SIZE = 128;// as bytes
	void* heap_buffer;
	uint free_bytes;
	FreeBlock* fbHead;
	std::unordered_map<std::string, TypeDescriptor*> type_map;
	std::string getTypeDescriptorName(TypeDescriptor* typeDescriptor) const;
	static std::string pointerToHexString(int* ptr);
	static std::string charToHex(char c);
	static std::string boolToString(bool b);

	// ---- Garbage Collection
	void mark(Block* rootPointer);
	void sweep();
	void* getHeapEnd() const;


public:
	// Constructor
	Heap();

	// Destructor
	~Heap();

	// Methods
	UsedBlock* alloc(const std::string& type);
	//void dealloc(Block* block);
	bool registerType(const std::string& type, TypeDescriptor& descriptor);
	void dump() const;
	std::string ToString();

	// ---- Garbage Collection
	void gc(void* rootPointers[]);
	void gc(Block* rootPointers[]);


	// tmp debug helper
	FreeBlock* getHead() const;
};

#endif// HEAP_HPP
