#include "pxt.h"


namespace  DS18B20  {
    
MicroBitPin *pin = &uBit.io.P13;

void sleep_us(int us){
  int lasttime,nowtime;
  lasttime  = system_timer_current_time_us();
  nowtime = system_timer_current_time_us();
  while((nowtime - lasttime) < us){
    nowtime = system_timer_current_time_us();
  }
}

void DS18B20Rest(void){
  pin->setDigitalValue(0);
  sleep_us(750);
  pin->setDigitalValue(1);
  sleep_us(15);
}

void DS18B20WiteByte(uint8_t data){
  int _data=0,i;
  for(i=0;i<8;i++){
    _data=data&0x01;
    data>>=1;
    if(_data){
      pin->setDigitalValue(0);
      sleep_us(2);
      pin->setDigitalValue(1);
      sleep_us(60);
    }else{
      pin->setDigitalValue(0);
      sleep_us(60);
      pin->setDigitalValue(1);
      sleep_us(2);
    }
    //sleep_us(2);
  }
}

int DS18B20ReadBit(void){
  int data;
  pin->setDigitalValue(0);
  sleep_us(2);
  pin->setDigitalValue(1);
  sleep_us(5);
  if(pin->getDigitalValue()){
      data = 1;
  }else data = 0;
  sleep_us(60);
  return data;
}                                                              

int DS18B20ReadByte(void){
  int i,j,data=0;
  for(i=0;i<8;i++){
    j = DS18B20ReadBit();
    //uBit.serial.printf("%d",j);
    sleep_us(2);
    data = (j<<7)|(data>>1);
  }
   sleep_us(2);
  //uBit.serial.printf("\r\n");
  return data;
}

int DS18B20Check(void){
    int state=0;
    while (pin->getDigitalValue())
    {
      state++;
      sleep_us(1);
      if(state>=200){
        break;
      }
    }
    if(state>=200)return 1;
    else state = 0;
    while(!pin->getDigitalValue()){
      state++;
      sleep_us(1);
      if(state>=240){
        break;
      }
    }
    if(state>=240)return 1;
    return 0; 
}

void DS18B20Start(void){
  DS18B20Rest();
  DS18B20Check();
  sleep_us(2);
  DS18B20WiteByte(0xcc);
  DS18B20WiteByte(0x44);
}

float DS18B20GetTemperture(void){
  int temp;
  int TH,TL;
  float value;
  DS18B20Start();
  sleep_us(100);
  DS18B20Rest();
  DS18B20Check();
  sleep_us(2);
  DS18B20WiteByte(0xCC);
  DS18B20WiteByte(0xBE);

  TL = DS18B20ReadByte();
  //uBit.serial.printf("TL=%d\r\n",TL);
  sleep_us(100);
  TH = DS18B20ReadByte();
  //uBit.serial.printf("TH=%d\r\n",TH);
  temp=TH;
  temp=(temp<<8)+TL;
 
  if((temp&0xf800)==0xf800){
		temp=(~temp)+1;
		value=temp*(-0.0625);
	}else{
		value=temp*0.0625;	
	}
  return value;
}

  //%
int Temperature(int p) {

    switch(p){
      case 0: pin = &uBit.io.P0; break;
      case 1: pin = &uBit.io.P1; break;
      case 2: pin = &uBit.io.P2; break;
      case 5: pin = &uBit.io.P5; break;
      case 8: pin = &uBit.io.P8; break;
      case 11: pin = &uBit.io.P11; break;
      case 12: pin = &uBit.io.P12; break;
      case 13: pin = &uBit.io.P13; break;
      case 14: pin = &uBit.io.P14; break;
      case 15: pin = &uBit.io.P15; break;
      case 16: pin = &uBit.io.P16; break;
      default: pin = &uBit.io.P0;
    }
    float data1,data2,data3;
    data1=DS18B20GetTemperture();
    data2=DS18B20GetTemperture();
    if((data2-data1)>2){
        return data1*10;
    }else{
        return data2*10;
    }
   
  }
}
