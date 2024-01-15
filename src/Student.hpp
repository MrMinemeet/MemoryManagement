#ifndef MEMORYMANAGEMENT_STUDENT_HPP
#define MEMORYMANAGEMENT_STUDENT_HPP

#include "Heap.hpp"
#include "LectNode.hpp"
#include <string>

extern Heap heap;
/**
 * Size of 48 Bytes:
 * - 4 byte int for id  		(0 offset)
 * - 4 byte padding				(4 offset)
 * - 32 byte string for name	(8 offset)
 * - 8 byte LectNode* for lect	(40 offset)
 */
class Student {
public:
	Student();

	int id;
	std::string name;
	LectNode* lect;
	void add(Lecture* lecture);
	void remove(Lecture lecture);
};

#endif//MEMORYMANAGEMENT_STUDENT_HPP
