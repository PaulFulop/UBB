#include "UserForm.h"
#include <QMessageBox>

UserForm::UserForm(Service _serv, QWidget *parent)
    : serv(_serv), QMainWindow(parent)
{
    ui.setupUi(this);
    this->setWindowTitle(QString::fromStdString(serv.user.name));
    ui.lineEditA->setEnabled(false);
    ui.pushButtonA->setEnabled(false);
    PopulateListWidgetQuestions();
}

UserForm::~UserForm()
{}

void UserForm::PopulateListWidgetQuestions() {
    ui.listWidgetQuestions->clear();
    serv.SortQuestions();
    for (const auto& q : serv.questions->data) {
        auto item = new QListWidgetItem(QString::fromStdString(q.ToString()));
        ui.listWidgetQuestions->addItem(item);
    }
}

void UserForm::PopulateListWidgetAnswers(std::vector<Answer> aToQ) {
    ui.listWidgetAnswers->clear();
    for (const auto& a : aToQ) {
        auto item = new QListWidgetItem(QString::fromStdString(a.ToString()));
        if (serv.AnswerByUser(a))
            item->setBackground(Qt::darkYellow);
        ui.listWidgetAnswers->addItem(item);
    }
}

void UserForm::on_questionAdded() {
    PopulateListWidgetQuestions();
}

void UserForm::on_answerAdded() {
}

void UserForm::on_pushButtonA_clicked() {
    std::string text = ui.lineEditA->text().toStdString();

    try {
        int i;
        for (i = 0; i < ui.listWidgetQuestions->count(); ++i)
            if (ui.listWidgetQuestions->item(i)->isSelected())
                break;
        serv.AddAnswer(serv.questions->data[i], text);
        auto item = new QListWidgetItem(QString::fromStdString(serv.answers->data[serv.answers->data.size() - 1].ToString()));
        item->setBackground(Qt::darkYellow);
        ui.listWidgetAnswers->addItem(item);
        ui.lineEditA->clear();
        emit answerAdded();
    }
    catch (const std::exception& e) {
        auto msg = new QMessageBox(QMessageBox::Icon::Warning, "Warning", e.what());
        msg->show();
    }
}

void UserForm::on_pushButtonQ_clicked() {
    std::string text = ui.lineEditQ->text().toStdString();

    try {
        serv.AddQuestion(text);
        PopulateListWidgetQuestions();
        ui.lineEditA->clear();
        emit questionAdded();
    }
    catch(const std::exception& e){
        auto msg = new QMessageBox(QMessageBox::Icon::Warning, "Warning", e.what());
        msg->show();
    }
}

void UserForm::on_listWidgetQuestions_itemClicked(QListWidgetItem* item) {
    ui.pushButtonA->setEnabled(true);
    ui.lineEditA->setEnabled(true);

    int row = ui.listWidgetQuestions->row(item);
    auto aToQ = serv.AnswersToQuestion(serv.questions->data[row]);
    PopulateListWidgetAnswers(aToQ);
}