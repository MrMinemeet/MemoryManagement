#ifndef SYSTEMSOFTWARE_MEMORYMANAGEMENT_SLIDEBLOCK_H
#define SYSTEMSOFTWARE_MEMORYMANAGEMENT_SLIDEBLOCK_H


#include "Block.hpp"
/**
 * Size of 32 Bytes:
 * - 8 byte Block* for x	(0 offset)
 * - 8 byte Block* for y	(8 offset)
 * - 4 byte int for data	(16 offset)
 * - 4 byte padding			(20 offset)
 * - 8 byte Block* for z	(24 offset)
 */
class SlideBlock {
public:
	SlideBlock();

	Block* x;
	Block* y;
	int data;
	Block* z;
};


#endif//SYSTEMSOFTWARE_MEMORYMANAGEMENT_SLIDEBLOCK_H
