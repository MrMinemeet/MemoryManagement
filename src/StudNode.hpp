#ifndef MEMORYMANAGEMENT_STUDNODE_HPP
#define MEMORYMANAGEMENT_STUDNODE_HPP

#include "Student.hpp"
/**
 * Size of 16 Bytes:
 * - 8 byte StudNode* for next	(0 offset)
 * - 8 byte Student* for stud	(8 offset)
 */
class StudNode {
public:
	StudNode();
	StudNode(StudNode* next, Student* stud);

	StudNode* next;
	Student* stud;
};

#endif//MEMORYMANAGEMENT_STUDNODE_HPP
