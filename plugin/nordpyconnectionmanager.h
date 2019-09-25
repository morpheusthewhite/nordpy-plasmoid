#ifndef NORDPYCONNECTIONMANAGER_H
#define NORDPYCONNECTIONMANAGER_H

#include <QQuickItem>
#include <QProcess>

class NordPyConnectionManager : public QQuickItem
{
    Q_OBJECT

    Q_PROPERTY(bool connected READ connected NOTIFY connectedChanged)
    Q_PROPERTY(bool connecting READ connecting NOTIFY connectingChanged)

public:
    NordPyConnectionManager();
    
    bool connected();
    bool connecting();
    
    void setConnecting(bool connecting);
    void setConnected(bool connected);
    
public slots:
    void startNordPy();
    void stopNordPy();

private:
    bool m_connecting;
    bool m_connected;

signals:
    void connectedChanged();
    void connectingChanged();
};

#endif // NORDPYCONNECTIONMANAGER_H
