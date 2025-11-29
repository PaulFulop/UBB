#include "MainWindow.h"
#include "EventsTableModel.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindowClass), userForm (new UserForm), adminForm (new AdminForm)
{
    //ui->setupUi(this);
    setup();
    
}

void MainWindow::setup()
{
    InitComponents();
    SetProps();

    QMetaObject::connectSlotsByName(this);
}

void MainWindow::InitComponents()
{
    userForm->mainWindow = this;
    adminForm->mainWindow = this;

    adminForm->serv->repo = new FileRepository("events.txt");
    userForm->serv->globalRepo = adminForm->serv->repo;
    userForm->serv->userRepo = new FileRepository("user_events.txt");
    adminForm->serv->userRepo = userForm->serv->userRepo;

    adminEventsModel = new EventsTableModel(*adminForm->serv->repo);
    userEventsModel = new EventsTableModel(*userForm->serv->userRepo);

    adminView = new QTableView();
    userView = new QTableView();

    layout2 = new QVBoxLayout(adminView);
    layout3 = new QVBoxLayout(userView);

    centralWidget = new QWidget(this);
    pushButtonSeeUserEvents = new QPushButton(centralWidget);
    pushButtonSeeAdminEvents = new QPushButton(centralWidget);
    pushButtonSeeAdminView = new QPushButton(centralWidget);
    pushButtonSeeUserView = new QPushButton(centralWidget);
    layout1 = new QVBoxLayout(centralWidget);
}

void MainWindow::SetProps()
{
    adminView->setWindowTitle("Admin");
    adminView->setModel(adminEventsModel);
    adminView->horizontalHeader()->setStretchLastSection(true);          
    adminView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);  
    adminView->resizeRowsToContents();                                  
    adminView->setAlternatingRowColors(true);
    adminView->setSelectionBehavior(QAbstractItemView::SelectRows);
    adminView->setSelectionMode(QAbstractItemView::SingleSelection);
    adminView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    adminView->setFixedSize(800, 475);

    userView->setWindowTitle("User");
    userView->setModel(userEventsModel);
    userView->horizontalHeader()->setStretchLastSection(true);
    userView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    userView->resizeRowsToContents();
    userView->setAlternatingRowColors(true);
    userView->setSelectionBehavior(QAbstractItemView::SelectRows);
    userView->setSelectionMode(QAbstractItemView::SingleSelection);
    userView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    userView->setFixedSize(800, 475);

    layout3->addWidget(userView);


    if (this->objectName().isEmpty())
        this->setObjectName("MainWindowClass");
    this->resize(298, 159);

    pushButtonSeeUserEvents->setText("Manage User Events");
    pushButtonSeeAdminEvents->setText("Manage Admin Events");
    pushButtonSeeAdminView->setText("See Admin Table");
    pushButtonSeeUserView->setText("See User Table");

    centralWidget->setObjectName("centralWidget");
    pushButtonSeeUserEvents->setObjectName("pushButtonSeeUserEvents");
    pushButtonSeeAdminEvents->setObjectName("pushButtonSeeAdminEvents");
    pushButtonSeeAdminView->setObjectName("pushButtonSeeAdminView");
    pushButtonSeeUserView->setObjectName("pushButtonSeeUserView");

    this->setCentralWidget(centralWidget);
    this->setWindowTitle("Menu");

    layout1->addWidget(pushButtonSeeAdminEvents);
    layout1->addWidget(pushButtonSeeUserEvents);
    layout1->addWidget(pushButtonSeeAdminView);
    layout1->addWidget(pushButtonSeeUserView);
}

MainWindow::~MainWindow()
{
    delete ui;
    delete adminView;
    delete userView;
    delete adminEventsModel;
    delete userEventsModel;
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

void MainWindow::on_pushButtonSeeAdminView_clicked() {
    adminView->show();
}

void MainWindow::on_pushButtonSeeUserView_clicked() {
    userView->show();
}