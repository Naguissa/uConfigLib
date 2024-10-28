/**
 * \class uConfigLibLib
 * \brief Arduino (and standard C) tiny and cross-device compatible configuration library.
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
 * @file uConfigLib.h
 * @copyright Naguissa
 * @author Naguissa
 * @see <a href="https://github.com/Naguissa/uConfigLib">https://github.com/Naguissa/uConfigLib</a>
 * @see <a href="mailto:naguissa@foroelectro.net">naguissa@foroelectro.net</a>
 * @version 1.0.0
 */
#ifndef _uConfigLib_h_
    #define _uConfigLib_h_

    #include <Arduino.h>


    #define UCONFIGLIB_TYPE_NOT_SET 0
    #define UCONFIGLIB_TYPE_CHAR 1
    #define UCONFIGLIB_TYPE_CHAR_ARRAY 2
    #define UCONFIGLIB_TYPE_INT8 11
    #define UCONFIGLIB_TYPE_UINT8 12
    #define UCONFIGLIB_TYPE_INT16 13
    #define UCONFIGLIB_TYPE_UINT16 14
    #define UCONFIGLIB_TYPE_INT32 15
    #define UCONFIGLIB_TYPE_UINT32 16

    struct uConfigLibList {
        uConfigLibList() : next(0), type(UCONFIGLIB_TYPE_NOT_SET){};
        uConfigLibList *next;
        char type;
        char * name;
        void * value;
    };


    #define uConfigLib_free(field) if (field != 0) { free(field); field = 0; }



    class uConfigLib {
        public:
            static void set(const char *, const uint8_t, const void *);
            static void * getPointer(const char *, const uint8_t);
            static bool remove(const char *, const uint8_t);


        private:
            uConfigLib(); // purely static methods
            static void * _malloc(const char);
            static bool _copyValue(const uint8_t, uConfigLibList *, const void *);
            static uConfigLibList *list;

    };

#endif
