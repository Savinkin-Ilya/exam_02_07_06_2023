#include <QtTest>
#include "../server/mytcpserver-ex.h"

class test : public QObject
{
    Q_OBJECT

public:
    test();
    ~test();

private slots:
    void test_case1();
    void test_case2();
    void test_case3();
    void test_case4();
    void test_case5();
    void test_case6();
    void test_case7();
    void test_case8();
    void test_case9();
    void test_case10();

};

test::test()
{

}

test::~test()
{

}

void test::test_case1()
{
    MyTcpServer tcpServer;
    QVERIFY(tcpServer.parse("sort&12&3 89 65 3 65 8 9 65 3 2 563 35 8") == "8 89 65 65 65 35 9 3 3 2 3 8 563\r\n");
}

void test::test_case2()
{
    MyTcpServer tcpServer;
    QVERIFY(tcpServer.parse("sort&1&678 34 23 78 98 8 64 34 23 65 89") == "8 23 23 34 34 64 65 78 89 98 678\r\n");
}

void test::test_case3()
{
    MyTcpServer tcpServer;
    QVERIFY(tcpServer.parse("sort&100&678 5 34 2354 78 8978 543 54 23 56") == "5 23 34 54 56 78 543 678 2354 8978\r\n");
}

void test::test_case4()
{
    MyTcpServer tcpServer;
    QVERIFY(tcpServer.parse("sort&10&8 56 3 21") == "3 8 21 56\r\n");
}

void test::test_case5()
{
    MyTcpServer tcpServer;
    QVERIFY(tcpServer.parse("sort&5&8 6 4 2 1 5 8") == "4 6 5 2 1 8 8\r\n");
}

void test::test_case6()
{
    MyTcpServer tcpServer;
    QVERIFY(tcpServer.parse("sort&21&89 78 654 4 31 5 8 76 34") == "4 5 8 31 34 76 78 89 654\r\n");
}

void test::test_case7()
{
    MyTcpServer tcpServer;
    QVERIFY(tcpServer.parse("sort&8&8 76 4 1 8") == "1 4 8 8 76\r\n");
}

void test::test_case8()
{
    MyTcpServer tcpServer;
    QVERIFY(tcpServer.parse("sort&3&4 3 2 1") == "1 3 2 4\r\n");
}

void test::test_case9()
{
    MyTcpServer tcpServer;
    QVERIFY(tcpServer.parse("sort&6&9 65 34 67 34 9 1") == "1 65 34 9 34 9 67\r\n");
}

void test::test_case10()
{
    MyTcpServer tcpServer;
    QVERIFY(tcpServer.parse("sort&8&9 56 23 21 78 4 3 67 0") == "0 67 23 21 56 4 3 9 78\r\n");
}

QTEST_APPLESS_MAIN(test)

#include "tst_test.moc"
