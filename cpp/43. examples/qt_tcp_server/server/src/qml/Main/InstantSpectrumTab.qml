import QtQml 2.15
import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Controls.Material 2.12
import QtQuick.Controls.Universal 2.15
import QtQuick.Layouts 1.15
import QtCharts 2.3

Pane {
    id: __this

    Connections {
        target: instantSpectrumTabData
        function onCurrentDosimeterChanged() {
            console.log("Current dosimeter changed:", instantSpectrumTabData.currentDosimeter);
            if (instantSpectrumTabData.currentDosimeter) {
                console.log("Current dosimeter name:", instantSpectrumTabData.currentDosimeter.name);
                instantSpectrumTabDataConnections.enabled = true;
            } else {
                console.log("No current dosimeter selected");
            }
        }
    }

    Connections {
        id: instantSpectrumTabDataConnections
        enabled: false
        target: instantSpectrumTabData.currentDosimeter
        function onSpectrumChanged() {
            if (instantSpectrumTabData.currentDosimeter) {
                console.log("Spectrum data changed for current dosimeter:", instantSpectrumTabData.currentDosimeter.spectrum);
            } else {
                console.log("No current dosimeter selected, skipping spectrum update.");
            }
        }
    }

    ColumnLayout
    {
        anchors.fill: parent

        RowLayout
        {
            Layout.fillWidth: true
            Layout.fillHeight: true
            
            ListView {
                id: dosimetersListView
                Layout.fillWidth: true
                Layout.fillHeight: true

                Connections {
                    target: dosimetersHolder
                    function onDosimetersChanged() {
                        console.log("Dosimeters changed:", dosimetersHolder.dosimeters);
                        console.log("Dosimeters length:", dosimetersHolder.dosimeters.length);
                        if (dosimetersHolder == null || dosimetersHolder.dosimeters == null) {
                            console.log("DosimetersHolder or dosimeters is null");
                            return;
                        }
                        console.log("Updating model with new dosimeters");
                        dosimetersListView.model = dosimetersHolder.dosimeters;
                    }
                }

                delegate: Pane {
                    width: ListView.view.width
                    visible: true

                    RowLayout {
                        anchors.fill: parent

                        TextArea {
                            text: modelData.name
                            Layout.fillWidth: true
                        }

                        TextArea {
                            text: modelData.port
                            Layout.alignment: Qt.AlignRight
                        }
                    }
                }
            }
            ListView {
                id: spectrumListView
                Layout.fillWidth: true
                Layout.fillHeight: true

                Connections {
                    target: instantSpectrumTabData
                    function onDosimetersChanged() {
                        console.log("Spectrum Dosimeters changed:", instantSpectrumTabData.dosimeters);
                        console.log("Spectrum Dosimeters length:", instantSpectrumTabData.dosimeters.length);
                        if (instantSpectrumTabData == null || instantSpectrumTabData.dosimeters == null) {
                            console.log("Spectrum Dosimeters or dosimeters is null");
                            return;
                        }
                        console.log("Spectrum Updating model with new dosimeters");
                        dosimetersListView.model = instantSpectrumTabData.dosimeters;
                    }
                }

                delegate: Pane {
                    width: ListView.view.width
                    visible: true

                    RowLayout {
                        anchors.fill: parent

                        TextArea {
                            text: modelData.name
                            Layout.fillWidth: true
                        }
                    }
                }
            }
        }

        SpectrumGraphic {
            id: spectrumGraphic
            Layout.fillWidth: true
            Layout.fillHeight: true
        }   
    }
}
