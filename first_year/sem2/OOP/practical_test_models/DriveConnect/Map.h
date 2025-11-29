#pragma once

#include <QMainWindow>
#include "ui_Map.h"
#include "Repo.h"
#include "Report.h"
#include <QPainter>

class Map : public QMainWindow
{
	Q_OBJECT

public:
	Map(Repo<Report>* _reports, QWidget *parent = nullptr);
	~Map();
	void paintEvent(QPaintEvent* event) override;

public slots:
	void on_reportValidated();

private:
	Ui::MapClass ui;
	Repo<Report>* reports;
};

