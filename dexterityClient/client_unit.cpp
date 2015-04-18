
/**
* @file client_unit.cpp
*/

#include "client_unit.h"

/**
* @function
*/
client_unit::client_unit( QObject* _parent ) :
  QObject(_parent), mSocket(0) {
}

/**
* @function
*/
client_unit::~client_unit() {
  stopClient();
}

/**
* @function
*/
void client_unit::startClient( const QBluetoothServiceInfo &_remoteService ) {

  if( mSocket ) { return; }

  // Connect to service
  mSocket = new QBluetoothSocket( QBluetoothServiceInfo::RfcommProtocol );
  mSocket->connectToService( _remoteService );

  QObject::connect( mSocket, SIGNAL(readyRead()),
                    this, SLOT(readSocket_slot()) );
  QObject::connect( mSocket, SIGNAL(connected() ),
                    this, SLOT(connected_slot()) );
  QObject::connect( mSocket, SIGNAL(disconnected()),
                    this, SIGNAL(disconnected_signal()) );
}

/**
* @function
*/
void client_unit::stopClient() {
  delete mSocket;
  mSocket = 0;
}

/**
* @function
*/
void client_unit::sendMsg_slot( const QString &_msg ) {

    QByteArray text = _msg.toUtf8() + '\n';

    if( mSocket->write( text ) < 0 ) {
        emit dbgMsg_signal("Error sending msg to server");
    } else {
        emit dbgMsg_signal("Send msg to server all right");
    }
}



/**
* @function
*/
void client_unit::readSocket_slot() {
  if( !mSocket ) {
    return;
  }

  while( mSocket->canReadLine() ) {
    QByteArray line = mSocket->readLine();
    emit rcvMsg_signal( mSocket->peerName(),
                        QString::fromUtf8( line.constData(), line.length() ) );
  }

}


/**
* @function
*/
void client_unit::connected_slot() {
  emit connected_signal( mSocket->peerName() );
}
