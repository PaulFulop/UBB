#pragma once
#include "ServiceAM.h"
#include "ServiceUM.h"
#include "EventViewer.h"
#include "CSVEventViewer.h"
#include "HTMLEventViewer.h"

class UserInterface {
public:
	std::vector<std::string> fileDescriptors;
	ServiceAM adminServ;
	ServiceUM userServ;

	UserInterface(std::vector<std::string> _fileDescriptors);
	~UserInterface();
	void InitializeData();
	bool Mode();
	void PrintAdminMenu();
	void PrintUserMenu();
	void PrintUserCommands();
	void RunAdminMenu();
	void RunUserMenu();
	void Start();
	void AddEvents(Repository& repo);
};