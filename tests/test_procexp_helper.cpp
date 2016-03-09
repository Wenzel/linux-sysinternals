#include <QtDBus/QDBusConnection>
#include <QtDBus/QDBusConnectionInterface>
#include <QObject>
#include <unistd.h>
#include <QCoreApplication>

#include "ProcexpHelperInterface.h"
#include "testhelper.h"

int main(int argc, char* argv[])
{
    QCoreApplication app(argc, argv);

    QDBusConnection connection = QDBusConnection::sessionBus();

    com::procexp::helper* helper = new com::procexp::helper("com.procexp.helper", "/", connection);
    TestHelper* h = new TestHelper();

    QObject::connect(helper, SIGNAL(fork(int,int,int,int)), h, SLOT(received(int,int,int,int)));

    app.exec();

    return 0;
}
