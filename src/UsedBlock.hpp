//
// Created by mrminemeet on 06.01.24.
//

#ifndef SYSTEMSOFTWARE_MEMORYMANAGEMENT_USEDBLOCK_H
#define SYSTEMSOFTWARE_MEMORYMANAGEMENT_USEDBLOCK_H


#include "Block.hpp"
#include "Declarations.hpp"

/*
 * A special "Block" that is used to mark used memory.
 * The "rawTypeDescriptor" points to a position which is outside the block.
 * The data part contains the actual data of the Object associated with the Blocks type.
 */
class UsedBlock : public Block {
public:
	UsedBlock(TypeDescriptor* typeDescriptor);

	// Additional member function declarations, if needed
	std::string ToString() const;
};


#endif//SYSTEMSOFTWARE_MEMORYMANAGEMENT_USEDBLOCK_H
