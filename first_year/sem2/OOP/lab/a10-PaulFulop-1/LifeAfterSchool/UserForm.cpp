#include "UserForm.h"

UserForm::UserForm(QWidget* parent, ServiceUM* _serv, QWidget* _mainWindow, CommandManager* _cmdManager)
    : QMainWindow(parent), ui(new Ui::UserWindowClass), serv (_serv), mainWindow (_mainWindow), cmdManager(_cmdManager)
{
    //ui->setupUi(this);
    setup();
}

UserForm::~UserForm()
{
    delete ui;
    delete serv;
}

void UserForm::StoreGlobalData()
{
    label->setStyleSheet("color:#ffffff");
    label->setText(" ");
    int row = 0, n = serv->globalRepo->events.size();
    int rc = tableWidgetAdminEvents->rowCount();

    while (tableWidgetAdminEvents->rowCount())
        tableWidgetAdminEvents->removeRow(0);

    int month = comboBoxMonths->currentIndex();
    Repository* filteredRepo = new MemoryRepository;

    if (month)
    {
        filteredRepo->events = serv->GetEventsByMonth(month)->events;
        n = filteredRepo->events.size();
        serv->SortEventsByDate(filteredRepo);
    }
    else
        filteredRepo->events = serv->globalRepo->events;

    if (!filteredRepo->events.size())
    {
        delete filteredRepo;
        return;
    }

    while (row < n)
    {
        tableWidgetAdminEvents->insertRow(row);

        QTableWidgetItem* token0 = new QTableWidgetItem;
        QTableWidgetItem* token1 = new QTableWidgetItem;
        QTableWidgetItem* token2 = new QTableWidgetItem;
        QTableWidgetItem* token3 = new QTableWidgetItem;


        token0->setText(QString(filteredRepo->events[row].title.c_str()));
        token1->setText(QString(filteredRepo->events[row].description.c_str()));
        token2->setText(QString(filteredRepo->events[row].dt.c_str()));
        token3->setText(QString(std::to_string(filteredRepo->events[row].nr_of_people).c_str()));

        QLabel* token4 = new QLabel();
        token4->setText("<a href='" + QString(filteredRepo->events[row].link.c_str()) + "'>" + QString(filteredRepo->events[row].link.c_str()) + "</a>");
        token4->setTextFormat(Qt::RichText);
        token4->setTextInteractionFlags(Qt::TextBrowserInteraction);
        token4->setOpenExternalLinks(true);


        tableWidgetAdminEvents->setItem(row, 0, token0);
        tableWidgetAdminEvents->setItem(row, 1, token1);
        tableWidgetAdminEvents->setItem(row, 2, token2);
        tableWidgetAdminEvents->setItem(row, 3, token3);
        tableWidgetAdminEvents->setCellWidget(row, 4, token4);
        ++row;
    }

    delete filteredRepo;

    if (tableWidgetAdminEvents->rowCount())
    {
        label->setText("Event: " + tableWidgetAdminEvents->item(0, 0)->text());
        currentRow = 1 % tableWidgetAdminEvents->rowCount();
        tableWidgetAdminEvents->selectRow(0);
    }
}

