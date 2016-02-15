#include "mapcategorymodel.h"
#include "mapdetailtreemodel.h"

MapCategoryModel::MapCategoryModel(const QStringList &headers, const std::vector<MMap>& maps, QObject *parent)
    : m_headers(headers)
{
    QStringList list_category_done;
    for (const MMap& map : maps)
    {
        QList<QString>* list;
        QString category = TOQSTRING(map.category());
        int index = list_category_done.indexOf(category);
        if (index == -1)
        {
            list_category_done.append(category);
            list = new QList<QString>();
            list->append("");
            list->append("");
            m_data.append(list);
        }
        else
            list = m_data.at(index);

        list->replace(0, category); // type
        int size = list->at(1).toInt();
        size += map.size();
        list->replace(1, QString::number(size));

    }
    // add total
    QList<QString>* list = new QList<QString>();
    list->append("Total");
    int total_size = 0;
    for (QList<QString>* l : m_data)
    {
        int size = l->at(1).toInt();
        total_size += size;
    }
    list->append(QString::number(total_size));
    m_data.append(list);
}

int MapCategoryModel::rowCount(const QModelIndex &parent) const
{
    return m_data.size();
}

int MapCategoryModel::columnCount(const QModelIndex &parent) const
{
    return 2;
}

QVariant MapCategoryModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    if (role == Qt::DisplayRole)
    {
        QList<QString>* list = m_data.at(index.row());
        return list->at(index.column());
    }
    else if (role == Qt::BackgroundColorRole)
    {
        QList<QString>* list = m_data.at(index.row());
        return QVariant(MapDetailTreeModel::getCategoryColor(list->at(0)));
    }

    return QVariant();
}

QVariant MapCategoryModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (orientation == Qt::Horizontal and role == Qt::DisplayRole)
        return m_headers[section];
    return QVariant();
}

void MapCategoryModel::addMap(const QString &category, const MMap &map)
{

}

QString MapCategoryModel::categoryAt(int row) const
{
    return m_data.at(row)->at(0);
}
