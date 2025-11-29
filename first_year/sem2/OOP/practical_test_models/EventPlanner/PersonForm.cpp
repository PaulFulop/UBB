#include "PersonForm.h"
#include <QMessageBox>

PersonForm::PersonForm(Service _serv, QWidget *parent)
    : serv(_serv), QMainWindow(parent)
{
    ui.setupUi(this);
    this->setWindowTitle(QString::fromStdString(serv.person.name));
    ui.labelPositon->setText(QString::fromStdString(serv.PersonLocationStr()));
    PopulateEventsWidget();
    ui.pushButtonUpdate->setEnabled(false);
    ui.dateEditUpdate->setDisplayFormat("yyyy/MM/dd");
    ui.dateEditAdd->setDisplayFormat("yyyy/MM/dd");
    ui.dateEditUpdate->setDate(QDate::currentDate());
    ui.dateEditAdd->setDate(QDate::currentDate());

    if (!serv.person.IsOrganiser())
        ui.pushButtonAdd->setEnabled(false);
}

PersonForm::~PersonForm()
{}

void PersonForm::PopulateEventsWidget() {
    ui.listWidgetEvents->clear();
    auto events = serv.SortedEvents();
    for (const auto& e : events) {
        auto item = new QListWidgetItem(QString::fromStdString(e.ToString()));
        if (serv.IsEventOrganisedByOrganiser(e)) item->setBackground(Qt::darkGreen);
        ui.listWidgetEvents->addItem(item);
    }
}

void PersonForm::PopulateFilteredEventsWidget() {
    ui.listWidgetEvents->clear();
    auto events = serv.NearEvents();
    for (const auto& e : events) {
        auto item = new QListWidgetItem(QString::fromStdString(e.ToString()));
        if (serv.IsEventOrganisedByOrganiser(e)) item->setBackground(Qt::darkGreen);
        ui.listWidgetEvents->addItem(item);
    }
}

void PersonForm::PopulatePersonsWidget(Event& e) {
    ui.listWidgetParticipants->clear();
    auto personsGoing = serv.PersonsGoingToEvent(e);

    for (const auto& p : personsGoing) {
        auto item = new QListWidgetItem(QString::fromStdString(p.name));
        ui.listWidgetParticipants->addItem(item);
    }
}

void PersonForm::on_listWidgetEvents_itemClicked(QListWidgetItem* item) {
    int row = ui.listWidgetEvents->row(item);
    auto events = serv.SortedEvents();
    actualRow = serv.GetEventPosition(events[row]);
    ui.textEdit->setPlainText(QString::fromStdString(serv.events->data[actualRow].desc));

    if (serv.person.IsOrganiser()) {
        ui.pushButtonUpdate->setEnabled(true);
        ui.lineEditDescUpdate->setText(QString::fromStdString(serv.events->data[actualRow].desc));
        ui.dateEditUpdate->setDate(QDate::fromString(QString::fromStdString(serv.events->data[actualRow].date)));
        PopulatePersonsWidget(serv.events->data[actualRow]);
    }

    if (serv.IsPersonGoingToEvent(serv.person, serv.events->data[actualRow]))
        ui.pushButtonGoing->setEnabled(false);
    else
        ui.pushButtonGoing->setEnabled(true);
}

void PersonForm::on_checkBox_checkStateChanged(Qt::CheckState state) {
    if (state == Qt::Checked)
        PopulateFilteredEventsWidget();
    else
        PopulateEventsWidget();
}

void PersonForm::on_pushButtonAdd_clicked() {
    try {
        std::string name = ui.lineEditName->text().toStdString();
        std::string desc = ui.lineEditDesc->text().toStdString();
        int latitude = std::atoi(ui.lineEditLat->text().toStdString().c_str());
        int longitude = std::atoi(ui.lineEditLong->text().toStdString().c_str());
        std::string date = ui.dateEditAdd->text().toStdString();

        auto event = Event(serv.person.name, name, desc, latitude, longitude, date);
        serv.events->Add(event);
        emit dataModified();
    }
    catch (const std::exception& e) {
        auto msg = new QMessageBox(QMessageBox::Icon::Warning, "Warning", e.what());
        msg->show();
    }
}

void PersonForm::on_pushButtonUpdate_clicked() {
    std::string desc = ui.lineEditDescUpdate->text().toStdString();
    std::string date = ui.dateEditUpdate->text().toStdString();
    serv.events->data[actualRow].desc = desc;
    serv.events->data[actualRow].date = date;
    emit dataModified();
}

void PersonForm::on_dataModified() {
    if(ui.checkBox->checkState() == Qt::Checked)
        PopulateFilteredEventsWidget();
    else
        PopulateEventsWidget();
}

void PersonForm::on_pushButtonGoing_clicked() {
    serv.AttendEvent(serv.events->data[actualRow]);
    ui.pushButtonGoing->setEnabled(false);

    if (serv.person.IsOrganiser()) PopulatePersonsWidget(serv.events->data[actualRow]);
}