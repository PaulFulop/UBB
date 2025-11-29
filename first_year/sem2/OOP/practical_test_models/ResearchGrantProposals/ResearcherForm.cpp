#include "ResearcherForm.h"
#include <QMessageBox>

ResearcherForm::ResearcherForm(Researcher* _researcher, Repo<Idea>* _ideas, IdeasTableModel* _itm, DevelopedIdeasTableModel* _ditm, QWidget* parent)
    : researcher(_researcher), ideas(_ideas), itm(_itm), ditm(_ditm), QMainWindow(parent)
{
    ui.setupUi(this);
    this->setWindowTitle(QString::fromStdString(researcher->name));
    QString postitionTxt = QString::fromStdString(researcher->position);
    ui.label->setText(postitionTxt);
    proxy = new QSortFilterProxyModel(this);
    proxy->setSourceModel(itm);
    proxy->sort(3);
    ui.tableViewIdeas->setModel(proxy);
    ui.tableViewIdeas->setSelectionBehavior(QAbstractItemView::SelectRows);

    if (!researcher->IsSenior()) {
        ui.pushButtonAccept->setEnabled(false);
        ui.pushButtonSaveAll->setEnabled(false);
    }
    
    ui.pushButtonDevelop->setEnabled(false);
    for(const auto& idea : ideas->data)
        if (idea.status == "accepted" && idea.creator == researcher->name) {
            ui.pushButtonDevelop->setEnabled(true);
            break;
        }
}

ResearcherForm::~ResearcherForm()
{}

void ResearcherForm::on_pushButtonAdd_clicked() {
    try {
        std::string title = ui.lineEditTitle->text().toStdString();
        std::string desc = ui.lineEditDesc->text().toStdString();
        int duration = std::atoi(ui.lineEditDuration->text().toStdString().c_str());

        if (title == "" || (duration < 1 || duration > 3)) throw std::exception("Invalid data!");
        auto idea = Idea(title, desc, "proposed", researcher->name, duration);
        itm->AddNewIdea(idea);
    }
    catch (const std::exception& e) {
        auto msg = new QMessageBox(QMessageBox::Icon::Warning, "Warning", e.what());
        msg->show();
    }
}

void ResearcherForm::on_tableViewIdeas_clicked(const QModelIndex& index) {
    int currentRow = index.row();
    std::vector<Idea> auxIdeas = ideas->data;
    std::sort(auxIdeas.begin(), auxIdeas.end(), [](const Idea& i1, const Idea& i2) {return i1.duration < i2.duration; });

    for(int i = 0; i < ideas->data.size(); ++i)
        if (ideas->data[i] == auxIdeas[currentRow]) {
            clickedRow = i;
            break;
        }
}

void ResearcherForm::on_pushButtonAccept_clicked() {
    if (clickedRow == -1 || ideas->data[clickedRow].status != "proposed") return;
    itm->AcceptIdea(clickedRow);
    emit ideaAccepted(clickedRow);
}

void ResearcherForm::on_ideaAccepted(int pos) {
    if (researcher->name == ideas->data[pos].creator)
        ui.pushButtonDevelop->setEnabled(true);
}

void ResearcherForm::on_pushButtonDevelop_clicked() {
    ui.tableViewDevelop->setModel(ditm);
}

void ResearcherForm::on_pushButtonSaveAll_clicked() {
    std::ofstream fout("accepted_ideas.txt");
    std::vector<Idea> auxIdeas = ideas->data;
    std::sort(auxIdeas.begin(), auxIdeas.end(), [](const Idea& i1, const Idea& i2) {return i1.duration < i2.duration; });

    if (!fout.is_open()) return;
    for (const auto& idea : auxIdeas)
        if (idea.status == "accepted") {
            std::string text = idea.title + ", (" + idea.creator + "), " + std::to_string(idea.duration) + ", " + idea.description;
            fout << text << '\n';
        }
    fout.close();
}