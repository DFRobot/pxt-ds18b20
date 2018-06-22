// tests go here; this will not be compiled when this package is used as a library

basic.forever(() => {
    serial.writeValue("0", DS18B20.Temperature_number(DS18B20.pin.pin0))
    serial.writeLine("0 : " + DS18B20.Temperature_string(DS18B20.pin.pin0))
    basic.pause(1000)
})