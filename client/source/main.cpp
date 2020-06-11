#include <QApplication>
#include <QCommandLineParser>
#include <QLoggingCategory>
#include <QtRemoteObjects/QRemoteObjectNode>
#include <QTimer>
#include <QIcon>
#include "client.hpp"


Q_LOGGING_CATEGORY(sbcclient, "sbcbmc.client");

#if 0
#define APP_VERSION #carputer_VERSION_MAJOR.#carputer_VERSION_MINOR.#carputer_VERSION_PATCH

#define DEF2STR2(x) #x
#define DEF2STR(x) DEF2STR2(x)
#endif

int main(int argc, char *argv[]) {

    QCoreApplication::setApplicationName("sbcbmc-client");
    //QCoreApplication::setApplicationVersion(DEF2STR(APP_VERSION));
    QCoreApplication::setOrganizationName("DynamX");
    QCoreApplication::setOrganizationDomain("dynam.com");
    QGuiApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QGuiApplication::setAttribute(Qt::AA_UseHighDpiPixmaps);

    QApplication a(argc, argv);

QLoggingCategory::setFilterRules("qt.remoteobjects.debug=true");

    QIcon::setThemeName("automotive");

    QCommandLineParser parser;
    parser.setApplicationDescription("SBCBMC Client");
    parser.addHelpOption();
    parser.addVersionOption();

    parser.process(a);

    SBCBMCClient client;

    a.exec();
}