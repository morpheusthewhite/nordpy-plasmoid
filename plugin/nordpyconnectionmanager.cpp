#include "nordpyconnectionmanager.h"
#include <iostream>


NordPyConnectionManager::NordPyConnectionManager()
    : QQuickItem(){
        setConnected(false);
        
        // connecting initially until VPN status is retrieved
        setConnecting(true);
        
        QString program = "nordpy";
        QStringList arguments;
        arguments << "--status";

        QProcess *nordpyProcess = new QProcess();
        
        // redirect stdout to main stdout
        nordpyProcess->setProcessChannelMode(QProcess::SeparateChannels);
        
        connect(nordpyProcess, static_cast<void(QProcess::*)(int, QProcess::ExitStatus)>(&QProcess::finished),
            [=]  (int exitCode, QProcess::ExitStatus exitStatus) 
            {
                QString output(nordpyProcess->readAllStandardOutput());
                
                if(output.contains("Enabled")) setConnected(true);
                setConnecting(false);
            });
    
        // register signal on error
        connect(nordpyProcess, &QProcess::errorOccurred, 
            [=](QProcess::ProcessError error) 
            {
                setConnecting(false);
            });
        
        nordpyProcess->start(program, arguments);
}

bool NordPyConnectionManager::connecting(){
    return m_connecting;
}

bool NordPyConnectionManager::connected(){
    return m_connected;
}

void NordPyConnectionManager::setConnected(bool connected)
{
    if(connected != m_connected){
        m_connected = connected;
        emit connectedChanged();
    }
}

void NordPyConnectionManager::setConnecting(bool connecting)
{
    if(connecting != m_connecting){
        m_connecting = connecting;
        emit connectingChanged();
    }
}

void NordPyConnectionManager::startNordPy()
{
    setConnecting(true);
    
    QString program = "pkexec";
    QStringList arguments;
    arguments << "nordpy" << "--quick-connect";

    QProcess *nordpyProcess = new QProcess();
    
    // redirect stdout to main stdout
    nordpyProcess->setProcessChannelMode(QProcess::ForwardedChannels);
    
    // register signal on terminate 
    connect(nordpyProcess, static_cast<void(QProcess::*)(int, QProcess::ExitStatus)>(&QProcess::finished),
        [=]  (int exitCode, QProcess::ExitStatus exitStatus) 
        {
            if(!exitCode) setConnected(true);

            setConnecting(false);
        });
    
    // register signal on error
    connect(nordpyProcess, &QProcess::errorOccurred, 
        [=](QProcess::ProcessError error) 
        { 
            setConnecting(false);
        });
    
    nordpyProcess->start(program, arguments);
    return;
}

void NordPyConnectionManager::stopNordPy()
{
    setConnecting(true);
    
    QString program = "pkexec";
    QStringList arguments;
    arguments << "nordpy" << "--quick-disconnect";

    QProcess *nordpyProcess = new QProcess();
    
    // redirect stdout to main stdout
    nordpyProcess->setProcessChannelMode(QProcess::ForwardedChannels);
    
    // register signal on terminate 
    connect(nordpyProcess, static_cast<void(QProcess::*)(int, QProcess::ExitStatus)>(&QProcess::finished),
        [=]  (int exitCode, QProcess::ExitStatus exitStatus) 
        {
            if(!exitCode) setConnected(false);

            setConnecting(false);
        });
    
    // register signal on error
    connect(nordpyProcess, &QProcess::errorOccurred, 
        [=](QProcess::ProcessError error) 
        { 
            setConnecting(false);
        });
    
    nordpyProcess->start(program, arguments);
    
    setConnected(false);
    return;
}
