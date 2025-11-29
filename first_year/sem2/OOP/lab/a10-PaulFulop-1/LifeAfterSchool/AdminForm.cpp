#include "AdminForm.h"
#include <exception>

AdminForm::AdminForm(QWidget* parent, ServiceAM* _serv, QWidget* _mainWindow, CommandManager* _cmdManager)
    : QMainWindow(parent), ui(new Ui::AdminWindowClass), serv (_serv), mainWindow (_mainWindow), cmdManager(_cmdManager)
{
    //ui->setupUi(this);
    setup();
}

AdminForm::~AdminForm()
{
    delete serv;
    delete ui;
}

void AdminForm::StoreData()
{
    int row = 0, n = serv->repo->events.size();
    int rc = tableWidgetEvents->rowCount();

    while (tableWidgetEvents->rowCount())
        tableWidgetEvents->removeRow(0);

    while (row < n)
    {
        tableWidgetEvents->insertRow(row);
        
        QTableWidgetItem* token0 = new QTableWidgetItem;
        QTableWidgetItem* token1 = new QTableWidgetItem;
        QTableWidgetItem* token2 = new QTableWidgetItem;
        QTableWidgetItem* token3 = new QTableWidgetItem;


        token0->setText(QString(serv->repo->events[row].title.c_str()));
        token1->setText(QString(serv->repo->events[row].description.c_str()));
        token2->setText(QString(serv->repo->events[row].dt.c_str()));
        token3->setText(QString(std::to_string(serv->repo->events[row].nr_of_people).c_str()));

        QLabel* token4 = new QLabel();
        token4->setText("<a href='" + QString(serv->repo->events[row].link.c_str()) + "'>" + QString(serv->repo->events[row].link.c_str()) + "</a>");
        token4->setTextFormat(Qt::RichText);
        token4->setTextInteractionFlags(Qt::TextBrowserInteraction);
        token4->setOpenExternalLinks(true);
        token4->setToolTip("Remove");


        tableWidgetEvents->setItem(row, 0, token0);
        tableWidgetEvents->setItem(row, 1, token1);
        tableWidgetEvents->setItem(row, 2, token2);
        tableWidgetEvents->setItem(row, 3, token3);
        tableWidgetEvents->setCellWidget(row, 4, token4);
        ++row;
    }
}

void AdminForm::setup()
{
    InitComponents();
    SetProps();

    QMetaObject::connectSlotsByName(this);
}

