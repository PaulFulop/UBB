#include "MainWindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindowClass), userForm (new UserForm), adminForm (new AdminForm)
{
    //ui->setupUi(this);
    setup();
    userForm->mainWindow = this;
    adminForm->mainWindow = this;

    adminForm->serv->repo = new FileRepository("events.txt");
    userForm->serv->globalRepo = adminForm->serv->repo;
    userForm->serv->userRepo = new FileRepository("user_events.txt");
    adminForm->serv->userRepo = userForm->serv->userRepo;
}

void MainWindow::setup()
{
    InitComponents();
    SetProps();

    QMetaObject::connectSlotsByName(this);
}

void MainWindow::InitComponents()
{
    centralWidget = new QWidget(this);
    pushButtonSeeUserEvents = new QPushButton(centralWidget);
    pushButtonSeeAdminEvents = new QPushButton(centralWidget);
    layout = new QVBoxLayout(centralWidget);
}

void MainWindow::SetProps()
{
    if (this->objectName().isEmpty())
        this->setObjectName("MainWindowClass");
    this->resize(298, 159);

    pushButtonSeeUserEvents->setGeometry(QRect(60, 70, 151, 41));
    pushButtonSeeAdminEvents->setGeometry(QRect(260, 70, 151, 41));
    pushButtonSeeUserEvents->setText("See User Events");
    pushButtonSeeAdminEvents->setText("See Admin Events");

    centralWidget->setObjectName("centralWidget");
    pushButtonSeeUserEvents->setObjectName("pushButtonSeeUserEvents");
    pushButtonSeeAdminEvents->setObjectName("pushButtonSeeAdminEvents");

    this->setCentralWidget(centralWidget);
    this->setWindowTitle("Choose mode");

    layout->addWidget(pushButtonSeeAdminEvents);
    layout->addWidget(pushButtonSeeUserEvents);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButtonSeeUserEvents_clicked()
{
    this->hide();
    userForm->StoreGlobalData();
    userForm->StoreUserData();
    userForm->show();
}


void MainWindow::on_pushButtonSeeAdminEvents_clicked()
{
    this->hide();
    adminForm->StoreData();
    adminForm->show();
}