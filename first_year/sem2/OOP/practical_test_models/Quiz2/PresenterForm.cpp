#include "PresenterForm.h"

PresenterForm::PresenterForm(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);

    Repository questions = Repository<Question>("questions.txt");
    Repository participants = Repository<Participant>("participants.txt");
    presenter = PresenterServices(questions, questions, participants);

    PopulateListWidget();

    for (auto& p : presenter.participants.data) {
        ParticipantServices partServ = ParticipantServices(&p, &presenter.questionsCopy);
        participantForms.push_back(new ParticipantForm(nullptr, partServ));
    }

    for (auto& partForm : participantForms) {
        partForm->show();
    }
}

PresenterForm::~PresenterForm()
{
    presenter.participants.SaveToFile();
}

void PresenterForm::PopulateListWidget() {
    ui.listWidgetQuizes->clear();

    for (const auto& q : presenter.questions.data) {
        QListWidgetItem* item = new QListWidgetItem(QString(q.ToStringPresenter().c_str()));
        ui.listWidgetQuizes->addItem(item);
    }
}

void PresenterForm::on_pushButtonAdd_clicked() {
    try {
        if (ui.lineEditAnswer->text() == "" || ui.lineEditID->text() == "" || ui.lineEditText->text() == "" || ui.lineEditScore->text() == "")
            throw std::exception("Incomplete data.");

        std::string text = ui.lineEditText->text().toStdString();
        std::string answer = ui.lineEditAnswer->text().toStdString();
        int id = atoi(ui.lineEditID->text().toStdString().c_str());
        int score = atoi(ui.lineEditScore->text().toStdString().c_str());


        presenter.AddQuestion(Question(id, text, answer, score));
        PopulateListWidget();
        for (auto& partForm : participantForms) {
            partForm->PopulateListWidget();
        }

        ui.labelError->setText("New question added.");
    }
    catch (const std::exception& e){
        ui.labelError->setText(QString(e.what()));
    }

}