void AdminForm::InitComponents()
{
    if (this->objectName().isEmpty())
        this->setObjectName("this");
    this->resize(1166, 872);

    centralwidget = new QWidget(this);
    centralwidget->setObjectName("centralwidget");

    gridLayout_4 = new QGridLayout(centralwidget);
    gridLayout_4->setObjectName("gridLayout_4");

    tableWidgetEvents = new QTableWidget(centralwidget);
    tableWidgetEvents->setObjectName("tableWidgetEvents");
    tableWidgetEvents->setRowCount(0);
    tableWidgetEvents->setColumnCount(5);

    gridLayout_4->addWidget(tableWidgetEvents, 0, 0, 1, 4);

    // Add groupBox
    groupBox = new QGroupBox(centralwidget);
    groupBox->setObjectName("groupBox");
    gridLayout = new QGridLayout(groupBox);
    gridLayout->setObjectName("gridLayout");

    // Add widgets to groupBox
    lineEditTitleAdd = new QLineEdit(groupBox);
    lineEditTitleAdd->setObjectName("lineEditTitleAdd");
    gridLayout->addWidget(lineEditTitleAdd, 0, 1, 1, 1);

    lineEditDescriptionAdd = new QLineEdit(groupBox);
    lineEditDescriptionAdd->setObjectName("lineEditDescriptionAdd");
    gridLayout->addWidget(lineEditDescriptionAdd, 1, 1, 1, 1);

    lineEditDateAdd = new QLineEdit(groupBox);
    lineEditDateAdd->setObjectName("lineEditDateAdd");
    gridLayout->addWidget(lineEditDateAdd, 2, 1, 1, 1);

    lineEditPartAdd = new QLineEdit(groupBox);
    lineEditPartAdd->setObjectName("lineEditPartAdd");
    gridLayout->addWidget(lineEditPartAdd, 3, 1, 1, 1);

    lineEditLinkAdd = new QLineEdit(groupBox);
    lineEditLinkAdd->setObjectName("lineEditLinkAdd");
    gridLayout->addWidget(lineEditLinkAdd, 4, 1, 1, 1);

    pushButtonAdd = new QPushButton(groupBox);
    pushButtonAdd->setObjectName("pushButtonAdd");
    gridLayout->addWidget(pushButtonAdd, 6, 0, 1, 2);

    labelErrorAdd = new QLabel(groupBox);
    labelErrorAdd->setObjectName("labelErrorAdd");

    gridLayout->addWidget(labelErrorAdd, 5, 0, 1, 2);

    // Labels for groupBox
    label = new QLabel(groupBox); label->setObjectName("label");
    gridLayout->addWidget(label, 0, 0, 1, 1);

    label_3 = new QLabel(groupBox); label_3->setObjectName("label_3");
    gridLayout->addWidget(label_3, 1, 0, 1, 1);

    label_4 = new QLabel(groupBox); label_4->setObjectName("label_4");
    gridLayout->addWidget(label_4, 2, 0, 1, 1);

    label_6 = new QLabel(groupBox); label_6->setObjectName("label_6");
    gridLayout->addWidget(label_6, 3, 0, 1, 1);

    label_7 = new QLabel(groupBox); label_7->setObjectName("label_7");
    gridLayout->addWidget(label_7, 4, 0, 1, 1);

    gridLayout_4->addWidget(groupBox, 1, 0, 5, 1);

    groupBox_3 = new QGroupBox(centralwidget);
    groupBox_3->setObjectName("groupBox_3");
    gridLayout_3 = new QGridLayout(groupBox_3);
    gridLayout_3->setObjectName("gridLayout_3");

    lineEditEventRemove = new QLineEdit(groupBox_3);
    lineEditEventRemove->setObjectName("lineEditEventRemove");
    gridLayout_3->addWidget(lineEditEventRemove, 0, 1, 1, 1);

    label_2 = new QLabel(groupBox_3);
    label_2->setObjectName("label_2");
    gridLayout_3->addWidget(label_2, 0, 0, 1, 1);

    labelErrorRemove = new QLabel(groupBox_3);
    labelErrorRemove->setObjectName("labelErrorRemove");

    gridLayout_3->addWidget(labelErrorRemove, 2, 0, 1, 2);

    pushButtonRemove = new QPushButton(groupBox_3);
    pushButtonRemove->setObjectName("pushButtonRemove");
    gridLayout_3->addWidget(pushButtonRemove, 1, 0, 1, 2);

    gridLayout_4->addWidget(groupBox_3, 1, 1, 1, 1);

    // Update groupBox
    groupBox_2 = new QGroupBox(centralwidget);
    groupBox_2->setObjectName("groupBox_2");
    gridLayout_2 = new QGridLayout(groupBox_2);
    gridLayout_2->setObjectName("gridLayout_2");

    lineEditTitleUpdate = new QLineEdit(groupBox_2); lineEditTitleUpdate->setObjectName("lineEditTitleUpdate");
    lineEditDescriptionUpdate = new QLineEdit(groupBox_2); lineEditDescriptionUpdate->setObjectName("lineEditDescriptionUpdate");
    lineEditDateUpdate = new QLineEdit(groupBox_2); lineEditDateUpdate->setObjectName("lineEditDateUpdate");
    lineEditPartUpdate = new QLineEdit(groupBox_2); lineEditPartUpdate->setObjectName("lineEditPartUpdate");
    lineEditLinkUpdate = new QLineEdit(groupBox_2); lineEditLinkUpdate->setObjectName("lineEditLinkUpdate");

    gridLayout_2->addWidget(lineEditTitleUpdate, 0, 1, 1, 1);
    gridLayout_2->addWidget(lineEditDescriptionUpdate, 1, 1, 1, 1);
    gridLayout_2->addWidget(lineEditDateUpdate, 2, 1, 1, 1);
    gridLayout_2->addWidget(lineEditPartUpdate, 3, 1, 1, 1);
    gridLayout_2->addWidget(lineEditLinkUpdate, 4, 1, 1, 1);

    label_5 = new QLabel(groupBox_2); label_5->setObjectName("label_5");
    label_8 = new QLabel(groupBox_2); label_8->setObjectName("label_8");
    label_9 = new QLabel(groupBox_2); label_9->setObjectName("label_9");
    label_10 = new QLabel(groupBox_2); label_10->setObjectName("label_10");
    label_11 = new QLabel(groupBox_2); label_11->setObjectName("label_11");

    labelErrorUpdate = new QLabel(groupBox_2);
    labelErrorUpdate->setObjectName("labelErrorUpdate");

    pushButtonUpdate = new QPushButton(groupBox_2);
    pushButtonUpdate->setObjectName("pushButtonUpdate");

    groupBox_4 = new QGroupBox(centralwidget);
    groupBox_4->setObjectName("groupBox_4");
    gridLayout_5 = new QGridLayout(groupBox_4);
    gridLayout_5->setObjectName("gridLayout_5");

    pushButtonUndo = new QPushButton(groupBox_4);
    pushButtonUndo->setObjectName("pushButtonUndo");
    gridLayout_5->addWidget(pushButtonUndo, 0, 0, 1, 2);

    pushButtonRedo = new QPushButton(groupBox_4);
    pushButtonRedo->setObjectName("pushButtonRedo");
    gridLayout_5->addWidget(pushButtonRedo, 1, 0, 1, 2);

    gridLayout_2->addWidget(label_5, 0, 0, 1, 1);
    gridLayout_2->addWidget(label_8, 1, 0, 1, 1);
    gridLayout_2->addWidget(label_9, 2, 0, 1, 1);
    gridLayout_2->addWidget(label_10, 3, 0, 1, 1);
    gridLayout_2->addWidget(label_11, 4, 0, 1, 1);
    gridLayout_2->addWidget(labelErrorUpdate, 5, 0, 1, 2);
    gridLayout_2->addWidget(pushButtonUpdate, 6, 0, 1, 2);

    gridLayout_4->addWidget(groupBox_2, 1, 2, 5, 1);
    gridLayout_4->addWidget(groupBox_4, 2, 1, 4, 1);

    undoShortcut = new QShortcut(QKeySequence("Ctrl+Z"), this);
    redoShortcut = new QShortcut(QKeySequence("Ctrl+Y"), this);
    undoShortcut->setObjectName("undoShortcut");
    redoShortcut->setObjectName("redoShortcut");
    undoShortcut->setContext(Qt::ApplicationShortcut);
    redoShortcut->setContext(Qt::ApplicationShortcut);

    this->setCentralWidget(centralwidget);

    QFont font;
    font.setPointSize(9);
}

