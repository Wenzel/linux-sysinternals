#include <QStack>

#include "processtreemodel.h"
#include "../convert.h"

ProcessTreeModel::ProcessTreeModel(QObject* parent)
    : QAbstractItemModel(parent)
{
    m_headers << "Process" << "PID" << "% CPU" << "IO B/s";
    // create root item
    m_root = new TreeItem(nullptr);

    std::vector<int> pids = processListPid();

    for (int pid : pids)
    {
        insertProcess(pid);
        m_set_pid.insert(pid);
    }

    QDBusConnection bus = QDBusConnection::systemBus();
    bus.connect("", "", HELPER_SERVICE, "fork", this, SLOT(processForked(int,int,int,int)));
    bus.connect("", "", HELPER_SERVICE, "exec", this, SLOT(processExecuted(int,int)));
    bus.connect("", "", HELPER_SERVICE, "exit", this, SLOT(processExited(int,int,uint)));

    // start timer to refresh data
    m_timer_id = startTimer(2000);
}

ProcessTreeModel::~ProcessTreeModel()
{
    if (m_root != nullptr)
        delete m_root;
}

void ProcessTreeModel::timerEvent(QTimerEvent *event)
{
    Q_UNUSED(event);

    // invalidate all data
    m_root->invalidateData();

    QModelIndex topleft = index(0, 2);
    QModelIndex bottomright = index(rowCount() - 1, columnCount() - 1);
    emit dataChanged(topleft, bottomright);

}

QVariant ProcessTreeModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (orientation == Qt::Horizontal && role == Qt::DisplayRole)
        return m_headers[section];

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
    {
        QVariant data = item->data(index.column());

//        if (index.column() == 0)
//            std::cout << TOSTDSTRING(data.toString()) << std::endl;
//        if (index.column() == 3)
//            std::cout << data.toDouble() << std::endl;
        if (index.column() == 2 || index.column() == 3)
            if (data.toInt() == 0)
                data = "";

        return data;
    }
    return QVariant();
}

TreeItem* ProcessTreeModel::insertProcess(int pid)
{
    // already inserted ?
    if (m_root->findPid(pid) != nullptr)
        return nullptr;

    ProcessInfo* pinfo = new ProcessInfo(pid);
    // look for parent in our tree
    int ppid = pinfo->ppid();

    // find parent
    TreeItem* parent;
    if (ppid == 0)
        parent = m_root;
    else
    {
        // parent already inserted in the tree ?
        parent = m_root->findPid(ppid);
        if (parent == nullptr)
        {
            // no present, insert it
            parent = insertProcess(ppid);
        }
    }
    // insert as child
    TreeItem* item = new TreeItem(pinfo);
    parent->appendChild(item);
    return item;
}

void ProcessTreeModel::processForked(int parent_pid, int parent_tgid, int child_pid, int child_tgid)
{
    Q_UNUSED(parent_pid);
    Q_UNUSED(parent_tgid);
    Q_UNUSED(child_pid);
    Q_UNUSED(child_tgid);
    //    ProcessInfo parent(parent_pid);
    //    ProcessInfo child(child_pid);
    //    std::cout << "[FORK] " << "(" << parent_pid << ") " << parent.exe() << " -> " <<"(" << child_pid << ") " << child.exe() << std::endl;
}

void ProcessTreeModel::processExecuted(int process_pid, int process_tgid)
{
    Q_UNUSED(process_tgid);
    ProcessInfo* pinfo = new ProcessInfo(process_pid);
    // std::cout << "[EXEC] " << "(" << process_pid << ") " << p.exe() << ", parent " << p.ppid() << std::endl;

    // check is process is not already in our tree
    if (!m_set_pid.contains(process_pid))
    {
        // insert into tree
        // find parent QModelIndex
        QModelIndexList list = match(index(0,1), Qt::DisplayRole, pinfo->ppid(), 1, Qt::MatchRecursive | Qt::MatchExactly);
        if (list.size() == 1)
        {
            QModelIndex parent_index = list.at(0);
            // parent_index doesn't work if we use it in beginInsertRows
            // we have to build our own QModelIndex with index()
            parent_index = index(parent_index.row(), 0, parent_index.parent());
            TreeItem* parent_item = static_cast<TreeItem*>(parent_index.internalPointer());
            // find last child
            int nb_child = rowCount(parent_index);
            int first;
            int last;
            if (nb_child == 0)
            {
                first = 0;
                last = 0;
            }
            else
            {
                QModelIndex last_child = parent_index.child(nb_child - 1, 0);
                first = last_child.row();
                last = last_child.row();
            }
            // start insert
            beginInsertRows(parent_index, first, last);
            // create new item
            TreeItem* new_item = new TreeItem(pinfo);
            // append to parent item
            parent_item->appendChild(new_item);
            m_set_pid.insert(process_pid);
            endInsertRows();
        }
    }
}

void ProcessTreeModel::processExited(int process_pid, int process_tgid, uint exit_code)
{
    Q_UNUSED(process_tgid);
    Q_UNUSED(exit_code);
    //     std::cout << "[EXIT] " << process_pid << " -> " << exit_code << std::endl;

    // check if this pid is in our set
    if (m_set_pid.contains(process_pid))
    {
        QModelIndexList list = match(index(0,1), Qt::DisplayRole, process_pid, 1, Qt::MatchRecursive | Qt::MatchExactly);
        if (list.size() == 1)
        {
            QModelIndex item_index = list.at(0);
            item_index = index(item_index.row(), 0, item_index.parent());
            beginRemoveRows(item_index.parent(), item_index.row(), item_index.row());
            TreeItem* item = static_cast<TreeItem*>(item_index.internalPointer());
            TreeItem* parent = item->parent();
            parent->deleteChild(item);
            m_set_pid.remove(process_pid);
            endRemoveRows();
        }
    }
}
