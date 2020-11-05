#include <QtTest>

#include <eirType/MultiName.h>

class testMultiName : public QObject
{
    Q_OBJECT

public:
    testMultiName();
    ~testMultiName();

private slots:
    void testAppend();

};

testMultiName::testMultiName()
{

}

testMultiName::~testMultiName()
{

}

void testMultiName::testAppend()
{
    MultiName none;
    BasicName bSome("Some");
    BasicName bWant("Want");
    BasicName bMore("More");
    BasicName bAnd("and");

    QVERIFY(none.isEmpty());
    QVERIFY( ! none.notEmpty());
    QCOMPARE(0, none.segmentCount());
    QCOMPARE(QString(), none.toString());
    QCOMPARE(QString(), none());
    QCOMPARE(QStringList(), none.toStringList());

    none += bSome;
    QStringList qsl = QStringList() << "Some";
    QVERIFY( ! none.isEmpty());
    QVERIFY(none.notEmpty());
    QCOMPARE(none.segmentCount(), 1);
    QCOMPARE("Some", none.toString());
    QCOMPARE("Some", none());
    QCOMPARE(qsl, none.toStringList());
    QCOMPARE(qsl.size(), none.segmentCount());
    QCOMPARE(bSome, none.firstSegment());
    QCOMPARE(bSome, none.lastSegment());
    QCOMPARE(bSome, none.segmentAt(0));

    none.prependName(bWant);
    QVERIFY( ! none.isEmpty());
    QVERIFY(none.notEmpty());
    QCOMPARE(none.segmentCount(), 2);
    QCOMPARE(none.toString(), "Want/Some");
    QCOMPARE(none(), "Want/Some");
    QCOMPARE(none.firstSegment(), bWant);
    QCOMPARE(none.lastSegment(), bSome);
    QCOMPARE(none.segmentAt(0), bWant);
    QCOMPARE(none.segmentAt(1), bSome);

    none.append(bMore);
    QVERIFY( ! none.isEmpty());
    QVERIFY(none.notEmpty());
    QCOMPARE(none.segmentCount(), 3);
    QCOMPARE(none.toString(), "Want/Some/More");
    QCOMPARE(none(), "Want/Some/More");
    QCOMPARE(none.firstSegment(), bWant);
    QCOMPARE(none.lastSegment(), bMore);
    QCOMPARE(none.segmentAt(0), bWant);
    QCOMPARE(none.segmentAt(1), bSome);
    QCOMPARE(none.segmentAt(2), bMore);

//    MultiName lots = none + "and";
  //  lots += "More";
//    MultiName lots = none.append(bAnd).append(bMore);
    MultiName lots = none.append("and").append("More");
    QVERIFY( ! lots.isEmpty());
    QVERIFY(lots.notEmpty());
    qDebug() << lots();
    QCOMPARE(lots.segmentCount(), 5);
    QCOMPARE(lots.toString(), "Want/Some/More/and/More");
    QCOMPARE(lots(), "Want/Some/More/and/More");
    QCOMPARE(lots.firstSegment(), bWant);
    QCOMPARE(lots.lastSegment(), bMore);
    QCOMPARE(lots.segmentAt(0), bWant);
    QCOMPARE(lots.segmentAt(1), bSome);
    QCOMPARE(lots.segmentAt(2), bMore);
    QCOMPARE(lots.segmentAt(3), bAnd);
    QCOMPARE(lots.segmentAt(4), bMore);

}

QTEST_APPLESS_MAIN(testMultiName)

#include "tst_multiname.moc"
