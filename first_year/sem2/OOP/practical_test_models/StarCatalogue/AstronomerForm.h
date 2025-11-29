#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_AstronomerForm.h"
#include <QSortFilterProxyModel>
#include "AstronomerModels.h"
#include "Services.h"
#include "StarsForm.h"
#include "Utils.h"

class AstronomerForm : public QMainWindow
{
    Q_OBJECT

public:
    AstronomerForm(AstronomerTableModel* _atm, AstronomerListModel* _alm, const Services& _serv, QWidget *parent = nullptr);
    ~AstronomerForm();

private slots:
    void on_pushButtonAdd_clicked();
    void on_pushButtonView_clicked();
    void on_checkBoxStars_checkStateChanged(Qt::CheckState state);
    void on_lineEditFilter_textChanged(const QString& text);

private:
    Ui::AstronomerFormClass ui;
    AstronomerTableModel* atm;
    AstronomerListModel* alm;
    Services serv;
    QSortFilterProxyModel *proxyTable,  *proxyList;
    StarsForm* starsForm;
};

