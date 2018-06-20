# DS18B20 Temperature Sensor for Microbit 

## Table of Contents

* [Summary](#summary)
* [Blocks](#blocks)
* [Example](#example)
* [License](#license)

## Summary
DS18B20 module, support single bus control, read temperature by pin1.

## Blocks
### Read temperature, return a number, makecode do not support floats, so the value is amplifies up to 100 times.
![image](https://github.com/DFRobot/pxt-ds18b20/blob/master/image/string.png)<br>

### Read temperature, return a string.
![image](https://github.com/DFRobot/pxt-ds18b20/blob/master/image/number.png)<br>

## Example
Example for JavaScript
```
basic.forever(() => {
    serial.writeValue("temp ", DS18B20.Temperature_number(DS18B20.pin.pin0))
    basic.pause(1000)
    serial.writeLine("temp : " + DS18B20.Temperature_string(DS18B20.pin.pin0))
    basic.pause(1000)
})
```

## License

GUI
## Supported targets

* for PXT/microbit
(The metadata above is needed for package search.)


