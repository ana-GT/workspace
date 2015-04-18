
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
this, SLOT(readSocket()) );
  QObject::connect( mSocket, SIGNAL(connected() ),
this, SLOT(connected()) );
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
void client_unit::sendMsg( const QString &_msg ) {

}



/**
* @function
*/
void client_unit::readSocket() {
  if( !mSocket ) {
    return;
  }
  printf("GOT A MESSAGE FROM CLIENT UNIT!!! \n");
  while( mSocket->canReadLine() ) {
    QByteArray line = mSocket->readLine();
    emit messageReceived( mSocket->peerName(),
QString::fromUtf8( line.constData(), line.length() ) );
  }

}


/**
* @function
*/
void client_unit::connected() {
  emit connected( mSocket->peerName() );
}
