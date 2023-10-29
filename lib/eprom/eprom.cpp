#include <eprom.h>

bool commmit()
{
    bool result = EEPROM.commit();
    if (result)
    {
        Serial.println("EEPROM successfully committed");
    }
    else
    {
        Serial.println("ERROR! EEPROM commit failed");
    }
    return result;
}

// запись строки data, начиная с адреса addr
int write2Eeprom(int addr, String data)
{
    int len = data.length();
    EEPROM.write(addr, len);
    for (int i = 0; i < len; i++)
    {
        EEPROM.write(addr + 1 + i, data[i]);
    }
    commmit();
    delay(100);
    return addr + 1 + len;
}

// получение данных, начиная с addr
String readFromEeprom(int addr)
{
    String str;
    int len = EEPROM.read(addr);
    str.reserve(len);
    for (int i = 0; i < len; i++)
    {
        str += (char)EEPROM.read(addr + 1 + i);
    }
    return str;
}

// полная очистка памяти
bool flushall()
{
    for (int i = 0; i < MAX_BUFF_SIZE; i++)
    {
        EEPROM.write(i, 0);
    }
    return commmit();
}