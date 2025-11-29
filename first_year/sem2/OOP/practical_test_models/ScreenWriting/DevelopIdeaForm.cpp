#include "DevelopIdeaForm.h"
#include <fstream>

DevelopIdeaForm::DevelopIdeaForm(Idea* _idea, QWidget *parent)
	: idea(_idea), QMainWindow(parent)
{
	ui.setupUi(this);
	ui.textEdit->setText(QString::fromStdString(idea->desc));
}

DevelopIdeaForm::~DevelopIdeaForm()
{}

void DevelopIdeaForm::on_pushButton_clicked() {
	idea->desc = ui.textEdit->toPlainText().toStdString();
	std::ofstream fout(idea->creator + "_act" + std::to_string(idea->act) + ".txt");

	fout << idea->desc;
	fout.close();
	emit ideaDeveloped();
}