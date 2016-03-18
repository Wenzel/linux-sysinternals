#include "processproxymodel.h"
#include <iostream>

ProcessProxyModel::ProcessProxyModel(QObject *parent)
    : QSortFilterProxyModel(parent)
{

}

ProcessProxyModel::~ProcessProxyModel()
{

}

bool ProcessProxyModel::filterAcceptsRow(int source_row, const QModelIndex &source_parent) const
{
    QList<QString> row_data;

    QModelIndex name_index = sourceModel()->index(source_row, 0, source_parent);
    QModelIndex pid_index = sourceModel()->index(source_row, 1, source_parent);

    QString name = sourceModel()->data(name_index).toString();
    QString pid = sourceModel()->data(pid_index).toString();

    row_data << name;
    row_data << pid;

    for (const QString& str : row_data)
        if (str.contains(filterRegExp()))
            return true;

    // search in children
    QModelIndex child_parent = name_index;
    int nb_child = sourceModel()->rowCount(child_parent);
    for (int i = 0; i < nb_child; i++)
    {
        QModelIndex child_index = child_parent.child(i, 0);
        if (filterAcceptsRow(i, child_parent))
            return true;
    }

    // this tree doesn't match the regexp
    return false;
}
