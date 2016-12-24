#include "stockmodel.h"
#include "QDate"
#include "QColor"

StockModel::StockModel(QObject *parent,
                       QSqlDatabase db) : QSqlRelationalTableModel(parent, db)
{

}

QVariant StockModel::data(const QModelIndex& index, int role) const
{
    if (!index.isValid())
        return QModelIndex();

    // get the actual value from base class
    QVariant value = QSqlTableModel::data(index, role);

    // do adjustments if necessary
    if (role == Qt::DisplayRole && (index.column() == ColumnIndex::PurchasePrice || index.column() == ColumnIndex::SoldPrice))
    {
        value = value.toString() + " €";
    }
    else if (role == Qt::DisplayRole && (index.column() == ColumnIndex::Profit))
    {
        const double purchase = QSqlTableModel::data(index.sibling(index.row(), ColumnIndex::PurchasePrice), role).toDouble();
        const double sale = QSqlTableModel::data(index.sibling(index.row(), ColumnIndex::SoldPrice), role).toDouble();
        value = QString::number(sale - purchase) + " €";
    }

    if(role == Qt::TextAlignmentRole && (index.column() >= ColumnIndex::PurchasePrice && index.column() <= ColumnIndex::Profit))
    {
        int flags = 0;
        flags |= Qt::AlignVCenter;
        flags |= Qt::AlignRight;
        return flags;
    }

    if(role == Qt::ForegroundRole && index.column() == ColumnIndex::Profit)
    {
        const double purchase = QSqlTableModel::data(index.sibling(index.row(), ColumnIndex::PurchasePrice), Qt::DisplayRole).toDouble();
        const double sale = QSqlTableModel::data(index.sibling(index.row(), ColumnIndex::SoldPrice), Qt::DisplayRole).toDouble();
        double result = sale - purchase;
        if(result > 0) {
            return QVariant(QColor(Qt::darkGreen));
        }
        else if(result < 0)
        {
            return QVariant(QColor(Qt::red));
        }
    }

    return value;
}

bool StockModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    QVariant val = value;
    if(index.column() == ColumnIndex::PurchasePrice || index.column() == ColumnIndex::SoldPrice) {
        val.convert(QMetaType::Double);
    }

    if(index.column() == ColumnIndex::SoldDate || index.column() == ColumnIndex::BoughtDate) {
        val.convert(QMetaType::QDate);
    }

    bool r= QSqlTableModel::setData(index,val,role);
    return r;
}
