//EDBike functionality

/**
 * Pauser eksekveringen af javascriptet i et antal millisekunder.
 * Taget fra https://stackoverflow.com/questions/951021/what-is-the-javascript-version-of-sleep
 * @param {number} ms Det antal millisekunder, pausen skal vare
 */
function sleep(ms) {
    return new Promise(resolve => setTimeout(resolve, ms));
}

/**
 * Enums, der indeholder ASCII-værdierne for de events der udveksles i EDBike-systemet.
 */
eventEnums = {
    //events fra client
    USER_LOCK: '76',
    USER_UNLOCK_TRY: '84',
    USER_REQUESTS_RIDES: '82',
    USER_SET_WHEELCIRCUMFERENCE: '87',
    USER_DISCARDED_RIDE: '88',
    USER_SAVED_RIDE: '83',
    USER_DELETED_RIDE: '67',

    //events fra server
    PIN_VALIDATE_RETURNED_WRONG_PIN: '77',
    PIN_VALIDATE_RETURNED_TIMEOUT: '78',
    PIN_VALIDATE_RETURNED_CORRECT_PIN: '86',
    SERVER_SENT_NUMBER_OF_RIDES: '68',
    SERVER_SENT_LIVEDATA: '80',
    SERVER_SENT_RIDES: '70',
    VALIDATEWHEELSIZE_RETURNED_TRUE: '81',
    VALIDATEWHEELSIZE_RETURNED_FALSE: '89',

    //events fra SLAVE
    LOCKED: '111'
}

/**
 * Tager imod et event fra serveren og kalder den funktion, der skal håndtere dette event
 * @param {string} event Det EDBike event og data, der er sendt til brugerfladen fra serveren
 */
function handleEvent(event) {
    var eventType = event.substr(0, 2)
    switch (eventType) {
        case eventEnums.SERVER_SENT_LIVEDATA:
            updateLiveData(event)
            break;
        case eventEnums.PIN_VALIDATE_RETURNED_CORRECT_PIN:
            unlockUI();
            break;
        case eventEnums.PIN_VALIDATE_RETURNED_WRONG_PIN:
            wrongPin(event);
            break;
        case eventEnums.PIN_VALIDATE_RETURNED_TIMEOUT:
            timeOut(event);
            break;
        case eventEnums.SERVER_SENT_RIDES:
            updateRideData(event);
            break;
        case eventEnums.SERVER_SENT_NUMBER_OF_RIDES:
            writeToNumOfRides(event)
            break;
        case eventEnums.LOCKED:
            UIlockedBySlave();
            break;
        case "gg":
            setWheelCirc();
            break;
        case "dd":
            illegalWheelSize();
            break;
        default:
            break;
    }
}

/**
 * Opdaterer livedata
 * @param {int} SERVER_SENT_LIVEDATA Livedata, der er sendt fra serveren
 */
function updateLiveData(SERVER_SENT_LIVEDATA) {
    var prependZeros = "0000" + SERVER_SENT_LIVEDATA.substr(2, 5);
    var cutToLength = prependZeros.substr(-4);
    document.getElementById("live_speed").innerHTML = cutToLength;
}

/**
 * Opdaterer antallet af ture
 * @param {int} SERVER_SENT_NUMBER_OF_RIDES Antal ture, der er sendt fra serveren
 */
function writeToNumOfRides(SERVER_SENT_NUMBER_OF_RIDES) {
    numOfRides = SERVER_SENT_NUMBER_OF_RIDES.substr(2)
    document.getElementById("numOfRides").innerHTML = numOfRides;
}

/**
 * Viser en popup der spørger brugeren, om den netop kørte tur skal gemmes i databasen
 */
function saveRideQuery() {
    document.getElementById("locktext1").className = "red";
    document.getElementById("locktext2").className = "transparent";
    document.getElementById("locktext3").className = "red";
    document.getElementById("locktext4").className = "transparent";
    document.getElementById("rideSavePopUp").style.display = "block";
}

/**
 * Kaldes når brugeren vælger at gemme den netop kørte tur og sender eventet USER_SAVED_RIDE til brugerfladen
 */
function confirmSaveRideQuery() {
    document.getElementById("rideSavePopUp").style.display = "none";
    UIlockedByUser();
    doSend(eventEnums.USER_SAVED_RIDE); //user saved ride
}

/**
 * Kaldes når brugeren vælger at gemme den netop kørte tur og sender eventet USER_DISCARDED_RIDE til brugerfladen
 */
function rejectSaveRideQuery() {
    document.getElementById("rideSavePopUp").style.display = "none";
    UIlockedByUser();
    doSend(eventEnums.USER_DISCARDED_RIDE); //user rejected saving ride
}

/**
 * Tager imod ID'et på en tur, der skal slettes, og sender det til serveren sammen med eventet USER_DELETED_RIDE.
 * Opdaterer derefter brugerfladen ved at trække alle rides fra serveren.
 * @param {int} ride ID'et på den tur, der skal slettes
 */
