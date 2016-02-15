#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QHash>
#include <QSortFilterProxyModel>

#include "sysinfo.h"
#include "processinfo.h"
#include "mmap.h"
#include "selectprocessview.h"
#include "mapcategorymodel.h"
#include "mapdetailtreemodel.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    void center();


    Ui::MainWindow *ui;
    SelectProcessView* m_select_process_view;
    ProcessInfo* m_pinfo;
    MapCategoryModel* m_map_category_model;
    MapDetailTreeModel* m_map_detail_model;
    QSortFilterProxyModel* m_proxy_map_detail_model;

private slots:
    void selectProcess();
    void showProcessMap(int pid);
    void categorySelected(const QModelIndex& index);

};

#endif // MAINWINDOW_H
