import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15
import com.chewnonobelix.gw2

Item {
    id: root

    property var model
    property var currentItem

    GridLayout {
        anchors.fill: parent
        columns: 4
        Repeater {
            model: root.model
            Button {
                icon.source: modelData.url
                icon.color: "transparent"
                property string name: modelData.name
                ToolTip {
                    text: name
                    delay: 100
                    timeout: 0
                }

                onClicked: root.currentItem = modelData
            }
        }
    }
}
