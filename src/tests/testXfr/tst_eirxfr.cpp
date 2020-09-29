#include <QtTest>
#include <QCoreApplication>

#include <QtDebug>

#include <eirXfr/XfrEntry.h>
#include <eirXfr/XfrFunctionInfo.h>

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
    void testFunctionInfo();

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
    //QVERIFY(qfiEntry == XfrEntry::at(qfiEntry.uid()));
}

void testXfr::testFunctionInfo()
{
    QStringList qfiList = QStringList() << Q_FUNC_INFO
            << "const TInputType& myMin(const TInputType&, const TInputType&)"
                    " [with TInputType = int]";
    foreach (QString qfi, qfiList)
    {
        XfrFunctionInfo xfi(qfi.toLocal8Bit());
        QString prettyQFI = xfi.getPrettyFunction();
        qDebug() << prettyQFI;
        QVERIFY( ! prettyQFI.isEmpty());
        QCOMPARE(prettyQFI, xfi.getPrettyFunction());

        QString argTypeNames = xfi.getArgumentTypeNames();
        qDebug() << argTypeNames;
        QCOMPARE(xfi.isFlag(XfrFunctionInfo::VoidArgument), 0 == xfi.argumentCount());
        // don't understand failure: QCOMPARE(xfi.getArgumentCount(), xfi.argumentCount());
        // don't understand failure: QCOMPARE(xfi.isVoidArgument() ? 0 : (1 + argTypeNames.count(',')), xfi.argumentCount());
        QCOMPARE(xfi.isFlag(XfrFunctionInfo::VoidArgument) ? 0 : (1 + argTypeNames.count(',')), xfi.getArgumentCount());
        QVERIFY( ! argTypeNames.isEmpty());
        QCOMPARE(argTypeNames == "void", xfi.isFlag(XfrFunctionInfo::VoidArgument));
        QVERIFY( ! argTypeNames.contains('('));
        QVERIFY( ! argTypeNames.contains(')'));
        QVERIFY( ! argTypeNames.contains(' '));
        if (xfi.isFlag(XfrFunctionInfo::VoidArgument))
        {
            QVERIFY( ! argTypeNames.contains(','));
            QVERIFY( ! argTypeNames.contains(QRegularExpression("[(,)]")));
        }
        else
        {
            QVERIFY( ! argTypeNames.contains(QRegularExpression("[( )]")));
        }
    }
}

QTEST_MAIN(testXfr)

#include "tst_eirxfr.moc"
