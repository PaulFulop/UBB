#include "UndeliveredParcelsForm.h"
#include <QPainter>

UndeliveredParcelsForm::UndeliveredParcelsForm(Repo<Parcel>* _parcels, QWidget *parent)
	: parcels(_parcels), QMainWindow(parent)
{
	ui.setupUi(this);
}

UndeliveredParcelsForm::~UndeliveredParcelsForm()
{}

void UndeliveredParcelsForm::paintEvent(QPaintEvent* event) {
	QPainter painter(this);

	painter.setRenderHint(QPainter::Antialiasing);
	painter.setBrush(Qt::red);
	
	for (const auto& p : parcels->data)
		if(!p.delivered)
			painter.drawEllipse(p.locationX, p.locationY, 50, 50);
}

void UndeliveredParcelsForm::parcelDelivered() {
	this->update();
}