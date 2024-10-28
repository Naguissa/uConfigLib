# Arduino (standard C) library to store configuration values in a registry-like structure.

## What is this repository for?

This is a registry-like list class used to be able to manipulate configuration variables.

This class lets you store a value for any name + datatype pair

 You need to specify the type when setting, getting or erasing. Available types are:
 * UCONFIGLIB_TYPE_CHAR
 * UCONFIGLIB_TYPE_CHAR_ARRAY
 * UCONFIGLIB_TYPE_INT8
 * UCONFIGLIB_TYPE_UINT8
 * UCONFIGLIB_TYPE_INT16
 * UCONFIGLIB_TYPE_UINT16
 * UCONFIGLIB_TYPE_INT32
 * UCONFIGLIB_TYPE_UINT32
 * UCONFIGLIB_TYPE_NOT_SET - Predefined type, not supported for operations.




## Usage ##

You have uConfigLib class with following static methods:

 * *void uConfigLib::set(const char *name, const uint8_t type, const void *value);* : Given a name and a type, sets it's value. A copy of name and value will be stored.
 * *void * uConfigLib::getPointer(const char * name, const uint8_t type);* : Given a name and type, gets a void pointer to its value. You'll need to cast return value in order to assgn or use it.
 * *bool uConfigLib::remove(const char *name, const uint8_t type);* : Given a name and type, removes them from list if found.



## How do I get set up?

You can get it from Arduino libraries directly, searching by uConfigLib.

For manual installation:

 * Get the ZIP from releases link: https://github.com/Naguissa/uConfigLib/releases
 * Rename to uConfigLib.zip
 * Install library on Arduino

## Example

Included on example folder, available on Arduino IDE.


## Who do I talk to?

 * [Naguissa](https://github.com/Naguissa)
 * https://www.foroelectro.net


## Contribute

Any code contribution, report or comment are always welcome. Don't hesitate to use GitHub for that.


 * You can sponsor this project using GitHub's Sponsor button: https://github.com/Naguissa/uConfigLib
 * You can make a donation via PayPal: https://paypal.me/foroelectro


Thanks for your support.


Contributors hall of fame: https://www.foroelectro.net/hall-of-fame-f32/contributors-contribuyentes-t271.html
