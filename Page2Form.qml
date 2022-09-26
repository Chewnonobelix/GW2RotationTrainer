import QtQuick 2.15
import QtQuick.Controls 2.15
import com.chewnonobelix.gw2 1.0

Page {
    id:root
    width: 600
    height: 400

    title: qsTr("Page 2")
    GW2RotationHandler {
        id: handler
        mapping: [
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
    }

    property var registerList: []
    function saveFile(fileUrl, text) {
        var request = new XMLHttpRequest();
        request.open("PUT", fileUrl, false);
        request.send(text);
        return request.status;
    }

    function onPushed(key) {
        console.log(registerList.length, handler.indexFromKey(key), handler.mapping[handler.indexFromKey(key)].role, handler.mapping[handler.indexFromKey(key)].key)
        var obj = {}
        obj.role = handler.mapping[handler.indexFromKey(key)].role
        registerList[registerList.length] = obj
        console.log(registerList, registerList.length, JSON.stringify(registerList))
        handler.save('D:/bouya.json', registerList)
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
}
