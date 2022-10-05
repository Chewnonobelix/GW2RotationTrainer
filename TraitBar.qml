import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15

import com.chewnonobelix.gw2

Item {
    id: root
    GridLayout {
        rows: 3
        columns: 8

        Button {
            id: spe
            Layout.row: 0
            Layout.column: 0
            Layout.rowSpan: 3
            Layout.columnSpan: 2
        }

        Label {
            id: minor1
            Layout.row: 1
            Layout.column: 2
            Layout.rowSpan: 1
            Layout.columnSpan: 1
        }

        Column {
            id: tier1
            Layout.row: 0
            Layout.column: 3
            Layout.rowSpan: 3
            Layout.columnSpan: 1
            Button {
                id: tier11
            }
            Button {
                id: tier12
            }
            Button {
                id: tier13
            }
        }
        Label {
            id: minor2
            Layout.row: 1
            Layout.column: 4
            Layout.rowSpan: 1
            Layout.columnSpan: 1
        }

        Column {
            id: tier2
            Layout.row: 0
            Layout.column: 5
            Layout.rowSpan: 3
            Layout.columnSpan: 1
            Button {
                id: tier21
            }
            Button {
                id: tier22
            }
            Button {
                id: tier23
            }
        }
        Label {
            id: minor3
            Layout.row: 1
            Layout.column: 6
            Layout.rowSpan: 1
            Layout.columnSpan: 1
        }

        Column {
            id: tier3
            Layout.row: 0
            Layout.column: 7
            Layout.rowSpan: 3
            Layout.columnSpan: 1
            Button {
                id: tier31
            }
            Button {
                id: tier32
            }
            Button {
                id: tier33
            }
        }
    }
}
