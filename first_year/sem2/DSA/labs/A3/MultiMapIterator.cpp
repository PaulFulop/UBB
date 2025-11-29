#include "MultiMapIterator.h"
#include "MultiMap.h"

// BC : theta(1)
// WC : theta(1)
// TC : theta(1)
MultiMapIterator::MultiMapIterator(const MultiMap& c): col(c), currPos(c.head)
{}

// BC : theta(1)
// WC : theta(1)
// TC : theta(1)
TElem MultiMapIterator::getCurrent() const {
	if (!this->valid())
		throw exception("Invalid!\n");

	return col.node[currPos].data;
}

// BC : theta(1)
// WC : theta(1)
// TC : theta(1)
bool MultiMapIterator::valid() const {
	return currPos != -1;
}

// BC : theta(1)
// WC : theta(1)
// TC : theta(1)
void MultiMapIterator::next() {
	if (!this->valid())
		throw exception("Invalid!\n");

	currPos = col.node[currPos].next;
}

// BC : theta(1)
// WC : theta(1)
// TC : theta(1)
void MultiMapIterator::first() {
	currPos = col.head;
}