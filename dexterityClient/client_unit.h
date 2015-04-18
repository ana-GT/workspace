#pragma once

#include <QBluetoothServiceInfo>
#include <QtCore/QObject>
#include <QBluetoothSocket>

/**
* @class client_unit
*/
class client_unit : public QObject {

  Q_OBJECT

 public:
  explicit client_unit( QObject* _parent = 0 );
  ~client_unit();

  void startClient( const QBluetoothServiceInfo &_remoteService );
  void stopClient();

  public slots:
    void sendMsg( const QString &_message );

 signals:
    void messageReceived( const QString &_sender,
                          const QString &_message );

    void connected( const QString &_name );
    void disconnected();

    private slots:
      void readSocket();
      void connected();

 private:
      QBluetoothSocket* mSocket;
};
