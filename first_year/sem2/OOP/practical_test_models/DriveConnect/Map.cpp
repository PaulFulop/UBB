#include "Map.h"

Map::Map(Repo<Report>* _reports, QWidget *parent)
	: reports(_reports), QMainWindow(parent)
{
	ui.setupUi(this);
}

Map::~Map()
{}

void Map::paintEvent(QPaintEvent* event) {
	QPainter painter(this);
	painter.setBrush(Qt::red);
	painter.setRenderHint(QPainter::Antialiasing);

	for (const auto& report : reports->data) {
		if (report.valid) {
			painter.drawEllipse(report.latitude, report.longitude, 20, 20);
			painter.drawText(report.latitude, report.longitude + 30, QString::fromStdString(report.description));
		}
	}
}

void Map::on_reportValidated() {
	this->update();
}