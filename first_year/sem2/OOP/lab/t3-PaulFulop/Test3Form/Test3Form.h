#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_Test3Form.h"
#include "Repository.h"

class Test3Form : public QMainWindow
{
    Q_OBJECT

public:
    Test3Form(QWidget *parent = nullptr);
    ~Test3Form();
    void PopulateList(Repository repo);

private slots:
    void on_lineEditSearch_textChanged(const QString& text);
    void on_listWidgetDocs_itemClicked(QListWidgetItem* item);

private:
    Ui::Test3FormClass ui;
    Repository mainRepo;
};

