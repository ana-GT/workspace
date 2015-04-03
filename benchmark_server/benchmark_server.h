#pragma once

#include <QMainWindow>
#include <QBluetoothHostInfo>
#include <QBluetoothLocalDevice>

#include "server_unit.h"

namespace Ui {
class benchmark_server;
}

class benchmark_server : public QMainWindow
{
    Q_OBJECT

public:
    explicit benchmark_server(QWidget *parent = 0);
    ~benchmark_server();

private:
    Ui::benchmark_server *ui;
    QBluetoothLocalDevice* mLocalAdapter;
    server_unit* mServer;
};

