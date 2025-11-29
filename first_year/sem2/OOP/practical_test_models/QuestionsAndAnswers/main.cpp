#include "UserForm.h"
#include "SearchQuestionWindow.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    std::vector<UserForm*> forms;
    Repo<User> users = Repo<User>("users.txt");
    Repo<Question> questions = Repo<Question>("questions.txt");
    Repo<Answer> answers = Repo<Answer>("answers.txt");

    for (const auto& u : users.data) {
        Service s = Service(u, &questions, &answers);
        UserForm* uForm = new UserForm(s);
        forms.push_back(uForm);
    }

    Service s = Service(users.data[0], &questions, &answers);
    SearchQuestionWindow* sqwForm = new SearchQuestionWindow(s);

    for (const auto& sender : forms) {
        for (const auto& receiver : forms)
            if (sender != receiver) {
                QObject::connect(sender, &UserForm::questionAdded, receiver, &UserForm::on_questionAdded);
                QObject::connect(sender, &UserForm::answerAdded, receiver, &UserForm::on_answerAdded);
            }
        QObject::connect(sender, &UserForm::answerAdded, sqwForm, &SearchQuestionWindow::on_dataModified);
    }

    for (const auto& uForm : forms)
        uForm->show();

    sqwForm->show();

    return app.exec();
}
