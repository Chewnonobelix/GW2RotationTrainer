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

    GW2RotationHandler {
        id: handler
    }


    GW2Profession {
        id: prof
    }

    GW2Build {
        id: build

        profession: classes.currentText
        mainHand1: mainHand1.currentText
        offHand1: offHand1.currentText
        heal: heal.currentSkill ? heal.currentSkill.id : -1
        elite: elite.currentSkill? elite.currentSkill.id : -1
//        name: name.text
    }

    Connections {
        target: network

        function onProfessionsEmited(pfs) {
            classes.model = pfs
        }
    }
    Menu {
        id: menuLoader
        x: loader.x + loader.width

        Repeater {
            id: rep

            MenuItem {
                text: modelData.name

                onClicked: build.load(modelData.id)
            }
        }
    }

    ScrollView {
        GridLayout {
            anchors.fill: parent
            columns: 5
            Button{
                id: loader
                text: "Load"
                onClicked: {
                    rep.model = handler.buildsList()
                    menuLoader.open()
                }
            }

            Button {
                text: "Save"
                onClicked: build.save()
            }

            Label{
                text: build.name
            }

            Label {
                text: "Class"
                Layout.row: 1
            }
            ComboBox {
                id: classes
                Layout.row: 1
                Layout.column: 1
                onCurrentTextChanged: prof.setName(currentText)
            }

            Label {
                text: "Weapons"
                Layout.row: 1
                Layout.column: 2
            }

            ComboBox {
                id: mainHand1
                model: prof.mainHand
                textRole: "name"
                valueRole: "twohanded"
                Layout.row: 1
                Layout.column: 3

                onCurrentValueChanged: function() {
                    if(currentValue) {
                        offHand1.currentIndex = offHand1.indexOfValue(currentText)
                        build.offHand1 = ""
                    }
                    else {
                        offHand1.currentIndex = 0
                        build.offHand1 = Qt.binding(function() {
                            return offHand1.currentText
                        })
                    }
                }
            }
            ComboBox {
                id: offHand1
                model: prof.offHand
                enabled: !mainHand1.currentValue
                textRole: "name"
                valueRole: "twohanded"
                Layout.row: 1
                Layout.column: 4

                onCurrentValueChanged: function() {
                    if(currentValue) {
                        mainHand1.currentIndex = mainHand1.find(currentText)
                    }
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
                    }
                }
            }

            SkillButton {
                Layout.preferredHeight: 100
                Layout.preferredWidth: 100
                Layout.row: 3
                id: heal
                model: prof.heal
                onClicked: {
                }
            }

            Repeater {
                id: repUtils
                model: [7,8,9]
                Layout.row: 3

                SkillButton {
                    Layout.preferredHeight: 100
                    Layout.preferredWidth: 100
                    id: skill
                    model: prof.utilities
                    property string getter: 'utility'+(index+1)

                    Connections {
                        target: build
                        function onUtilityChanged() {
                            var skillId
                            skillConnection.enabled = false
                            for(var it in prof.utilities) {
                                if(prof.utilities[it].id === build[getter])
                                    skillId = prof.utilities[it]
                            }

                            reset(skillId ? skillId : null)
                            skillConnection.enabled = true
                        }
                    }

                    Connections {
                        id: skillConnection
                        target: skill
                        function onCurrentSkillChanged(currentSkill) {
                            build[getter] = skill.currentSkill ? skill.currentSkill.id : -1                        }
                    }

                    onClicked: {
                    }
                }
            }

            SkillButton {
                Layout.preferredHeight: 100
                Layout.preferredWidth: 100
                Layout.row: 3
                Layout.column: 4
                id: elite
                model: prof.elite
                editable: true
                onClicked: {
                }
            }
        }
    }
}
