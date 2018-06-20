//% color=#5042f4 icon="\uf2c9"
namespace DS18B20 {

    // Functions for interfacing with the DS1820

    /**
     * Reads the temperature from the one-wire temperature sensor.
     * Returns a 4 digit number. value should be divided by 100 to get 
     *temperature in hundreths of a degree centigrade. 
     * block="Temperature(C)"
     */

     enum pin {
       //% block=pin0
       pin0 = 0,
       //% block=pin1
       pin1 = 1,
       //% block=pin2
       pin2 = 2
     }
     
    //% shim=DS18B20::Temperature
    export function Temperature(p : number): number {
        // Fake function for simulator
        return 0
    }
    
    //% weight=10 blockId="Temperature_number" 
    //% block="Temperature_number %p"
    export function Temperature_number(p : number): number {
        // Fake function for simulator
        return Temperature(p)
    }
    
    //% weight=10 blockId="Temperature_string" 
    //% block="Temperature_string %p"
    export function Temperature_string(p : pin) : string{
        let temp = Temperature(p);
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
