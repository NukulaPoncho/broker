#ifndef STOCKDELEGATE_H
#define STOCKDELEGATE_H

#include "QSqlRelationalDelegate"

class StockDelegate : public QSqlRelationalDelegate
{
public:
    StockDelegate(QObject *aParent = 0);

    void paint(QPainter *painter, const QStyleOptionViewItem &option,
                   const QModelIndex &index) const;
    QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option,
                              const QModelIndex &index) const;
};

#endif // STOCKDELEGATE_H
