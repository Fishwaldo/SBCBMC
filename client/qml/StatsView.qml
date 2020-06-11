import QtQuick 2.12
import QtQuick.Layouts 1.12
import QtQuick.Controls 2.12
import QtQuick.Controls.Imagine 2.12
import QtQuick.Window 2.0
import QtCharts 2.15
import QtQuick.Extras 1.4 as OldExtras
import QtQuick.Controls.Styles 1.4 as Oldstyle
import QtRemoteObjects 5.12

Frame {
    width: parent.width
    Layout.fillWidth: true
    Layout.fillHeight: true
    ColumnLayout { 
        width: parent.width
        GlowingLabel {
            text: remoteModel.name
            color: "white"
            font.pixelSize: fontSizeMedium
            Layout.alignment: Qt.AlignVCenter
            Layout.fillWidth: true

        }
        Frame { 
            width: parent.width
            Layout.fillWidth: true
            Layout.fillHeight: true

            OldExtras.CircularGauge {
                style: Oldstyle.CircularGaugeStyle {
                    needle: Rectangle {
                        y: outerRadius * 0.15
                        implicitWidth: outerRadius * 0.03
                        implicitHeight: outerRadius * 0.9
                        antialiasing: true
                        color: Qt.rgba(0.66, 0.3, 0, 1)
                    }
                }
                value: remoteModel.temp
                anchors.centerIn: parent
            }
        }
    }
}
