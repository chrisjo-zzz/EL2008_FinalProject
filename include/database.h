#ifndef DATABASE_H
#define DATABASE_H

#include <Arduino.h>
#include <EEPROM.h>

// --- THE 80-BIT (10-BYTE) STRUCTURE ---
struct __attribute__((packed)) ItemData {
    uint8_t id : 7;              // 0-127

    // 8 Characters * 6 bits = 48 bits
    uint8_t pName0 : 6;
    uint8_t pName1 : 6;
    uint8_t pName2 : 6;
    uint8_t pName3 : 6;
    uint8_t pName4 : 6;
    uint8_t pName5 : 6;
    uint8_t pName6 : 6;
    uint8_t pName7 : 6;          

    uint8_t category : 2;        // 0-3
    uint8_t location : 6;        // 0-63 racks
    uint8_t status : 2;          // 0-3 states
    
    // 3 Characters * 5 bits = 15 bits
    uint16_t pic : 15;           
};

// --- LINKED LIST NODE ---
struct Node {
    ItemData data;
    Node* next;
};

// --- GLOBAL VARIABLES (Declared extern for modularity) ---
extern Node* head;
extern Node* tail;
extern const int MAX_ITEMS;
extern const int ITEM_SIZE;

// --- VOID FUNCTION PROTOTYPES ---

// 1. Core System Functions
void initDatabase();
void processSerialInput();

// 2. Data Compression & Decompression
void encodeChar6Bit(char inChar, uint8_t* outByte);
void decodeChar6Bit(uint8_t inByte, char* outChar);
void encodeChar5Bit(char inChar, uint8_t* outByte);
void decodeChar5Bit(uint8_t inByte, char* outChar);
void packItemData(ItemData* item, uint8_t id, const char* name, uint8_t cat, uint8_t loc, uint8_t stat, const char* pic);
void unpackItemName(ItemData* item, char* outBuffer);
void unpackItemPIC(ItemData* item, char* outBuffer);

// 3. Linked List & EEPROM Operations
void insertItem(ItemData newData);
void deleteItem(uint8_t targetId);
void syncListToEEPROM();
void printInventory();
void parseAndAddCommand(char* commandString);

#endif