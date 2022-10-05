import QtQuick 2.15
import QtQuick.Layouts 1.15
import QtQuick.Controls 2.15

import com.chewnonobelix.gw2 1.0
Item {
    id: root
    GW2RotationHandler {
        id: handler
    }

    signal skillActivated(string role)
    RowLayout  {
        anchors.fill: parent
        Repeater {
            model: ["swap", "1", "2", "3", "4", "5", "6", "7", "8", "9", "0" , "roll"]

            Button {
                text: modelData
                Shortcut {
                    sequence: handler.keyFromRole(modelData)
                    onActivated: root.skillActivated(modelData)
                }
            }
        }
    }
}