void UserForm::StoreUserData()
{
    int row = 0, n = serv->userRepo->events.size();
    int rc = tableWidgetUserEvents->rowCount();

    while (tableWidgetUserEvents->rowCount())
        tableWidgetUserEvents->removeRow(0);

    while (row < n)
    {
        tableWidgetUserEvents->insertRow(row);

        QTableWidgetItem* token0 = new QTableWidgetItem;
        QTableWidgetItem* token1 = new QTableWidgetItem;
        QTableWidgetItem* token2 = new QTableWidgetItem;
        QTableWidgetItem* token3 = new QTableWidgetItem;


        token0->setText(QString(serv->userRepo->events[row].title.c_str()));
        token1->setText(QString(serv->userRepo->events[row].description.c_str()));
        token2->setText(QString(serv->userRepo->events[row].dt.c_str()));
        token3->setText(QString(std::to_string(serv->userRepo->events[row].nr_of_people).c_str()));
        token0->setToolTip("remove with a double-click");
        token1->setToolTip("remove with a double-click");
        token2->setToolTip("remove with a double-click");
        token3->setToolTip("remove with a double-click");

        QLabel* token4 = new QLabel();
        token4->setText("<a href='" + QString(serv->userRepo->events[row].link.c_str()) + "'>" + QString(serv->userRepo->events[row].link.c_str()) + "</a>");
        token4->setTextFormat(Qt::RichText);
        token4->setTextInteractionFlags(Qt::TextBrowserInteraction);
        token4->setOpenExternalLinks(true);
        token4->setToolTip("remove with a double-click");


        tableWidgetUserEvents->setItem(row, 0, token0);
        tableWidgetUserEvents->setItem(row, 1, token1);
        tableWidgetUserEvents->setItem(row, 2, token2);
        tableWidgetUserEvents->setItem(row, 3, token3);
        tableWidgetUserEvents->setCellWidget(row, 4, token4);
        ++row;
    }
}

void UserForm::setup()
{
    InitComponents();
    SetProps();

    QMetaObject::connectSlotsByName(this);
}

void UserForm::InitComponents()
{
    if (this->objectName().isEmpty())
        this->setObjectName("UserWindowClass");
    this->resize(1376, 545);

    centralwidget = new QWidget(this);
    gridLayout_3 = new QGridLayout(centralwidget);
    groupBox_2 = new QGroupBox(centralwidget);
    gridLayout_2 = new QGridLayout(groupBox_2);
    tableWidgetUserEvents = new QTableWidget(groupBox_2);

    groupBox_3 = new QGroupBox(centralwidget);


    gridLayout_4 = new QGridLayout(groupBox_3);


    gridLayout_2->addWidget(tableWidgetUserEvents, 0, 0, 1, 1);
    gridLayout_3->addWidget(groupBox_2, 0, 1, 1, 1);

    groupBox = new QGroupBox(centralwidget);
    gridLayout = new QGridLayout(groupBox);
    comboBoxMonths = new QComboBox(groupBox);
    pushButtonNext = new QPushButton(groupBox);
    label = new QLabel(groupBox);
    tableWidgetAdminEvents = new QTableWidget(groupBox);
    pushButtonAdd = new QPushButton(groupBox);

    pushButtonViewCSV = new QPushButton(groupBox_2);
    pushButtonViewHTML = new QPushButton(groupBox_2);

    gridLayout->addWidget(comboBoxMonths, 4, 0, 1, 1);
    gridLayout->addWidget(pushButtonNext, 2, 0, 1, 1);
    gridLayout->addWidget(label, 5, 0, 1, 1);
    gridLayout->addWidget(tableWidgetAdminEvents, 0, 0, 1, 1);
    gridLayout->addWidget(pushButtonAdd, 3, 0, 1, 1);

    gridLayout_2->addWidget(pushButtonViewCSV, 1, 0, 1, 1);
    gridLayout_2->addWidget(pushButtonViewHTML, 2, 0, 1, 1);

    gridLayout_3->addWidget(groupBox, 0, 0, 2, 1);

    pushButtonUndo = new QPushButton(groupBox_3);
    gridLayout_4->addWidget(pushButtonUndo, 0, 0, 1, 1);

    pushButtonRedo = new QPushButton(groupBox_3);
    gridLayout_4->addWidget(pushButtonRedo, 1, 0, 1, 1);

    gridLayout_3->addWidget(groupBox_3, 1, 1, 1, 1);

    undoShortcut = new QShortcut(QKeySequence("Ctrl+Z"), this);
    redoShortcut = new QShortcut(QKeySequence("Ctrl+Y"), this);
    undoShortcut->setObjectName("undoShortcut");
    redoShortcut->setObjectName("redoShortcut");
    undoShortcut->setContext(Qt::ApplicationShortcut);
    redoShortcut->setContext(Qt::ApplicationShortcut);

    this->setCentralWidget(centralwidget);
}

