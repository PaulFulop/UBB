#include "SortedBag.h"
#include "SortedBagIterator.h"

//BC: theta(m)
//WC: theta(m)
//TC: theta(m)
SortedBag::SortedBag(Relation r) {
	this->r = r;
	this->bag = new Node * [INITIAL_CAPACITY];
	this->m = INITIAL_CAPACITY;
	this->n = 0;

	for (int i = 0; i < this->m; ++i)
		this->bag[i] = nullptr;
}

//BC: theta(1) -> no resize, and the bucket is currently empty
//WC: theta(n^2 / m) -> we need to resize, and the element has not been found in the bucket
																// considering the length of a bucket is n/m on average																			
//TC: O(n^2 / m)
void SortedBag::add(TComp e) {
	if (n > m) { // resize
		m *= 2;
		Node** newBag = new Node * [m];

		for (int i = 0; i < m; ++i)
			newBag[i] = nullptr;

		for (int i = 0; i < m/2; ++i) {
			Node* current = this->bag[i];
			while (current != nullptr) {

				int hashPosition = (current->data.first % m + m) % m;

				if (newBag[hashPosition] == nullptr) { // the list corresponding to this position is empty => add first elem
					Node* newElem = new Node;
					newElem->prev = nullptr;
					newElem->data = current->data;
					newElem->next = nullptr;
					newBag[hashPosition] = newElem;
				}
				else { // the list corresponding to this position is not empty => add elem in corresponding position
					Node* current1 = newBag[hashPosition];
					while (current1 && this->r(current1->data.first, current->data.first)) {
						current1 = current1->next;
					}

					if (current1) {
						Node* newElem = new Node;
						newElem->next = current1;
						newElem->prev = current1->prev;
						newElem->data = current->data;

						if (current1->prev)
							current1->prev->next = newElem;
						else
							newBag[hashPosition] = newElem;

						current1->prev = newElem;
					}
					else {
						// insert at end of the list
						Node* last = newBag[hashPosition];
						if (!last) {
							// empty bucket: just add the node
							Node* newElem = new Node;
							newElem->prev = nullptr;
							newElem->next = nullptr;
							newElem->data = current->data;
							newBag[hashPosition] = newElem;
						}
						else {
							while (last->next)
								last = last->next;

							Node* newElem = new Node;
							newElem->prev = last;
							newElem->next = nullptr;
							newElem->data = current->data;
							last->next = newElem;
						}
					}
				}

				Node* next = current->next;
				delete current;
				current = next;
			}
		}

		delete[] this->bag;
		this->bag = newBag;
	}

	int hashPosition = (e % m + m) % m;

	if (this->bag[hashPosition] == nullptr) { // the list corresponding to this position is empty => add first elem
		Node* newElem = new Node;
		newElem->prev = nullptr;
		newElem->data = std::pair<TComp, int>(e, 1);
		newElem->next = nullptr;

		this->bag[hashPosition] = newElem;
		++this->n;
		return;
	}

	if (search(e)) { // found the elem => increase frequency
		Node* current = this->bag[hashPosition];
		while (current && current->data.first != e)
			current = current->next;

		if (current) {
			++current->data.second;
			++this->n;
		}
		return;
	}

	Node* current = bag[hashPosition];
	while (current && this->r(current->data.first, e)) {
		current = current->next;
	}

	Node* newElem = new Node;
	newElem->data = std::pair<TComp, int>(e, 1);
	newElem->prev = nullptr;
	newElem->next = nullptr;

	if (current) {
		newElem->next = current;
		newElem->prev = current->prev;
		if (current->prev)
			current->prev->next = newElem;
		current->prev = newElem;
		if (current == bag[hashPosition]) {
			bag[hashPosition] = newElem;
		}
	}
	else {
		// Insert at end
		current = bag[hashPosition];
		if(current) {
			while (current->next)
				current = current->next;
			current->next = newElem;
			newElem->prev = current;
		}
	}

	++this->n;
}

//BC: theta(1) -> the element has been found on the first position in the bucket
//WC: theta(n/m) -> the element has been found on the last position of the bucket
//TC: O(n/m) 
bool SortedBag::remove(TComp e) {
	if (!search(e)) return false;

	int hashPosition = (e % m + m) % m;

	Node* current = this->bag[hashPosition];
	while (current && current->data.first != e)
		current = current->next;

	if (current) {
		--current->data.second; // decrease frequency

		if (!current->data.second) { // in case there was only 1 element, remove it from the list
			if (current->prev)
				current->prev->next = current->next;
			else // if the element to be deleted is the first
				this->bag[hashPosition] = current->next; // current was head of the list

			if (current->next) // if the element to be deleted is NOT the last
				current->next->prev = current->prev;

			delete current;
		}

		--this->n;
		return true;
	}

	return false;
}

//BC: theta(1) -> bucket is empty
//WC: theta(n / m) -> the element has not been found in the bucket (considering the length of the buckets are about equal -> m = capacity, n = size) 
//TC: O(n/m)
bool SortedBag::search(TComp elem) const {
	int hashPosition = (elem % m + m) % m;

	if (!this->bag[hashPosition]) return false;

	Node* current = this->bag[hashPosition];
	while (current && current->data.first != elem)
		current = current->next;

	if (current) return true;
	return false;
}

//BC: theta(1) -> the element has been found on the first postion in the bucket
//WC: theta(n / m) -> the element has been found on the last position of the bucket
//TC: O(n/m)
int SortedBag::nrOccurrences(TComp elem) const {
	if (!search(elem)) return 0;

	int hashPosition = (elem % m + m) % m;
	Node* current = this->bag[hashPosition];
	while (current && current->data.first != elem)
		current = current->next;

	if (current) return current->data.second;
	return 0;
}

//BC: theta(1)
//WC: theta(1)
//TC: theta(1)
int SortedBag::size() const {
	return n;
}

//BC: theta(1)
//WC: theta(1)
//TC: theta(1)
bool SortedBag::isEmpty() const {
	return n == 0;
}

//BC: theta(1)
//WC: theta(1)
//TC: theta(1)
SortedBagIterator SortedBag::iterator() const {
	return SortedBagIterator(*this);
}

//BC: theta(m) -> the bag is empty
//WC: theta(n) -> n elements to be removed 
//TC: O(n)
SortedBag::~SortedBag() {
	for (int i = 0; i < m; ++i) {
		Node* head = this->bag[i];
		while (head != nullptr) {
			Node* next = head->next;
			delete head;
			head = next;
		}
	}
	delete[] this->bag;
}