void AdminForm::SetProps()
{
    // Header items
    QTableWidgetItem* __qtablewidgetitem = new QTableWidgetItem();
    QTableWidgetItem* __qtablewidgetitem1 = new QTableWidgetItem();
    QTableWidgetItem* __qtablewidgetitem2 = new QTableWidgetItem();
    QTableWidgetItem* __qtablewidgetitem3 = new QTableWidgetItem();
    QTableWidgetItem* __qtablewidgetitem4 = new QTableWidgetItem();

    // Fonts
    QFont font;
    font.setPointSize(9);
    __qtablewidgetitem3->setFont(font);
    __qtablewidgetitem4->setFont(font);

    QFont font1;
    font1.setPointSize(14);
    font1.setBold(true);

    groupBox->setFont(font1);
    groupBox->setAlignment(Qt::AlignCenter);
    groupBox_2->setFont(font1);
    groupBox_2->setAlignment(Qt::AlignCenter);
    groupBox_3->setFont(font1);
    groupBox_3->setAlignment(Qt::AlignCenter);
    groupBox_4->setFont(font1);
    groupBox_4->setAlignment(Qt::AlignCenter);
    groupBox_4->setTitle("Undo and Redo");

    QFont font2;
    font2.setPointSize(10);
    font2.setBold(true);

    QFont font3;
    font3.setPointSize(11);
    font3.setBold(true);
    pushButtonAdd->setFont(font3);
    pushButtonRemove->setFont(font3);
    pushButtonUpdate->setFont(font3);
    pushButtonUndo->setFont(font3);
    pushButtonRedo->setFont(font3);

    pushButtonUndo->setText("Undo");
    pushButtonRedo->setText("Redo");

    QFont font4;
    font4.setPointSize(11);
    font4.setBold(false);
    tableWidgetEvents->setFont(font4);

    // Set fonts and alignments for labels
    QList<QLabel*> labels = { label, label_2, label_3, label_4, label_5, label_6, label_7, label_8, label_9, label_10, label_11, labelErrorAdd, labelErrorRemove, labelErrorUpdate };
    for (QLabel* l : labels) {
        l->setFont(font2);
        l->setAutoFillBackground(false);
        l->setFrameShape(QFrame::NoFrame);
        l->setFrameShadow(QFrame::Plain);
        l->setAlignment(Qt::AlignCenter);
    }

    // Texts
    this->setWindowTitle("Manage Admin Events");

    tableWidgetEvents->setHorizontalHeaderItem(0, __qtablewidgetitem);
    tableWidgetEvents->setHorizontalHeaderItem(1, __qtablewidgetitem1);
    tableWidgetEvents->setHorizontalHeaderItem(2, __qtablewidgetitem2);
    tableWidgetEvents->setHorizontalHeaderItem(3, __qtablewidgetitem3);
    tableWidgetEvents->setHorizontalHeaderItem(4, __qtablewidgetitem4);

    tableWidgetEvents->horizontalHeaderItem(0)->setText("Title");
    tableWidgetEvents->horizontalHeaderItem(1)->setText("Description");
    tableWidgetEvents->horizontalHeaderItem(2)->setText("Date and Time");
    tableWidgetEvents->horizontalHeaderItem(3)->setText("Participants");
    tableWidgetEvents->horizontalHeaderItem(4)->setText("Link");

    tableWidgetEvents->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    tableWidgetEvents->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    tableWidgetEvents->horizontalHeader()->setStretchLastSection(true);


    tableWidgetEvents->setEditTriggers(QAbstractItemView::NoEditTriggers);
    tableWidgetEvents->setSelectionMode(QAbstractItemView::NoSelection);
    tableWidgetEvents->setFocusPolicy(Qt::NoFocus);

    groupBox->setTitle("Add new event");
    label->setText("Title:");
    label_3->setText("Description:");
    label_4->setText("Date:");
    label_6->setText("Participants:");
    label_7->setText("Link:");
    labelErrorAdd->setText("");
    pushButtonAdd->setText("Add");

    groupBox_3->setTitle("Remove event");
    label_2->setText("Title:");
    labelErrorRemove->setText("");
    pushButtonRemove->setText("Remove");

    groupBox_2->setTitle("Update event");
    label_5->setText("Title:");
    label_8->setText("New Description:");
    label_9->setText("New Date:");
    label_10->setText("New Participants:");
    label_11->setText("New Link:");
    labelErrorUpdate->setText("");
    pushButtonUpdate->setText("Update");
}

