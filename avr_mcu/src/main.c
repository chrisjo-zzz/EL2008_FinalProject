#include <avr/io.h>
#include "database.h"

int main(void) {
    // Setara dengan Serial.begin(9600)
    initUART();
    
    // Setara dengan fungsi setup()
    initDatabase();

    // Setara dengan fungsi loop()
    while (1) {
        processSerialInput();
    }

    return 0;
}