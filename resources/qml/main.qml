import QtQuick 2.12

import Blusher 0.1

import ColorMeter 1.0

Window {
  width: 400
  height: 300
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

//  Flow {
//    width: 200
//    height: 200

//    Repeater {
//      model: ColorMeter.image
//      Rectangle {
//        width: 10
//        height: 10
//        color: ColorMeter.image[index]
//      }
//    }
//  }
}
