#include <QtDBus/QDBusConnection>
#include <QtDBus/QDBusConnectionInterface>

#include "procconnector.h"
#include "connector.h"
#include "ConnectorAdapter.h"
#include "ConnectorInterface.h"

#define CONNECTOR_SERVICE "org.proccon"
#define CONNECTOR_PATH "/"

static org::proccon* iface = nullptr;

void handler(struct proc_event event)
{
    switch (event.what) {
    case event.PROC_EVENT_NONE:
        break;
    case event.PROC_EVENT_FORK:
        emit iface->fork(
               event.event_data.fork.parent_pid,
               event.event_data.fork.parent_tgid,
               event.event_data.fork.child_pid,
               event.event_data.fork.child_tgid);
        break;
    case event.PROC_EVENT_EXEC:
        emit iface->exec(
               event.event_data.exec.process_pid,
               event.event_data.exec.process_tgid);
        break;
    case event.PROC_EVENT_UID:
        emit iface->uid(
               event.event_data.id.process_pid,
               event.event_data.id.process_tgid,
               event.event_data.id.r.ruid,
               event.event_data.id.e.euid);
        break;
    case event.PROC_EVENT_GID:
        emit iface->gid(
               event.event_data.id.process_pid,
               event.event_data.id.process_tgid,
               event.event_data.id.r.rgid,
               event.event_data.id.e.egid);
        break;
    case event.PROC_EVENT_EXIT:
        emit iface->exit(
               event.event_data.exit.process_pid,
               event.event_data.exit.process_tgid,
               event.event_data.exit.exit_code);
        break;
    default:
        break;
    }

}

int main(int argc, char* argv[])
{
    QDBusConnection connection = QDBusConnection::sessionBus();

    Connector* conn = new Connector();
    ConnectorAdapter* adapter = new ConnectorAdapter(conn);

    if (!connection.registerService(CONNECTOR_SERVICE))
        qFatal("Could not register the service");

    if (!connection.registerObject(CONNECTOR_PATH, conn))
        qFatal("Could not register the connector object");

    iface = new org::proccon(CONNECTOR_SERVICE, CONNECTOR_PATH, connection);

    ProcConnector connector = ProcConnector();
    connector.addCallback(handler);
    connector.listen();
}
