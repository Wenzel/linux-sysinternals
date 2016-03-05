#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
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
    void adjustColumnSize(const QModelIndex& index);

private:
    void center();

    ProcessTreeModel* m_process_treemodel;
    Ui::MainWindow *ui;

};

#endif // MAINWINDOW_H
