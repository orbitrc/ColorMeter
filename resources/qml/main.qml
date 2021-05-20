import QtQuick 2.12

import Blusher 0.1

import ColorMeter 1.0

Window {
  width: 400
  height: 300
  minimumWidth: 400
  minimumHeight: 300
  maximumWidth: 400
  maximumHeight: 300

  visible: true
  title: Process.env.BLUSHER_APP_NAME

  Preview {
    id: preview

    image: ColorMeter.image
  }

  Button {
    id: pickButton

    anchors.top: preview.bottom
    anchors.topMargin: 20

    title: 'Pick'

    onClicked: {
      ColorMeter.pickMode = true;
    }
  }

  Text {
    x: 200
    y: 10
    text: 'R: ' + hexTo256Red()
  }
  Text {
    x: 200
    y: 30
    text: 'G: ' + hexTo256Green()
  }
  Text {
    x:200
    y: 50
    text: 'B: ' + hexTo256Blue()
  }

  Text {
    x: 200
    y: 200
    text: ColorMeter.color.toString()
  }

  function hexTo256Red() {
    return Number.parseInt(ColorMeter.color.toString().slice(1).slice(0, 2), 16);
  }

  function hexTo256Green() {
    return Number.parseInt(ColorMeter.color.toString().slice(1).slice(2, 4), 16);
  }

  function hexTo256Blue() {
    return Number.parseInt(ColorMeter.color.toString().slice(1).slice(4, 6), 16);
  }
}
