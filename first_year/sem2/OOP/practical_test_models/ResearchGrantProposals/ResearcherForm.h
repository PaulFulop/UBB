#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_ResearcherForm.h"
#include "Repo.h"
#include "Researcher.h"
#include "Idea.h"
#include "IdeasTableModel.h"
#include "DevelopedIdeasTableModel.h"
#include <QSortFilterProxyModel>

class ResearcherForm : public QMainWindow
{
    Q_OBJECT

public:
    ResearcherForm(Researcher* _researcher, Repo<Idea>* _ideas, IdeasTableModel* _itm, DevelopedIdeasTableModel* _ditm, QWidget *parent = nullptr);
    ~ResearcherForm();

signals:
    void ideaAccepted(int pos);

public slots:
    void on_pushButtonAdd_clicked();
    void on_tableViewIdeas_clicked(const QModelIndex& index);
    void on_pushButtonAccept_clicked();
    void on_ideaAccepted(int pos);
    void on_pushButtonDevelop_clicked();
    void on_pushButtonSaveAll_clicked();

private:
    Ui::ResearcherFormClass ui;
    Researcher* researcher;
    Repo<Idea>* ideas;
    IdeasTableModel* itm;
    DevelopedIdeasTableModel* ditm;
    QSortFilterProxyModel* proxy;
    int clickedRow = -1;
};

