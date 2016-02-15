#ifndef MAPDETAILTREEMODEL_H
#define MAPDETAILTREEMODEL_H

#include <QAbstractItemModel>
#include <QString>
#include <QVariant>
#include <QModelIndex>
#include <QColor>

#include "treeitem.h"
#include "mmap.h"

class MapDetailTreeModel : public QAbstractItemModel
{
    Q_OBJECT

public:
    explicit MapDetailTreeModel(const QStringList& headers, const std::vector<MMap>& maps, QObject* parent = nullptr);
    ~MapDetailTreeModel();

    QVariant headerData(int section, Qt::Orientation orientation,
                        int role = Qt::DisplayRole) const Q_DECL_OVERRIDE;
    Qt::ItemFlags flags(const QModelIndex &index) const Q_DECL_OVERRIDE;
    int rowCount(const QModelIndex &parent = QModelIndex()) const Q_DECL_OVERRIDE;
    int columnCount(const QModelIndex &parent = QModelIndex()) const Q_DECL_OVERRIDE;
    QModelIndex index(int row, int column,
                      const QModelIndex &parent = QModelIndex()) const Q_DECL_OVERRIDE;
    QModelIndex parent(const QModelIndex &index) const Q_DECL_OVERRIDE;
    QVariant data(const QModelIndex &index, int role) const Q_DECL_OVERRIDE;

    static QColor getCategoryColor(const QString& category);
private:

    TreeItem *m_root;
};

#endif // MAPDETAILTREEMODEL_H
