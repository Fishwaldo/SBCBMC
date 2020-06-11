#include <QObject>
#include <QQmlApplicationEngine>
#include <QRemoteObjectNode>

#include "rep_dcdc_usb_200_replica.h"
#include "rep_thermal_replica.h"


class SBCBMCClient : public QObject {
    Q_OBJECT
    public:
        SBCBMCClient(QObject *parent = nullptr);
        ~SBCBMCClient();
    public Q_SLOTS:
        void ready();
    private:
    QQmlApplicationEngine *engine;
    Thermal_PropertiesReplica *thermal;
    QRemoteObjectNode *node;
};