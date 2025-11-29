#include "Statistics.h"
#include <unordered_set>

Statistics::Statistics(Repo<Doctor>* _doctors, Repo<Patient>* _patients, QWidget *parent)
	: doctors(_doctors), patients(_patients), QMainWindow(parent)
{
	ui.setupUi(this);
}

Statistics::~Statistics()
{}

void Statistics::paintEvent(QPaintEvent* event) {
	QPainter painter(this);
	painter.setRenderHint(QPainter::Antialiasing);
	painter.setBrush(Qt::red);
	std::unordered_set<std::string> specialisations;

	for (const auto& d : doctors->data)
		specialisations.insert(d.specialisation);

	int x = 50, y = 50;
	for (const auto& sp : specialisations) {
		painter.drawText(x, y, QString::fromStdString(sp));
		y += 100;
	}

	y = 50;
	x = 170;
	for (const auto& sp : specialisations) {
		int size = 0;
		for (const auto& p : patients->data)
			if (sp == p.specialisation || p.diagnosis == "undiagnosed") ++size;

		painter.drawEllipse(x, y-50, size * 20, size * 20);
		y += 100;
	}
}

void Statistics::on_dataModified() {
	update();
}