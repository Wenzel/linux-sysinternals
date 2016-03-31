#ifndef TREEITEM_H
#define TREEITEM_H

#include <QList>
#include <QVariant>

#include "processinfo.h"

class TreeItem
{
public:
    explicit TreeItem(ProcessInfo *pinfo, TreeItem* parent = nullptr);
    ~TreeItem();

    void appendChild(TreeItem* child);
    bool deleteChild(TreeItem* child);
    TreeItem* child(int row);
    int childCount() const;
    int columnCount() const;
    int row() const;
    TreeItem *parent();
    void setParent(TreeItem* item);

    TreeItem* findPid(int pid);
    void invalidateData();
    void display();
    ProcessInfo* pinfo();

private:
    QList<TreeItem*> m_children;
    ProcessInfo* m_pinfo;
    TreeItem *m_parent;
};

#endif // TREEITEM_H
