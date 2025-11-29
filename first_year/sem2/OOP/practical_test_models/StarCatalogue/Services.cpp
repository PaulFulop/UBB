#include "Services.h"


void Services::AddStar(Star newStar) {
	if (newStar.name.empty() || newStar.diameter <= 0)
		throw std::exception("Invalid star!");

	for(const auto& star : stars->data)
		if(star.name == newStar.name)
			throw std::exception("Found a star with the same name!");

	stars->Add(newStar);
}

void Services::SortStarsByConstellation() {
	for (int i = 0; i < stars->data.size() - 1; ++i)
		for (int j = i + 1; j < stars->data.size(); ++j)
			if (stars->data[i].constellation > stars->data[j].constellation)
				std::swap(stars->data[i], stars->data[j]);
}