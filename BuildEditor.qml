import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15

import com.chewnonobelix.gw2 1.0

Page {
    id: root
    GridLayout {
        anchors.fill: parent
        SkillBar {
            Layout.row: 0
            Layout.fillHeight: true
            Layout.fillWidth: true
            id: bar
            onSkillActivated: console.log(root.contentWidth, root.contentHeight)
        }
        TraitBar {
            Layout.row: 1
            Layout.fillHeight: true
            Layout.fillWidth: true
        }
    }
}
