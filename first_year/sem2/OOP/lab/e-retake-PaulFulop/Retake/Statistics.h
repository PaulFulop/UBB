#pragma once

#include <QMainWindow>
#include "ui_Statistics.h"
#include "Service.h"
#include <QPainter>

class Statistics : public QMainWindow
{
	Q_OBJECT

public:
	Statistics(Service _serv, QWidget *parent = nullptr);
	~Statistics();
	void paintEvent(QPaintEvent* event) override;

public slots:
	void on_dataModified();

private:
	Ui::StatisticsClass ui;
	Service serv;
};

