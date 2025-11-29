#include "Statistics.h"

Statistics::Statistics(Repo<Programmer>* _programmers, QWidget *parent)
	: programmers(_programmers), QMainWindow(parent)
{
	ui.setupUi(this);
}

Statistics::~Statistics()
{}

void Statistics::paintEvent(QPaintEvent* event) {
	QPainter p1(this);

	p1.setRenderHint(QPainter::Antialiasing);

	int x = 100, y = 100, offset = 200, circleSize = 25;
	for (const auto& p : programmers->data) {
		if (!p.filesToRevise) {
			p1.setPen(Qt::blue);
			p1.drawText(x, y, QString::fromStdString(p.name));
			p1.drawEllipse(x, y + offset / 2, circleSize * p.revisedFiles, circleSize * p.revisedFiles);
			x += offset;
		}
		else {
			p1.setPen(Qt::red);
			p1.drawText(x, y, QString::fromStdString(p.name));
			p1.drawEllipse(x, y + offset / 2, circleSize * p.revisedFiles, circleSize * p.revisedFiles);
			x += offset;
		}
	}
}

void Statistics::on_dataModified() {
	this->update();
}