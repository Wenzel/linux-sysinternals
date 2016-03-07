#include <QDesktopWidget>

#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    m_process_treemodel(nullptr),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    center();

    m_process_treemodel = new ProcessTreeModel(this);
    ui->treeView_process->setModel(m_process_treemodel);
    // expand all items
    ui->treeView_process->expandAll();
    ui->treeView_process->resizeColumnToContents(0);
    connect(ui->treeView_process, SIGNAL(expanded(QModelIndex)), this, SLOT(adjustColumnSize(QModelIndex)));
    connect(ui->treeView_process, SIGNAL(collapsed(QModelIndex)), this, SLOT(adjustColumnSize(QModelIndex)));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::center()
{
    // size 70%
    QDesktopWidget dw;

    int x=dw.width()*0.7;
    int y=dw.height()*0.7;
    this->setFixedSize(x,y);

    // center
    this->setGeometry(
        QStyle::alignedRect(
            Qt::LeftToRight,
            Qt::AlignCenter,
            this->size(),
            qApp->desktop()->availableGeometry()
        )
    );
}

void MainWindow::adjustColumnSize(const QModelIndex &index)
{
    if (!index.isValid())
        return;

    ui->treeView_process->resizeColumnToContents(0);
}
