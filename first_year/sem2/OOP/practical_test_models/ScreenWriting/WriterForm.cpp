#include "WriterForm.h"
#include <QMessageBox>
#include <unordered_set>
#include "DevelopIdeaForm.h"

WriterForm::WriterForm(const Writer& _w, IdeasTableModel* _itm, QWidget *parent)
    : w(_w), itm(_itm), QMainWindow(parent)
{
    ui.setupUi(this);
    this->setWindowTitle(QString::fromStdString(w.name));
    ui.tableView->setModel(itm);
    itm->Sort();
    ui.tableView->setSelectionBehavior(QAbstractItemView::SelectRows);

    ui.pushButtonAccept->setEnabled(false);
    ui.pushButtonRevise->setEnabled(false);
    ui.textEdit->setEnabled(false);

    if (!itm->WriterAcceptedIdeas(w).size()) {
        ui.pushButtonDevelop->setEnabled(false);
    }
}

WriterForm::~WriterForm()
{}

void WriterForm::on_tableView_clicked(const QModelIndex& index) {
    selectedRow = index.row();
    ui.textEdit->clear();

    if (w.expertise == "Senior" && itm->ideas->data[selectedRow].status == "proposed") {
        ui.pushButtonRevise->setEnabled(true);
    }
    else {
        ui.pushButtonRevise->setEnabled(false);
    }
}

void WriterForm::on_pushButtonAdd_clicked() {
    try {
        std::string desc = ui.lineEditDesc->text().toStdString();
        int act = std::atoi(ui.lineEditAct->text().toStdString().c_str());

        Idea newIdea = Idea(desc, "proposed", w.name, act);
        itm->AddIdea(newIdea);
        itm->Sort();
    }
    catch (const std::exception& e) {
        auto msg = new QMessageBox(QMessageBox::Icon::Warning, "Warning", e.what());
        msg->show();
    }
}

void WriterForm::on_pushButtonRevise_clicked() {
    ui.textEdit->setText(QString::fromStdString(itm->ideas->data[selectedRow].desc));
    ui.pushButtonAccept->setEnabled(true);
}

void WriterForm::on_pushButtonAccept_clicked() {
    itm->AcceptIdea(itm->ideas->data[selectedRow]);
    ui.textEdit->clear();
    ui.pushButtonAccept->setEnabled(false);
    ui.pushButtonRevise->setEnabled(false);
    emit ideaAccepted(itm->ideas->data[selectedRow].creator);
}

void WriterForm::on_ideaAccepted(const std::string& creator) {
    if (w.name == creator && !ui.pushButtonDevelop->isEnabled()) {
        ui.pushButtonDevelop->setEnabled(true);
    }
}

void WriterForm::on_pushButtonSave_clicked() {
    std::ofstream fout("plot.txt");
    if (!fout.is_open()) return;

    auto acceptedIdeas = itm->AcceptedIdeas();
    std::unordered_set<int> acts;
    for (const auto& i : acceptedIdeas)
        acts.insert(i.act);

    for (const auto& act : acts) {
        fout << "Act " << act << '\n';
        for (const auto& i : acceptedIdeas)
            if (i.act == act)
                fout << i.desc << ' ' << '(' << i.creator << ')' << '\n';
        fout << '\n';
    }

    fout.close();
}

void WriterForm::on_pushButtonDevelop_clicked() {
    auto acceptedWriterIdeas = itm->WriterAcceptedIdeas(w);
    for (auto i : acceptedWriterIdeas) {
        auto developIdeaForm = new DevelopIdeaForm(i);

        developIdeaForm->show();
    }
}

void WriterForm::on_ideaDeveloped() {
    itm->RefreshModel();
}