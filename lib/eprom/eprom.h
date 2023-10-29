#include <Arduino.h>
#include <EEPROM.h>

#define MAX_BUFF_SIZE 128

// получение данных, начиная с addr
String readFromEeprom(int addr);

// запись строки data, начиная с адреса addr
int write2Eeprom(int addr, String data);


bool flushall();