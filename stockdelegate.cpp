#include "stockdelegate.h"
#include "QDateEdit"
#include "QDebug"
#include "stockmodel.h"

StockDelegate::StockDelegate(QObject *aParent) : QSqlRelationalDelegate(aParent)
{

}

void StockDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
   /* if (index.data().canConvert<QDateEdit>()) {
        QDateEdit edit = qvariant_cast<QDateEdit>(index.data());
           qDebug() << "yeah";
        QSqlRelationalDelegate::paint(painter, option, index);
    } else {
        QSqlRelationalDelegate::paint(painter, option, index);
    }
    */
    QSqlRelationalDelegate::paint(painter, option, index);
}

QWidget *StockDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    if (index.column() == ColumnIndex::SoldDate || index.column() == ColumnIndex::BoughtDate) {
        QDateEdit *edit = new QDateEdit(parent);
        edit->setDate(QDate::currentDate());
        return edit;
    } else {
        return QSqlRelationalDelegate::createEditor(parent, option, index);
    }
}
