#include "StudentList.hpp"
#include "UsedBlock.hpp"

StudentList::StudentList() {
	first = nullptr;
}

void StudentList::add(Student* student) {
	UsedBlock* ub = heap.alloc("StudNode");
	StudNode* sn = new (ub->getDataPart()) StudNode(first, student);
	first = sn;
}

void StudentList::remove(Student* student) {}