void AdminForm::on_pushButtonAdd_clicked()
{
    if (lineEditTitleAdd->text() == "" || lineEditDescriptionAdd->text() == "" ||
        lineEditDateAdd->text() == "" || lineEditPartAdd->text() == "" || lineEditLinkAdd->text() == "")
    {
        labelErrorAdd->setStyleSheet("color:#822d27");
        labelErrorAdd->setText("Data is not complete.");
        return;
    }

    try {
        labelErrorAdd->setStyleSheet("color:#549150");
        Event newEvent = Event(lineEditTitleAdd->text().toStdString(), lineEditDescriptionAdd->text().toStdString(),
            lineEditDateAdd->text().toStdString(), std::stoi(lineEditPartAdd->text().toStdString()), lineEditLinkAdd->text().toStdString());
        cmdManager->CommandExecute(new AddCommand(serv, nullptr, newEvent, AdminService));

        //serv->AddEvent(Event(lineEditTitleAdd->text().toStdString(), lineEditDescriptionAdd->text().toStdString(),
        //    lineEditDateAdd->text().toStdString(), std::stoi(lineEditPartAdd->text().toStdString()), lineEditLinkAdd->text().toStdString()));

        int newRow = tableWidgetEvents->rowCount();
        tableWidgetEvents->insertRow(newRow);

        QTableWidgetItem* token0 = new QTableWidgetItem;
        QTableWidgetItem* token1 = new QTableWidgetItem;
        QTableWidgetItem* token2 = new QTableWidgetItem;
        QTableWidgetItem* token3 = new QTableWidgetItem;

        QLabel* token4 = new QLabel();
        token4->setText("<a href='" + QString(serv->repo->events[newRow].link.c_str()) + "'>" + QString(serv->repo->events[newRow].link.c_str()) + "</a>");
        token4->setTextFormat(Qt::RichText);
        token4->setTextInteractionFlags(Qt::TextBrowserInteraction);
        token4->setOpenExternalLinks(true);


        token0->setText(QString(serv->repo->events[newRow].title.c_str()));
        token1->setText(QString(serv->repo->events[newRow].description.c_str()));
        token2->setText(QString(serv->repo->events[newRow].dt.c_str()));
        token3->setText(QString(std::to_string(serv->repo->events[newRow].nr_of_people).c_str()));

        tableWidgetEvents->setItem(newRow, 0, token0);
        tableWidgetEvents->setItem(newRow, 1, token1);
        tableWidgetEvents->setItem(newRow, 2, token2);
        tableWidgetEvents->setItem(newRow, 3, token3);
        tableWidgetEvents->setCellWidget(newRow, 4, token4);

        labelErrorAdd->setText("Event has been added.");
    }
    catch (const std::exception& e) {
        labelErrorAdd->setStyleSheet("color:#822d27");
        labelErrorAdd->setText(e.what());
    }
}

