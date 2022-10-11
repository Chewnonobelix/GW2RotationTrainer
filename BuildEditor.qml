import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15

import com.chewnonobelix.gw2 1.0

Page {
    id: root
    GW2DataProvider {
        id: network

        Component.onCompleted: requestProfessions()
    }

    GW2Profession {
        id: prof
    }

    Connections {
        target: network

        function onProfessionsEmited(pfs) {
            classes.model = pfs
        }
    }

    ScrollView {
        Grid {
            anchors.fill: parent
            columns: 5
            Label {
                text: "Class"
            }
            ComboBox {
                id: classes

                onCurrentTextChanged: prof.setName(currentText)
            }

            Repeater {
                id: rep
                model: prof.utilities
                Button {
                    id: skill
                    icon.source: modelData.url
                    icon.color: "transparent"

                    onClicked: {
                        console.log(index, rep.model.length, modelData.description)
                    }
                }
            }
        }
    }
}
