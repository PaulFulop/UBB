#pragma once
#include "Astronomer.h"
#include "Star.h"
#include "Repository.h"
#include <algorithm>

class Services{
public:
	Astronomer* astronomer;
	Repository<Star>* stars;


	Services() = default;

	Services(Astronomer* astronomer, Repository<Star>* stars)
		: astronomer(astronomer), stars(stars)
	{}
	
	void SortStarsByConstellation();
	void AddStar(Star newStar);
};

