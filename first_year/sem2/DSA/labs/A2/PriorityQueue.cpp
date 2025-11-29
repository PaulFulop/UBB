#include "PriorityQueue.h"
#include <exception>
using namespace std;

// BC: theta(1)
// WC: theta(1)
// TC: theta(1)
PriorityQueue::PriorityQueue(Relation r) : data{ nullptr }, relation{ r } 
{}

// BC: theta(1) -> the new element has the highest priority
// WC: theta(n) -> the new element has the lowest priority and the queue is not empty
// TC: O(n)
void PriorityQueue::push(TElem e, TPriority p) {
	Element new_elem = std::pair<TElem, TPriority>(e, p);

	if (this->data == nullptr){
		this->data = new Node;
		this->data->info = new_elem;
		this->data->next = nullptr;
		return;
	}

	if (this->relation(new_elem.second, this->data->info.second)){
		Node* new_node = new Node;
		new_node->info = new_elem;
		new_node->next = this->data;
		this->data = new_node;
		return;
	}

	Node* aux_data = this->data;
	while (aux_data != nullptr && aux_data->next != nullptr && !this->relation(new_elem.second, aux_data->next->info.second)){
		aux_data = aux_data->next;
	}

	if (aux_data != nullptr){
		Node* new_node = new Node;
		new_node->info = new_elem;
		new_node->next = aux_data->next;
		aux_data->next = new_node;
	}
}

// BC: theta(1)
// WC: theta(1)
// TC: theta(1)
Element PriorityQueue::top() const {
	if (this->data == nullptr)
		throw exception("The queue is empty!");

	return data->info;
}

// BC: theta(1)
// WC: theta(1)
// TC: theta(1)
Element PriorityQueue::pop() {
	if (this->data == nullptr)
		throw exception("The queue is empty!");

	Node* p = this->data;
	Element elem = p->info;
	data = data->next;
	delete p;

	return elem;
}

// BC: theta(1)
// WC: theta(1)
// TC: theta(1)
bool PriorityQueue::isEmpty() const {
	return this->data == nullptr ? true : false;
}

// BC: theta(n)
// WC: theta(n)
// TC: theta(n)
PriorityQueue::~PriorityQueue() {
	while (this->data != nullptr){
		Node* p = this->data;
		data = data->next;
		delete p;
	}
};

// BC: theta(1) -> the queue is empty, we don't find the element and return -1
// WC: theta(n + n) = theta(2n) = theta(n) -> the queue is not empty and the element for which we want to increase the priority is the last element +
// the push function takes theta(n) time complexity
// TC: O(n)
TPriority PriorityQueue::increasePriority(TElem elem, TPriority newPriority)
{
	Element newElem = std::pair<TElem, TPriority>(elem, newPriority);	
	Node* auxData = this->data;

	while (auxData != nullptr)
	{
		if (auxData->info.first == newElem.first)
			break;

		auxData = auxData->next;
	}

	if (auxData == nullptr)
		return -1; // we didn't find the element

	TPriority oldPriority = auxData->info.second;
	if (!this->relation(newPriority, oldPriority)) 
		throw exception("The new exception is less priority than the old one!\n");

	if (auxData == this->data) {
		this->data = this->data->next;
		delete auxData;
		push(elem, newPriority);
		return oldPriority;
	}

	Node* prevNode = this->data;
	while (prevNode != nullptr && prevNode->next != auxData)
		prevNode = prevNode->next;

	if (prevNode != nullptr)
		prevNode->next = auxData->next;
	delete auxData;

	push(elem, newPriority);
	return oldPriority;
}