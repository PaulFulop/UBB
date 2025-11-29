#include "CourierCompanyForm.h"

CourierCompanyForm::CourierCompanyForm(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
    couriers = Repository<Courier>("couriers.txt");
    packages = Repository<Package>("packages.txt");
    upf = new UndeliveredPackagesForm(nullptr, &packages);

    for (auto& c : couriers.data) {
        CourierService courierService = CourierService(&packages, &c);
        courierForms.push_back(new CourierForm(nullptr, courierService, upf));
    }

    upf->show();

    for (auto& form : courierForms)
        form->show();

    PopulateListWidget();
}

CourierCompanyForm::~CourierCompanyForm()
{}

void CourierCompanyForm::PopulateListWidget() {
    ui.listWidgetPackages->clear();

    for (const auto& p : packages.data) {
        QListWidgetItem* item = new QListWidgetItem(QString(p.ToString().c_str()));
        if (p.deliveryStatus)
            item->setBackground(QBrush(Qt::darkGreen));
        else
            item->setBackground(QBrush(Qt::darkRed));

        ui.listWidgetPackages->addItem(item);
    }
}

void CourierCompanyForm::on_pushButtonAdd_clicked() {
    std::string recipient = ui.lineEditRecipient->text().toStdString();
    std::string addressStreet = ui.lineEditStreet->text().toStdString();
    int addressNumber = ui.lineEditNumber->text().toInt();
    double x = ui.lineEditX->text().toDouble();
    double y = ui.lineEditY->text().toDouble();
    
    Package newPackage = Package(recipient, addressStreet, addressNumber, x, y, false);
    packages.data.push_back(newPackage);
    packages.SaveToFile();
    for (auto& form : courierForms)
        form->PopulateListWidget(), form->serv.FilterCourierPackages();
    PopulateListWidget();
    upf->update();
}