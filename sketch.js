let serial;
let midi;

function setup() {
  createCanvas(400, 400);

  // Setup MIDI
  WebMidi.enable(function (err) {
    if (err) {
      console.log("WebMidi could not be enabled.", err);
    } else {
      console.log("WebMidi enabled!");

      // Retrieve an input by name, id, or index
      midi = WebMidi.inputs[0];

      if (midi) {
        console.log("Found MIDI input:", midi.name);
        midi.addListener('noteon', 'all',function (e) {
            let acc = e.note.accidental || "";
            console.log("Note On:", `${e.note.name}${acc}${e.note.octave}`);
;
            sendToArduino(e.note.name);
          }
        );
      }
    }
  });
 
  // Setup serial communication to Arduino
  serial = new p5.SerialPort();
  serial.open('/dev/cu.usbmodem142201'); // Be sure to change to your Arduino port
  serial.on('connected', serverConnected);
  serial.on('list', gotList);
  serial.on('data', gotData);
  serial.on('error', gotError);
  serial.on('open', gotOpen);
  serial.on('close', gotClose);
}

function draw() {
  background(220);
  // Just a sample, we can add more code for drawing if needed
}

function sendToArduino(name) {
  // Send a signal to Arduino when a G major chord note is played
  serial.write(name);
  console.log("send");
}

// Serial communication callback functions
function serverConnected() {
  console.log('Connected to the server.');
}

function gotList(thelist) {
  console.log('List of Serial Ports:');
  // thelist is an array of their names
  for (let i = 0; i < thelist.length; i++) {
    console.log(i + ' ' + thelist[i]);
  }
}

function gotOpen() {
  console.log('Serial Port is Open');
    // send a byte to start the microcontroller sending:
    serial.write("x");
}

function gotClose() {
  console.log('Serial Port is Closed');
}

function gotError(theerror) {
  console.log(theerror);
}

function gotData() {
    console.log("got data");
  // Not used in this example, but you can use it to receive data from Arduino if needed

  // read a string from the serial port
  // until you get carriage return and newline:
  let inString = serial.readStringUntil("\r\n");
  //check to see that there's actually a string there:
  if (inString) {
    if (inString !== "hello") {
      // if you get hello, ignore it
      // split the string on the commas:
      if (inString == "start") {
        console.log("here");
      }

    // send a byte back to prompt for more data:
    serial.write('x');
    }
  }
}
