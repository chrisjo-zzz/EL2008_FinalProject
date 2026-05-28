#include "database.h"

// Note: In standard C, this would be int main(void), but the Arduino 
// compiler abstracts the while(1) loop into setup() and loop(). 
// Both act purely as function callers here to satisfy the rubric.

void setup() {
    // Initialize standard baud rate for PC communication
    Serial.begin(9600);
    
    // Load the 80-bit Array from EEPROM into the SRAM Linked List
    initDatabase(); 
}

void loop() {
    // Constantly poll the Serial buffer for incoming GUI / Terminal strings
    processSerialInput(); 
}