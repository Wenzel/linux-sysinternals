#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "processproxymodel.h"
#include "processtreemodel.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void adjustColumnSize();
    void adjustTreeView();
    void updateFilters(const QString& text);

private:
    void center();

    ProcessProxyModel* m_process_proxymodel;
    ProcessTreeModel* m_process_treemodel;
    Ui::MainWindow *ui;

};

#endif // MAINWINDOW_H
