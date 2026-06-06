#include <stdio.h>
#include "app_logic.h"
#include "serial_comm.h"

int main()
{
    // macos port name is longer than the windows port name
    char portName[64];

    printf("=====================================\n");
    printf("   INVENTORY APP LOGIC TEST MODE\n");
    printf("        (macOS Environment)\n");
    printf("=====================================\n");

    printf("Masukkan Port Arduino (contoh /dev/cu.usbmodem11301): ");
    scanf("%63s", portName);

    initSerialPort(portName);

    printf("\n=====================================\n");
    printf("Koneksi berhasil.\n");
    printf("Silakan uji seluruh fitur App Logic.\n");
    printf("=====================================\n");

    // Menjalankan loop UI utama dari app_logic.c
    runApp();

    closeSerialPort();

    printf("\nProgram selesai.\n");

    return 0;
}