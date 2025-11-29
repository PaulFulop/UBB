#include "SMIterator.h"
#include "SortedMap.h"
#include <exception>

using namespace std;

// BC: theta(n)
// WC: theta(n)
// TC: theta(n)
SMIterator::SMIterator(const SortedMap& m) : map(m), currentPosition(0){
	Node* auxList = map.list;
	elems = new TElem[map.n];
	int k = 0;
	InOrderTraversal(auxList, k);
}

// BC: theta(1)
// WC: theta(1)
// TC: theta(1)
void SMIterator::first(){
	currentPosition = 0;
}

// BC: theta(n)
// WC: theta(n)
// TC: theta(n)
void SMIterator::InOrderTraversal(Node* list, int& k) {
	if (!list) return;

	InOrderTraversal(list->leftChild, k);
	elems[k++] = list->data;
	InOrderTraversal(list->rightChild, k);
}

// BC: theta(1)
// WC: theta(1)
// TC: theta(1)
void SMIterator::next(){
	if (!valid())
		throw exception("Invalid!\n");
	++currentPosition;
}

// BC: theta(1)
// WC: theta(1)
// TC: theta(1)
bool SMIterator::valid() const{
	return currentPosition < map.n;
}

// BC: theta(1)
// WC: theta(1)
// TC: theta(1)
TElem SMIterator::getCurrent() const{
	if (!valid())
		throw exception("Invalid!\n");
	return elems[currentPosition];
}

// BC: theta(1)
// WC: theta(1)
// TC: theta(1)
SMIterator::~SMIterator() {
	delete[] elems;
}
