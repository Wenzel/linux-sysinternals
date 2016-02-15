#include <QDesktopWidget>

#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    m_select_process_view(nullptr)
{
    ui->setupUi(this);
    center();
    connect(ui->actionExit, SIGNAL(triggered(bool)), qApp, SLOT(quit()));
    connect(ui->actionSelectProcess, SIGNAL(triggered(bool)), this, SLOT(selectProcess()));
    connect(ui->tableView_mapcategory, SIGNAL(clicked(QModelIndex)), this, SLOT(categorySelected(QModelIndex)));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::center()
{
    // size 70%
    QDesktopWidget dw;

    int x=dw.width()*0.5;
    int y=dw.height()*0.6;
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

void MainWindow::selectProcess()
{
    m_select_process_view = new SelectProcessView(nullptr);
    connect(m_select_process_view, SIGNAL(processChoosen(int)), this, SLOT(showProcessMap(int)));
    m_select_process_view->show();
}


void MainWindow::showProcessMap(int pid)
{
    // delete subwindow
    m_select_process_view->close();
    delete m_select_process_view;
    m_select_process_view = nullptr;

    m_pinfo = new ProcessInfo(pid);

    // fill header
    // name
    QString name = QString::fromUtf8(m_pinfo->name().data(), m_pinfo->name().size());
    ui->label_process_name->setText(name);
    // icon
    QIcon icon = QIcon::fromTheme(name, QIcon());
    ui->label_icon->setPixmap(icon.pixmap(48));
    // pid
    QString str_pid = QString::number(pid);
    ui->label_process_pid->setText(str_pid);


    // get list of MMap
    const std::vector<MMap>& maps = m_pinfo->maps();

    // build MapDetail model
    QStringList headers;
    headers << "Address" << "Type" << "Virtual Size" << "Details";
    m_map_detail_model = new MapDetailTreeModel(headers, maps, this);
    m_proxy_map_detail_model = new QSortFilterProxyModel(this);
    m_proxy_map_detail_model->setSourceModel(m_map_detail_model);
    m_proxy_map_detail_model->setFilterKeyColumn(1); // filter on category
    ui->treeView_mapdetail->setModel(m_proxy_map_detail_model);

    // build MapCategory model
    headers.clear();
    headers << "Type" << "Virtual Size";
    m_map_category_model = new MapCategoryModel(headers, maps, this);
    ui->tableView_mapcategory->setModel(m_map_category_model);

    // enable ui
    ui->treeView_mapdetail->setEnabled(true);
    ui->tableView_mapcategory->setEnabled(true);
}

void MainWindow::categorySelected(const QModelIndex &index)
{
    QString category = m_map_category_model->categoryAt(index.row());
    if (category == "Total")
        m_proxy_map_detail_model->setFilterRegExp(QRegExp(".*"));
    else
        m_proxy_map_detail_model->setFilterRegExp(QRegExp(category));
}
