#include "StarsForm.h"
#include <QPainter>

StarsForm::StarsForm(const Services& _serv, QWidget *parent)
	: serv(_serv), QMainWindow(parent)
{
	ui.setupUi(this);
}

StarsForm::~StarsForm()
{}

void StarsForm::paintEvent(QPaintEvent* event) {
	QPainter painter(this);
	painter.setRenderHint(QPainter::Antialiasing);
	painter.setBrush(Qt::red);

	for (const auto& star : serv.stars->data)
		if (star.constellation == serv.astronomer->constellation)
			painter.drawEllipse(star.RA, star.Dec, star.diameter, star.diameter);
}