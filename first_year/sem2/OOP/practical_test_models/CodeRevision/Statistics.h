#pragma once

#include <QMainWindow>
#include "ui_Statistics.h"
#include "Repo.h"
#include "Programmer.h"
#include <QPainter>

class Statistics : public QMainWindow
{
	Q_OBJECT

public:
	Statistics(Repo<Programmer>* _programmers, QWidget *parent = nullptr);
	~Statistics();
	void paintEvent(QPaintEvent* event) override;

public slots:
	void on_dataModified();

private:
	Ui::StatisticsClass ui;
	Repo<Programmer>* programmers;
};

