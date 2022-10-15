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

    GW2Build {
        id: build

        mainHand1: mainHand1.currentText
        offHand1: offHand1.currentText
        heal: heal.currentSkill ? heal.currentSkill.id : -1
        elite: elite.currentSkill? elite.currentSkill.id : -1
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

            Label {
                text: "Weapons"
            }

            ComboBox {
                id: mainHand1
                model: prof.mainHand
                textRole: "name"
                valueRole: "twohanded"

                onCurrentValueChanged: function() {
                    console.log(currentValue, currentText, offHand1.indexOfValue(currentText))
                    if(currentValue) {
                        offHand1.currentIndex = offHand1.indexOfValue(currentText)
                        build.offHand1 = ""
                    }
                    else {
                        offHand1.currentIndex = -1
                    }
                }
            }
            ComboBox {
                id: offHand1
                model: prof.offHand
                enabled: !mainHand1.currentValue
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
                    Component.onCompleted: console.log(objectName)
                    model: prof.utilities
                    property string getter: 'utility'+(index+1)

                    onCurrentSkillChanged: build[getter] = currentSkill.id
                    onClicked: {
                        console.log(currentSkill.name, index, modelData, build[getter])
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
                editable: true
                onClicked: {
                    console.log(currentSkill.name)
                }
            }

            Repeater {
                id: rep2
                model: [1,2,3,4,5]
                Layout.row: 2

                SkillButton {
                    Layout.preferredHeight: 100
                    Layout.preferredWidth: 100
                    id: skillWeapon
                    editable: false

                    onClicked: {
                        console.log(currentSkill.name, index, modelData)
                    }
                }
            }

        }
    }
}
