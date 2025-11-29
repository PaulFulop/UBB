#pragma once

#include <QMainWindow>
#include "ui_SearchQuestionWindow.h"
#include "Service.h"

class SearchQuestionWindow : public QMainWindow
{
	Q_OBJECT

public:
	SearchQuestionWindow(Service _serv, QWidget *parent = nullptr);
	~SearchQuestionWindow();
	void PopulateListWidget(std::string filter);

signals:
	void dataModified();

public slots:
	void on_dataModified();
	void on_lineEditSearch_textChanged(const QString& text);

private:
	Ui::SearchQuestionWindowClass ui;
	Service serv;
};

