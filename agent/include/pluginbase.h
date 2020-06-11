#ifndef PLUGINBASE_H
#define PLUGINBASE_H
#include <QObject>
#include <QTimer>
#include <QtRemoteObjects/QRemoteObjectHostBase>

class PluginBase : public QObject {
    Q_OBJECT
    public:
        PluginBase(QObject *parent = nullptr);
        ~PluginBase();
        virtual bool initilize() = 0;
        virtual void startTimer();
    public Q_SLOTS:
        virtual void update() = 0;
        virtual bool registerSource(QRemoteObjectHostBase *host) = 0;



    private:
        QTimer m_updateTimer;
};


#endif