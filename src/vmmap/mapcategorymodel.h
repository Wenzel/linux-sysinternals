#ifndef MAPCATEGORYMODEL_H
#define MAPCATEGORYMODEL_H

#include <QAbstractListModel>
#include <QHash>

#include "processinfo.h"
#include "../convert.h"

class MapCategoryModel : public QAbstractListModel
{
    Q_OBJECT

public:
    MapCategoryModel(const QStringList& headers, const std::vector<MMap>& maps, QObject* parent = nullptr);

    int rowCount(const QModelIndex & parent = QModelIndex()) const;
    int columnCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex & index, int role = Qt::DisplayRole) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const;
    QString categoryAt(int row) const;

private:
    void addMap(const QString& category, const MMap& map);

    QList<QList<QString>*> m_data;
    QStringList m_headers;
};

#endif // MAPCATEGORYMODEL_H
