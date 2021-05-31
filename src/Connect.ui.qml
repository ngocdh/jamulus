import QtQuick 2.12
import QtQuick.Controls 2.5

import QtQml 2.14 as Qml
import QtQuick 2.4
import QtQuick.Layouts 1.0
import QtQuick.Controls 1.4
import QtQuick.Controls.Styles.Flat 1.0 as Flat
import QtQuick.Extras 1.4
import QtQuick.Extras.Private 1.0
import QtQuick.Controls.Styles 1.4


Page {
    width: 600
    height: 400

    header: Label {
        text: qsTr("Connect")
        font.pixelSize: Qt.application.font.pixelSize * 2
        padding: 10
    }

    Label {
        text: qsTr("You are on Page connect.")
        anchors.centerIn: parent
    }

    TextField {
        id: edtServerAddress
        x: 6
        y: 233
        placeholderText: qsTr("Server Address")
        style: TextFieldStyle {
            textColor: "black"
        }
    }

    Button {
        id: button
        x: 238
        y: 233
        text: qsTr("Connect")
        onClicked: connectDlg.connect(edtServerAddress.text)
    }
}
