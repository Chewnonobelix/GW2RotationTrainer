import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Dialogs
import QtQuick.Layouts 1.15
import com.chewnonobelix.gw2 1.0

Page {
    id:root
    width: 600
    height: 400

    title: qsTr("Register rotation")
    GW2RotationHandler {
        id: handler

        rotation: {"opening": [], "rotation": []}
    }

    property var registerList: []
    Dialog {
        id: saver
        onOpened: buildName.text = ""
        width: parent.width * 0.6
        height: parent.height * 0.5
        ColumnLayout {
            anchors.fill: parent
            TextField {
                id: buildName
            }

            RowLayout {
                Button {
                    text: "Save"
                    onClicked: {
                        handler.save(buildName.text)
                        saver.close()
                    }
                }
                Button {
                    text: "Cancel"
                    onClicked: saver.close()
                }
            }
        }
    }

    //    FileDialog {
    //        id: saver
    //        nameFilters: ["JSON Files (*.json)"]
    //        fileMode: FileDialog.SaveFile

    //        onAccepted: handler.save(selectedFile)
    //    }

    function onPushed(key) {
        var obj = {}
        obj.role = handler.mapping[handler.indexFromKey(key)].role
        handler.append(switcher.text, obj)
    }

    Shortcut {
        sequence: "&"

        onActivated: onPushed(sequence)
    }
    Shortcut {
        sequence: "é"

        onActivated: onPushed(sequence)
    }
    Shortcut {
        sequence: "\""

        onActivated: onPushed(sequence)
    }
    Shortcut {
        sequence: "'"

        onActivated: onPushed(sequence)
    }
    Shortcut {
        sequence: "("

        onActivated: onPushed(sequence)
    }

    Shortcut {
        sequence: "-"

        onActivated: onPushed(sequence)
    }
    Shortcut {
        sequence: "è"

        onActivated: onPushed(sequence)
    }
    Shortcut {
        sequence: "_"

        onActivated: onPushed(sequence)
    }
    Shortcut {
        sequence: "ç"

        onActivated: onPushed(sequence)
    }
    Shortcut {
        sequence: "à"

        onActivated: onPushed(sequence)
    }
    Shortcut {
        sequence: "c"

        onActivated: onPushed(sequence)
    }
    Shortcut {
        sequence: "²"

        onActivated: onPushed(sequence)
    }

    Button {
        id: save
        text: "Save"
        onClicked:saver.open()
    }

    Switch {
        id: switcher
        text: checked ? "opening" : "rotation"
        anchors {
            left: save.right
        }
    }

    Button {
        id: clear
        text: "Clear"
        onClicked: handler.rotation = {"opening": [], "rotation": []}
        anchors {
            top: save.bottom
        }
    }
}
