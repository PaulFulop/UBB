#include "Test3Form.h"

Test3Form::Test3Form(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
    mainRepo = Repository("domain.txt");
    mainRepo.SortDocsByDescLen();
    PopulateList(this->mainRepo);
}

void Test3Form::PopulateList(Repository repo) {
    ui.listWidgetDocs->clear();
    for (auto& doc : repo.docs) {
        QListWidgetItem* item = new QListWidgetItem(QString(doc.ToString().c_str()));
        ui.listWidgetDocs->addItem(item);
    }
}

void Test3Form::on_lineEditSearch_textChanged(const QString& text) {
    if (text == "") {
        PopulateList(mainRepo);
        return;
    }
    Repository filtRepo = mainRepo.FilterRepo(text.toStdString());
    PopulateList(filtRepo);
}
void Test3Form::on_listWidgetDocs_itemClicked(QListWidgetItem* item) {
    std::string substring = ui.lineEditSearch->text().toStdString();
    Repository filtRepo = mainRepo.FilterRepo(substring);

    if (ui.lineEditSearch->text().toStdString() == "")
        filtRepo.docs = mainRepo.docs;

    for (int i = 0; i < filtRepo.docs.size(); ++i) {
        if (ui.listWidgetDocs->item(i)->text() == item->text()) {
            ui.labelSImilarity->setText(QString(std::to_string(filtRepo.docs[i].ComputeSimilarity(substring)).c_str()));
            break;
        }
    }
}

Test3Form::~Test3Form()
{}

