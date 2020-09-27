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

    XfrEntry nonoEntry = XfrEntry::from("", "");
    QVERIFY(nonoEntry.isNull());
    QVERIFY(nonoEntry.notValidLevel());
    QVERIFY(nullEntry.toLevel().notValid());

    XfrEntry qfiEntry = XfrEntry::from(Q_FUNC_INFO, "");
    QCOMPARE(Q_FUNC_INFO, qfiEntry.getQFuncInfo());
}

QTEST_MAIN(testXfr)

#include "tst_eirxfr.moc"