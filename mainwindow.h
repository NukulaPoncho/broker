#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTableView>
#include <stockmodel.h>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void init(QSqlDatabase *db);
    void addEntry(QString ISIN, QString name);

protected:
    void initializeTable();
    void initializeModel(QSqlDatabase *db);
    void executeQuery(QSqlDatabase db, QString query);

private slots:
    void on_actionEintrag_hinzuf_gen_triggered();

    void on_actionEintrag_l_schen_triggered();

private:
    Ui::MainWindow *ui;
    QTableView *table;
    StockModel *model;
};

#endif // MAINWINDOW_H
