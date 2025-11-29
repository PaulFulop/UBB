#pragma once

#include <QMainWindow>
#include "ui_Patricipant.h"
#include "ParticipantServices.h"

class ParticipantForm : public QMainWindow
{
	Q_OBJECT

public:
	ParticipantForm(QWidget *parent = nullptr, const ParticipantServices& _participant = ParticipantServices());
	~ParticipantForm();
	void PopulateListWidget();
private slots:
	void on_listWidgetQuizes_itemClicked(QListWidgetItem* item);
	void on_pushButtonAnswer_clicked();
private:
	Ui::PatricipantClass ui;
	ParticipantServices participant;
	int row = -1;
};