function deleteRide(ride) {
    doSend(eventEnums.USER_DELETED_RIDE + ride);
    document.getElementById("rideDataContent").innerHTML = ""; //remove all rides from UI
    doSend(eventEnums.USER_REQUESTS_RIDES);
}

/**
 * Tager imod en tur fra databasen og genererer et collapsible html-element med turdataene.
 * @param {string} SERVER_SENT_RIDES Den tur, der er sendt fra serveren
 */
function updateRideData(SERVER_SENT_RIDES) {
    //create variables with ride data
    var rideNum = SERVER_SENT_RIDES.substr(3, 3);
    var distance = "<b>Distance:</b> " + SERVER_SENT_RIDES.substr(7, 3) + " km";
    var topSpeed = "<b>Tophastighed:</b> " + SERVER_SENT_RIDES.substr(11, 3) + " km/h";
    var avgSpeed = "<b>Gennemsnitlig hastighed:</b> " + SERVER_SENT_RIDES.substr(15, 2) + " km/h";
    var startTime = "<b>Turen begyndte klokken:</b> " + SERVER_SENT_RIDES.substr(18, 2) + ":" + SERVER_SENT_RIDES.substr(20, 2);
    var endTime = "<b>Turen sluttede klokken:</b> " + SERVER_SENT_RIDES.substr(23, 2) + ":" + SERVER_SENT_RIDES.substr(25, 2);
    var date = "<b>Dato:</b> " + SERVER_SENT_RIDES.substr(28, 2) + "/" + SERVER_SENT_RIDES.substr(30, 2) + "/" + SERVER_SENT_RIDES.substr(32, 2);

    //create paragraphs with ride data
    var distanceP = document.createElement("P");
    distanceP.innerHTML = distance;
    var topSpeedP = document.createElement("P");
    topSpeedP.innerHTML = topSpeed;
    var avgSpeedP = document.createElement("P");
    avgSpeedP.innerHTML = avgSpeed;
    var startTimeP = document.createElement("P");
    startTimeP.innerHTML = startTime;
    var endTimeP = document.createElement("P");
    endTimeP.innerHTML = endTime;
    var dateP = document.createElement("P");
    dateP.innerHTML = date;

    //create ride deletion button
    var deleteButton = document.createElement("BUTTON");
    deleteButton.innerHTML = "Slet tur";
    deleteButton.onclick = function () { deleteRide(rideNum); };

    //create div for holding ride content
    var rideContent = document.createElement("div");
    rideContent.className = "rideContent";
    rideContent.id = SERVER_SENT_RIDES;

    //add ride data to div
    rideContent.appendChild(distanceP);
    rideContent.appendChild(topSpeedP);
    rideContent.appendChild(avgSpeedP);
    rideContent.appendChild(startTimeP);
    rideContent.appendChild(endTimeP);
    rideContent.appendChild(dateP);
    rideContent.appendChild(deleteButton);

    //create collapsible for ride
    rideContainer = document.createElement("button");
    rideContainer.className = "collapsible";
    rideContainer.innerHTML = "Tur " + rideNum;
    rideContainer.onclick = function () { collapsibleFunc(SERVER_SENT_RIDES); };

    //add div to collapsible
    rideContainer.appendChild(rideContent);
    document.getElementById("rideDataContent").appendChild(rideContainer);//put everything into the page
}

/**
 * Sørger for at folde en tur ind og ud, når brugeren trykkes på dens collapsible
 * @param {string} rideContentID Den tur, der er trykket på 
 */
function collapsibleFunc(rideContentID) {
    content = document.getElementById(rideContentID);
    if (content.style.display === "block") {
        content.style.display = "none";
    } else {
        content.style.display = "block";
    }
}

/**
 * Låser UI op ved at manuipulere CSS-klasserne for relevante HTML-elementer.
 * Opdaterer samtidig turdata ved at sende eventet USER_REQUESTS_RIDES til serveren
 */
async function unlockUI() {
    document.getElementById("locktext1").className = "green";
    document.getElementById("locktext2").className = "green";
    document.getElementById("locktext3").className = "green";
    document.getElementById("locktext4").className = "green";
    await sleep(800);
    document.getElementById("lock_overlay").style.display = "none";
    document.getElementById("wrongPinPrompt").style.display = "none";
    document.getElementById("rideDataContent").innerHTML = ""; //remove all rides from UI
    doSend(eventEnums.USER_REQUESTS_RIDES); //request rides from server
}

/**
 * Tager imod det antal forsøg brugeren har tilbage og viser antallet i brugerfladen
 * @param {int} PIN_VALIDATE_RETURNED_WRONG_PIN Det antal forsøg til at indtaste den rigtige kode brugeren har tilbage
 */
function wrongPin(PIN_VALIDATE_RETURNED_WRONG_PIN) {
    output = "Du har " + PIN_VALIDATE_RETURNED_WRONG_PIN.substr(2, 3) + " forsøg tilbage";
    document.getElementById("wrongPinPrompt").style.display = "inline";
    document.getElementById("wrongPinPrompt").innerHTML = output;
}

