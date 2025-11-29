#pragma once

#include <QMainWindow>
#include "ui_StarsForm.h"
#include "Services.h"

class StarsForm : public QMainWindow
{
	Q_OBJECT

public:
	StarsForm(const Services& _serv, QWidget *parent = nullptr);
	~StarsForm();
protected:
	void paintEvent(QPaintEvent* event) override;

private:
	Ui::StarsFormClass ui;
	Services serv;
};

