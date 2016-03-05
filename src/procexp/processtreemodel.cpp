#include "processtreemodel.h"
#include "../convert.h"

ProcessTreeModel::ProcessTreeModel(QObject* parent)
    : QAbstractItemModel(parent)
{
    QList<QVariant> headers;
    headers << "Process" << "PID";
    // create root item
    m_root = new TreeItem(headers);

    std::vector<int> pids = processListPid();

    for (int pid : pids)
    {
        insertProcess(pid);
    }
}

ProcessTreeModel::~ProcessTreeModel()
{
    if (m_root != nullptr)
        delete m_root;
}

QVariant ProcessTreeModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (orientation == Qt::Horizontal && role == Qt::DisplayRole)
        return m_root->data(section);

    return QVariant();
}

Qt::ItemFlags ProcessTreeModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return 0;

    // return default flags (read only)
    return QAbstractItemModel::flags(index);
}

int ProcessTreeModel::rowCount(const QModelIndex &parent) const
{
    TreeItem *parentItem;

    if (!parent.isValid())
        parentItem = m_root;
    else
        parentItem = static_cast<TreeItem*>(parent.internalPointer());

    return parentItem->childCount();
}

int ProcessTreeModel::columnCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return static_cast<TreeItem*>(parent.internalPointer())->columnCount();
    else
        return m_root->columnCount();
}

QModelIndex ProcessTreeModel::index(int row, int column, const QModelIndex &parent)
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

QModelIndex ProcessTreeModel::parent(const QModelIndex &index) const
{
    if (!index.isValid())
        return QModelIndex();

    TreeItem *childItem = static_cast<TreeItem*>(index.internalPointer());
    TreeItem *parentItem = childItem->parent();

    if (parentItem == m_root)
        return QModelIndex();

    return createIndex(parentItem->row(), 0, parentItem);
}


QVariant ProcessTreeModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    TreeItem *item = static_cast<TreeItem*>(index.internalPointer());

    if (role == Qt::DisplayRole)
        return item->data(index.column());

    return QVariant();
}

TreeItem* ProcessTreeModel::insertProcess(int pid)
{
    ProcessInfo pinfo = ProcessInfo(pid);
    std::cout << pid << ", " << pinfo.ppid() << std::endl;
    // look for parent in our tree
    int ppid = pinfo.ppid();

    // find parent
    TreeItem* parent;
    if (ppid == 0)
        parent = m_root;
    else
    {
        parent = m_root->findPid(ppid);
        if (parent == nullptr)
            parent = insertProcess(ppid);
    }
    QList<QVariant> data;
    data << TOQSTRING(pinfo.name()) << pinfo.pid();
    TreeItem* item = new TreeItem(data);
    parent->appendChild(item);
    return item;
}
