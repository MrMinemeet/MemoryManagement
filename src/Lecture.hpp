#ifndef MEMORYMANAGEMENT_LECTURE_HPP
#define MEMORYMANAGEMENT_LECTURE_HPP

#include <string>
/**
 * Size of Z Bytes
 * - 4 byte for id			(0 offset)
 * - X byte for name		(X offset)
 * - 4 byte for semester	(X offset)
 */
class Lecture {
public:
	Lecture();

	int id;
	std::string name;
	int semester;
};

#endif//MEMORYMANAGEMENT_LECTURE_HPP
