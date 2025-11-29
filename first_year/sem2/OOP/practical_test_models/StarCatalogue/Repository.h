#pragma once
#include <vector>
#include <string>
#include <fstream>
#include "Utils.h"

template<typename T>
class Repository {
public:
	std::vector<T> data;
	std::string fileName;

	Repository() = default;
	Repository(const std::string& _fileName);
	void Add(T newElem);
	void SaveToFile();
};

template<typename T>
Repository<T>::Repository(const std::string& _fileName): fileName(_fileName) {
	std::ifstream fin(fileName);
	if (!fin.is_open())
		throw std::exception("Cannot open file!");

	T elem = T();
	while (fin >> elem) {
		data.push_back(elem);
	}

	fin.close();
}

template<typename T>
void Repository<T>::Add(T newElem) {
	data.push_back(newElem);
}

template<typename T>
void Repository<T>::SaveToFile() {
	std::ofstream fout(fileName);

	if(!fout.is_open())
		throw std::exception("Cannot open file!");

	for (const auto& e : data)
		fout << e << '\n';

	fout.close();
}