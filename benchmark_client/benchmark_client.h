#ifndef BENCHMARK_CLIENT_H
#define BENCHMARK_CLIENT_H

#include <QMainWindow>
#include <QDebug>
#include <QtBluetooth/QBluetoothServiceDiscoveryAgent>

namespace Ui {
class benchmark_client;
}

enum ROBOT_TYPE {
    CRICHTON = 0,
    ALITA = 1
};

class benchmark_client : public QMainWindow
{
    Q_OBJECT

public:
    explicit benchmark_client(QWidget *parent = 0);
    ~benchmark_client();

private slots:
    void onConnect();
    void onServiceDiscovered( QBluetoothServiceInfo );
    void onServiceDiscoveryFinished();

private:
    Ui::benchmark_client *ui;
    int mRobotIndex;
    QBluetoothServiceDiscoveryAgent* mServiceDiscoveryAgent;
};

#endif // BENCHMARK_CLIENT_H
