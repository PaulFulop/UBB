#pragma once

#include <QMainWindow>
#include "ui_MainForm.h"
#include "Service.h"
#include "Repository.h"
#include "Department.h"
#include <vector>

class MainForm : public QMainWindow
{
	Q_OBJECT

public:
	MainForm(std::vector<Service> _s, QWidget *parent = nullptr);
	~MainForm();
	void PopulateListWidget();

private:
	Ui::MainFormClass ui;
	std::vector<Service> services;
};

