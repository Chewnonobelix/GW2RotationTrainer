import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15

import com.chewnonobelix.gw2

Item {
    id: root

    property var currentSkill: skills.currentItem
    property var model
    property bool editable: true
    signal clicked()
    Popup {
        id: popup
        background: Rectangle {
            color: "transparent"
        }

        SkillGrid {
            id: skills
            anchors.fill: parent
            model: root.model

            onCurrentItemChanged: popup.close()
        }
    }


    ColumnLayout {
        anchors.fill: parent
        spacing: 0.1
        ToolButton {
            id: openUp
            text: "^"
            visible: editable
            enabled: editable
            Layout.fillHeight: true
            Layout.preferredWidth: root.height*0.8
            onClicked: {
                popup.open()
            }
        }

        Button {
            id: skill
            Layout.preferredHeight: root.height * (editable ? 0.8 : 1)
            Layout.preferredWidth: Layout.preferredHeight
            icon.source: currentSkill ? currentSkill.url : ""
            icon.color: "transparent"
            display: AbstractButton.IconOnly
            icon {
                width: Layout.preferredHeight
                height: Layout.preferredHeight
            }

            onClicked: {
                root.clicked()
            }
        }
    }
}
