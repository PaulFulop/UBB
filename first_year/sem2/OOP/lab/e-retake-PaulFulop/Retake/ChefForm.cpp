#include "ChefForm.h"
#include "Utils.h"
#include <QMessageBox>

ChefForm::ChefForm(Service _serv, QWidget *parent)
    : serv(_serv), QMainWindow(parent)
{
    ui.setupUi(this);
    this->setWindowTitle(QString::fromStdString(serv.c.name));
    PopulateListWidget();
    stats = new Statistics(serv);
    connect(this, &ChefForm::dataModified, stats, &Statistics::on_dataModified);
}

ChefForm::~ChefForm()
{}

void ChefForm::PopulateListWidget() {
    ui.listWidget->clear();
    serv.SortRecipes();

    for (const auto& r : serv.recipes->data) {
        auto item = new QListWidgetItem(QString::fromStdString(r.ToString()));
        ui.listWidget->addItem(item);
    }
}

void ChefForm::on_checkBox_checkStateChanged(Qt::CheckState state) {
    if (ui.lineEditSearch->text() != "") {
        PopulateBySearchBox(ui.lineEditSearch->text());
        return;
    }

    if (state == Qt::Checked)
        PopualteListWidgetFiltered();
    else
        PopulateListWidget();
}

void ChefForm::PopualteListWidgetFiltered() {
    ui.listWidget->clear();
    auto filteredRecipes = serv.FilterRecipesByCuisine();

    for (const auto& r : filteredRecipes) {
        auto item = new QListWidgetItem(QString::fromStdString(r.ToString()));
        ui.listWidget->addItem(item);
    }
}

void ChefForm::on_pushButtonAdd_clicked() {
    try {
        std::string name = ui.lineEditName->text().toStdString();
        int prep = std::atoi(ui.lineEditPrep->text().toStdString().c_str());
        auto ingredients = Tokenize(ui.lineEditIng->text().toStdString(), ',');
        auto newR = Recipe(name, serv.c.speciality, prep, ingredients);
        serv.AddRecipe(newR);
        ui.lineEditIng->clear();
        ui.lineEditName->clear();
        ui.lineEditPrep->clear();
        emit dataModified();
    }
    catch (const std::exception& e) {
        auto msg = new QMessageBox(QMessageBox::Icon::Warning, "Warning", e.what());
        msg->show();
    }
}

void ChefForm::on_pushButtonView_clicked() {
    stats->show();
}

void ChefForm::on_lineEditSearch_textChanged(const QString& text) {
    if (text == "") {
        if (ui.checkBox->checkState() == Qt::Checked)
            PopualteListWidgetFiltered();
        else
            PopulateListWidget();
        return;
    }

    PopulateBySearchBox(text);
}

void ChefForm::PopulateBySearchBox(const QString& text)
{
    std::string strText = text.toStdString();
    auto ingredients = Tokenize(strText, ',');
    auto filteredRecipes = serv.FilterByIngredients(ingredients);
    ui.listWidget->clear();

    if (ui.checkBox->checkState() == Qt::Checked) {
        for (const auto& r : filteredRecipes) {
            if (r.cuisine == serv.c.speciality) {
                auto item = new QListWidgetItem(QString::fromStdString(r.ToString()));
                ui.listWidget->addItem(item);
            }
        }
    }
    else {
        for (const auto& r : filteredRecipes) {
            auto item = new QListWidgetItem(QString::fromStdString(r.ToString()));
            ui.listWidget->addItem(item);
        }
    }
}

void ChefForm::on_dataModified() {
    if (ui.lineEditSearch->text() != "") {
        PopulateBySearchBox(ui.lineEditSearch->text());
        return;
    }
    if (ui.checkBox->checkState() == Qt::Checked)
        PopualteListWidgetFiltered();
    else
        PopulateListWidget();
}