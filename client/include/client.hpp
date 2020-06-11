#include <QObject>
#include <QQmlApplicationEngine>

class SBCBMCClient : public QObject {
    Q_OBJECT
    public:
        SBCBMCClient(QObject *parent = nullptr);
        ~SBCBMCClient();

    private:
    QQmlApplicationEngine *engine;
};