#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_MedicalDisordersForm.h"
#include "Repository.h"

class MedicalDisordersForm : public QMainWindow
{
    Q_OBJECT

public:
    MedicalDisordersForm(QWidget *parent = nullptr);
    ~MedicalDisordersForm();
    void PopulateList(Repository repo);
    void PopulateSymptomsList(std::vector<std::string> symptoms);

private slots:
    void on_lineEditSearchCategory_textChanged(const QString& text);
    void on_lineEditSearchName_textChanged(const QString& text);
    void on_pushButtonShowSymptoms_clicked();

private:
    Ui::MedicalDisordersFormClass ui;
    Repository mainRepo;
};

