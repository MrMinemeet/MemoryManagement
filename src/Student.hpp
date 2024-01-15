#ifndef MEMORYMANAGEMENT_STUDENT_HPP
#define MEMORYMANAGEMENT_STUDENT_HPP

#include "LectNode.hpp"
#include <string>

class Student {
public:
	int id;
	std::string name;
	LectNode* lect;
	void add(Lecture lecture);
	void remove(Lecture lecture);
};

#endif//MEMORYMANAGEMENT_STUDENT_HPP
