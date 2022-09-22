import QtQuick 2.0

QtObject {
    id: root
    property var rotation

    property int success: 0
    property int total: 0
    property string currentDisplay: ""
    property string currentRole: ""
    property var mapping: [
        { "role":"1", "key": "&"},
        { "role":"2", "key": "é"},
        { "role":"3", "key": "\""},
        { "role":"4", "key": "'"},
        { "role":"5", "key": "("},
        { "role":"6", "key": "-"},
        { "role":"7", "key": "è"},
        { "role":"8", "key": "_"},
        { "role":"9", "key": "ç"},
        { "role":"0", "key": "à"},
        { "role":"swap", "key": "²"},
        { "role":"roll", "key": "c"},
        { "role":"F1", "key": "F1"},
        { "role":"F2", "key": "F2"},
        { "role":"F3", "key": "F3"},
        { "role":"F4", "key": "F4"},
        { "role":"F5", "key": "F5"}
    ]
    property int currentRot: 0
    property int currentOpening: 0
    property bool isOpening: rotation && rotation.opening && (currentOpening < rotation.opening.length)
    property string color: "white"
    function indexFromKey(key) {
        for(var i = 0; i < 17; i++) {
            if(mapping[i].key === key) {
                return i
            }
        }
    }

    function keyFromRole(role) {
        for(var i = 0; i < 17; i++) {
            if(mapping[i].role === role) {
                return mapping[i].key
            }
        }
    }

    function validate(key) {
        if(key === currentDisplay) {
            color = "green"
            success++
        }
        else
            color = "red"

        next()
    }

    function next() {
        if(isOpening) {
            currentOpening++
        }
        else {
            currentRot = (currentRot+1)%rotation.rotation.length

        }

        total++
    }

    function randomKey() {
        var rnd = Math.floor(Math.random() * 17)
        currentRole = mapping[rnd].role
        currentDisplay = mapping[rnd].key
        total++
    }
}
