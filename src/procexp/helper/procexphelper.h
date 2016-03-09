#ifndef PROCEXPHELPER_H
#define PROCEXPHELPER_H

#include <QObject>

class ProcexpHelper : public QObject
{
    Q_OBJECT
    Q_CLASSINFO("D-Bus Interface", "com.procexp.helper")

public:
    ProcexpHelper(QObject* parent = 0);
    ~ProcexpHelper();

signals:
    void fork(int parent_pid, int parent_tgid, int child_pid, int child_tgid);
    void exec(int process_pid, int process_tgid);
    void uid(int process_pid, int process_tgid, int ruid, int euid);
    void gid(int process_pid, int process_tgid, int rgid, int egid);
    void exit(int process_pid, int process_tgid, int exit_code);

};

#endif // PROCEXPHELPER_H