void UserForm::SetProps()
{
    QTableWidgetItem* __qtablewidgetitem = new QTableWidgetItem();
    QTableWidgetItem* __qtablewidgetitem1 = new QTableWidgetItem();
    QTableWidgetItem* __qtablewidgetitem2 = new QTableWidgetItem();
    QTableWidgetItem* __qtablewidgetitem3 = new QTableWidgetItem();
    QTableWidgetItem* __qtablewidgetitem4 = new QTableWidgetItem();
    QTableWidgetItem* __qtablewidgetitem5 = new QTableWidgetItem();
    QTableWidgetItem* __qtablewidgetitem6 = new QTableWidgetItem();
    QTableWidgetItem* __qtablewidgetitem7 = new QTableWidgetItem();
    QTableWidgetItem* __qtablewidgetitem8 = new QTableWidgetItem();
    QTableWidgetItem* __qtablewidgetitem9 = new QTableWidgetItem();

    centralwidget->setObjectName("centralwidget");
    gridLayout_3->setObjectName("gridLayout_3");
    gridLayout_4->setObjectName("gridLayout_4");


    groupBox_2->setObjectName("groupBox_2");
    gridLayout_2->setObjectName("gridLayout_2");
    tableWidgetUserEvents->setObjectName("tableWidgetUserEvents");
    tableWidgetUserEvents->setRowCount(0);
    tableWidgetUserEvents->setColumnCount(5);
    tableWidgetUserEvents->setHorizontalHeaderItem(0, __qtablewidgetitem);
    tableWidgetUserEvents->setHorizontalHeaderItem(1, __qtablewidgetitem1);
    tableWidgetUserEvents->setHorizontalHeaderItem(2, __qtablewidgetitem2);

    tableWidgetUserEvents->horizontalHeader()->setStretchLastSection(true);
    tableWidgetUserEvents->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    tableWidgetUserEvents->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);

    tableWidgetUserEvents->setEditTriggers(QAbstractItemView::NoEditTriggers);  // Prevent editing

    QFont font;
    font.setPointSize(7);
    __qtablewidgetitem3->setFont(font);
    tableWidgetUserEvents->setHorizontalHeaderItem(3, __qtablewidgetitem3);
    tableWidgetUserEvents->setHorizontalHeaderItem(4, __qtablewidgetitem4);

    groupBox->setObjectName("groupBox");
    gridLayout->setObjectName("gridLayout");

    QFont font1;
    font1.setPointSize(11);
    font1.setBold(true);

    font1.setStyleStrategy(QFont::PreferDefault);
    comboBoxMonths->setFont(font1);
    comboBoxMonths->setSizeAdjustPolicy(QComboBox::SizeAdjustPolicy::AdjustToMinimumContentsLengthWithIcon);

    groupBox_3->setObjectName("groupBox_3");
    groupBox_3->setTitle("Undo and Redo");
    groupBox_3->setAlignment(Qt::AlignCenter);
    groupBox_3->setFont(font1);
    groupBox->setFont(font1);
    groupBox_2->setFont(font1);

    QFont font3;
    font3.setPointSize(11);
    font3.setBold(false);
    tableWidgetAdminEvents->setFont(font3);
    tableWidgetUserEvents->setFont(font3);

    pushButtonNext->setObjectName("pushButtonNext");
    QFont font2;
    font2.setPointSize(11);
    font2.setBold(true);
    pushButtonNext->setFont(font2);

    pushButtonViewCSV->setObjectName("pushButtonViewCSV");
    pushButtonViewCSV->setFont(font2);
    pushButtonViewCSV->setText("View in CSV");

    pushButtonViewHTML->setObjectName("pushButtonViewHTML");
    pushButtonViewHTML->setFont(font2);
    pushButtonViewHTML->setText("View in HTML");

    label->setObjectName("label");
    label->setFont(font2);
    label->setAlignment(Qt::AlignmentFlag::AlignCenter);

    tableWidgetAdminEvents->setObjectName("tableWidgetAdminEvents");
    tableWidgetAdminEvents->setRowCount(0);
    tableWidgetAdminEvents->setColumnCount(5);
    tableWidgetAdminEvents->setHorizontalHeaderItem(0, __qtablewidgetitem5);
    tableWidgetAdminEvents->setHorizontalHeaderItem(1, __qtablewidgetitem6);
    tableWidgetAdminEvents->setHorizontalHeaderItem(2, __qtablewidgetitem7);

    tableWidgetAdminEvents->horizontalHeader()->setStretchLastSection(true);
    tableWidgetAdminEvents->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    tableWidgetAdminEvents->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);

    tableWidgetAdminEvents->setEditTriggers(QAbstractItemView::NoEditTriggers);  // Prevent editing
    tableWidgetAdminEvents->setFocusPolicy(Qt::NoFocus);                         // Prevent focus outline

    __qtablewidgetitem8->setFont(font);
    tableWidgetAdminEvents->setHorizontalHeaderItem(3, __qtablewidgetitem8);
    tableWidgetAdminEvents->setHorizontalHeaderItem(4, __qtablewidgetitem9);

    pushButtonAdd->setObjectName("pushButtonAdd");
    pushButtonAdd->setFont(font2);

    // Translations & Text
    this->setWindowTitle(QCoreApplication::translate("UserWindowClass", "Manage User Events", nullptr));
    groupBox_2->setTitle(QCoreApplication::translate("UserWindowClass", "Your List", nullptr));
    groupBox->setTitle(QCoreApplication::translate("UserWindowClass", "Add events to your list", nullptr));

    tableWidgetUserEvents->horizontalHeaderItem(0)->setText(QCoreApplication::translate("UserWindowClass", "Title", nullptr));
    tableWidgetUserEvents->horizontalHeaderItem(1)->setText(QCoreApplication::translate("UserWindowClass", "Description", nullptr));
    tableWidgetUserEvents->horizontalHeaderItem(2)->setText(QCoreApplication::translate("UserWindowClass", "Date and Time", nullptr));
    tableWidgetUserEvents->horizontalHeaderItem(3)->setText(QCoreApplication::translate("UserWindowClass", "Number of Participants", nullptr));
    tableWidgetUserEvents->horizontalHeaderItem(4)->setText(QCoreApplication::translate("UserWindowClass", "Link", nullptr));

    comboBoxMonths->setObjectName("comboBoxMonths");
    comboBoxMonths->addItem(QString());
    comboBoxMonths->addItem(QString());
    comboBoxMonths->addItem(QString());
    comboBoxMonths->addItem(QString());
    comboBoxMonths->addItem(QString());
    comboBoxMonths->addItem(QString());
    comboBoxMonths->addItem(QString());
    comboBoxMonths->addItem(QString());
    comboBoxMonths->addItem(QString());
    comboBoxMonths->addItem(QString());
    comboBoxMonths->addItem(QString());
    comboBoxMonths->addItem(QString());
    comboBoxMonths->addItem(QString());

    comboBoxMonths->setItemText(0, QCoreApplication::translate("UserWindowClass", "No Filter", nullptr));
    comboBoxMonths->setItemText(1, QCoreApplication::translate("UserWindowClass", "January", nullptr));
    comboBoxMonths->setItemText(2, QCoreApplication::translate("UserWindowClass", "February", nullptr));
    comboBoxMonths->setItemText(3, QCoreApplication::translate("UserWindowClass", "March", nullptr));
    comboBoxMonths->setItemText(4, QCoreApplication::translate("UserWindowClass", "April", nullptr));
    comboBoxMonths->setItemText(5, QCoreApplication::translate("UserWindowClass", "May", nullptr));
    comboBoxMonths->setItemText(6, QCoreApplication::translate("UserWindowClass", "June", nullptr));
    comboBoxMonths->setItemText(7, QCoreApplication::translate("UserWindowClass", "July", nullptr));
    comboBoxMonths->setItemText(8, QCoreApplication::translate("UserWindowClass", "August", nullptr));
    comboBoxMonths->setItemText(9, QCoreApplication::translate("UserWindowClass", "September", nullptr));
    comboBoxMonths->setItemText(10, QCoreApplication::translate("UserWindowClass", "October", nullptr));
    comboBoxMonths->setItemText(11, QCoreApplication::translate("UserWindowClass", "November", nullptr));
    comboBoxMonths->setItemText(12, QCoreApplication::translate("UserWindowClass", "December", nullptr));

    for (int i = 0; i < comboBoxMonths->count(); ++i) {
        comboBoxMonths->setItemData(i, Qt::AlignmentFlag::AlignCenter, Qt::TextAlignmentRole);
    }

    pushButtonNext->setText(QCoreApplication::translate("UserWindowClass", "Next", nullptr));
    label->setText(QCoreApplication::translate("UserWindowClass", "TextLabel", nullptr));
    tableWidgetAdminEvents->horizontalHeaderItem(0)->setText(QCoreApplication::translate("UserWindowClass", "Title", nullptr));
    tableWidgetAdminEvents->horizontalHeaderItem(1)->setText(QCoreApplication::translate("UserWindowClass", "Description", nullptr));
    tableWidgetAdminEvents->horizontalHeaderItem(2)->setText(QCoreApplication::translate("UserWindowClass", "Date and Time", nullptr));
    tableWidgetAdminEvents->horizontalHeaderItem(3)->setText(QCoreApplication::translate("UserWindowClass", "Number of Participants", nullptr));
    tableWidgetAdminEvents->horizontalHeaderItem(4)->setText(QCoreApplication::translate("UserWindowClass", "Link", nullptr));
    pushButtonAdd->setText(QCoreApplication::translate("UserWindowClass", "Add", nullptr));

    pushButtonUndo->setObjectName("pushButtonUndo");
    pushButtonUndo->setText(QCoreApplication::translate("UserWindowClass", "Undo", nullptr));
    pushButtonUndo->setFont(font2);

    pushButtonRedo->setObjectName("pushButtonRedo");
    pushButtonRedo->setText(QCoreApplication::translate("UserWindowClass", "Redo", nullptr));
    pushButtonRedo->setFont(font2);
}

