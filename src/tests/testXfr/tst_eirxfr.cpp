#include <QtTest>
#include <QCoreApplication>

#include <QtDebug>

#include <eirXfr/XfrEntry.h>

class testXfr : public QObject
{
    Q_OBJECT

public:
    testXfr();
    ~testXfr();

private slots:
    void initTestCase();
    void cleanupTestCase();
    void testEntry();

};

testXfr::testXfr() {;}
testXfr::~testXfr() {;}
void testXfr::initTestCase() {;}
void testXfr::cleanupTestCase() {;}

void testXfr::testEntry()
{
    XfrEntry null;

    QVERIFY(null.isNull());
}

QTEST_MAIN(testXfr)

#include "tst_eirxfr.moc"
