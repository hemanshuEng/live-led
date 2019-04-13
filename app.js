// Initialize Firebase
var config = {
  apiKey: "AIzaSyBW_vThDMGBXA4KY7V2eqfTB0-ff1YEqFk",
  authDomain: "mcu-led.firebaseapp.com",
  databaseURL: "https://mcu-led.firebaseio.com",
  projectId: "mcu-led",
  storageBucket: "mcu-led.appspot.com",
  messagingSenderId: "593676244756"
};
firebase.initializeApp(config);
let database = firebase.database();
let ref = database.ref("led");

ref.on("value", gotData, errData);

function gotData(data) {
  let leds = data.val();
  let keys = Object.keys(leds);

  keys.forEach(key => {
    const status = leds[key] ? "ON" : "OFF";
    document.getElementById(key + "_status").innerHTML = status;
  });
}
function errData(err) {
  console.log(err);
}
let ledStatus;

const led = document.querySelector(".led");
led.addEventListener("click", updateLed);

function updateLed(e) {
  if (e.target.classList.contains("btn")) {
    const ledID = e.target.id;
    const ledStatus = ledID.split("-");
    const updates ={};
    updates["/"+ledStatus[0]] = ledStatus[1] ==="On" ? 1 :0;
    ref.update(updates);
  }
}

