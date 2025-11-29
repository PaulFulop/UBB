#include "UI.h"

void UI::InitData()
{
	BP* bp = new BP;
	BMI* bmi = new BMI;

	bp->setSyastolicValue(70);
	bp->setDiastolicValue(40);
	bp->setDate("2025.09.20");

	bmi->setValue(100);
	bmi->setDate("2025.10.20");

	person.addAnalysis(bp);
	person.addAnalysis(bmi);
}

void UI::PrintCommands()
{
	std::cout << "Commands:\n1 -> add a new analysis.\n2 -> show all anaylses\n3 -> show if the person is ill in the current month\n4 -> save analyses between 2 dates in a file\n5 -> exit\n\n";
}

void UI::Start()
{
	InitData();
	PrintCommands();
	int cmd = -1;
	int month;
	std::string date1, date2;
	std::vector<MedicalAnalysis*> a;

	while (true)
	{
		std::cout << "\n> ";
		std::cin >> cmd;

		switch (cmd)
		{
		case 1:
			std::cout << "Read the date: ";
			std::cin >> date1;

			std::cout << "\nChoose type (a -> bp, b -> bmi): ";
			char c;
			std::cin >> c;

			if (c == 'a') {
				BP* bp = new BP;
				int sv, dv;
				std::cout << "Read the syastolic value: ";
				std::cin >> sv;

				std::cout << "Read the diastolic value: ";
				std::cin >> dv;

				bp->setSyastolicValue(sv);
				bp->setDiastolicValue(dv);
				bp->setDate(date1);

				person.addAnalysis(bp);
				std:: cout << "New analysis added.\n";
			}
			else if (c == 'b') {
				BMI* bmi = new BMI;
				int v;
				std::cout << "Read the bmi value: ";
				std::cin >> v;

				bmi->setValue(v);
				bmi->setDate(date1);
				person.addAnalysis(bmi);
				std::cout << "New analysis added.\n";
			}
			else {
				std::cout << "Invalid type.\n";
			}
			break;
		case 2:
			a = person.getAllAnalyses();
			for (const auto& analysis : a)
				std:: cout << analysis->toString() << '\n';
			break;
		case 3:
			std::cout << "Insert the current month here (numerical value): ";
			std::cin >> month;

			if (person.IsIll(month))
				std::cout << "The person is ill.\n";
			else
				std::cout << "The person is not ill.\n";
			break;
		case 4:
			std::cout << "Insert the first date here: ";
			std::cin >> date1;

			std::cout << "Insert the second date here: ";
			std::cin >> date2;

			person.writeToFile("analyses.txt", date1, date2);
			std::cout << "Data has been written to the file.\n";
			break;
		case 5:
			std::cout << "Exiting...\n\n";
			exit(0);
			break;
		default:
			break;
		}
	}
}