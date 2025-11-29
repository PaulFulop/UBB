#include "ProgrammerForm.h"
#include <QMessageBox>

ProgrammerForm::ProgrammerForm(Service _serv, QWidget *parent)
    : serv(_serv), QMainWindow(parent)
{
    ui.setupUi(this);
    this->setWindowTitle(QString::fromStdString(serv.p->name));
    ui.label_2->setText("Number of revised files: " + QString::fromStdString(std::to_string(serv.p->revisedFiles)));
    ui.label->setText("Number of files to revise: " + QString::fromStdString(std::to_string(serv.p->filesToRevise)));
    ui.pushButton->setEnabled(false);
    PopulateListWidget();
    if (serv.RevisedAllFiles())
        ui.labelCongrats->setText("CONGRATS!");
}

ProgrammerForm::~ProgrammerForm()
{}

void ProgrammerForm::PopulateListWidget() {
    serv.SortFiles();
    ui.listWidget->clear();
    for (const auto& f : serv.files->data) {
        auto item = new QListWidgetItem(QString::fromStdString(f.ToString()));
        if (!serv.IsRevised(f)) {
            auto font = item->font();
            font.setBold(true);
            item->setFont(font);
        }

        ui.listWidget->addItem(item);
    }
}

void ProgrammerForm::on_listWidget_itemClicked(QListWidgetItem* item) {
    selectedRow = ui.listWidget->row(item);

    if(!serv.RevisedAllFiles())
        if (!serv.IsRevised(serv.files->data[selectedRow]) && !serv.CreatorOfFile(serv.files->data[selectedRow]))
            ui.pushButton->setEnabled(true);
        else
            ui.pushButton->setEnabled(false);
}

void ProgrammerForm::on_pushButton_clicked() {
    serv.ReviseFile(serv.files->data[selectedRow]);
    ui.label_2->setText("Number of revised files: " + QString::fromStdString(std::to_string(serv.p->revisedFiles)));
    ui.label->setText("Number of files to revise: " + QString::fromStdString(std::to_string(serv.p->filesToRevise)));

    if (serv.RevisedAllFiles())
        ui.labelCongrats->setText("CONGRATS!");

    emit dataModified();
    ui.listWidget->item(selectedRow)->setBackground(Qt::darkGreen);
    ui.pushButton->setEnabled(false);
}

void ProgrammerForm::on_pushButtonAdd_clicked() {
    try {
        std::string name = ui.lineEditName->text().toStdString();
        auto newFile = SourceFile(name, "not_revised", serv.p->name, "");
        ui.lineEditName->clear();
        serv.AddFile(newFile);
        emit dataModified();
    }
    catch (const std::exception& e) {
        auto msg = new QMessageBox(QMessageBox::Icon::Warning, "Warning", e.what());
        msg->show();
    }
}

void ProgrammerForm::on_dataModified() {
    PopulateListWidget();
}