#ifndef MEMORYMANAGEMENT_STUDENTLIST_HPP
#define MEMORYMANAGEMENT_STUDENTLIST_HPP

#include "StudNode.hpp"

class StudentList {
public:
	StudNode* first;
	void add(Student student);
	void remove(Student student);
};

#endif//MEMORYMANAGEMENT_STUDENTLIST_HPP
