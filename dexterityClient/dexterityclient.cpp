#include "dexterityclient.h"
#include "ui_dexterityclient.h"
#include <iostream>

#include "connectDialog.h"

/**
 * @brief Constructor
 * @param parent
 */
DexterityClient::DexterityClient(QWidget *parent) :
    QMainWindow(parent),
    mLocalAdapter(0),
    mClient(0),
    ui(new Ui::DexterityClient) {
    ui->setupUi(this);

    // Setting buttons initial state
    ui->disconnect_pushButton->setEnabled(false);

    // Button messages
    QObject::connect( ui->connect_pushButton, SIGNAL(clicked()),
                      this, SLOT(connect_slot()) );
    QObject::connect( ui->disconnect_pushButton, SIGNAL(clicked()),
                      this, SLOT(clientDisconnected_slot()) );
    QObject::connect( ui->testSend_pushButton, SIGNAL(clicked()),
                      this, SLOT(sendTestMsg_slot()) );


    // Get local device
    QList<QBluetoothHostInfo>  adapters = QBluetoothLocalDevice::allDevices();
    if ( adapters.count() < 1) {
        ui->connect_pushButton->setEnabled(false);
        new QListWidgetItem( "[!] No local adapter found", ui->msgs_listWidget );
        return;
    }

    mLocalAdapter = new QBluetoothLocalDevice( adapters.at(0).address() );
    mLocalAdapter->setHostMode( QBluetoothLocalDevice::HostDiscoverable);

}

/**
 * @brief Destructor
 * @param parent
 */
DexterityClient::~DexterityClient() {

}

/**
 * @function connect
 */
void DexterityClient::connect_slot(){

  connectDialog mCd( mLocalAdapter->address(), this );

  if( mCd.exec() == QDialog::Accepted ) {

    QBluetoothServiceInfo service = mCd.service();
    mClient = new client_unit(this);

    QObject::connect( mClient, SIGNAL( rcvMsg_signal(QString,QString)),
                      this, SLOT( rcvMsg_slot( QString, QString)));

    QObject::connect( mClient, SIGNAL( disconnected_signal()),
                      this, SLOT( clientDisconnected_slot()));

    QObject::connect( this, SIGNAL( sendMsg_signal(QString)),
                      mClient, SLOT(sendMsg_slot(QString)));

    QObject::connect( mClient, SIGNAL( dbgMsg_signal(QString)),
                      this, SLOT(dbgMsg_slot(QString)));


    QString msg = QString("Connected to service %1").arg( service.serviceName() );
    new QListWidgetItem(msg, ui->msgs_listWidget );
    ui->disconnect_pushButton->setEnabled(true);

    mClient->startClient(service);
  } else {
      QString msg = QString("[!] No service selected");
      new QListWidgetItem( msg, ui->msgs_listWidget );
  }
}


/**
 * @brief clientDisconnected_slot
 */
void DexterityClient::clientDisconnected_slot() {

  client_unit* client = qobject_cast<client_unit*>(sender());
  if( client ) {
      client->deleteLater();
  }
  showPlainMsg("Client was disconnected \n");
}


/**
 * @function showPlainMsg
 */
void DexterityClient::showPlainMsg( const QString &_msg ) {
  new QListWidgetItem( _msg, ui->msgs_listWidget );

}

/**
 * @function rcvMsg
 */
void DexterityClient::rcvMsg_slot( const QString &_sender,
                                   const QString &_message ) {

  QString msg = QString("%1: %2").arg( _sender, _message );
  new QListWidgetItem( msg, ui->msgs_listWidget );

  std::string msg2; msg2 = _message.toStdString();
  std::cout << "Msg: "<< msg2<<std::endl;
/*
  if( msg.compare( "We are going to start\n" ) == 0 ) {
    printf("Start updates \n");
    startUpdate();
  } else if( msg.compare( " We are finishing!\n" ) == 0 ) {
    printf("Stop updates \n");
    stopUpdate();
  }
  */
}

void DexterityClient::sendTestMsg_slot() {
    emit sendMsg_signal("Testing sending msg");

}

void DexterityClient::dbgMsg_slot( const QString &_msg ) {
    showPlainMsg( _msg );
}

