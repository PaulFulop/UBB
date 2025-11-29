#include "AgentForm.h"

AgentForm::AgentForm(QWidget* parent, const Agent& _agent, Repo<Parcel>* _parcels)
    : QMainWindow(parent), agent(_agent), parcels(_parcels)
{
    ui.setupUi(this);
    this->setWindowTitle(QString::fromStdString(agent.name));
    ui.labelSA->setText(QString::fromStdString(agent.ServiceAreaDetails()));
    PopulateListWidget();
    PopulateComboBox();
}

void AgentForm::PopulateListWidget() {
    ui.listWidgetParcels->clear();
    for (const auto& parcel : parcels->data) {
        if (!parcel.delivered) {
            bool found = false;
            for(const auto& street : agent.streets)
                if (parcel.adrStreet == street) {
                    QListWidgetItem* item = new QListWidgetItem(QString::fromStdString(parcel.ToString()));
                    ui.listWidgetParcels->addItem(item);
                    found = true;
                    break;
                }

            if (!found && (parcel.locationX > agent.areaX - agent.areaRadius && parcel.locationX < agent.areaX + agent.areaRadius) &&
                parcel.locationY > agent.areaY - agent.areaRadius && parcel.locationY < agent.areaY + agent.areaRadius) {
                QListWidgetItem* item = new QListWidgetItem(QString::fromStdString(parcel.ToString()));
                ui.listWidgetParcels->addItem(item);
            }

        }
    }
}

void AgentForm::PopulateComboBox() {
    ui.comboBoxParcel->clear();
    std::vector<std::string> streets{""};
    for (const auto& parcel : parcels->data) {
        std::string street = parcel.adrStreet;

        bool found = false;
        for(const auto& str : streets)
            if (str == street) {
                found = true;
                break;
            }

        if (!found) streets.push_back(street);
    }

    for (const auto& str : streets)
        ui.comboBoxParcel->addItem(QString::fromStdString(str));
}

void AgentForm::PopulateParcelsOnStreet(std::string street) {
    ui.listWidgetSearch->clear();
    for (const auto& parcel : parcels->data) {
        if (parcel.adrStreet == street) {
            QListWidgetItem* item = new QListWidgetItem(QString::fromStdString(parcel.ToString()));
            ui.listWidgetSearch->addItem(item);
        }
    }
}

void AgentForm::on_comboBoxParcel_activated(int index) {
    PopulateParcelsOnStreet(ui.comboBoxParcel->itemText(index).toStdString());
}

void AgentForm::on_pushButtonDeliver_clicked() {
    std::string parcelStr;
    for(int i = 0; i < ui.listWidgetParcels->count(); ++i)
        if (ui.listWidgetParcels->item(i)->isSelected() == true) {
            parcelStr = ui.listWidgetParcels->item(i)->text().toStdString();
            break;
        }

    for (auto& parcel : parcels->data) {
        if (parcelStr.find(parcel.name) != std::string::npos && parcelStr.find(parcel.adrStreet) != std::string::npos &&
            parcelStr.find(std::to_string(parcel.adrNumber)) != std::string::npos &&
            parcelStr.find(std::to_string(parcel.locationX)) != std::string::npos &&
            parcelStr.find(std::to_string(parcel.locationY)) != std::string::npos) {
            parcel.delivered = true;
            parcels->SaveToFile();
            PopulateListWidget();
            emit dataChanged();
            break;
        }
    }

}

void AgentForm::parcelDelivered() {
    PopulateListWidget();
    PopulateComboBox();
}

AgentForm::~AgentForm()
{}

