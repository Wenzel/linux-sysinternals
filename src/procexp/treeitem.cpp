#include <iostream>
#include "../convert.h"
#include "treeitem.h"

TreeItem::TreeItem(ProcessInfo* pinfo, TreeItem* parent)
    : m_pinfo(pinfo),
      m_parent(parent)
{

}

TreeItem::~TreeItem()
{
    qDeleteAll(m_children);
    if (m_pinfo != nullptr)
        delete m_pinfo;
}

void TreeItem::appendChild(TreeItem *item)
{
    m_children.append(item);
    item->setParent(this);
}

bool TreeItem::deleteChild(TreeItem *child)
{
    return m_children.removeOne(child);
}

TreeItem *TreeItem::child(int row)
{
    return m_children.value(row);
}

int TreeItem::childCount() const
{
    return m_children.count();
}

int TreeItem::row() const
{
    if (m_parent)
        return m_parent->m_children.indexOf(const_cast<TreeItem*>(this));

    return 0;
}

int TreeItem::columnCount() const
{
    return 4;
}

TreeItem *TreeItem::parent()
{
    return m_parent;
}

void TreeItem::setParent(TreeItem *item)
{
    m_parent = item;
}

TreeItem* TreeItem::findPid(int pid)
{
    if (m_parent != nullptr && m_pinfo->pid() == pid)
        return this;
    // find in children
    for (TreeItem* item : m_children)
    {
        TreeItem* found = item->findPid(pid);
        if (found == nullptr)
            continue;
        else
            return found;
    }

    // not found
    return nullptr;
}

void TreeItem::invalidateData()
{
    // invalidate current node
    if (m_parent != nullptr)
        m_pinfo->needUpdate();
    // invalidate children
    for (TreeItem* item : m_children)
        item->invalidateData();
}

void TreeItem::display()
{
    // display root
    std::cout << "node " << m_pinfo->name() << " : " << m_pinfo->pid() << std::endl;
    for (TreeItem* item : m_children)
        item->display();
}

ProcessInfo* TreeItem::pinfo()
{
    return m_pinfo;
}