void AdminForm::on_pushButtonRemove_clicked()
{
    if (lineEditEventRemove->text() == "") {
        labelErrorRemove->setStyleSheet("color:#822d27");
        labelErrorRemove->setText("You should provide a title.");
        return;
    }

    try {
        labelErrorRemove->setStyleSheet("color:#549150");
        Event event = Event();
        event.title = lineEditEventRemove->text().toStdString();
        cmdManager->CommandExecute(new RemoveCommand(serv, nullptr, serv->repo->events[serv->FindEvent(event)], AdminService));
        //serv->RemoveEvent(lineEditEventRemove->text().toStdString());
        labelErrorRemove->setText("Event removed.");
        StoreData();
    }
    catch (const std::exception& e) {
        labelErrorRemove->setStyleSheet("color:#822d27");
        labelErrorRemove->setText(e.what());
    }
}

void AdminForm::on_pushButtonUpdate_clicked()
{
    if (lineEditTitleUpdate->text() == "" || lineEditDescriptionUpdate->text() == "" ||
        lineEditDateUpdate->text() == "" || lineEditPartUpdate->text() == "" || lineEditLinkUpdate->text() == "")
    {
        labelErrorUpdate->setStyleSheet("color:#822d27");
        labelErrorUpdate->setText("Data is not complete.");
        return;
    }

    try {
        labelErrorUpdate->setStyleSheet("color:#549150");

        Event auxEvent = Event(), newEvent = Event(lineEditTitleUpdate->text().toStdString(), lineEditDescriptionUpdate->text().toStdString(),
            lineEditDateUpdate->text().toStdString(), std::stoi(lineEditPartUpdate->text().toStdString()), lineEditLinkUpdate->text().toStdString());

        auxEvent.title = lineEditTitleUpdate->text().toStdString();
        cmdManager->CommandExecute(new UpdateCommand(serv, nullptr, newEvent, serv->repo->events[serv->FindEvent(auxEvent)], AdminService));

       /* serv->UpdateEvent(auxEvent, Event(lineEditTitleUpdate->text().toStdString(), lineEditDescriptionUpdate->text().toStdString(),
            lineEditDateUpdate->text().toStdString(), std::stoi(lineEditPartUpdate->text().toStdString()), lineEditLinkUpdate->text().toStdString()));*/
        StoreData();
        labelErrorUpdate->setText("Event has been updated.");
    }
    catch (const std::exception& e) {
        labelErrorUpdate->setStyleSheet("color:#822d27");
        labelErrorUpdate->setText(e.what());
    }
}

void AdminForm::on_undoShortcut_activated() {
    on_pushButtonUndo_clicked();
}

void AdminForm::on_redoShortcut_activated() {
    on_pushButtonRedo_clicked();
}

void AdminForm::on_pushButtonUndo_clicked() {
    cmdManager->CommandUndo();
    StoreData();
}

void  AdminForm::on_pushButtonRedo_clicked() {
    cmdManager->CommandRedo();
    StoreData();
}

void AdminForm::closeEvent(QCloseEvent* event)
{
    this->close();

    lineEditEventRemove->clear();
    labelErrorRemove->clear();

    lineEditTitleAdd->clear();
    lineEditDescriptionAdd->clear();
    lineEditDateAdd->clear();
    lineEditPartAdd->clear();
    lineEditLinkAdd->clear();
    labelErrorAdd->clear();

    lineEditTitleUpdate->clear();
    lineEditDescriptionUpdate->clear();
    lineEditDateUpdate->clear();
    lineEditPartUpdate->clear();
    lineEditLinkUpdate->clear();
    labelErrorUpdate->clear();

    mainWindow->show();
    event->accept();
}