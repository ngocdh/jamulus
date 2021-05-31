import QtQuick 2.12
import QtQuick.Controls 2.5


ApplicationWindow {
    width: 640
    height: 480
    visible: true
    title: qsTr("Tabs")

    SwipeView {
        id: swipeView
        anchors.fill: parent
        currentIndex: tabBar.currentIndex

        Connect {
        }

//        Chat {
//        }

        Mixerboard {
        }

        Profile {
        }

/*        Settings {
        }

        Advanced {
        }*/
    }

    footer: TabBar {
        id: tabBar
        currentIndex: swipeView.currentIndex

        TabButton {
            text: qsTr("Connect")
        }
/*        TabButton {
            text: qsTr("Chat")
        }*/
        TabButton {
            text: qsTr("Mixer")
        }
        TabButton {
            text: qsTr("Profile (Not working)")
        }
/*        TabButton {
            text: qsTr("Settings")
        }
        TabButton {
            text: qsTr("Advanced")
        }*/
    }
}
