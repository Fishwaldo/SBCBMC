#include <QCoreApplication>
#include <QCommandLineParser>
#include <QLoggingCategory>
#include <QtRemoteObjects/QRemoteObjectNode>
#include <QTimer>


Q_LOGGING_CATEGORY(ozwdaemon, "ozw.daemon");

#if 0
#define APP_VERSION #carputer_VERSION_MAJOR.#carputer_VERSION_MINOR.#carputer_VERSION_PATCH

#define DEF2STR2(x) #x
#define DEF2STR(x) DEF2STR2(x)
#endif

int main(int argc, char *argv[]) {

    QCoreApplication a(argc, argv);
    QCoreApplication::setApplicationName("carclient");
    //QCoreApplication::setApplicationVersion(DEF2STR(APP_VERSION));
    QCoreApplication::setOrganizationName("DynamX");
    QCoreApplication::setOrganizationDomain("dynam.com");

    QCommandLineParser parser;
    parser.setApplicationDescription("CarClient");
    parser.addHelpOption();
    parser.addVersionOption();

    parser.process(a);

    QRemoteObjectNode node(QUrl("tcp://127.0.0.1:1999"));

    QObject::connect(&node, &QRemoteObjectNode::remoteObjectAdded,
                     [](const QRemoteObjectSourceLocation& info){
        qDebug() << "New source added : " << info;
    });

    qDebug() << "Waiting for registry ";
    node.waitForRegistry(10000);

    qDebug() << "Already here sources : " << node.registry()->sourceLocations();

    QTimer timer;
    timer.start(5000);

    QObject::connect(&timer, &QTimer::timeout,
                     [&](){
        qDebug() << "New sources list : " << node.registry()->sourceLocations();
    });

    QRemoteObjectDynamicReplica *plugin = node.acquireDynamic("plugins/thermal/thermal_zone1/x86_pkg_temp");
    QRemoteObjectDynamicReplica *plugin2 = node.acquireDynamic("plugins/thermal/thermal_zone0/x86_pkg_temp");


    a.exec();
}