#ifndef TESTHELPER_H
#define TESTHELPER_H

#include <QObject>

class TestHelper : public QObject
{
    Q_OBJECT

public:
    TestHelper(QObject* parent = 0);

public slots:
    void received(int a, int b, int c, int d);

};

#endif // TESTHELPER_H
