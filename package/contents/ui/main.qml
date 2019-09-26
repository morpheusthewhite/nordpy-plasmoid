import QtQuick 2.0
import QtQuick.Layouts 1.0
import org.kde.plasma.core 2.0 as PlasmaCore
import org.kde.plasma.plasmoid 2.0
import org.kde.plasma.components 2.0 as PlasmaComponents

import org.kde.private.nordpy 1.0 as NordPy

Item {
    id: root
    property var connected: nordpyManager.connected
    property var connecting: nordpyManager.connecting
    property var ipText: "Retrieving IP..."
    
    property int refreshIntervalMs: 30000
    
    Plasmoid.fullRepresentation: ColumnLayout {
        id: rootLayout
        
        RowLayout {
            PlasmaComponents.Button {
                id: connectButton
                
                text: "Connect"
                enabled: !connected && !connecting
                
                onClicked: nordpyManager.startNordPy()
            }
            
            PlasmaComponents.Button {
                id: disconnectButton
                
                text: "Disconnect"
                enabled: connected && !connecting
                
                onClicked: nordpyManager.stopNordPy()
            }
        }
        
        PlasmaComponents.Label {
            id: connectionStatusLabel
            
            Layout.alignment: Qt.AlignCenter
            
            text: {
                if (connecting) return "Connecting"
                else if (connected) return "Connected" 
                else "Disconnected"
            }
            
            color: {
                if (!connected) return systemPalette.text
                else return systemPalette.highlight
            }
            
        }
        
        PlasmaComponents.Label {
            id: ipLabel
            
            Layout.alignment: Qt.AlignCenter
            text: root.ipText
            
            Component.onCompleted: ipScript.sendMessage({})
        }
    }
    
    SystemPalette { id: systemPalette; colorGroup: SystemPalette.Active }
    
    // retrieve asyncronously IP
    WorkerScript {
        id: ipScript
        source: "../scripts/utils.mjs"
        
        onMessage: root.ipText = "IP: " + messageObject
    }
    
    NordPy.NordPyConnectionManager {
         id: nordpyManager
         
         onConnectedChanged: {
             ipScript.sendMessage({})
         }
    }
    
    Timer {
        interval: root.refreshIntervalMs; running: true; repeat: true
        onTriggered: {
            console.log("Refreshing status")
            nordpyManager.refreshStatus()
        }
    }
}