/**
 * Tager imod det antal sekunder der er tilbage af timeoutet og viser det på brugerfladen
 * @param {string} PIN_VALIDATE_RETURNED_TIMEOUT Det antal sekunder, der er tilbage af timeout
 */
function timeOut(PIN_VALIDATE_RETURNED_TIMEOUT) {
    var timeOutValue = PIN_VALIDATE_RETURNED_TIMEOUT.substr(2)
    switch (timeOutValue) {
        case "0":
            output = "Prøv igen";
            document.getElementById("wrongPinPrompt").style.display = "inline";
            document.getElementById("wrongPinPrompt").innerHTML = output;
            break;
        case "1":
            output = "Vent " + PIN_VALIDATE_RETURNED_TIMEOUT.substr(2, 3) + " sekund";
            document.getElementById("wrongPinPrompt").style.display = "inline";
            document.getElementById("wrongPinPrompt").innerHTML = output;
            break;
        default:
            output = "Vent " + PIN_VALIDATE_RETURNED_TIMEOUT.substr(2, 3) + " sekunder";
            document.getElementById("wrongPinPrompt").style.display = "inline";
            document.getElementById("wrongPinPrompt").innerHTML = output;
            break;
    }
}

/**
 * Låser brugerfladen og sender USER_LOCK til serveren
 */
function UIlockedByUser() {
    document.getElementById("lock_overlay").style.display = "block";
    document.getElementById("wrongPinPrompt").style.display = "none";
    doSend(eventEnums.USER_LOCK);
}

/**
 * Låser brugerfladen
 */
function UIlockedBySlave() {
    document.getElementById("lock_overlay").style.display = "block";
    document.getElementById("wrongPinPrompt").style.display = "none";
}

/**
 * Sender en indtastet PIN, der skal valideres, til serveren sammen med eventet USER_UNLOCK_TRY
 */
function validatePin() {
    var pin = document.getElementById("pin_input").value;
    if (pin.length == 4) {
        doSend(eventEnums.USER_UNLOCK_TRY + pin);
        document.getElementById("pin_input").value = "";
    }
}

/**
 * Opdaterer brugerfladen ud fra det menupunkt, brugeren har valgt.
 * @param {int} menu_button Det valgte menupunkt
 */
function selectPage(menu_button) {

    switch (menu_button) {
        case menu_button1:
            {
                document.getElementById("menu_button1").src = "img/livedata_selected.png";
                document.getElementById("menu_button2").src = "img/ridedata_notselected.png";
                document.getElementById("menu_button3").src = "img/settings_notselected.png";
                document.getElementById("page1").style.display = "inline";
                document.getElementById("page2").style.display = "none";
                document.getElementById("page3").style.display = "none";
                break;
            }
        case menu_button2:
            {
                document.getElementById("menu_button1").src = "img/livedata_notselected.png";
                document.getElementById("menu_button2").src = "img/ridedata_selected.png";
                document.getElementById("menu_button3").src = "img/settings_notselected.png";
                document.getElementById("page1").style.display = "none";
                document.getElementById("page2").style.display = "inline";
                document.getElementById("page3").style.display = "none";
                document.getElementById("rideDataContent").innerHTML = ""; //remove all rides from UI
                doSend(eventEnums.USER_REQUESTS_RIDES); //request t from server
                break;
            }
        case menu_button3:
            {
                document.getElementById("menu_button1").src = "img/livedata_notselected.png";
                document.getElementById("menu_button2").src = "img/ridedata_notselected.png";
                document.getElementById("menu_button3").src = "img/settings_selected.png";
                document.getElementById("page1").style.display = "none";
                document.getElementById("page2").style.display = "none";
                document.getElementById("page3").style.display = "inline";
                break;
            }
    }
}

/**
 * Sender den indtastede hjulstørrelse til servern
 */
function validateWheelSize() {
    var wheel_size = document.getElementById("wheel_input").value
    doSend(eventEnums.USER_SET_WHEELCIRCUMFERENCE + wheel_size);
    document.getElementById("wheel_input").value = "";
}

/**
 * Melder, at den valgte hjulstørrelse er indstillet
 */
function setWheelCirc() {
    document.getElementById("illegalWheelSize").style.display = "none";
    output = "Hjulstørrelsen er indstillet";
    document.getElementById("legalWheelSize").style.display = "inline";
    document.getElementById("legalWheelSize").innerHTML = output;
}

/**
 * Melder, at den valgte hjulstørrelse ikke blev godkendt
 */
function illegalWheelSize() {
    document.getElementById("legalWheelSize").style.display = "none";
    output = "Du har indtastet en ugyldig værdi, prøv igen";
    document.getElementById("illegalWheelSize").style.display = "inline";
    document.getElementById("illegalWheelSize").innerHTML = output;
}