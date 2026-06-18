#ifndef SERIAL_COMM_H
#define SERIAL_COMM_H

void initSerialPort(const char* portName, int* statusFlag);
void sendSerialData(const char* dataStr);
void receiveSerialData(char* buffer);
void closeSerialPort();

#endif // SERIAL_COMM_H