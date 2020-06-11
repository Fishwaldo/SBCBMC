#include <QCoreApplication>
#include <QCommandLineParser>
#include <QLoggingCategory>

#include "config.h"
#include "daemon.h"

Q_LOGGING_CATEGORY(ozwdaemon, "ozw.daemon");

#define APP_VERSION #carputer_VERSION_MAJOR.#carputer_VERSION_MINOR.#carputer_VERSION_PATCH

#define DEF2STR2(x) #x
#define DEF2STR(x) DEF2STR2(x)

int main(int argc, char *argv[]) {

    QCoreApplication a(argc, argv);
    QCoreApplication::setApplicationName("carputer");
    QCoreApplication::setApplicationVersion(DEF2STR(APP_VERSION));
    QCoreApplication::setOrganizationName("DynamX");
    QCoreApplication::setOrganizationDomain("dynam.com");

    QCommandLineParser parser;
    parser.setApplicationDescription("CarPuter Daemon");
    parser.addHelpOption();
    parser.addVersionOption();

    parser.process(a);

    daemon carserver;
    carserver;

    a.exec();
}