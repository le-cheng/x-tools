import QtQuick
import QtQuick.Layouts
import QtQuick.Controls
import QtQuick.Controls.Universal

import SAK.Custom
import "../toolbox"

ToolBox {
    id: root
    controllerComponent: comComtrollerComponent
    groupName: "TCPClient"

    property SAKTcpClientTool tcpClientTool: null

    Component {
        id: comComtrollerComponent
        TcpClientPageController {}
    }

    Component.onCompleted: {
        toolBox.initialize(SAKToolsFactory.TcpClientTool)
        tcpClientTool = toolBox.communicator
        if (tcpClientTool) {
            var controller = deviceControllerLoader.item
            tcpClientTool.clientIp = Qt.binding(function () {
                return controller.deviceController.clientIp
            })
            tcpClientTool.clientPort = Qt.binding(function () {
                return Number(controller.deviceController.clientPort)
            })
            tcpClientTool.specifyClientIpPort = Qt.binding(function () {
                return controller.deviceController.specifyClientIpPort
            })
            tcpClientTool.serverIp = Qt.binding(function () {
                return controller.deviceController.serverIp
            })
            tcpClientTool.serverPort = Qt.binding(function () {
                return Number(controller.deviceController.serverPort)
            })
            controller.deviceController.bindingIpPort = Qt.binding(function () {
                return tcpClientTool.bindingIpPort
            })
            controller.deviceController.deviceIsWorking = Qt.binding(function () {
                return tcpClientTool.isWorking
            })
        }
    }

    onInvokeOpenDevice: {
        toolBox.open()
    }

    onInvokeCloseDevice: {
        toolBox.close()
    }
}