#pragma once

#include <QMainWindow>
#include "ui_UndeliveredParcelsForm.h"
#include "Repository.h"
#include "Parcel.h"

class UndeliveredParcelsForm : public QMainWindow
{
	Q_OBJECT

public:
	UndeliveredParcelsForm(Repo<Parcel>* _parcels, QWidget *parent = nullptr);
	~UndeliveredParcelsForm();

public slots:
	void parcelDelivered();

protected:
	void paintEvent(QPaintEvent* event) override;

private:
	Ui::UndeliveredParcelsFormClass ui;
	Repo<Parcel>* parcels;
};

