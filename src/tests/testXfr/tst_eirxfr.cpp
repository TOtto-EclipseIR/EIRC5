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
    XfrEntry nullEntry;

    QVERIFY(nullEntry.isNull());
    QVERIFY(nullEntry.notValidLevel());
    QVERIFY(nullEntry.toLevel().notValid());
}

QTEST_MAIN(testXfr)

#include "tst_eirxfr.moc"
