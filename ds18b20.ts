/**
* Jordan Electronics
* May, 2018
* Based on Weatherbit code from Sparkfun:
* https://github.com/sparkfun/pxt-weather-bit
*
* Development environment specifics:
* Written in Microsoft PXT
*
* This code is released under the [MIT License](http://opensource.org/licenses/MIT).
* Distributed as-is; no warranty is given.
*/

//% color=#5042f4 icon="\uf2c9"
namespace DS18B20 {

    // Functions for interfacing with the DS1820

    /**
     * Reads the temperature from the one-wire temperature sensor.
     * Returns a 4 digit number. value should be divided by 100 to get 
     *temperature in hundreths of a degree centigrade. 
     * block="Temperature(C)"
     */

    //% shim=DS18B20::Temperature
    export function Temperature(): number {
        // Fake function for simulator
        return 0
    }
    
    //% weight=10 blockId="Temperature_number" 
    //% block="Temperature_number"
    export function Temperature_number(): number {
        // Fake function for simulator
        return Temperature()
    }
    
    //% weight=10 blockId="Temperature_string" 
    //% block="Temperature_string"
    export function Temperature_string() : string{
        let temp = Temperature();
        let x = (temp / 100)
        let y = (temp % 100)
        let z = ''
        if((y < 10)&&(y >= 0)){
            z = x.toString() + '.0' + y.toString()
        }
        else if(y >= 10){
            z = x.toString() + '.' + y.toString()
        }
        else if((y > -10)&&(y < 0)){
            z = x.toString() + '.0' + (-y).toString()
        }
        else{
            z = x.toString() + '.' + (-y).toString()
        }
        return z
    }
}
