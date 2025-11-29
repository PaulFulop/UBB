#include "MainForm.h"

MainForm::MainForm(std::vector<Service> _s, QWidget* parent)
	: services(_s), QMainWindow(parent)
{
	ui.setupUi(this);
	PopulateListWidget();
}

MainForm::~MainForm()
{}

void MainForm::PopulateListWidget() {
	ui.listWidgetDepartments->clear();

	for (auto& s : services) {
		std::string str = s.d->ToString() + ", " + std::to_string(s.NrOfVolunteers());
		QListWidgetItem* item = new QListWidgetItem(QString::fromStdString(str));
		ui.listWidgetDepartments->addItem(item);
	}
}