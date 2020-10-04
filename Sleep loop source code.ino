//Time and Temperature

var lcd = new jsUpmI2cLcd.Jhd1313m1(6, 0x3E, 0x62);

var groveSensor = require('jsupm_grove');

var today = setInterval(function ()
    {
    var d = new Date();
    var b= d.toTimeString();
    lcd.setColor(0, 255, 0);

// Go to the 2nd row, 6th character (0-indexed)

    lcd.setCursor(0,0);
    lcd.write(b);
     var celsius = temp.value();
        var fahrenheit = celsius * 9.0/5.0 + 32.0;
        var t = Math.round(fahrenheit);
        lcd.setCursor(1, 1);
        lcd.write(t+" *F");
       v.saveValue(t);
}, 1000);

// Accelerometer and Gyroscope

var accelrCompassSensor = require('jsupm_lsm303');

// Instantiate LSM303 compass on I2C

var myAccelrCompass = new accelrCompassSensor.LSM303(0);


var successFail, coords, outputStr, accel;

var myInterval = setInterval(function()

{

        // Load coordinates into LSM303 object

        successFail = myAccelrCompass.getCoordinates();

        // in XYZ order. The sensor returns XZY,

        // but the driver compensates and makes it XYZ

        coords = myAccelrCompass.getRawCoorData();


    // Print out the X, Y, and Z coordinate data using two different methods

        outputStr = "coor: rX " + coords.getitem(0)

                                      + " - rY " + coords.getitem(1)

                                      + " - rZ " + coords.getitem(2);

        console.log(outputStr);

        outputStr = "coor: gX " + myAccelrCompass.getCoorX()

                               + " - gY " + myAccelrCompass.getCoorY()

                               + " - gZ " + myAccelrCompass.getCoorZ();

        console.log(outputStr);


    // Get and print out the heading

        console.log("heading: " + myAccelrCompass.getHeading());


    // Get the acceleration

        myAccelrCompass.getAcceleration();

        accel = myAccelrCompass.getRawAccelData();

    // Print out the X, Y, and Z acceleration data using two different methods

        outputStr = "acc: rX " + accel.getitem(0)

                               + " - rY " + accel.getitem(1)

                               + " - Z " + accel.getitem(2);

        console.log(outputStr);

        outputStr = "acc: gX " + myAccelrCompass.getAccelX()

                               + " - gY " + myAccelrCompass.getAccelY()

                               + " - gZ " + myAccelrCompass.getAccelZ();

        console.log(outputStr);

        console.log(" ");

}, 1000);


// Print message when exiting

process.on('SIGINT', function()

{

        clearInterval(myInterval);

        myAccelrCompass = null;

        accelrCompassSensor.cleanUp();

        accelrCompassSensor = null;

        console.log("Exiting");

        process.exit(0);

});