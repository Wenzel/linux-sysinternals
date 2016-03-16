#ifndef TREEITEM_H
#define TREEITEM_H

#include <QList>
#include <QVariant>

class TreeItem
{
public:
    explicit TreeItem(const QList<QVariant>& data, TreeItem* parent = nullptr);
    ~TreeItem();

    void appendChild(TreeItem* child);
    bool deleteChild(TreeItem* child);
    TreeItem* child(int row);
    int childCount() const;
    int columnCount() const;
    QVariant data(int column) const;
    int row() const;
    TreeItem *parent();
    void setParent(TreeItem* item);

    TreeItem* findPid(int pid);
    void display();

private:
    QList<TreeItem*> m_children;
    QList<QVariant> m_data;
    TreeItem *m_parent;
};

#endif // TREEITEM_H
