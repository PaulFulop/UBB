#include "Repository.h"

Repository::Repository(): docs(std::vector<Document>()){}
Repository::Repository(std::string fileName) {
	std::ifstream fin(fileName);

	std::string line;
	while (std::getline(fin, line)) {
		std::string _name, _keyw, _content;

		std::stringstream ss(line);
		std::getline(ss, _name, '|');
		_name.pop_back();

		std::getline(ss, _keyw, '|');
		_keyw.pop_back();
		_keyw.erase(0, 1);

		std::getline(ss, _content, '\n');
		_content.erase(0, 1);

		docs.push_back(Document(_name, _keyw, _content));
	}
	fin.close();
}

Repository Repository::FilterRepo(std::string text) {
	Repository filtRepo = Repository();

	for (const auto& doc : docs) {
		if (doc.name.find(text) != std::string::npos || doc.keywords.find(text) != std::string::npos || doc.content.find(text) != std::string::npos)
			filtRepo.docs.push_back(doc);
	}

	return filtRepo;
}

void Repository::SortDocsByDescLen() {
	for (int i = 0; i < docs.size() - 1; ++i)
		for (int j = i + 1; j < docs.size(); ++j)
			if (docs[i].desc_length > docs[j].desc_length)
				std::swap(docs[i], docs[j]);
}