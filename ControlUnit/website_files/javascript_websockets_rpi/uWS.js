// **** CORE WEBSOCKET FUNCTIONALITY ****
var wsUri = "ws://10.9.8.2:3000/";
var output;
var counter = 0;

/**
 * Initialiserer uWebSockets
 */
function init() {
    output = document.getElementById("output");
    websocket = new WebSocket(wsUri);
    initialiseFunctions();
}
/**
 * Initialiserer uWebSockets' basisfunktioner
 */
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

/**
 * Sender besked til serveren om, at klienten er forbundet
 */
function onOpen(evt) {
    doSend("EDBIKE Client Connected to Server");
}

/**
 * Sender besked til serveren om, at klienten ikke længere er forbundet
 */
function onClose(evt) {
    doSend("EDBIKE Client Disconnected from Server");
}

/**
 * Sender data til serveren
 */
function doSend(Message) {
    websocket.send(Message); //sends to server
}

/**
 * Modtager data fra serveren
 */
function onMessage(evt) { //receives from server
    handleEvent(evt.data);
}

window.addEventListener("load", init, false);
