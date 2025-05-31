import QtCharts 2.3
import QtQuick 2.0

ChartView {
    id: __this

    property var arrayData: []
    property int maxX: 1024
    property int maxY: 1024
    property int minX: 0
    property int minY: 0
    property int xStep: 12
    property int yStep: 10

    LineSeries {
        id: lineSeries
        name: "Spectrum Data"
        axisX: xAxis
        axisY: yAxis

        // Dynamically update the series data
        onPointsChanged: {
            console.log("Line series points changed:", lineSeries.points);
        }
    }
}
