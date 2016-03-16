#ifndef PROCESSTREEMODEL_H
#define PROCESSTREEMODEL_H

#include <QAbstractItemModel>
#include <QString>
#include <QVariant>
#include <QModelIndex>
#include <QtDBus/QDBusConnection>
#include <QtDBus/QDBusConnectionInterface>
#include <QSet>

#include "treeitem.h"
#include "sysinfo.h"

#define HELPER_SERVICE "com.procexp.helper"
#define HELPER_PATH "/"

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

    // properties
    TreeItem *m_root;
    QSet<int> m_set_pid;

private slots:
    void processForked(int parent_pid, int parent_tgid, int child_pid, int child_tgid);
    void processExecuted(int process_pid, int process_tgid);
    void processExited(int process_pid, int process_tgid, uint exit_code);
};

#endif // PROCESSTREEMODEL_H
