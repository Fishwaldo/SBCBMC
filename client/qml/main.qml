import QtQuick 2.15
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.15
import QtQuick.Window 2.0
import QtCharts 2.15


ApplicationWindow {
    visible: true

    menuBar: MenuBar {
        // ...
    }

    header: ToolBar {
        // ...
    }

    footer: TabBar {
        // ...
    }

    StackView {
        anchors.fill: parent
        GridLayout {
            id: grid
            anchors.fill: parent
            Text { text: "Three"; font.bold: true; }
            Text { text: "words"; color: "red" }
            Text { text: "in"; font.underline: true }
            Text { text: "a"; font.pixelSize: 20 }
            Text { text: "row"; font.strikeout: true }
        }

    }
}