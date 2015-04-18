#include "dexterityserver.h"
#include "ui_dexterityserver.h"
#include <QListWidget>
#include <QListWidgetItem>

/**
 * @brief Constructor
 * @param parent
 */
DexterityServer::DexterityServer(QWidget *parent) :
    QMainWindow(parent),
    mLocalAdapter(0),
    mServer(0),
    mTimer(0),
    mNumTimeouts(0),
    ui(new Ui::DexterityServer)
{
    ui->setupUi(this);

    // Button messages
    QObject::connect( ui->see_pushButton, SIGNAL(clicked()),
                      this, SLOT(sendMsg_slot()) );
    QObject::connect( ui->plan_pushButton, SIGNAL(clicked()),
                      this, SLOT(sendMsg_slot()) );
    QObject::connect( ui->execute_pushButton, SIGNAL(clicked()),
                      this, SLOT(sendMsg_slot()) );
    QObject::connect( ui->start_pushButton, SIGNAL(clicked()),
                      this, SLOT(sendMsg_slot()) );
    QObject::connect( ui->stop_pushButton, SIGNAL(clicked()),
                      this, SLOT(sendMsg_slot()) );

    // Get local adapter
    QList<QBluetoothHostInfo> adapters;
    adapters = QBluetoothLocalDevice::allDevices();
    mLocalAdapter = new QBluetoothLocalDevice( adapters.at(0).address() );
    mLocalAdapter->setHostMode( QBluetoothLocalDevice::HostDiscoverable);

    // Create server
    mServer = new server_unit(this);

    this->connect( mServer, SIGNAL(clientConnected_signal(QString)),
                   this, SLOT( clientConnected_slot(QString)) );
    this->connect( mServer, SIGNAL(rcvMsg_signal(QString, QString)),
                   this, SLOT( showMsg_slot(QString, QString)));
    this->connect( this, SIGNAL(sendMsg_signal(QString)),
                   mServer, SLOT(sendMsg_slot(QString)) );

    this->connect( mServer, SIGNAL(dbgMsg_signal(QString)),
                   this, SLOT(dbgMsg_slot(QString)) );


    // Start server
    mServer->startServer(mLocalAdapter->address() );

    // Get local device name
    mLocalName = QBluetoothLocalDevice().name();

    // Timer
    mTimer = new QTimer(this);
    connect( mTimer, SIGNAL(timeout()), this, SLOT(updateTimeDisplay_slot()) );

}

/**
 * @function dbgMsg_slot
 */
void DexterityServer::dbgMsg_slot( const QString &_msg ) {

    new QListWidgetItem( _msg, ui->msgs_listWidget );
}


DexterityServer::~DexterityServer()
{
    delete ui;
}

/**
 * @function showMessage_slot
 */
void DexterityServer::showMsg_slot( const QString &_sender, const QString &_message )  {
    QString msg = QString("Msg from %1 : %2 \n").arg( _sender, _message );
    new QListWidgetItem( msg, ui->msgs_listWidget );
}

/**
 * @brief clientConnected_slot
 */
void DexterityServer::clientConnected_slot( const QString &_name ) {

    QString msg =QString( "CONNECTION with client %1 \n").arg(_name);
    new QListWidgetItem( msg, ui->msgs_listWidget );
}

/**
 *
 */
void DexterityServer::updateTimeDisplay_slot() {

   mNumTimeouts++;
   // Tenths of second show
       double value; value = mNumTimeouts / 10.0;
       ui->totalTime_lcdNumber->display( value );
}


/**
 * @brief sendMsg_slot
 */
void DexterityServer::sendMsg_slot() {

   QObject* obj = sender();

   if( obj == ui->see_pushButton ) {
     new QListWidgetItem( tr("Send START SEE message"), ui->msgs_listWidget );
     emit sendMsg_signal( "START SEE Process" );
   }
   else if( obj == ui->plan_pushButton ) {
       new QListWidgetItem( tr("Send START PLAN message"), ui->msgs_listWidget );
       emit sendMsg_signal( "START PLAN Process" );
   }
   else if( obj == ui->execute_pushButton ) {
       new QListWidgetItem( tr("Send START EXECUTE message"), ui->msgs_listWidget );
       emit sendMsg_signal( "START EXECUTE Process" );
   }

   else if( obj == ui->start_pushButton ) {
       new QListWidgetItem( tr("Send START ALL message"), ui->msgs_listWidget );
       emit sendMsg_signal( "START ALL Process" );
       mTimer->start(100);
   }
   else if( obj == ui->stop_pushButton ) {
       new QListWidgetItem( tr("Send STOP ALL message"), ui->msgs_listWidget );
       emit sendMsg_signal( "STOP ALL Process" );
       mTimer->stop();
   }

}

