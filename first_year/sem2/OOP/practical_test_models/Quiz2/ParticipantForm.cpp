#include "ParticipantForm.h"

ParticipantForm::ParticipantForm(QWidget *parent, const ParticipantServices& _participant)
	: QMainWindow(parent)
{
	participant.p = _participant.p;
	participant.questions = _participant.questions;
	ui.setupUi(this);
	this->setWindowTitle(QString(participant.p->name.c_str()));
	ui.labelScore->setText(QString(std::to_string(participant.p->score).c_str()));
	PopulateListWidget();
}

ParticipantForm::~ParticipantForm()
{}

void ParticipantForm::PopulateListWidget() {
	ui.listWidgetQuizes->clear();

	for (const auto& q : participant.questions->data) {
		QListWidgetItem* item = new QListWidgetItem(QString(q.ToStringParticipant().c_str()));
		ui.listWidgetQuizes->addItem(item);
	}
}

void ParticipantForm::on_pushButtonAnswer_clicked() {
	if (row != -1){
		if (ui.lineEditAnswer->text() == participant.questions->data[row].answer) {
			participant.p->score += participant.questions->data[row].score;
			ui.labelScore->setText(QString(std::to_string(participant.p->score).c_str()));
		}

		ui.listWidgetQuizes->item(row)->setBackground(QBrush(Qt::darkGreen));
		ui.pushButtonAnswer->setDisabled(true);
	}
}

void ParticipantForm::on_listWidgetQuizes_itemClicked(QListWidgetItem* item) {
	if (item->background() == QBrush(Qt::darkGreen)) {
		ui.pushButtonAnswer->setDisabled(true);
		return;
	}

	ui.pushButtonAnswer->setDisabled(false);
	for(int i = 0; i < participant.questions->data.size(); ++i)
		if (item->text() == ui.listWidgetQuizes->item(i)->text()) {
			row = i;
			return;
		}
}