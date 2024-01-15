#ifndef MEMORYMANAGEMENT_LECTURE_HPP
#define MEMORYMANAGEMENT_LECTURE_HPP

#include <string>
/**
 * Size of 48 Bytes
 * - 4 byte for id			(0 offset)
 * - 4 byte padding			(4 offset)
 * - 32 byte for name		(8 offset)
 * - 4 byte for semester	(40 offset)
 */
class Lecture {
public:
	Lecture();

	int id;
	std::string name;
	int semester;
};

#endif//MEMORYMANAGEMENT_LECTURE_HPP
