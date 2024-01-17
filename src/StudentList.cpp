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

void StudentList::remove(Student* student) {
	StudNode* prev = nullptr;
	StudNode* cur = first;

	while (cur != nullptr && cur->stud != student) {
		prev = cur;
		cur = cur->next;
	}

	if (cur == nullptr) {
		// Student not in list
		return;
	}

	// Student in list, remove
	if (prev == nullptr) {
		// Student was 1st element
		first = cur->next;
	} else {
		// Student was somewhere else
		prev->next = cur->next;
	}
}
