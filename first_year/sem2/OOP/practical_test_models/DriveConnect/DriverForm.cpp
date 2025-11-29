#include "DriverForm.h"
#include <QMessageBox>
#include "Utils.h"
#include <QPainter>

DriverForm::DriverForm(int _id, std::vector<int>* _validations, Repo<Report>* _reports, Driver* _d, QWidget *parent)
    : id(_id), validations(_validations), reports(_reports), d(_d), QMainWindow(parent)
{
    ui.setupUi(this);
    this->setWindowTitle(QString::fromStdString(d->name));
    std::string details = std::to_string(d->latitude) + ", " + std::to_string(d->longitude) + ", " + std::to_string(d->score);
    ui.labelDetails->setText(QString::fromStdString(details));
    validated = std::vector<bool>(reports->data.size(), false);
    ui.horizontalSlider->setValue(10);
    ui.horizontalSlider->setMaximum(1000);
    ui.horizontalSlider->setMinimum(0);
    PopulateListWidget();
}

DriverForm::~DriverForm()
{}

void DriverForm::PopulateListWidget() {
    ui.listWidgetReports->clear();

    for (const auto& rep : reports->data) {
        if (d->isInRegionOfInterest(rep.latitude, rep.longitude, ui.horizontalSlider->value())) {
            QListWidgetItem* item = new QListWidgetItem(QString::fromStdString(rep.ToString()));
            if (rep.valid) {
                QFont font = item->font();
                font.setBold(true);
                item->setFont(font);
            }
            ui.listWidgetReports->addItem(item);
        }
    }
}

void DriverForm::on_pushButtonSend_clicked() {
    QString message = QString::fromStdString(d->name) + QString::fromStdString(": ") + ui.lineEdit->text();
    QListWidgetItem* item = new QListWidgetItem(message);
    ui.listWidgetChat->addItem(item);
    emit messageAdded(message);
    ui.lineEdit->clear();
}

void DriverForm::on_messageAdded(QString message) {
    QListWidgetItem* item = new QListWidgetItem(message);
    ui.listWidgetChat->addItem(item);
}

void DriverForm::on_pushButtonAdd_clicked() {
    try {
        std::string descripton = ui.lineEditName->text().toStdString();
        if (descripton == "") throw std::exception("No description.");

        int latitude = std::atoi(ui.lineEditLat->text().toStdString().c_str());
        int longitude = std::atoi(ui.lineEditLong->text().toStdString().c_str());
        Report r = Report(descripton, d->name, latitude, longitude, false);
        
        if (sqrt((d->latitude - latitude) * (d->latitude - latitude) - (d->longitude - longitude) * (d->longitude - longitude)) > 20)
            throw std::exception("Report location is too far away.");

        reports->Add(r);
        validated.push_back(false);
        PopulateListWidget();
        emit reportAdded();
    }
    catch (const std::exception& e) {
        QMessageBox* msg = new QMessageBox(QMessageBox::Icon::Warning, "Warning", e.what());
        msg->show();
    }
}

void DriverForm::on_listWidgetReports_itemDoubleClicked(QListWidgetItem* item) {
    int actualRow = 0;
    for(int i = 0; i < reports->data.size(); ++i)
        if (reports->data[i].ToString() == item->text().toStdString()) {
            actualRow = i;
            break;
        }
    
    if (reports->data[actualRow].valid || reports->data[actualRow].reporter == d->name || validated[actualRow]) return;
    validated[actualRow] = true;
    emit reportValidated(actualRow, item, reports->data[actualRow].reporter);
}

void DriverForm::on_reportValidated(int row, QListWidgetItem* item, std::string name) {
    if (name == d->name) {
        if (++(*validations)[id] == 2) {
            (*validations)[id] = 0;
            reports->data[row].valid = true;
            PopulateListWidget();
            emit reportActuallyValidated();
            ++d->score;

            if (d->score == 10) {
                this->setStyleSheet("background-color: grey");
            }

            if (d->score == 15) {
                this->setStyleSheet("background-color: green");
            }

            std::string details = std::to_string(d->latitude) + ", " + std::to_string(d->longitude) + ", " + std::to_string(d->score);
            ui.labelDetails->setText(QString::fromStdString(details));
        }
    }
}

void DriverForm::on_reportAdded() {
    validated.push_back(false);
    PopulateListWidget();
}

void DriverForm::on_horizontalSlider_valueChanged(int value) {
    PopulateListWidget();
}