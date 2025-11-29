#include <iostream>
#include <assert.h>
#include "UI.h"

void Test();

int main()
{
	UI ui = UI();
	ui.serv.repo.Add(School("Avram_Iancu", pair<double, double>(46.77, 23.60), "2023.04.15", true));
	ui.serv.repo.Add(School("George_Cosbuc", pair<double, double>(46.77, 23.58), "2023.04.08", false));
	ui.serv.repo.Add(School("Alexandru_Vaida", pair<double, double>(46.77, 23.60), "2023.04.15", false));
	ui.serv.repo.Add(School("Romulus_Guga", pair<double, double>(46.77, 23.60), "2023.04.15", false));
	ui.serv.repo.Add(School("Colegiul_Transilvania", pair<double, double>(46.54, 23.60), "2023.05.03", false));

	ui.StartMenu();
	Test();
	return 0;
}

void Test()
{
	Service serv = Service();
	serv.repo.Add(School("Avram_Iancu1", pair<double, double>(46.77, 23.60), "2023.04.15", true));
	serv.repo.Add(School("Avram_Iancu2", pair<double, double>(46.77, 23.60), "2023.04.16", false));

	serv.RemoveSchool("Avram_Iancu1", pair<double, double>(46.77, 23.60));
	assert(serv.repo.schools.size() == 1);

	serv.MarkDisplaySchools("2023.04.17");
	assert(serv.repo.schools[0].visited = true);

	std::cout << "All good!";
}