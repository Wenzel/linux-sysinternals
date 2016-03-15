#include <QtDBus/QDBusConnection>
#include <QtDBus/QDBusConnectionInterface>
#include <QCoreApplication>
#include <iostream>
#include <unistd.h>

#include "procconnector.h"
#include "procexphelper.h"

#define HELPER_SERVICE "com.procexp.helper"
#define HELPER_PATH "/"

//static com::procexp::helper* iface = nullptr;

void handler(struct proc_event event)
{
    QDBusConnection bus = QDBusConnection::systemBus();
    QDBusMessage m;

    switch (event.what) {
    case event.PROC_EVENT_NONE:
        break;
    case event.PROC_EVENT_FORK:
        std::cout << "[FORK] parent " << event.event_data.fork.parent_pid << ", child " << event.event_data.fork.child_pid << std::endl;
        m = QDBusMessage::createSignal(HELPER_PATH, HELPER_SERVICE, "fork");
        m << event.event_data.fork.parent_pid;
        m << event.event_data.fork.parent_tgid;
        m << event.event_data.fork.child_pid;
        m << event.event_data.fork.child_tgid;
        bus.send(m);
        break;
    case event.PROC_EVENT_EXEC:
        std::cout << "[EXEC] process " << event.event_data.exec.process_pid << std::endl;
        m = QDBusMessage::createSignal(HELPER_PATH, HELPER_SERVICE, "exec");
        m << event.event_data.exec.process_pid;
        m << event.event_data.exec.process_tgid;
        bus.send(m);
        break;
    case event.PROC_EVENT_UID:
        m = QDBusMessage::createSignal(HELPER_PATH, HELPER_SERVICE, "uid");
        m << event.event_data.id.process_pid;
        m << event.event_data.id.process_tgid;
        m << event.event_data.id.r.ruid;
        m << event.event_data.id.e.euid;
        bus.send(m);
        break;
    case event.PROC_EVENT_GID:
        m = QDBusMessage::createSignal(HELPER_PATH, HELPER_SERVICE, "gid");
        m << event.event_data.id.process_pid;
        m << event.event_data.id.process_tgid;
        m << event.event_data.id.r.rgid;
        m << event.event_data.id.e.egid;
        bus.send(m);
        break;
    case event.PROC_EVENT_EXIT:
        m = QDBusMessage::createSignal(HELPER_PATH, HELPER_SERVICE, "exit");
        m << event.event_data.exit.process_pid;
        m << event.event_data.exit.process_tgid;
        m << event.event_data.exit.exit_code;
        bus.send(m);
        break;
    default:
        break;
    }
}

int main(int argc, char* argv[])
{
    QCoreApplication app(argc, argv);

    //    QDBusConnection connection = QDBusConnection::sessionBus();

    //    ProcexpHelper helper(&app);
    //    ProcexpHelperAdaptor adaptor(&helper);

    //    if (!connection.registerService(CONNECTOR_SERVICE))
    //        qFatal("Could not register the service");

    //    if (!connection.registerObject(CONNECTOR_PATH, &adaptor, QDBusConnection::ExportAllSignals))
    //        qFatal("Could not register the connector object");

    //    iface = new com::procexp::helper(CONNECTOR_SERVICE, CONNECTOR_PATH, connection);

    ProcConnector connector = ProcConnector();
    connector.addCallback(handler);
    connector.listen(false);

    app.exec();
}
