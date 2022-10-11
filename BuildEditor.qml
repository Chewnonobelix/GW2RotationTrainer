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
        GridLayout {
            anchors.fill: parent
            columns: 5
            Label {
                text: "Class"
            }
            ComboBox {
                id: classes

                onCurrentTextChanged: prof.setName(currentText)
            }

            SkillButton {
                Layout.preferredHeight: 100
                Layout.preferredWidth: 100
                Layout.row: 1
                id: heal
                model: prof.heal
                onClicked: {
                    console.log(currentSkill.name)
                }
            }

            Repeater {
                id: rep
                model: [7,8,9]
                Layout.row: 1

                SkillButton {
                    Layout.preferredHeight: 100
                    Layout.preferredWidth: 100
                    id: skill
                    model: prof.utilities
                    onClicked: {
                        console.log(currentSkill.name)
                    }
                }
            }

            SkillButton {
                Layout.preferredHeight: 100
                Layout.preferredWidth: 100
                Layout.row: 1
                Layout.column: 4
                id: elite
                model: prof.elite
                onClicked: {
                    console.log(currentSkill.name)
                }
            }

        }
    }
}
