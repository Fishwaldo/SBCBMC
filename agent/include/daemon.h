#ifndef DAEMON_H
#define DAEMON_H

#include <QObject>
#include <QString>
#include <QHash>

#include "pluginbase.h"

class daemon : public QObject 
{
    Q_OBJECT
    public:
        daemon(QObject *parent = nullptr);
        ~daemon();
    private:
        QHash<QString, PluginBase *> m_Plugins;
        QRemoteObjectHost *m_rohost;
        QRemoteObjectRegistryHost * m_roregistryhost;
};

#endif