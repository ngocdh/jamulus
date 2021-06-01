import QtQuick 2.12
import QtQuick.Controls 2.5

import QtQml 2.14 as Qml
import QtQuick 2.4
import QtQuick.Layouts 1.0
import QtQuick.Controls 1.4
/*import QtQuick.Controls.Styles.Flat 1.0 as Flat
import QtQuick.Extras 1.4
import QtQuick.Extras.Private 1.0
*/

Page {
    width: 600
    height: 400

    header: Label {
        text: qsTr("Profile")
        font.pixelSize: Qt.application.font.pixelSize * 2
        padding: 10
    }

    Label {
        text: qsTr("You are on Page profile.")
        anchors.centerIn: parent
    }

    TextField {
        id: textField
        x: 26
        y: 4
        placeholderText: qsTr("Alias/Name")
    }

    ComboBox {
        id: cmbInstrument
        x: 26
        y: 58
    }

    ComboBox {
        id: cmbCountry
        x: 26
        y: 113
    }

    TextField {
        id: edtCity
        x: 26
        y: 170
        placeholderText: qsTr("City")
    }

    ComboBox {
        id: cmbSkill
        x: 26
        y: 216
    }
}
