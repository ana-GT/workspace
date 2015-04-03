#include "benchmark_client.h"
#include "ui_benchmark_client.h"

benchmark_client::benchmark_client(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::benchmark_client)
{
    ui->setupUi(this);
    QObject::connect( ui->connect_pushButton, SIGNAL(clicked()),
                      this, SLOT(onConnect()) );
    mServiceDiscoveryAgent = new QBluetoothServiceDiscoveryAgent(this);
    QObject::connect( mServiceDiscoveryAgent, SIGNAL(serviceDiscovered(QBluetoothServiceInfo)),
                      this, SLOT(onServiceDiscovered(QBluetoothServiceInfo)));
    QObject::connect( mServiceDiscoveryAgent, SIGNAL(finished()),
                      this, SLOT(onServiceDiscoveryFinished()));
}

benchmark_client::~benchmark_client()
{
    delete ui;
}

/*
 * @function onConnect
 * @brief Connect to one of the robot services
 */
void benchmark_client::onConnect() {

    // Which robot?
    QString item = ui->robot_comboBox->currentText();
    if( item.compare(QString("Crichton")) == 0 ) {
        mRobotIndex = CRICHTON;
    } else {
        mRobotIndex = ALITA;
    }

    // Get the corresponding device
    qDebug() << "Setting address...";
    QBluetoothAddress address(QString("00:15:83:0C:BF:EB"));
    if( mServiceDiscoveryAgent->setRemoteAddress( address ) == false ) {
        ui->connectStatus_label->setText(QString("Could not access the robot's address"));
        return;
    }

    // Access the service to communicate, if available
    mServiceDiscoveryAgent->start();

}

/**
 * @brief benchmark_client::onServiceDiscovered
 */
void benchmark_client::onServiceDiscovered( QBluetoothServiceInfo _serviceInfo) {
    QString name = _serviceInfo.serviceName();
    qDebug() << "Service name: "<< name;
}

/**
 * @brief benchmark_client::onServiceDiscoveryFinished
 */
void benchmark_client::onServiceDiscoveryFinished() {
    qDebug() << "Service discovery finished";
}
