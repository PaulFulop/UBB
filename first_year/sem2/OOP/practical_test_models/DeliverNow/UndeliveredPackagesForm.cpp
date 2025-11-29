#include "UndeliveredPackagesForm.h"
#include <QPainter>

UndeliveredPackagesForm::UndeliveredPackagesForm(QWidget *parent, Repository<Package>* _packages)
	: QMainWindow(parent), packages(_packages)
{
	ui.setupUi(this);
}

UndeliveredPackagesForm::~UndeliveredPackagesForm()
{}

void UndeliveredPackagesForm::paintEvent(QPaintEvent* event) {
	QPainter painter(this);
	painter.setRenderHint(QPainter::Antialiasing);
	painter.setBrush(Qt::red);


	for (const auto& p : packages->data)
		if(!p.deliveryStatus)
			painter.drawEllipse(p.x, p.y, 50, 50);
}
