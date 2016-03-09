#ifndef CONNECTOR_H
#define CONNECTOR_H

#include <QObject>

class Connector : public QObject
{
    Q_OBJECT
    Q_CLASSINFO("D-Bus Interface", "org.proccon")

public:
    Connector(QObject* parent = 0);
    ~Connector();

signals:
    void fork(int parent_pid, int parent_tgid, int child_pid, int child_tgid);
    void exec(int process_pid, int process_tgid);
    void uid(int process_pid, int process_tgid, int ruid, int euid);
    void gid(int process_pid, int process_tgid, int rgid, int egid);
    void exit(int process_pid, int process_tgid, int exit_code);

};

#endif // CONNECTOR_H
