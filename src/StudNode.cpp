#include "StudNode.hpp"

StudNode::StudNode() {
	next = nullptr;
	stud = nullptr;
}
StudNode::StudNode(StudNode* next, Student* stud) {
	this->next = next;
	this->stud = stud;
}
