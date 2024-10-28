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
 * @file uConfigLib.cpp
 * @copyright Naguissa
 * @author Naguissa
 * @see <a href="https://github.com/Naguissa/uConfigLib">https://github.com/Naguissa/uConfigLib</a>
 * @see <a href="mailto:naguissa@foroelectro.net">naguissa@foroelectro.net</a>
 * @version 1.0.0
 */
 #ifndef _uConfigLib_cpp_
    #define _uConfigLibg_cpp_
    #include <Arduino.h>
    #include "uConfigLib.h"


    uConfigLibList * uConfigLib::list = 0;
    
    bool uConfigLib::_copyValue(const uint8_t type, uConfigLibList * slot, const void * value) {
        switch (type) {
            case UCONFIGLIB_TYPE_INT8:
                slot->value = (void *) malloc(sizeof(char));
                *((int8_t *) slot->value) = *((int8_t *) value);
                break;
            case UCONFIGLIB_TYPE_UINT8:
                slot->value = (void *) malloc(sizeof(char));
                *((uint8_t *) slot->value) = *((uint8_t *) value);
                break;
            case UCONFIGLIB_TYPE_CHAR:
                slot->value = (void *) malloc(sizeof(char));
                *((char *) slot->value) = *((char *) value);
                break;
            case UCONFIGLIB_TYPE_CHAR_ARRAY:
                slot->value = (void *) malloc(sizeof(char) * (strlen((char *) value) + 1));
                strcpy((char *) slot->value, (char *) value);
                break;
            case UCONFIGLIB_TYPE_INT16:
                slot->value = (void *) malloc(sizeof(int16_t));
                *((int16_t *) slot->value) = *((int16_t *) value);
                break;
            case UCONFIGLIB_TYPE_UINT16:
                slot->value = (void *) malloc(sizeof(uint16_t));
                *((uint16_t *) slot->value) = *((uint16_t *) value);
                break;
            case UCONFIGLIB_TYPE_INT32:
                slot->value = (void *) malloc(sizeof(int32_t));
                *((int32_t *) slot->value) = *((int32_t *) value);
                break;
            case UCONFIGLIB_TYPE_UINT32:
                slot->value = (void *) malloc(sizeof(uint32_t));
                *((uint32_t *) slot->value) = *((uint32_t *) value);
                break;
            default: return false;
        }
        return true;
    }

    void uConfigLib::set(const char * name, const uint8_t type, const void *value) {
        if (list == 0) {
            list = new uConfigLibList;
            list->name = (char *) malloc(sizeof(char) * (strlen((char *) name) + 1));
            strcpy(list->name, name);
            list->type= type;
            _copyValue(type, list, value);
            list->next = 0;
            return;
        }
        
        uConfigLibList * prev = list;
        for (uConfigLibList * slot = list; slot != 0; slot = slot->next) {
            if (strcmp(slot->name, name) == 0 && slot->type == type) {
                uConfigLib_free(slot->value);                
                _copyValue(type, slot, value);
                return;
            }
            prev = slot;
        }
        
        prev->next = new uConfigLibList;
        prev->next->name = (char *) malloc(sizeof(char) * (strlen((char *) name) + 1));
        strcpy(prev->next->name, name);
        prev->next->type= type;
        _copyValue(type, prev->next, value);
        prev->next->next = 0;
    }

    void * uConfigLib::getPointer(const char * name, const uint8_t type) {
        for (uConfigLibList * slot = list; slot != 0; slot = slot->next) {
            if (slot->type == type && strcmp(slot->name, name) == 0) {
                return slot->value;
            }
        }
        return 0;
    }

    bool uConfigLib::remove(const char *name, const uint8_t type) {
        uConfigLibList *slot, *prev;
        for (slot = list, prev = 0; slot != 0; slot = slot->next) {
            if (slot->type == type && strcmp(slot->name, name) == 0) {
                if (prev == 0 && slot->next == 0) { // Only element of the list
                    uConfigLib_free(list->name);
                    uConfigLib_free(list->value);
                    uConfigLib_free (list);
                    list = 0;
                    return true;
                }
                if (prev != 0) {
                    prev->next = slot->next;
                }
                uConfigLib_free(slot->name);
                uConfigLib_free(slot->value);
                uConfigLib_free(slot);
                return true;
            }
            prev = slot;
        }
        return false;
    }

#endif
