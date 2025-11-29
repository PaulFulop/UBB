#pragma once

#include <QMainWindow>
#include "ui_UndeliveredPackagesForm.h"
#include "Repository.h"
#include "Package.h"

class UndeliveredPackagesForm : public QMainWindow
{
	Q_OBJECT

public:
	UndeliveredPackagesForm(QWidget *parent = nullptr, Repository<Package>* _packages = nullptr);
	~UndeliveredPackagesForm();
protected:
	void paintEvent(QPaintEvent* event) override;
private:
	Ui::UndeliveredPackagesFormClass ui;
	Repository<Package>* packages;
};

