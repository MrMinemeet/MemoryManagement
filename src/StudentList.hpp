#ifndef MEMORYMANAGEMENT_STUDENTLIST_HPP
#define MEMORYMANAGEMENT_STUDENTLIST_HPP

#include "StudNode.hpp"
/**
 * Size of 8 Bytes:
 * - 8 byte StudNode* for first	(0 offset)
 */
class StudentList {
public:
	StudentList();

	StudNode* first;
	void add(Student* student);
	void remove(Student* student);
};

#endif//MEMORYMANAGEMENT_STUDENTLIST_HPP
