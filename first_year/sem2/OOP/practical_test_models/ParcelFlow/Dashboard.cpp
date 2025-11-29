#include "Dashboard.h"

Dashboard::Dashboard(Repo<Parcel>* _parcels, QWidget *parent)
	: parcels(_parcels), QMainWindow(parent)
{
	ui.setupUi(this);
	PopulateListWidget();
}

void Dashboard::PopulateListWidget() {
    ui.listWidgetParcels->clear();
    for (const auto& parcel : parcels->data) {
		QListWidgetItem* item = new QListWidgetItem(QString::fromStdString(parcel.ToString()));

		if (parcel.delivered)
			item->setBackground(Qt::darkGreen);
		else
			item->setBackground(Qt::darkRed);
		ui.listWidgetParcels->addItem(item);

    }
}

void Dashboard::on_pushButtonDeliver_clicked() {
	std::string name = ui.lineEditName->text().toStdString();
	std::string adrStreet = ui.lineEditStreet->text().toStdString();
	int adrNum = std::atoi(ui.lineEditNumber->text().toStdString().c_str());
	double locX = std::atof(ui.lineEditX->text().toStdString().c_str());
	double locY = std::atof(ui.lineEditY->text().toStdString().c_str());

	Parcel newParcel = Parcel(name, adrStreet, adrNum, locX, locY, false);
	parcels->Add(newParcel);
	parcels->SaveToFile();
	PopulateListWidget();
	emit dataChanged();
}

void Dashboard::parcelsDataModified() {
	PopulateListWidget();
}

Dashboard::~Dashboard()
{}

