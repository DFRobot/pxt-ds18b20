// tests go here; this will not be compiled when this package is used as a library

basic.forever(() => {
    serial.writeLine(DS18B20.Temperature())
})