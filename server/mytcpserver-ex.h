#ifndef MYSERVER_H
#define MYSERVER_H
#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>

#include <QtNetwork>
#include <QByteArray>
#include <QDebug>

#include <QVector>

class MyTcpServer : public QObject
{
    Q_OBJECT
public:
    explicit MyTcpServer(QObject *parent = nullptr);
    QString parse(QString);
    ~MyTcpServer();
public slots:
    void slotNewConnection();
    void slotClientDisconnected();

    void slotServerRead();
    //void slotReadClient();
private:
    QTcpServer * mTcpServer;
    //QTcpSocket * mTcpSocket;
    QMap<int, QTcpSocket*> mTcpSocket;
    int server_status;

    void swap(double&, double&);
    QVector<double> sift(QVector<double>, int, int);
    QVector<double> heap_sort(QVector<double>, int);
};
#endif // MYSERVER_H
