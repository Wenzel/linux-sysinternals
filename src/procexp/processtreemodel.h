#ifndef PROCESSTREEMODEL_H
#define PROCESSTREEMODEL_H

#include <QAbstractItemModel>
#include <QString>
#include <QVariant>
#include <QModelIndex>

#include "treeitem.h"
#include "sysinfo.h"

class ProcessTreeModel : public QAbstractItemModel
{
    Q_OBJECT

public:
    explicit ProcessTreeModel(QObject* parent = nullptr);
    ~ProcessTreeModel();

    QVariant headerData(int section, Qt::Orientation orientation,
                        int role = Qt::DisplayRole) const Q_DECL_OVERRIDE;
    Qt::ItemFlags flags(const QModelIndex &index) const Q_DECL_OVERRIDE;
    int rowCount(const QModelIndex &parent = QModelIndex()) const Q_DECL_OVERRIDE;
    int columnCount(const QModelIndex &parent = QModelIndex()) const Q_DECL_OVERRIDE;
    QModelIndex index(int row, int column,
                      const QModelIndex &parent = QModelIndex()) const Q_DECL_OVERRIDE;
    QModelIndex parent(const QModelIndex &index) const Q_DECL_OVERRIDE;
    QVariant data(const QModelIndex &index, int role) const Q_DECL_OVERRIDE;
private:
    TreeItem *insertProcess(int pid);

    TreeItem *m_root;
};

#endif // PROCESSTREEMODEL_H
