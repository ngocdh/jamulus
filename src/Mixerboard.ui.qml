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
        text: qsTr("Mixerboard")
        font.pixelSize: Qt.application.font.pixelSize * 2
        padding: 10
        color: "black"
    }

    TextArea {
        id:txtClientList
        //width: 240
        text: "Clients list";
    }

    Button {
        id: butRefresh
        x: 0
        y: 233
        text: qsTr("Refresh")
        onClicked: {
            txtClientList.append( mixerDlg.sClientList );
            mixerDlg.Refresh();
            console.log("Refesh clicked");
            console.log(mixerDlg.sClientList);
        }
    }

    Button {
        id: butPracticeMode
        x: 238
        y: 233
        text: qsTr("Practice Mode")
        onClicked: {
            mixerDlg.PracticeMode()
        }
    }
}


