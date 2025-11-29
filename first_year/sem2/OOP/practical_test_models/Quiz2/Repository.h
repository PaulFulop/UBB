#pragma once
#include <vector>
#include <string>
#include <fstream>

template <typename T>
class Repository {
public:
	std::vector<T> data;
	std::string fileName;

	Repository();
	Repository(std::string _fileName);
	void Add(const T& new_elem);
	void SaveToFile();
};

template <typename T>
Repository<T>::Repository(): data(std::vector<T>()), fileName("") {}

template <typename T>
Repository<T>::Repository(std::string _fileName): fileName(_fileName) {
	std::ifstream fin(fileName);

	if (!fin.is_open())
		throw std::exception("Error opening file!");

	T elem = T();
	while (fin >> elem) {
		data.push_back(elem);
	}

	fin.close();
}

template <typename T>
void Repository<T>::Add(const T& new_elem) {
	data.push_back(new_elem);
}

template <typename T>
void Repository<T>::SaveToFile() {
	std::ofstream fout(fileName);

	if(!fout.is_open())
		throw std::exception("Error opening file!");
	
	for (const auto& elem : data)
		fout << elem << '\n';

	fout.close();
}