#pragma once
#include <vector>
#include <string>
#include <fstream>

template<typename T>
class Repo {
public:
	std::vector<T> data;
	std::string fileName;

	Repo() = default;
	Repo(std::string _fileName) : fileName(_fileName) { ReadFromFile(); }
	~Repo() { SaveToFile(); }

	void ReadFromFile();
	void SaveToFile();
	void Add(T newElem);
};

template<typename T>
void Repo<T>::ReadFromFile() {
	std::ifstream fin(fileName);
	if (!fin.is_open()) return;

	T elem = T();
	while (fin >> elem)
		Add(elem);
	fin.close();
}

template<typename T>
void Repo<T>::SaveToFile() {
	std::ofstream fout(fileName);
	if (!fout.is_open()) return;

	for (const auto& elem : data)
		fout << elem << '\n';

	fout.close();
}

template<typename T>
void Repo<T>::Add(T newElem) {
	data.push_back(newElem);
}