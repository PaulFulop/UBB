#include "CourierForm.h"
#include <QPainter>

CourierForm::CourierForm(QWidget *parent, CourierService _serv, UndeliveredPackagesForm* _upf)
	: QMainWindow(parent), serv(_serv), upf(_upf)
{
	ui.setupUi(this);
	this->setWindowTitle(QString(_serv.c->name.c_str()));
    PopulateListWidget();
    PopulateComboBox();

    
}

CourierForm::~CourierForm()
{}

void CourierForm::PopulateListWidget() {
    ui.listWidgetPackages->clear();

    if (serv.courierPackages.empty())
        return;
    for (const auto& p : serv.courierPackages) {
        QListWidgetItem* item = new QListWidgetItem(QString(p.ToString().c_str()));
        ui.listWidgetPackages->addItem(item);
    }
}

void CourierForm::PopulateComboBox() {
    if (serv.c->streets.empty())
        return;

    for (const auto& str : serv.c->streets) {
        ui.comboBoxStreets->addItem(QString(str.c_str()));
    }
}

void CourierForm::on_pushButtonDeliver_clicked() {
    QListWidgetItem* item = nullptr;
    for(int i = 0; i < ui.listWidgetPackages->count(); ++i)
        if (ui.listWidgetPackages->item(i)->isSelected()) {
            item = ui.listWidgetPackages->item(i);
            break;
        }

    if (!item) return;

    for(int i = 0; i < serv.packages->data.size(); ++i)
        if (serv.packages->data[i].ToString() == item->text()) {
            serv.packages->data[i].deliveryStatus = true;
            serv.FilterCourierPackages();
            PopulateListWidget();
            serv.packages->SaveToFile();
            upf->update();
            return;
        }
}

void CourierForm::on_comboBoxStreets_currentIndexChanged(int index) {
    ui.listWidgetPackages->clear();

    if (serv.courierPackages.empty())
        return;
    for (const auto& p : serv.courierPackages) {
        if (p.addressStreet == serv.c->streets[index]) {
            QListWidgetItem* item = new QListWidgetItem(QString(p.ToString().c_str()));
            ui.listWidgetPackages->addItem(item);
        }

    }
}

void CourierForm::paintEvent(QPaintEvent* event) {
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setBrush(Qt::red);
    painter.drawEllipse(300 + serv.c->x, 25+ serv.c->x, serv.c->radius, serv.c->radius);
}