void UserForm::on_pushButtonAdd_clicked()
{
    try {
        int rc = tableWidgetAdminEvents->rowCount();

        if (!rc)
            throw OutOfRangeException();

        int pos = (((currentRow - 1) % rc) + rc) % rc;
        Event newEvent = serv->globalRepo->events[pos];
        serv->AddUserEvent(pos);
        serv->RemoveUserEvent(newEvent.title);

        cmdManager->CommandExecute(new AddCommand(nullptr, serv, newEvent, UserService));

        int newRow = tableWidgetUserEvents->rowCount();
        tableWidgetUserEvents->insertRow(newRow);

        QTableWidgetItem* token0 = new QTableWidgetItem;
        QTableWidgetItem* token1 = new QTableWidgetItem;
        QTableWidgetItem* token2 = new QTableWidgetItem;
        QTableWidgetItem* token3 = new QTableWidgetItem;

        token0->setText(QString(serv->userRepo->events[newRow].title.c_str()));
        token1->setText(QString(serv->userRepo->events[newRow].description.c_str()));
        token2->setText(QString(serv->userRepo->events[newRow].dt.c_str()));
        token3->setText(QString(std::to_string(serv->userRepo->events[newRow].nr_of_people).c_str()));
        token0->setToolTip("remove with a double-click");
        token1->setToolTip("remove with a double-click");
        token2->setToolTip("remove with a double-click");
        token3->setToolTip("remove with a double-click");


        QLabel* token4 = new QLabel();
        token4->setText("<a href='" + QString(serv->userRepo->events[newRow].link.c_str()) + "'>" + QString(serv->userRepo->events[newRow].link.c_str()) + "</a>");
        token4->setTextFormat(Qt::RichText);
        token4->setTextInteractionFlags(Qt::TextBrowserInteraction);
        token4->setOpenExternalLinks(true);
        token4->setToolTip("remove with a double-click");

        tableWidgetUserEvents->setItem(newRow, 0, token0);
        tableWidgetUserEvents->setItem(newRow, 1, token1);
        tableWidgetUserEvents->setItem(newRow, 2, token2);
        tableWidgetUserEvents->setItem(newRow, 3, token3);
        tableWidgetUserEvents->setCellWidget(newRow, 4, token4);


        StoreGlobalData();
        label->setStyleSheet("color:#549150");
        label->setText("Event has been added.");
    }
    catch (const std::exception& e) {
        label->setStyleSheet("color:#822d27");
        label->setText(e.what());
    }
}

