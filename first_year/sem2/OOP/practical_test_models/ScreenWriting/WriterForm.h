#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_WriterForm.h"
#include <QSortFilterProxyModel>
#include "IdeasTableModel.h"

class WriterForm : public QMainWindow
{
    Q_OBJECT

public:
    WriterForm(const Writer& _w, IdeasTableModel* _itm, QWidget *parent = nullptr);
    ~WriterForm();

signals:
    void ideaAccepted(const std::string& creator);

public slots:
    void on_tableView_clicked(const QModelIndex& index);
    void on_pushButtonAdd_clicked();
    void on_pushButtonRevise_clicked();
    void on_pushButtonAccept_clicked();
    void on_ideaAccepted(const std::string& creator);
    void on_pushButtonSave_clicked();
    void on_pushButtonDevelop_clicked();
    void on_ideaDeveloped();

private:
    Ui::WriterFormClass ui;
    Writer w;
    IdeasTableModel* itm;
    int selectedRow = -1;
    //QSortFilterProxyModel* proxy;
};

