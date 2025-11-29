#include "FixedCapBiMap.h"
#include "FixedCapBiMapIterator.h"
#include <exception>
using namespace std;


FixedCapBiMapIterator::FixedCapBiMapIterator(const FixedCapBiMap& d) : map(d), current_position(0)
{}


void FixedCapBiMapIterator::first() {
	this->current_position = 0;
}


void FixedCapBiMapIterator::next() {
	if (this->current_position >= this->map.map_size)
		throw std::exception("Out of the container.");
	++this->current_position;
}

void FixedCapBiMapIterator::previous() {
	if (this->current_position < 0)
		throw std::exception("Out of the container.");
	--this->current_position;
}


TElem FixedCapBiMapIterator::getCurrent(){
	if (this->current_position >= this->map.map_size)
		throw std::exception("Out of the container.");

	return this->map.elems[current_position];
}


// BC: theta(1)
// WC: theta(1)
// TC: theta(1)
bool FixedCapBiMapIterator::valid() const {
	return this->current_position < this->map.map_size && this->current_position >= 0 ? true : false;
}