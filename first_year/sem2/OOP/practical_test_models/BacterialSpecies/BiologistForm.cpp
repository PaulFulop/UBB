#include "BiologistForm.h"
#include "Utils.h"
#include <QMessageBox>

BiologistForm::BiologistForm(BacteriumTableModel* _btm, Biologist _b, Repo<Bacterium>* _bacterium, QWidget* parent)
    : btm(_btm), b(_b), bacterium(_bacterium), QMainWindow(parent)
{
    ui.setupUi(this);
    this->setWindowTitle(QString::fromStdString(b.name));
    PopulateComboBox();

    pattern += "^(";
    for (const auto& sp : b.species)
        pattern += sp + "|";
    pattern.pop_back();
    pattern += ")$";

    bacteriumForm = new BacteriumForm(bacterium);

    proxyTable = new QSortFilterProxyModel(this);
    proxyTable->setSourceModel(btm);
    proxyTable->setFilterCaseSensitivity(Qt::CaseInsensitive);
    proxyTable->setFilterKeyColumn(1);
    proxyTable->sort(0);
    proxyTable->setFilterRegularExpression(QRegularExpression(QString::fromStdString(pattern)));
    ui.tableViewBacterium->setModel(proxyTable);
}

BiologistForm::~BiologistForm()
{}

void BiologistForm::PopulateComboBox() {
    ui.comboBoxSearch->clear();
    ui.comboBoxSearch->addItem("");
    for (const auto& sp : b.species)
        ui.comboBoxSearch->addItem(QString::fromStdString(sp));
}

void BiologistForm::on_comboBoxSearch_currentTextChanged(const QString& text) {
    if(text == "")
        proxyTable->setFilterRegularExpression(QRegularExpression(QString::fromStdString(pattern)));
    else
        proxyTable->setFilterRegularExpression(QRegularExpression("^" + text + "$"));
}

void BiologistForm::on_pushButtonAddBacterium_clicked() {
    try {
        std::string name = ui.lineEditName->text().toStdString();
        std::string species = ui.lineEditSpecies->text().toStdString();
        int size = ui.lineEditSize->text().toInt();
        std::vector<std::string> diseases = Tokenize(ui.lineEditDiseases->text().toStdString(), ',');

        Bacterium newBacteria = Bacterium(name, species, size, diseases);
        btm->AddBacteria(newBacteria);
        bacterium->SaveToFile();
    }
    catch(const std::exception & e) {
        QMessageBox* msg = new QMessageBox(QMessageBox::Icon::Warning,"Warning", "This bacterium already exists!");
        msg->show();
    }
}

void BiologistForm::on_tableViewBacterium_clicked(const QModelIndex& index) {

    row = index.row();

    std::vector<Bacterium> actualList;
    for (const auto& bacteria : bacterium->data) {
        if (std::find(b.species.begin(), b.species.end(), bacteria.species) != b.species.end())
            actualList.push_back(bacteria);
    }

    std::sort(actualList.begin(), actualList.end(), [](const Bacterium& b1, const Bacterium& b2) { return b1.name < b2.name; });

    int actualRow = 0;
    for (int i = 0; i < bacterium->data.size(); ++i)
        if (bacterium->data[i] == actualList[row]) {
            actualRow = i;
            break;
        }

    ui.listWidgetDiseases->clear();
    for (const auto& ds : bacterium->data[actualRow].diseases) {
        QListWidgetItem* item = new QListWidgetItem(QString::fromStdString(ds));
        ui.listWidgetDiseases->addItem(item);
    }
}

void BiologistForm::on_pushButtonAddDisease_clicked() {
    std::string newDisease = ui.lineEdit->text().toStdString();
    if (row == -1 || newDisease == "") return;

    std::vector<Bacterium> actualList;
    for (const auto& bacteria : bacterium->data) {
        if (std::find(b.species.begin(), b.species.end(), bacteria.species) != b.species.end())
            actualList.push_back(bacteria);
    }

    std::sort(actualList.begin(), actualList.end(), [](const Bacterium& b1, const Bacterium& b2) { return b1.name < b2.name; });

    int actualRow = 0;
    for(int i = 0; i < bacterium->data.size(); ++i)
        if (bacterium->data[i] == actualList[row]) {
            actualRow = i;
            break;
        }

    bacterium->data[actualRow].diseases.push_back(newDisease);
    bacterium->SaveToFile();
    QListWidgetItem* item = new QListWidgetItem(QString::fromStdString(newDisease));
    ui.listWidgetDiseases->addItem(item);
}

void BiologistForm::on_pushButtonView_clicked() {
    bacteriumForm->show();
}