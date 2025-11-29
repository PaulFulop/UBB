#pragma once

#include <QMainWindow>
#include "ui_DevelopIdeaForm.h"
#include "Idea.h"

class DevelopIdeaForm : public QMainWindow
{
	Q_OBJECT

public:
	DevelopIdeaForm(Idea* _idea, QWidget *parent = nullptr);
	~DevelopIdeaForm();

signals:
	void ideaDeveloped();

public slots:
	void on_pushButton_clicked();

private:
	Ui::DevelopIdeaFormClass ui;
	Idea* idea;
};

