#include <QQmlContext>
#include <QCoreApplication>
#include "client.hpp"




SBCBMCClient::SBCBMCClient(QObject *parent) :
    QObject(parent)
{
    node = new QRemoteObjectNode();
    node->connectToNode(QUrl("tcp://10.100.200.49:1998"));

    QObject::connect(node, &QRemoteObjectNode::remoteObjectAdded,
                     [](const QRemoteObjectSourceLocation& info){
        qDebug() << "New source added : " << info;
    });

//    qDebug() << "Waiting for registry ";
//    node.waitForRegistry(10000);

    thermal = node->acquire<Thermal_PropertiesReplica>(QStringLiteral("plugins/thermal/thermal_zone1/x86_pkg_temp"));

    qDebug() << "Waiting for Source";
    thermal->waitForSource(10000);
    qDebug() << "Starting";
    qDebug() << thermal->state();
    //qmlRegisterType<DCDCUSB200_PropertiesReplica>("custom",1,0,"DCDCUSB200_PropertiesReplica");
    qmlRegisterType<Thermal_PropertiesReplica>("custom",1,0,"Thermal_PropertiesReplica");

    ready();
//     this->engine = new QQmlApplicationEngine("qrc:/qml/automotive.qml");

}

SBCBMCClient::~SBCBMCClient() 
{

}

void SBCBMCClient::ready() {
     this->engine = new QQmlApplicationEngine();
     this->engine->rootContext()->setContextProperty("remoteModel", thermal);
     this->engine->load("qrc:/qml/automotive.qml");
}

#if 0

    qDebug() << "Already here sources : " << node.registry()->sourceLocations();

    QTimer timer;
    timer.start(5000);

    QObject::connect(&timer, &QTimer::timeout,
                     [&](){
        qDebug() << "New sources list : " << node.registry()->sourceLocations();
    });

    QRemoteObjectDynamicReplica *plugin = node.acquireDynamic("plugins/thermal/thermal_zone1/x86_pkg_temp");
    QRemoteObjectDynamicReplica *plugin2 = node.acquireDynamic("plugins/thermal/thermal_zone0/x86_pkg_temp");

#endif