#pragma once

#include <QtBluetooth/QBluetoothServiceInfo>
#include <QtBluetooth/QBluetoothServiceDiscoveryAgent>
#include <QDialog>
#include <QListWidget>

namespace Ui {
class connectDialog;
}

class connectDialog : public QDialog
{
    Q_OBJECT

public:
    explicit connectDialog( const QBluetoothAddress &_localAdapter, QWidget *parent = 0);
    ~connectDialog();

    void startDiscovery( const QBluetoothUuid &_uuid );
    void stopDiscovery();
    QBluetoothServiceInfo service() const;

private slots:
  void scan();
  void serviceDiscovered( const QBluetoothServiceInfo &_serviceInfo );
  void discoveryFinished();

  void connect();

private:
    Ui::connectDialog *ui;
    QBluetoothServiceDiscoveryAgent* mDiscoveryAgent;
    QBluetoothServiceInfo mService;
    QMap<QListWidgetItem*, QBluetoothServiceInfo> mDiscoveredServices;

};

