import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.12
import QtQuick.Dialogs

import com.chewnonobelix.gw2 1.0

Page {
    id: page
    width: 600
    height: 400

    title: qsTr("Trainer")

    GW2RotationHandler {
        id: handler
    }

    Component.onCompleted: {
    }

//    FileDialog {
//        id: loader
//        nameFilters: ["JSON Files (*.json)"]
//        fileMode: FileDialog.OpenFile

//        onAccepted: handler.load(selectedFile)
//    }

    Button{
        text: "Load"
        onClicked: handler.load()
    }

    Label {
        id: display
        Component.onCompleted:{
        }
        anchors.left: parent.left
        anchors.top: parent.top
        anchors.right: parent.right
        height: page.height * .1
        fontSizeMode: Text.Fit
        verticalAlignment: Text.AlignVCenter
        horizontalAlignment: Text.AlignHCenter
        text: (handler.success/handler.total)*100+"%(" + handler.success+"/"+handler.total + ") \n" + handler.currentRole + " (" + handler.currentDisplay + ")"
        color: handler.color
    }

    RowLayout {
        id: skillColumn
        anchors.left: parent.left
        anchors.bottom: parent.bottom
        anchors.right: parent.right
        height: page.height * .45

        Button {
            id: button1
            text: "1"

            Shortcut {
                sequences: ["&", "a"]
                onActivated: button1.clicked()
            }

            onClicked: {
                handler.validate("&")
            }
        }
        Button {
            id: button2
            text: "2"
            Shortcut {
                sequence: "é"
                onActivated: button2.clicked()
            }

            onClicked: {
                handler.validate("é")
            }
        }
        Button {
            id: button3
            text: "3"
            Shortcut {
                sequence: "\""
                onActivated: button3.clicked()
            }

            onClicked: {
                handler.validate("\"")
            }
        }
        Button {
            id: button4
            text: "4"
            Shortcut {
                sequence: "'"
                onActivated: button4.clicked()
            }

            onClicked: {
                handler.validate("'")
            }
        }
        Button {
            id: button5
            text: "5"
            Shortcut {
                sequence: "("
                onActivated: button5.clicked()
            }

            onClicked: {
                handler.validate("(")
            }
        }
        Button {
            id: button6
            text: "6"
            Shortcut {
                sequence: "-"
                onActivated: button6.clicked()
            }

            onClicked: {
                handler.validate("-")
            }
        }
        Button {
            id: button7
            text: "7"
            Shortcut {
                sequence: "è"
                onActivated: button7.clicked()
            }

            onClicked: {
                handler.validate("è")
            }
        }
        Button {
            id: button8
            text: "8"
            Shortcut {
                sequence: "_"
                onActivated: button8.clicked()
            }

            onClicked: {
                handler.validate("_")
            }
        }
        Button {
            id: button9
            text: "9"
            Shortcut {
                sequence: "ç"
                onActivated: button9.clicked()
            }

            onClicked: {
                handler.validate("ç")
            }
        }
        Button {
            id: button0
            text: "0"
            Shortcut {
                sequence: "à"
                onActivated: button0.clicked()
            }

            onClicked: {
                handler.validate("à")
            }
        }
    }

    RowLayout {
        id: fColumn
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.top: display.bottom
        height: page.height * .45

        Button {
            id: c
            text: "c"
            Shortcut {
                sequence: "c"
                onActivated: c.clicked()
            }

            onClicked: {
                handler.validate("c")
            }
        }
        Button {
            id: square
            text: "²"
            Shortcut {
                sequence: "²"
                onActivated: square.clicked()
            }

            onClicked: {
                handler.validate("²")
            }
        }
        Button {
            id: f1
            text: "F1"
            Shortcut {
                sequence: "F1"
                onActivated: f1.clicked()
            }

            onClicked: {
                handler.validate("F1")
            }
        }
        Button {
            id: f2
            text: "F2"
            Shortcut {
                sequence: "F2"
                onActivated: f2.clicked()
            }

            onClicked: {
                handler.validate("F2")
            }
        }
        Button {
            id: f3
            text: "F3"
            Shortcut {
                sequence: "F3"
                onActivated: f3.clicked()
            }

            onClicked: {
                handler.validate("F3")
            }
        }
        Button {
            id: f4
            text: "F4"
            Shortcut {
                sequence: "F4"
                onActivated: f4.clicked()
            }

            onClicked: {
                handler.validate("F4")
            }
        }
        Button {
            id: f5
            text: "F5"
            Shortcut {
                sequence: "F5"
                onActivated: f5.clicked()
            }

            onClicked: {
                handler.validate("F5")
            }
        }
    }
}
