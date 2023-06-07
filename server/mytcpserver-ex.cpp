#include "mytcpserver-ex.h"
#include <QDebug>
#include <QCoreApplication>

MyTcpServer::~MyTcpServer()
{
    for (auto Socket : mTcpSocket) {
        Socket->close();
    }
    mTcpServer->close();
    server_status=0;
}
MyTcpServer::MyTcpServer(QObject *parent) : QObject(parent){
    mTcpServer = new QTcpServer(this);
    connect(mTcpServer, &QTcpServer::newConnection,
            this, &MyTcpServer::slotNewConnection);

    if(!mTcpServer->listen(QHostAddress::Any, 33333)){
        qDebug() << "server is not started";
    } else {
        server_status=1;
        qDebug() << "server is started";
    }
}

void MyTcpServer::slotNewConnection(){
    if(server_status==1){
        QTcpSocket* socket = mTcpServer->nextPendingConnection();
        int client_desc = socket->socketDescriptor();
        mTcpSocket[client_desc] = socket;
        qDebug() << client_desc;

        connect(socket, &QTcpSocket::readyRead,
                this, &MyTcpServer::slotServerRead);
        connect(socket, &QTcpSocket::disconnected,
                this, &MyTcpServer::slotClientDisconnected);
    }
}

void MyTcpServer::slotServerRead(){
    QTcpSocket* socket = (QTcpSocket*)sender();
    int desc = socket->socketDescriptor();
    QByteArray array;
    QString tmp;

    while(mTcpSocket[desc]->bytesAvailable() > 0)
    {
        array=(socket->readLine());
        tmp.append(array);
    }

    array.clear();
    array.append(tmp.toUtf8());
    qDebug() << "MyTcpServer::slotServerRead()\t" << array.left(array.size() - 2);
    qDebug() << parse((QString)array);
    socket->write(parse((QString)array).toUtf8());
}

QString MyTcpServer::parse(QString str)
{
    if(!str.startsWith("sort"))
        return "";

    QStringList qsl = str.split("&");
    QStringList arr = qsl[2].split(" ");
    QVector<double> array;

    for (auto number : arr) {
        array.append(number.toDouble());
    }

    array = heap_sort(array, qsl[1].toInt());

    QString res;
    for (const double& number : array) {
        res += QString::number(number) + " ";
    }
    res.chop(1);

    return res + "\r\n";
}

void MyTcpServer::slotClientDisconnected(){
    // closing connection with socket
    QTcpSocket* socket = (QTcpSocket*)sender();
    socket->close();

    // deleting socket from qmap
    QMap<int, QTcpSocket*>::iterator i = mTcpSocket.begin();
    while(i.value() != socket)
    {
        if(i.value() == socket)
            mTcpSocket.erase(i);
        i++;
    }
}

void MyTcpServer::swap(double &a, double &b)
{
    double temp = a;
    a = b;
    b = temp;
}

QVector<double> MyTcpServer::sift(QVector<double> A, int i, int m)
{
    int j = i, k = i * 2 + 1; // left son
    while (k <= m)
    {
        if (k < m && A[k] < A[k + 1])
            k++; // bigger son
        if (A[j] < A[k])
        {
            swap(A[j], A[k]);
            j = k;
            k = k * 2 + 1;
        }
        else
            break;
    }

    return A;
}

QVector<double> MyTcpServer::heap_sort(QVector<double> A, int step)
{
    int n = A.size();
    QVector<double> sortedArray = A;

    // make the pyramyd
    for (int i = n / 2; i >= 0; i--)
        sortedArray = sift(sortedArray, i, n - 1);

    // sort array
    for (int m = n - 1; m >= 1; m--)
    {
        swap(sortedArray[0], sortedArray[m]);
        if (m == step)
            return sortedArray;  // return array on the step
        sortedArray = sift(sortedArray, 0, m - 1);
    }

    return sortedArray;
}
