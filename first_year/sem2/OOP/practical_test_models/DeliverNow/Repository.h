#pragma once
#include <vector>
#include <string>
#include <fstream>

template <typename T>
class Repository {
public:
	std::vector<T> data;
	std::string fileName;

	Repository() = default;
	Repository(std::string _fileName);
	void SaveToFile();
};

template <typename T>
Repository<T>::Repository(std::string _fileName): fileName(_fileName) {
	std::ifstream fin(fileName);

	if (!fin.is_open())
		throw std::exception("Error opening the file.");

	T elem = T();
	while (fin >> elem)
		data.push_back(elem);

	fin.close();
}

template <typename T>
void Repository<T>::SaveToFile() {
	std::ofstream fout(fileName);

	if (!fout.is_open())
		throw std::exception("Error opening the file.");
	
	for (const auto& e : data)
		fout << e << '\n';

	fout.close();
}