#ifndef MEMORYMANAGEMENT_LECTNODE_HPP
#define MEMORYMANAGEMENT_LECTNODE_HPP

#include "Lecture.hpp"
/**
 * Size of 16 Bytes:
 * - 8 byte LectNode* for next	(0 offset)
 * - 8 byte Lecture* for lect	(8 offset)
 */
class LectNode {
public:
	LectNode();

	LectNode* next;
	Lecture* lect;
};

#endif//MEMORYMANAGEMENT_LECTNODE_HPP
