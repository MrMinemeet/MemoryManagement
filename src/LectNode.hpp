#ifndef MEMORYMANAGEMENT_LECTNODE_HPP
#define MEMORYMANAGEMENT_LECTNODE_HPP

#include "Lecture.hpp"

class LectNode {
public:
	LectNode* next;
	Lecture* lect;
};

#endif//MEMORYMANAGEMENT_LECTNODE_HPP
