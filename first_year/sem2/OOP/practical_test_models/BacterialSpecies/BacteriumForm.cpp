#include "BacteriumForm.h"
#include <unordered_set>

BacteriumForm::BacteriumForm(Repo<Bacterium>* _bacterium, QWidget *parent)
	: bacterium(_bacterium), QMainWindow(parent)
{
	ui.setupUi(this);
}

BacteriumForm::~BacteriumForm()
{}

void BacteriumForm::paintEvent(QPaintEvent* event) {
	QPainter painter(this);
	painter.setRenderHint(QPainter::Antialiasing);
	painter.setBrush(Qt::black);

	std::unordered_set<std::string> species;

	for (const auto& b : bacterium->data)
		species.insert(b.species);

	QPoint p = QPoint(50, 50);
	int i = 0;
	std::vector<int> dist = std::vector<int>(species.size(), 100);
	for (const auto& sp : species) {
		p.setX(p.x() + 50);
		painter.drawText(p, QString::fromStdString(sp));

		int currDist = p.y() + 50;
		for (int j = 0; j < bacterium->data.size(); ++j)
			if (bacterium->data[j].species == sp) {
				painter.drawEllipse(p.x(), currDist, 25, 25);
				currDist += 50;
			}

		++i;
	}
}