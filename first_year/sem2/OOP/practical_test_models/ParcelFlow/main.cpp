#include "AgentForm.h"
#include <QtWidgets/QApplication>
#include "Agent.h"
#include "Repository.h"
#include "Parcel.h"
#include "Dashboard.h"
#include "UndeliveredParcelsForm.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    Repo<Parcel> parcels = Repo<Parcel>("parcels.txt");
    Repo<Agent> agents = Repo<Agent>("agents.txt");
    
    std::vector<AgentForm*> agentForms;
    for (const auto& agent : agents.data) {
        AgentForm* af = new AgentForm(nullptr, agent, &parcels);
        agentForms.push_back(af);
    }

    Dashboard* d = new Dashboard(&parcels);
    UndeliveredParcelsForm* undeliveredForm = new UndeliveredParcelsForm(&parcels);

    for (const auto& senderForm : agentForms) {
        for (const auto& receiverForm : agentForms)
            if (senderForm != receiverForm)
                QObject::connect(senderForm, &AgentForm::dataChanged, receiverForm, &AgentForm::parcelDelivered);

        QObject::connect(senderForm, &AgentForm::dataChanged, d, &Dashboard::parcelsDataModified);
        QObject::connect(d, &Dashboard::dataChanged, senderForm, &AgentForm::parcelDelivered);
        QObject::connect(senderForm, &AgentForm::dataChanged, undeliveredForm, &UndeliveredParcelsForm::parcelDelivered);
    }

    QObject::connect(d, &Dashboard::dataChanged, undeliveredForm, &UndeliveredParcelsForm::parcelDelivered);

    for (const auto& form : agentForms)
        form->show();

    d->show();
    undeliveredForm->show();
    return app.exec();
}
