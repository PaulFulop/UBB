#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_UserForm.h"
#include "SearchQuestionWindow.h"
#include "Service.h"

class UserForm : public QMainWindow
{
    Q_OBJECT

public:
    UserForm(Service _serv, QWidget *parent = nullptr);
    ~UserForm();
    void PopulateListWidgetQuestions();
    void PopulateListWidgetAnswers(std::vector<Answer> aToQ);

signals:
    void questionAdded();
    void answerAdded();

public slots:
    void on_questionAdded();
    void on_answerAdded();
    void on_pushButtonA_clicked();
    void on_pushButtonQ_clicked();
    void on_listWidgetQuestions_itemClicked(QListWidgetItem* item);

private:
    Ui::UserFormClass ui;
    Service serv;
};