void UserForm::on_pushButtonNext_clicked()
{
    try {
        label->setStyleSheet("color:#ffffff");
        int rc = tableWidgetAdminEvents->rowCount();

        if (rc)
        {
            label->setText("Event: " + tableWidgetAdminEvents->item(currentRow, 0)->text());
            tableWidgetAdminEvents->selectRow(currentRow++);
            currentRow %= rc;
        }
        else
            label->setText(" ");
    }
    catch (const std::exception e) {
        label->setStyleSheet("color:#822d27");
        label->setText(e.what());
    }
}

void UserForm::on_pushButtonViewCSV_clicked()
{
    try {
        CSVEventViewer csvEventViewer = CSVEventViewer(&serv->userRepo->events, "user_events.csv");
        csvEventViewer.StoreData();
        std::string openFile = "start " + csvEventViewer.GetFile();
        system(openFile.c_str());
    }
    catch (const std::exception e) {
    }
}

void UserForm::on_pushButtonViewHTML_clicked()
{
    try {
        HTMLEventViewer htmlEventViewer = HTMLEventViewer(&serv->userRepo->events, "user_events.html");
        htmlEventViewer.StoreData();
        std::string openFile = "start " + htmlEventViewer.GetFile();
        system(openFile.c_str());
    }
    catch (const std::exception e) {
        pushButtonViewHTML->setText(e.what());
    }
}

void UserForm::on_undoShortcut_activated() {
    on_pushButtonUndo_clicked();
}

void UserForm::on_redoShortcut_activated() {
    on_pushButtonRedo_clicked();
}

void UserForm::on_pushButtonUndo_clicked() {
    cmdManager->CommandUndo();
    StoreUserData();
}

void UserForm::on_pushButtonRedo_clicked() {
    cmdManager->CommandRedo();
    StoreUserData();
}

void UserForm::on_comboBoxMonths_currentIndexChanged(int index)
{
    StoreGlobalData();
}

void UserForm::on_tableWidgetUserEvents_cellDoubleClicked(int row, int column)
{
    Event event = Event();
    event.title = tableWidgetUserEvents->item(row, 0)->text().toStdString();
    cmdManager->CommandExecute(new RemoveCommand(nullptr, serv, event, UserService));

    //serv->RemoveUserEvent(tableWidgetUserEvents->item(row, 0)->text().toStdString());
    StoreUserData();
    StoreGlobalData();
}

void UserForm::closeEvent(QCloseEvent* event)
{
    this->close();
    mainWindow->show();
    event->accept();
}