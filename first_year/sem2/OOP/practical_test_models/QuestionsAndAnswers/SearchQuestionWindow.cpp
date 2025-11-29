#include "SearchQuestionWindow.h"

SearchQuestionWindow::SearchQuestionWindow(Service _serv, QWidget *parent)
	: serv(_serv), QMainWindow(parent)
{
	ui.setupUi(this);
}

SearchQuestionWindow::~SearchQuestionWindow()
{}

void SearchQuestionWindow::PopulateListWidget(std::string filter) {
	int row = serv.FindBestMatchingQuestion(filter);
	if (filter == "") {
		ui.listWidgetSearch->clear();
		return;
	}
	if (row == -1) return;

	auto top3 = serv.FindTop3Answers(serv.questions->data[row]);
	ui.listWidgetSearch->clear();

	auto item1 = new QListWidgetItem(QString::fromStdString(serv.questions->data[row].ToString()));
	ui.listWidgetSearch->addItem(item1);

	if (std::get<0>(top3).id == -1) {
		return;
	}
	else if (std::get<1>(top3).id == -1) {
		auto item2 = new QListWidgetItem(QString::fromStdString(std::get<0>(top3).ToString()));
		ui.listWidgetSearch->addItem(item2);
	}
	else if (std::get<2>(top3).id == -1) {
		auto item2 = new QListWidgetItem(QString::fromStdString(std::get<0>(top3).ToString()));
		ui.listWidgetSearch->addItem(item2);
		auto item3 = new QListWidgetItem(QString::fromStdString(std::get<1>(top3).ToString()));
		ui.listWidgetSearch->addItem(item3);
	}
	else {
		auto item2 = new QListWidgetItem(QString::fromStdString(std::get<0>(top3).ToString()));
		ui.listWidgetSearch->addItem(item2);
		auto item3 = new QListWidgetItem(QString::fromStdString(std::get<1>(top3).ToString()));
		ui.listWidgetSearch->addItem(item3);
		auto item4 = new QListWidgetItem(QString::fromStdString(std::get<2>(top3).ToString()));
		ui.listWidgetSearch->addItem(item4);
	}
}

void SearchQuestionWindow::on_lineEditSearch_textChanged(const QString& text) {
	PopulateListWidget(text.toStdString());
}

void SearchQuestionWindow::on_dataModified() {
	PopulateListWidget(ui.lineEditSearch->text().toStdString());
}