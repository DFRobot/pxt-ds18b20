
#include "pxt.h"
#include <cstdint>
#include <math.h>

using namespace pxt;

namespace DS18B20 {

class microbitp : public MicroBitComponent
{
  public:
    void *pin;
    int id;
    int status;
    PinCapability capability;
    uint8_t pullMode;
    PinName name;

    microbitp(int id, PinName name, PinCapability capability){
        this->id = id;
        this->name = name;
        this->capability = capability;
        this->pullMode = 1;
        this->status = 0x00;
        this->pin = NULL;
    }

    void disconnect(){ 
        if (status & 0x01)
            delete ((DigitalIn *)pin);
        if (status & 0x02)
            delete ((DigitalOut *)pin);
        this->pin = NULL;
        this->status = 0;
    }

    int setDigitalValue(int value){
        // Move into a Digital input state if necessary.
        if (!(status & 0x02)){
            disconnect();
            pin = new DigitalOut(name);
            status |= 0x02;
        }
        // Write the value.
        ((DigitalOut *)pin)->write(value);
        return 0;
    }

    int getDigitalValue(){
        if (!(status & (0x01 | 0x20 | 0x40)))
        {
            ((DigitalIn *)pin)->mode(PullNone);
            status |= 0x01;
        }
        return ((DigitalIn *)pin)->read();
//          return 0;
    }
};
    

//    MicroBit uBit;
 //   MicroBitPin pin1 = uBit.io.P2;
//    microbitp  pin0(7, 3, 15);
    microbitp  pin0(7, MICROBIT_PIN_P0, PIN_CAPABILITY_ALL);
    microbitp  pin1(8, MICROBIT_PIN_P1, PIN_CAPABILITY_ALL);
    microbitp  pin2(9, MICROBIT_PIN_P2, PIN_CAPABILITY_ALL);
    microbitp  pin3(10, MICROBIT_PIN_P3, PIN_CAPABILITY_ALL),
    microbitp  pin4(11, MICROBIT_PIN_P4, PIN_CAPABILITY_ALL),             //COL2 (ANALOG/DIGITAL)
    microbitp  pin5(12, MICROBIT_PIN_P5, PIN_CAPABILITY_STANDARD),        //BTN_A
    microbitp  pin6(13, MICROBIT_PIN_P6, PIN_CAPABILITY_STANDARD),        //ROW2
    microbitp  pin7(14, MICROBIT_PIN_P7, PIN_CAPABILITY_STANDARD),        //ROW1
    microbitp  pin8(15, MICROBIT_PIN_P8, PIN_CAPABILITY_STANDARD),        //PIN 18
    microbitp  pin9(16, MICROBIT_PIN_P9, PIN_CAPABILITY_STANDARD),        //ROW3
    microbitp  pin10(17,MICROBIT_PIN_P10,PIN_CAPABILITY_ALL),             //COL3 (ANALOG/DIGITAL)
    microbitp  pin11(18,MICROBIT_PIN_P11,PIN_CAPABILITY_STANDARD),        //BTN_B
    microbitp  pin12(19,MICROBIT_PIN_P12,PIN_CAPABILITY_STANDARD),        //PIN 20
    microbitp  pin13(20,MICROBIT_PIN_P13,PIN_CAPABILITY_STANDARD),        //SCK
    microbitp  pin14(21,MICROBIT_PIN_P14,PIN_CAPABILITY_STANDARD),        //MISO
    microbitp  pin15(22,MICROBIT_PIN_P15,PIN_CAPABILITY_STANDARD),        //MOSI
    microbitp  pin16(23,MICROBIT_PIN_P16,PIN_CAPABILITY_STANDARD),        //PIN 16
    microbitp  pin19(24,MICROBIT_PIN_P19,PIN_CAPABILITY_STANDARD),        //SCL
    microbitp  pin20(25,MICROBIT_PIN_P20,PIN_CAPABILITY_STANDARD)         //SDA
    
    microbitp  pin = pin0;

    uint8_t init() {
        pin.setDigitalValue(0);
        for (volatile uint16_t i = 0; i < 600; i++);
        pin.setDigitalValue(1);
        for (volatile uint8_t i = 0; i < 30; i++);
        int b = pin.getDigitalValue();
        for (volatile uint16_t i = 0; i < 600; i++);
        return b;
    }


    void writeBit(int b) {
        int delay1, delay2;
        if (b == 1) {
            delay1 = 1;
            delay2 = 80;
        } else {
            delay1 = 75;
            delay2 = 6;
        }
        pin.setDigitalValue(0);
        for (uint8_t i = 1; i < delay1; i++);
        pin.setDigitalValue(1);
        for (uint8_t i = 1; i < delay2; i++);
    }

    void writeByte(int byte) {
        int i;
        for (i = 0; i < 8; i++) {
            if (byte & 1) {
                writeBit(1);
            } else {
                writeBit(0);
            }
            byte = byte >> 1;
        }
    }

    int readBit() {
        volatile int i;
        pin.setDigitalValue(0);
        pin.setDigitalValue(1);
        for (i = 1; i < 20; i++);
        int b = pin.getDigitalValue();
        for (i = 1; i < 60; i++);
        return b;
    }

    int convert() {
        volatile int i;
        int j;
        writeByte(0x44);
        for (j = 1; j < 1000; j++) {
            for (i = 1; i < 900; i++) {
        };
        if (readBit() == 1)
            break;
        };
        return (j);
    }

    int readByte() {
        int byte = 0;
        int i;
        for (i = 0; i < 8; i++) {
            byte = byte | readBit() << i;
        };
        return byte;
    }

    //%
    int16_t Temperature(int p) {
        switch(p){
          case 0: pin = pin0; break;
          case 1: pin = pin1; break;
          case 2: pin = pin2; break;
          case 3: pin = pin3; break;
          case 4: pin = pin4; break;
          case 5: pin = pin5; break;
          case 6: pin = pin6; break;
          case 7: pin = pin7; break;
          case 8: pin = pin8; break;
          case 9: pin = pin9; break;
          case 10: pin = pin10; break;
          case 11: pin = pin11; break;
          case 12: pin = pin12; break;
          case 13: pin = pin13; break;
          case 14: pin = pin14; break;
          case 15: pin = pin15; break;
          case 16: pin = pin16; break;
          case 19: pin = pin19; break;
          case 20: pin = pin20; break;
          default: pin = pin0; 
        }
        init();
        writeByte(0xCC);
        convert();
        init();
        writeByte(0xCC);
        writeByte(0xBE);
        int b1 = readByte();
        int b2 = readByte();

        int16_t temp = (b2 << 8 | b1);
        return temp * 100 / 16;
    }
}
