#include "mapdetailtreemodel.h"
#include "../convert.h"

QColor MapDetailTreeModel::getCategoryColor(const QString &category)
{
    if (category == "Image")
        return Qt::GlobalColor::magenta;
    else if (category == "Heap")
        return Qt::GlobalColor::red;
    else if (category == "Stack")
        return Qt::GlobalColor::darkYellow;
    else if (category == "Shareable")
        return Qt::GlobalColor::cyan;
    else if (category == "Mapped File")
        return Qt::GlobalColor::green;
    else if (category == "Private")
        return Qt::GlobalColor::yellow;
    else // Total
        return Qt::GlobalColor::gray;
}

MapDetailTreeModel::MapDetailTreeModel(const QStringList& headers, const std::vector<MMap> &maps, QObject* parent)
{
    // convert QStringList to QList<QVariant>
    QList<QVariant> hdr;
    for (const QString& s : headers)
        hdr << s;
    // build root item and store headers
    m_root = new TreeItem(hdr);

    for (const MMap& map : maps)
    {
        TreeItem* item;
        QList<QVariant> data;
        data << TOQSTRING(map.addressFrom());
        data << TOQSTRING(map.category());
        data << map.size();
        data << TOQSTRING(map.path());
        item = new TreeItem(data);
        m_root->appendChild(item);
    }
}

MapDetailTreeModel::~MapDetailTreeModel()
{
    delete m_root;
}

QVariant MapDetailTreeModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (orientation == Qt::Horizontal && role == Qt::DisplayRole)
        return m_root->data(section);

    return QVariant();
}

Qt::ItemFlags MapDetailTreeModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return 0;

    // return default flags (read only)
    return QAbstractItemModel::flags(index);
}

int MapDetailTreeModel::rowCount(const QModelIndex &parent) const
{
    TreeItem *parentItem;

    if (!parent.isValid())
        parentItem = m_root;
    else
        parentItem = static_cast<TreeItem*>(parent.internalPointer());

    return parentItem->childCount();
}

int MapDetailTreeModel::columnCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return static_cast<TreeItem*>(parent.internalPointer())->columnCount();
    else
        return m_root->columnCount();
}

QModelIndex MapDetailTreeModel::index(int row, int column, const QModelIndex &parent)
const
{
    if (!hasIndex(row, column, parent))
        return QModelIndex();

    TreeItem *parentItem;

    if (!parent.isValid())
        parentItem = m_root;
    else
        parentItem = static_cast<TreeItem*>(parent.internalPointer());

    TreeItem *childItem = parentItem->child(row);
    if (childItem)
        return createIndex(row, column, childItem);
    else
        return QModelIndex();
}

QModelIndex MapDetailTreeModel::parent(const QModelIndex &index) const
{
    if (!index.isValid())
        return QModelIndex();

    TreeItem *childItem = static_cast<TreeItem*>(index.internalPointer());
    TreeItem *parentItem = childItem->parent();

    if (parentItem == m_root)
        return QModelIndex();

    return createIndex(parentItem->row(), 0, parentItem);
}


QVariant MapDetailTreeModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    TreeItem *item = static_cast<TreeItem*>(index.internalPointer());
    if (role == Qt::DisplayRole)
        return item->data(index.column());
    else if (role == Qt::BackgroundRole)
    {
        QString category = item->data(1).toString();
        return QVariant(MapDetailTreeModel::getCategoryColor(category));
    }
    return QVariant();
}


