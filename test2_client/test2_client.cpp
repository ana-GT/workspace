#include "test2_client.h"
#include "ui_test2_client.h"
#include <iostream>
#include "connectDialog.h"
#include "selectObjectDialog.h"
#include <sstream>

/**
* @brief Constructor
* @param parent
*/
Test2_Client::Test2_Client(QWidget *parent) :
    QMainWindow(parent),
    mLocalAdapter(0),
    mClient(0),
    mTimer(0),
    mNumTimeouts(0),
    ui(new Ui::Test2_Client) {

    ui->setupUi(this);

    // Setting buttons initial state
    ui->disconnect_pushButton->setEnabled(false);

    // Button messages
    QObject::connect( ui->connect_pushButton, SIGNAL(clicked()),
                      this, SLOT(connect_slot()) );
    QObject::connect( ui->disconnect_pushButton, SIGNAL(clicked()),
                      this, SLOT(clientDisconnected_slot()) );
    QObject::connect( ui->start_pushButton, SIGNAL(clicked()),
                      this, SLOT(sendMsg_slot()) );
    QObject::connect( ui->stop_pushButton, SIGNAL(clicked()),
                      this, SLOT(sendMsg_slot()) );
    QObject::connect( ui->reset_pushButton, SIGNAL(clicked()),
                      this, SLOT(sendMsg_slot()) );
    QObject::connect( ui->cancel_pushButton, SIGNAL(clicked()),
                      this, SLOT(close()) );

    // Get local device
    QList<QBluetoothHostInfo> adapters = QBluetoothLocalDevice::allDevices();
    if ( adapters.count() < 1) {
        ui->connect_pushButton->setEnabled(false);
        new QListWidgetItem( "[!] No local adapter found", ui->msgs_listWidget );
        return;
    }
    mLocalAdapter = new QBluetoothLocalDevice( adapters.at(0).address() );
    mLocalAdapter->setHostMode( QBluetoothLocalDevice::HostDiscoverable);

    // Timer
    mTimer = new QTimer(this);
    connect( mTimer, SIGNAL(timeout()), this, SLOT(updateTimeDisplay_slot()) );
}

/**
* @brief Destructor
* @param parent
*/
Test2_Client::~Test2_Client() {
}


/**
 * @function sendMsg_slot
 */
void Test2_Client::sendMsg_slot() {

    QObject* obj = sender();
    bool send = false;

    // Get details from combo boxes
    QString command;
    QString side = ui->side_comboBox->currentText();
    QString conf = ui->goalConfig_comboBox->currentText();
    QString msg;

    if( obj == ui->start_pushButton ) {
        command = QString("start");
        mTimer->start(100); send = true;
    }
    else if( obj == ui->stop_pushButton ) {
        command = QString("stop");
        mTimer->stop();
    } else if( obj == ui->reset_pushButton ) {
        command = QString("reset");
        mTimer->stop();
        mNumTimeouts = 0;
        ui->time_lcdNumber->display( 0.0 );
    }

    if( send == true ) {
        msg = QString("%1 %2 %3").arg( command, side, conf );
    }

    new QListWidgetItem( msg, ui->msgs_listWidget );
    emit sendMsg_signal( msg );

}

/**
* @function connect
*/
void Test2_Client::connect_slot(){

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

        QString msg = QString("%1: Connected to this client").arg( service.serviceName() );
        new QListWidgetItem(msg, ui->msgs_listWidget );
        ui->disconnect_pushButton->setEnabled(true);
        mClient->startClient(service);
    } else {
        QString msg = QString("[!] No service selected");
        new QListWidgetItem( msg, ui->msgs_listWidget );
    }
}


/**
 * @function showPlainMsg
 */
void Test2_Client::showPlainMsg( const QString &_msg ) {
  new QListWidgetItem( _msg, ui->msgs_listWidget );

}

/**
 * @function rcvMsg
 */
void Test2_Client::rcvMsg_slot( const QString &_sender,
                                const QString &_message ) {

  QString msg = QString("%1: %2").arg( _sender, _message );
  new QListWidgetItem( msg, ui->msgs_listWidget );

  /*
  std::string msg2; msg2 = _message.toStdString();
  std::cout << "Msg: "<< msg2<<std::endl;

  if( msg.compare( "We are going to start\n" ) == 0 ) {
    printf("Start updates \n");
    startUpdate();
  } else if( msg.compare( " We are finishing!\n" ) == 0 ) {
    printf("Stop updates \n");
    stopUpdate();
  }
  */

  std::string msg_type;
  std::string image_name;
  std::istringstream iss( _message.toStdString() );
  iss >> msg_type;
  iss >> image_name;

  //-- RECEIVE IMAGE FROM SERVER
  if( msg_type.compare( "RCV_IMG") == 0 ) {

      char localFile[255];
      sprintf( localFile, "/storage/emulated/0/Bluetooth/%s", image_name.c_str() );
      SelectObjectDialog so( this);
      so.loadFile( QString(localFile) );

    if( so.exec() == QDialog::Accepted ) {
         so.getClicked( mPx, mPy );
         // Send acknowledgment back
         QString ack_msg = QString("CLIENT_INPUT %1 %2").arg( mPx ).arg( mPy );
         emit sendMsg_signal( ack_msg );
    }

  }

}


/**
* @function clientDisconnected_slot
*/
void Test2_Client::clientDisconnected_slot() {

   if( mClient ) {
        mClient->deleteLater();
   }

   showPlainMsg("Client-server disconnected \n");
}


/**
 * @funcion dbgMsg_slot
 */
void Test2_Client::dbgMsg_slot( const QString &_msg ) {
    showPlainMsg( _msg );
}

/**
 * @function updateTimeDisplay_slot
 */
void Test2_Client::updateTimeDisplay_slot() {

   mNumTimeouts++;
   // Tenths of second show
       double value; value = mNumTimeouts / 10.0;
       ui->time_lcdNumber->display( value );
}

