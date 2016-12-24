#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "QDebug"
#include "QMessageBox"
#include "QUuid"
#include "QSqlError"
#include "QSqlQuery"
#include "QSqlRecord"
#include "stockdelegate.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::init(QSqlDatabase *db) {
    this->initializeTable();
    this->initializeModel(db);
}

void MainWindow::initializeTable() {
    this->table = new QTableView();;
    this->ui->gridLayout->addWidget(this->table);
    this->table->show();
}

void MainWindow::initializeModel(QSqlDatabase *db)
{
    //this->executeQuery(*db, "DROP TABLE IF EXISTS stock;");
    this->executeQuery(*db, "create table if not exists \"stock\" ("
                       "ID int primary key, "
                       "WKN VARCHAR(255), "
                       "name VARCHAR(255) DEFAULT '', "
                       "bought INTEGER DEFAULT NULL, "
                       "sold INTEGER DEFAULT NULL, "
                       "purchasePrice REAL DEFAULT 0, "
                       "salePrice REAL DEFAULT 0)");

    this->model = new StockModel(this, *db);
    this->table->setModel(this->model);
    this->table->setItemDelegate(new StockDelegate(table));
    this->model->setTable("stock");
    this->model->setEditStrategy(QSqlRelationalTableModel::OnFieldChange);
    if (!this->model->select())
    {
        QSqlError err = this->model->lastError();
        QMessageBox::information(0,
                                 qApp->tr("Failed to select data from table"),
                                 err.text(),
                                 QMessageBox::Ok);
    }

    this->model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
    this->model->setHeaderData(1, Qt::Horizontal, QObject::tr("WKN"));
    this->model->setHeaderData(2, Qt::Horizontal, QObject::tr("Name"));
    this->model->setHeaderData(3, Qt::Horizontal, QObject::tr("Gekauft am"));
    this->model->setHeaderData(4, Qt::Horizontal, QObject::tr("Verkauft am"));
    this->model->setHeaderData(5, Qt::Horizontal, QObject::tr("Kaufpreis"));
    this->model->setHeaderData(6, Qt::Horizontal, QObject::tr("Verkaufspreis"));

    this->model->insertColumn(7);
    this->model->setHeaderData(7, Qt::Horizontal, QObject::tr("Delta"));

    qDebug() << this->model->lastError().text();
    qDebug() << this->model->rowCount();
    qDebug() << this->model->columnCount();

    this->table->setColumnHidden(0, true);
}

void MainWindow::executeQuery(QSqlDatabase db, QString query)
{
    QSqlQuery q(db);
    if(!q.exec(query)) {
        qDebug() << "Execute query error: " << q.lastError().text();
    }
}

void MainWindow::addEntry(QString ISIN, QString name) {
    QUuid uuid = QUuid::createUuid();
    Q_CHECK_PTR(this->model);
    //QSqlRelationalTableModel *this->model = (QSqlRelationalTableModel*)this->table->this->model();
    QSqlRecord record = this->model->record();
    record.setValue(0,QVariant(uuid.toString()));
    record.setValue(1,QVariant(ISIN)); //tr("hello2")));
    record.setValue(2,QVariant(name));
    this->model->insertRecord(this->model->rowCount(),record);
}

void MainWindow::on_actionEintrag_hinzuf_gen_triggered()
{
    this->addEntry("ISIN", "Name");
}

void MainWindow::on_actionEintrag_l_schen_triggered()
{
    int rowIdx = this->table->currentIndex().row();
    this->model->removeRow(rowIdx);
    this->model->submitAll();
}
