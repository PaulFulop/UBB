#include "AstronomerForm.h"
#include <QMessageBox>

AstronomerForm::AstronomerForm(AstronomerTableModel* _atm, AstronomerListModel* _alm, const Services& _serv, QWidget* parent)
    : atm(_atm), alm(_alm), serv(_serv), QMainWindow(parent)
{
    ui.setupUi(this);
    this->setWindowTitle(QString::fromStdString(serv.astronomer->name));
    ui.tableView->setModel(_atm);
    ui.listView->setModel(alm);
    proxyTable = new QSortFilterProxyModel(this);
    proxyList = new QSortFilterProxyModel(this);
    proxyTable->setSourceModel(atm);
    proxyList->setSourceModel(alm);

    proxyList->setFilterCaseSensitivity(Qt::CaseInsensitive);
    proxyList->setFilterFixedString("   ");
    ui.listView->setModel(proxyList);
    starsForm = new StarsForm(serv);
}

AstronomerForm::~AstronomerForm()
{}

void AstronomerForm::on_pushButtonAdd_clicked() {
    try {
        std::string name = ui.lineEdit->text().toStdString();
        int RA = ui.lineEdit_2->text().toInt();
        int Dec = ui.lineEdit_3->text().toInt();
        int diameter = ui.lineEdit_4->text().toInt();
        Star newStar = Star(name, serv.astronomer->constellation, RA, Dec, diameter);

        if (newStar.name.empty() || newStar.diameter <= 0)
            throw std::exception("Invalid star!");

        for (const auto& star : serv.stars->data)
            if (star.name == newStar.name)
                throw std::exception("Found a star with the same name!");

        atm->AddStar(newStar);
        serv.SortStarsByConstellation();
        serv.stars->SaveToFile();
    }
    catch (const std::exception& e) {
        QMessageBox* msg = new QMessageBox(QMessageBox::Warning, "Warning", QString::fromStdString(e.what()));
        msg->show();
    }
}

void AstronomerForm::on_pushButtonView_clicked() {
    starsForm->show();
}

void AstronomerForm::on_checkBoxStars_checkStateChanged(Qt::CheckState state) {
    if (state == Qt::Checked) {
        proxyTable->setFilterKeyColumn(1);
        proxyTable->setFilterFixedString(QString::fromStdString(serv.astronomer->constellation));
        ui.tableView->setModel(proxyTable);
    }
    else {
        ui.tableView->setModel(atm);
    }
}

void AstronomerForm::on_lineEditFilter_textChanged(const QString& text) {
    if (text == "")
        proxyList->setFilterFixedString("   ");
    else
        proxyList->setFilterFixedString(text);
}