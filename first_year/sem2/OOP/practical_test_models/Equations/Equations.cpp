#include "Equations.h"

Equations::Equations(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
    repo = Repository("equations.txt");
    PopulateList();
}

Equations::~Equations()
{}

void Equations::PopulateList() {
    ui.listWidgetEq->clear();
    for (auto& eq : repo.equations) {
        QListWidgetItem* item = new QListWidgetItem(QString(eq.ToString().c_str()));
        ui.listWidgetEq->addItem(item);
    }
}

void Equations::on_pushButtonSol_clicked(){
    for (int i = 0; i < repo.equations.size(); ++i) {
        if (ui.listWidgetEq->item(i)->isSelected()) {

            std::string x1, x2;

            if (repo.equations[i].IsImg()) {
                x1 = "x1 = " + std::to_string((repo.equations[i].coef2 * -1) / (2 * repo.equations[i].coef1)) + " + " + std::to_string(std::sqrt(std::abs(std::pow(repo.equations[i].coef2, 2) - 4 * repo.equations[i].coef1 * repo.equations[i].coef3)) / (2 * repo.equations[i].coef1)) + "i";
                x2 = "x2 = " + std::to_string((repo.equations[i].coef2 * -1) / (2 * repo.equations[i].coef1)) + " - " + std::to_string(std::sqrt(std::abs(std::pow(repo.equations[i].coef2, 2) - 4 * repo.equations[i].coef1 * repo.equations[i].coef3)) / (2 * repo.equations[i].coef1)) + "i";
            }
            else {
                x1 = "x1 = " + std::to_string(((repo.equations[i].coef2 * -1) - std::sqrt(std::abs(std::pow(repo.equations[i].coef2, 2) - 4 * repo.equations[i].coef1 * repo.equations[i].coef3))) / (2 * repo.equations[i].coef1));
                x2 = "x2 = " + std::to_string(((repo.equations[i].coef2 * -1) + std::sqrt(std::abs(std::pow(repo.equations[i].coef2, 2) - 4 * repo.equations[i].coef1 * repo.equations[i].coef3))) / (2 * repo.equations[i].coef1));
            }

            std::string sol = x1 + ", " + x2;
            ui.labelSol->setText(QString(sol.c_str()));
            break;
        }
    }

    //ui.labelSol->setText("Test");
}

void Equations::on_pushButtonUpdate_clicked() {
    for (int i = 0; i < repo.equations.size(); ++i) {
        if (ui.listWidgetEq->item(i)->isSelected()) {
            repo.equations[i].coef1 = std::atof(ui.lineEditCoef1->text().toStdString().c_str());
            repo.equations[i].coef2 = std::atof(ui.lineEditCoef2->text().toStdString().c_str());
            repo.equations[i].coef3 = std::atof(ui.lineEditCoef3->text().toStdString().c_str());
            repo.SortDescendingByGrade();
            PopulateList();
            ui.labelUpdated->setText("Updated!");
            break;
        }
    }
}

void Equations::on_listWidgetEq_itemClicked(QListWidgetItem* item) {
    for (int i = 0; i < repo.equations.size(); ++i) {
        ui.listWidgetEq->item(i)->setSelected(false);
    }

    item->setSelected(true);
}