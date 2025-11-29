#include "Statistics.h"

Statistics::Statistics(Service _serv, QWidget *parent)
	: serv(_serv), QMainWindow(parent)
{
	ui.setupUi(this);
}

Statistics::~Statistics()
{}

void Statistics::paintEvent(QPaintEvent* event) {
	QPainter painter(this);
	auto filteredRecipes = serv.FilterRecipesByCuisine();

	int x = 100, y = 100, offset = 200, shapeSize = 50;
	for (const auto& r : filteredRecipes) {
		if (r.prep > 100)
			painter.setPen(Qt::red);
		else
			painter.setPen(Qt::blue);

		painter.drawText(x, y, QString::fromStdString(r.name));
		painter.drawEllipse(x, y + offset / 4, shapeSize * r.prep / 100, shapeSize * r.prep / 100);
		x += offset;
	}
}

void Statistics::on_dataModified() {
	this->update();
}