# DS18B20 Temperature Sensor for Microbit 

## Table of Contents

* [Summary](#summary)
* [Blocks](#blocks)
* [Example](#example)
* [License](#license)

## Summary
DS18B20 module, support single bus control, read temperature by pin1.

## Blocks
### readTemperature, return a number
![image](https://github.com/DFRobot/pxt-ds18b20/blob/master/image/string.png)<br>

### readTemperature, return a string
![image](https://github.com/DFRobot/pxt-ds18b20/blob/master/image/number.png)<br>

## Example
Example for JavaScript
```
basic.forever(() => {
    serial.writeLine("temp : "+DS18B20.Temp())
    basic.pause(1000)
    serial.writeValue("temp : ", DS18B20.Temperature())
    basic.pause(1000)
})
```

## License

GUI
## Supported targets

* for PXT/microbit
(The metadata above is needed for package search.)


