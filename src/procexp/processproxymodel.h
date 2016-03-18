#ifndef PROCESSPROXYMODEL_H
#define PROCESSPROXYMODEL_H


#include <QSortFilterProxyModel>

class ProcessProxyModel : public QSortFilterProxyModel
{

public:
    ProcessProxyModel(QObject* parent = 0);
    virtual ~ProcessProxyModel();

protected:
    bool filterAcceptsRow(int source_row, const QModelIndex &source_parent) const Q_DECL_OVERRIDE;
};

#endif // PROCESSPROXYMODEL_H
