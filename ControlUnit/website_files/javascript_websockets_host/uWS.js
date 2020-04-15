// **** CORE WEBSOCKET FUNCTIONALITY ****
var wsUri = "ws://localhost:3000/";
var output;
var counter = 0;

//initialise websocket
function init() {
    output = document.getElementById("output");
    websocket = new WebSocket(wsUri);
    initialiseFunctions();
}

//initialise core websockets functions
function initialiseFunctions() {
    websocket.onopen = function (evt) {
        onOpen(evt)
    };
    websocket.onclose = function (evt) {
        onClose(evt)
    };
    websocket.onmessage = function (evt) {
        onMessage(evt)
    };
    websocket.onerror = function (evt) {
        onError(evt)
    };
}

//define core websockets functions
function onOpen(evt) {
    doSend("EDBIKE Client Connected to Server");
}

function onClose(evt) {
    doSend("EDBIKE Client Disconnected from Server");
}

function onError(evt) {
    writeToReceived(evt.data);
}

function doSend(message) {
    websocket.send(message); //sends to server
}

function onMessage(evt) { //receives from server
    handleEvent(evt.data);
}

window.addEventListener("load", init, false);