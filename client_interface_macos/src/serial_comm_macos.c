#include "serial_comm.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <termios.h>
#include <errno.h>

static int serial_fd = -1;

void initSerialPort(const char* portName, int* statusFlag) {
    // Set default status menjadi 0 (Gagal) di awal
    *statusFlag = 0; 
    
    printf("[SYSTEM] Mencoba terhubung ke %s (macOS/Linux)...\n", portName);
    
    serial_fd = open(portName, O_RDWR | O_NOCTTY | O_SYNC);
    if (serial_fd < 0) {
        printf("[ERROR] Gagal membuka port %s.\n", portName);
        return; // Fungsi langsung berhenti, status tetap 0
    }

    struct termios tty;
    if (tcgetattr(serial_fd, &tty) != 0) {
        printf("[ERROR] Gagal mendapatkan atribut serial.\n");
        return;
    }

    cfsetospeed(&tty, B9600);
    cfsetispeed(&tty, B9600);

    tty.c_cflag = (tty.c_cflag & ~CSIZE) | CS8; // 8-bit chars
    tty.c_cflag &= ~PARENB;                     // No parity
    tty.c_cflag &= ~CSTOPB;                     // 1 stop bit
    tty.c_cflag &= ~CRTSCTS;                    // No hardware flow control
    tty.c_cflag |= (CLOCAL | CREAD);
    
    tty.c_lflag &= ~(ICANON | ECHO | ECHOE | ISIG); 
    tty.c_iflag &= ~(IXON | IXOFF | IXANY);         
    tty.c_oflag &= ~OPOST;

    tty.c_cc[VMIN]  = 0;
    tty.c_cc[VTIME] = 1; // 100ms timeout

    if (tcsetattr(serial_fd, TCSANOW, &tty) != 0) {
        printf("[ERROR] Gagal menerapkan pengaturan serial.\n");
        return;
    }

    printf("[SYSTEM] Port terbuka. Menunggu 2 detik untuk Arduino Boot...\n");
    sleep(2); 
    tcflush(serial_fd, TCIOFLUSH);
    printf("[SYSTEM] Koneksi Serial Siap!\n");
    
    // Jika eksekusi berhasil mencapai titik ini, ubah status menjadi 1 (Sukses)
    *statusFlag = 1; 
}

void sendSerialData(const char* dataStr) {
    if (serial_fd < 0) return;
    write(serial_fd, dataStr, strlen(dataStr));
    tcflush(serial_fd, TCOFLUSH); 
    usleep(50000); // delay 50ms
}

void receiveSerialData(char* buffer) {
    if (serial_fd < 0) {
        strcpy(buffer, "ERR_PORT_CLOSED");
        return;
    }

    int total_bytes = 0;
    char temp_char;
    
    while (read(serial_fd, &temp_char, 1) > 0) {
        buffer[total_bytes] = temp_char;
        total_bytes++;
        if (total_bytes >= 4095) break; 
    }
    buffer[total_bytes] = '\0'; 
}

void closeSerialPort() {
    if (serial_fd != -1) {
        close(serial_fd);
        printf("[SYSTEM] Koneksi Serial macOS diputus.\n");
        serial_fd = -1;
    }
}