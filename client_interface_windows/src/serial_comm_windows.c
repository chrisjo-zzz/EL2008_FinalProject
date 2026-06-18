#include "serial_comm.h"
#include <windows.h>
#include <stdio.h>
#include <string.h>

static HANDLE hSerial = INVALID_HANDLE_VALUE;

void initSerialPort(const char* portName, int* statusFlag) {
    *statusFlag = 0; // Set default gagal
    printf("[SYSTEM] Mencoba terhubung ke %s (Windows)...\n", portName);
    
    char portPath[32];
    snprintf(portPath, sizeof(portPath), "\\\\.\\%s", portName);

    hSerial = CreateFileA(
        portPath,
        GENERIC_READ | GENERIC_WRITE,
        0, NULL, OPEN_EXISTING, 0, NULL
    );

    if (hSerial == INVALID_HANDLE_VALUE) {
        printf("[ERROR] Gagal membuka port %s. Pastikan tidak sedang dipakai Arduino IDE.\n", portName);
        return;
    }

    DCB dcbSerialParams = {0};
    dcbSerialParams.DCBlength = sizeof(dcbSerialParams);
    
    if (!GetCommState(hSerial, &dcbSerialParams)) {
        printf("[ERROR] Gagal membaca status port.\n");
        CloseHandle(hSerial);
        hSerial = INVALID_HANDLE_VALUE;
        return;
    }

    dcbSerialParams.BaudRate = CBR_9600;
    dcbSerialParams.ByteSize = 8;
    dcbSerialParams.StopBits = ONESTOPBIT;
    dcbSerialParams.Parity   = NOPARITY;

    if (!SetCommState(hSerial, &dcbSerialParams)) {
        printf("[ERROR] Gagal mengatur parameter port.\n");
        return;
    }

    COMMTIMEOUTS timeouts = {0};
    timeouts.ReadIntervalTimeout         = 50;
    timeouts.ReadTotalTimeoutConstant    = 50;
    timeouts.ReadTotalTimeoutMultiplier  = 10;
    timeouts.WriteTotalTimeoutConstant   = 50;
    timeouts.WriteTotalTimeoutMultiplier = 10;
    SetCommTimeouts(hSerial, &timeouts);

    printf("[SYSTEM] Port terbuka. Menunggu 2 detik untuk Arduino Boot...\n");
    Sleep(2000); 
    PurgeComm(hSerial, PURGE_RXCLEAR | PURGE_TXCLEAR); 
    printf("[SYSTEM] Koneksi Serial Siap!\n");
    
    *statusFlag = 1; // Ubah menjadi sukses
}

void sendSerialData(const char* dataStr) {
    if (hSerial == INVALID_HANDLE_VALUE) return;
    DWORD bytesWritten;
    WriteFile(hSerial, dataStr, strlen(dataStr), &bytesWritten, NULL);
    Sleep(50); 
}

void receiveSerialData(char* buffer) {
    if (hSerial == INVALID_HANDLE_VALUE) {
        strcpy(buffer, "ERR_PORT_CLOSED");
        return;
    }

    DWORD bytesRead;
    char temp_char;
    int total_bytes = 0;

    while (ReadFile(hSerial, &temp_char, 1, &bytesRead, NULL) && bytesRead > 0) {
        buffer[total_bytes] = temp_char;
        total_bytes++;
        if (total_bytes >= 4095) break;
    }
    buffer[total_bytes] = '\0';
}

void closeSerialPort() {
    if (hSerial != INVALID_HANDLE_VALUE) {
        CloseHandle(hSerial);
        printf("[SYSTEM] Koneksi Serial Windows diputus.\n");
        hSerial = INVALID_HANDLE_VALUE;
    }
}