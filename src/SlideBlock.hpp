#ifndef SYSTEMSOFTWARE_MEMORYMANAGEMENT_SLIDEBLOCK_H
#define SYSTEMSOFTWARE_MEMORYMANAGEMENT_SLIDEBLOCK_H


#include "Block.hpp"
class SlideBlock {
public:
	SlideBlock();

	Block* x;
	Block* y;
	int data;
	Block* z;
};


#endif//SYSTEMSOFTWARE_MEMORYMANAGEMENT_SLIDEBLOCK_H
