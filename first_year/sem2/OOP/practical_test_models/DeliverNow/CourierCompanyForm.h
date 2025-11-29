#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_CourierCompanyForm.h"
#include "Repository.h"
#include "Package.h"
#include "CourierService.h"
#include "CourierForm.h"
#include <vector>
#include "UndeliveredPackagesForm.h"

class CourierForm;  // Forward declaration

class CourierCompanyForm : public QMainWindow
{
    Q_OBJECT

public:
    CourierCompanyForm(QWidget *parent = nullptr);
    ~CourierCompanyForm();
    void PopulateListWidget();

private slots:
    void on_pushButtonAdd_clicked();

private:
    Ui::CourierCompanyFormClass ui;
    Repository<Package> packages;
    Repository<Courier> couriers;
    std::vector<CourierForm*> courierForms;
    UndeliveredPackagesForm* upf;
};

