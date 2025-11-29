#pragma once

#include <QMainWindow>
#include "ui_Statistics.h"
#include "Repo.h"
#include "Patient.h"
#include "Doctor.h"
#include <QPainter>

class Statistics : public QMainWindow
{
	Q_OBJECT

public:
	Statistics(Repo<Doctor>* _doctors, Repo<Patient>* _patients, QWidget *parent = nullptr);
	~Statistics();
	void paintEvent(QPaintEvent* event) override;

public slots:
	void on_dataModified();

private:
	Ui::StatisticsClass ui;
	Repo<Doctor>* doctors;
	Repo<Patient>* patients;
};

