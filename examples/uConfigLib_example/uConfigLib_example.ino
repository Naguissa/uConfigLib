/**
 * Arduino (and standard C) tiny and cross-device compatible configuration library.
 *
 * This is a registry-like list class used to be able to manipulate configuration variables.
 *
 * This class lets you store a value for any name + datatype pair
 *
 * You need to specify the type when setting, getting or erasing. Available types are:
 * UCONFIGLIB_TYPE_CHAR
 * UCONFIGLIB_TYPE_CHAR_ARRAY
 * UCONFIGLIB_TYPE_INT8
 * UCONFIGLIB_TYPE_UINT8
 * UCONFIGLIB_TYPE_INT16
 * UCONFIGLIB_TYPE_UINT16
 * UCONFIGLIB_TYPE_INT32
 * UCONFIGLIB_TYPE_UINT32
 * UCONFIGLIB_TYPE_NOT_SET - Predefined type, not supported for operations.
 *
 * You have uConfigLib class with following static methods:
 *
 *	* *void uConfigLib::set(const char *name, const uint8_t type, const void *value);* : Given a name and a type, sets it's value. A copy of name and value will be stored.
 *	* *void * uConfigLib::getPointer(const char * name, const uint8_t type);* : Given a name and type, gets a void pointer to its value. You'll need to cast return value in order to assgn or use it.
 *	* *bool uConfigLib::remove(const char *name, const uint8_t type);* : Given a name and type, removes them from list if found.
 *
 *
 *
 * @copyright Naguissa
 * @author Naguissa
 * @see <a href="https://github.com/Naguissa/uConfigLib">https://github.com/Naguissa/uConfigLib</a>
 * @see <a href="mailto:naguissa@foroelectro.net">naguissa@foroelectro.net</a>
 * @version 1.0.0
 */

#include "Arduino.h"
#include "uConfigLib.h"


void setup() {
    Serial.begin(115200);
    while (!Serial) {
      ; // wait for serial port to connect. Needed for Leonardo only
    }

    Serial.println(" - SETUP -");
    
    Serial.println(" - Brief usage -");    
    char a = 'A';
    char b[10] = "CharArray";
    int16_t c = 10;
    uint32_t d = 10000;
    uConfigLib::set("NameA", UCONFIGLIB_TYPE_CHAR, (void * ) &a);
    uConfigLib::set("B-name", UCONFIGLIB_TYPE_CHAR_ARRAY, (void *) &b[0]);
    uConfigLib::set("Name-of-C", UCONFIGLIB_TYPE_INT16, (void *) &c);
    uConfigLib::set("uint32Name", UCONFIGLIB_TYPE_UINT32, (void *) &d);
    
    char *aR;
    char *bR;
    int16_t *cR;
    uint32_t *dR;

    aR = (char *) uConfigLib::getPointer("NameA", UCONFIGLIB_TYPE_CHAR);
    bR = (char *) uConfigLib::getPointer("B-name", UCONFIGLIB_TYPE_CHAR_ARRAY);
    cR = (int16_t *) uConfigLib::getPointer("Name-of-C", UCONFIGLIB_TYPE_INT16);
    dR = (uint32_t *) uConfigLib::getPointer("uint32Name", UCONFIGLIB_TYPE_UINT32);


    Serial.print("A: ");
    Serial.print(a);
    Serial.print(" - ");
    Serial.println(*aR);

    Serial.print("B: ");
    Serial.print(b);
    Serial.print(" - ");
    Serial.println(bR);

    Serial.print("C: ");
    Serial.print(c);
    Serial.print(" - ");
    Serial.println(*cR);

    Serial.print("D: ");
    Serial.print(d);
    Serial.print(" - ");
    Serial.println(*dR);



    Serial.println(" - Typical usage -");    

    char *result;
    char option[3][16] = {"wifi_ssid", "wifi_pass", "client_name"};


    // Set defaults:
    uConfigLib::set("wifi_ssid", UCONFIGLIB_TYPE_CHAR_ARRAY, (void * ) "MySSID");
    uConfigLib::set("wifi_pass", UCONFIGLIB_TYPE_CHAR_ARRAY, (void * ) "MyPass");
    uConfigLib::set("client_name", UCONFIGLIB_TYPE_CHAR_ARRAY, (void * ) "ClientName");

    for (int i = 0; i < 3; i++) {
        Serial.print("Value of config option '");
        Serial.print(option[i]);
        Serial.print("' is '");
        result = (char *) uConfigLib::getPointer(option[i], UCONFIGLIB_TYPE_CHAR_ARRAY);
        Serial.print(result);
        Serial.println("'");
    }
    
    // Now, we get config from HTTP request, SPIFFS file, SDCard file, EEPROM... wherever. And set new value:
    char clientNameRead[10] = "NewClient";
    uConfigLib::set("client_name", UCONFIGLIB_TYPE_CHAR_ARRAY, (void * ) &clientNameRead[0]);
    
    Serial.println(" - changed value -");

    for (int i = 0; i < 3; i++) {
        Serial.print("Value of config option '");
        Serial.print(option[i]);
        Serial.print("' is '");
        result = (char *) uConfigLib::getPointer(option[i], UCONFIGLIB_TYPE_CHAR_ARRAY);
        Serial.print(result);
        Serial.println("'");
    }



    Serial.println(" - END -");
    Serial.println();
}


void loop() {
}

