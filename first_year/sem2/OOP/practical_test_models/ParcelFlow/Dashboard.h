#pragma once

#include <QMainWindow>
#include "ui_Dashboard.h"
#include "Repository.h"
#include "Parcel.h"

class Dashboard : public QMainWindow
{
	Q_OBJECT

public:
	Dashboard(Repo<Parcel>* _parcels, QWidget *parent = nullptr);
	~Dashboard();
	void PopulateListWidget();

signals:
	void dataChanged();

public slots:
	void parcelsDataModified();
	void on_pushButtonDeliver_clicked();

private:
	Ui::DashboardClass ui;
	Repo<Parcel>* parcels;
};

