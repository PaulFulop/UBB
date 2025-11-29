#pragma once

#include <QMainWindow>
#include "ui_CourierForm.h"
#include "CourierService.h"
#include "CourierCompanyForm.h"
#include "UndeliveredPackagesForm.h"

class CourierForm : public QMainWindow
{
	Q_OBJECT

public:
	CourierService serv;
	CourierForm(QWidget *parent = nullptr, CourierService _serv = CourierService(), UndeliveredPackagesForm* _upf = nullptr);
	~CourierForm();

	void PopulateListWidget();
	void PopulateComboBox();

private slots:
	void on_pushButtonDeliver_clicked();
	void on_comboBoxStreets_currentIndexChanged(int index);
protected:
	void paintEvent(QPaintEvent* event) override;
private:
	Ui::CourierFormClass ui;
	UndeliveredPackagesForm* upf;
};

