#ifndef SELECTPROCESSVIEW_H
#define SELECTPROCESSVIEW_H

#include <QWidget>
#include <vector>
#include <sysinfo.h>


namespace Ui {
class SelectProcessView;
}

class SelectProcessView : public QWidget
{
    Q_OBJECT

public:
    explicit SelectProcessView(QWidget *parent = 0);
    ~SelectProcessView();

signals:
    void processChoosen(int pid);

private:
    void center();

    Ui::SelectProcessView *ui;
    std::vector<ProcessInfo> m_processes;

private slots:
    void refresh();
    void ok();
};

#endif // SELECTPROCESSVIEW_H
