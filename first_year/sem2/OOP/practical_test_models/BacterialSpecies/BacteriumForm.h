#pragma once

#include <QMainWindow>
#include "ui_BacteriumForm.h"
#include "Repo.h"
#include "Bacterium.h"
#include <QPainter>

class BacteriumForm : public QMainWindow
{
	Q_OBJECT

public:
	BacteriumForm(Repo<Bacterium>* _bacterium, QWidget *parent = nullptr);
	~BacteriumForm();
	void paintEvent(QPaintEvent* event) override;

private:
	Ui::BacteriumFormClass ui;
	Repo<Bacterium>* bacterium;
};

