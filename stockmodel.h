#ifndef STOCKMODEL_H
#define STOCKMODEL_H

#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlRelationalTableModel>

enum ColumnIndex {
    Id = 0,
    WKN = 1,
    Name = 2,
    BoughtDate = 3,
    SoldDate = 4,
    PurchasePrice = 5,
    SoldPrice = 6,
    Profit = 7
};

class StockModel : public QSqlRelationalTableModel
{
public:
    StockModel(QObject *parent = Q_NULLPTR,
               QSqlDatabase db = QSqlDatabase());

    QVariant data(const QModelIndex& index, int role) const;
    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole);
};

#endif // STOCKMODEL_H
