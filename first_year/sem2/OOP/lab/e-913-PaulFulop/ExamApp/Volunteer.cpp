#include "Volunteer.h"
#include "Utils.h"

std::istream& operator >> (std::istream& is, Volunteer& v) {
	std::string line;
	std::getline(is, line);

	std::vector<std::string> tokens = Tokenize(line, ',');

	if (tokens.size() != 3 && tokens.size() != 5)
		return is;

	std::string name = tokens[0];
	std::string email = tokens[1];
	std::vector<std::string> listOfInterests = Tokenize(tokens[2], ' ');
	if (tokens.size() == 3) {
		v = Volunteer(name, email, listOfInterests, Department()); 
		return is;
	}

	std::string departmentName = tokens[3];
	std::string departentDescription = tokens[4];
	v = Volunteer(name, email, listOfInterests, Department(departmentName, departentDescription));
	return is;
}

std::ostream& operator << (std::ostream& os, const Volunteer& v) {
	os << v.name << ',' << v.email << ',';
	for (int i = 0; i < v.listOfInterests.size() - 1; ++i)
		os << v.listOfInterests[i] << ' ';
	os << v.listOfInterests[v.listOfInterests.size() - 1];

	if (v.department.desc == "" && v.department.name == "")
		return os;
	os << ',' << v.department;
	return os;
}

double Volunteer::SuitabilityScore() {
	int wordsInDepDesc = Tokenize(department.desc, ' ').size();
	int nrInterests = 0;

	for (const auto& i : listOfInterests)
		if (department.desc.find(i) != std::string::npos)
			++nrInterests;

	return double(nrInterests / wordsInDepDesc);
}

std::string Volunteer::ToString() {
	std::string str;
	str += name + " " + email + ", ";
	for (const auto& i : listOfInterests)
		str += i + " ";

	return str;
}