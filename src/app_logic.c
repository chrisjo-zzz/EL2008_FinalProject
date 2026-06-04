/*
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "app_logic.h"
#include "user_interface.h"
#include "serial_comm.h"

void runApp() {
    // Initialize serial port, display main menu in a while loop, 
    // and route the user's choice to the functions below.
}

void addInventory() {
    // Prompt UI for new item details, format into ADD string, 
    // send via serial, and print Arduino's ACK response.
}

void deleteInventory() {
    // Prompt UI for ID, format into DEL string, 
    // send via serial, and print Arduino's ACK response.
}

void searchByID() {
    // Prompt UI for ID, call GET_ALL via serial, 
    // parse the returned data, and display only the matching item.
}

void updateStockAndStatus() {
    // Prompt UI for ID, prompt for new quantities, 
    // format into ADD/UPDATE string, and send via serial to overwrite.
}

void displayAllInventory() {
    // Call GET_ALL via serial, parse the incoming CSV data, 
    // and print it using the UI header and formatted rows.
}

void displaySummary() {
    // Call GET_ALL via serial, parse data to calculate 
    // total available/borrowed/broken items, and print the math summary.
}
*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "app_logic.h"
#include "user_interface.h"
#include "serial_comm.h"

// Buffer global untuk menampung respons serial dan data input
char serialBuffer[512];
char inputBuffer[50];

void runApp() {
    int pilihan = 0;
    int berjalan = 1;
    
    // Asumsi fungsi dari serial_comm.h untuk menginisialisasi port
    inisialisasiSerial(); 
    
    while (berjalan == 1) {
        // Asumsi fungsi dari user_interface.h untuk menampilkan menu utama
        tampilkanMenuUtama(&pilihan); 
        
        switch (pilihan) {
            case 1:
                addInventory();
                break;
            case 2:
                deleteInventory();
                break;
            case 3:
                searchByID();
                break;
            case 4:
                updateStockAndStatus();
                break;
            case 5:
                displayAllInventory();
                break;
            case 6:
                displaySummary();
                break;
            case 7:
                printf("\nKeluar dari sistem. Terima kasih!\n");
                berjalan = 0;
                break;
            default:
                printf("\nPilihan tidak valid! Silakan coba lagi.\n");
                break;
        }
    }
}

void addInventory() {
    char id[15], nama[30], kategori[20], lokasi[20], status[15], pemilik[20], pic[20];
    int stok;
    char perintahADD[250];

    printf("\n=== TAMBAH DATA INVENTARIS ===\n");
    printf("Masukkan ID Barang      : "); scanf("%s", id);
    printf("Masukkan Nama Komponen  : "); scanf(" %[^\n]", nama);
    printf("Masukkan Kategori       : "); scanf(" %[^\n]", kategori);
    printf("Masukkan Jumlah Stok    : "); scanf("%d", &stok);
    printf("Masukkan Lokasi Rak     : "); scanf(" %[^\n]", lokasi);
    printf("Masukkan Status Barang  : "); scanf("%s", status);
    printf("Masukkan Pemilik Barang : "); scanf(" %[^\n]", pemilik);
    printf("Masukkan PIC Barang     : "); scanf(" %[^\n]", pic);

    // Format data menjadi string perintah ADD (Menggunakan format CSV standar)
    sprintf(perintahADD, "ADD;%s;%s;%s;%d;%s;%s;%s;%s\n", id, nama, kategori, stok, lokasi, status, pemilik, pic);

    // Kirim string perintah ke Arduino via Serial
    kirimDataSerial(perintahADD);

    // Baca dan cetak respons ACK (Acknowledgment) dari Arduino
    terimaDataSerial(serialBuffer, sizeof(serialBuffer));
    printf("\n[Respon Arduino]: %s\n", serialBuffer);
}

void deleteInventory() {
    char id[15];
    char perintahDEL[30];

    printf("\n=== HAPUS DATA INVENTARIS ===\n");
    printf("Masukkan ID Barang yang akan dihapus: ");
    scanf("%s", id);

    // Format perintah DEL
    sprintf(perintahDEL, "DEL;%s\n", id);

    // Kirim ke Arduino
    kirimDataSerial(perintahDEL);

    // Baca respons ACK dari Arduino (sukses hapus / ID tidak ditemukan)
    terimaDataSerial(serialBuffer, sizeof(serialBuffer));
    printf("\n[Respon Arduino]: %s\n", serialBuffer);
}

void searchByID() {
    char idCari[15];
    char idBarang[15], nama[30], kategori[20], lokasi[20], status[15], pemilik[20], pic[20];
    int stok;
    int ditemukan = 0;

    printf("\n=== CARI DATA BERDASARKAN ID ===\n");
    printf("Masukkan ID Barang yang dicari: ");
    scanf("%s", idCari);

    // Minta seluruh data dari Arduino untuk di-parse di sisi aplikasi penampil
    kirimDataSerial("GET_ALL\n");
    terimaDataSerial(serialBuffer, sizeof(serialBuffer));

    // Proses parsing CSV baris demi baris menggunakan strtok
    char* baris = strtok(serialBuffer, "\n");
    
    // Tampilkan header tabel via UI jika data ditemukan
    while (baris != NULL) {
        // Parse atribut beralaskan pembatas koma atau titik koma (;)
        sscanf(baris, "%[^;];%[^;];%[^;];%d;%[^;];%[^;];%[^;];%[^;\n]", 
               idBarang, nama, kategori, &stok, lokasi, status, pemilik, pic);

        if (strcmp(idBarang, idCari) == 0) {
            if (!ditemukan) {
                printf("\n%-10s | %-20s | %-5s | %-10s | %-10s\n", "ID", "Nama Alat", "Stok", "Lokasi", "Status");
                printf("----------------------------------------------------------------------\n");
            }
            printf("%-10s | %-20s | %-5d | %-10s | %-10s\n", idBarang, nama, stok, lokasi, status);
            printf("Pemilik: %s | PIC: %s\n", pemilik, pic);
            ditemukan = 1;
            break;
        }
        baris = strtok(NULL, "\n");
    }

    if (!ditemukan) {
        printf("\n[INFO]: ID Barang '%s' tidak ditemukan di sistem.\n", idCari);
    }
}

void updateStockAndStatus() {
    char id[15], statusBaru[15];
    int stokBaru;
    char perintahUPDATE[50];

    printf("\n=== UPDATE STOK & STATUS BARANG ===\n");
    printf("Masukkan ID Barang: ");
    scanf("%s", id);
    printf("Masukkan Jumlah Stok Baru: ");
    scanf("%d", &stokBaru);
    printf("Masukkan Status Baru     : ");
    scanf("%s", statusBaru);

    // Format perintah UPDATE ke sistem
    sprintf(perintahUPDATE, "UPDATE;%s;%d;%s\n", id, stokBaru, statusBaru);

    // Kirim serial ke Arduino untuk menulis ulang data node terkait
    kirimDataSerial(perintahUPDATE);

    // Cetak konfirmasi
    terimaDataSerial(serialBuffer, sizeof(serialBuffer));
    printf("\n[Respon Arduino]: %s\n", serialBuffer);
}

void displayAllInventory() {
    char id[15], nama[30], kategori[20], lokasi[20], status[15], pemilik[20], pic[20];
    int stok;
    int dataKosong = 1;

    // Ambil data mentah CSV dari memori Arduino 
    kirimDataSerial("GET_ALL\n");
    terimaDataSerial(serialBuffer, sizeof(serialBuffer));

    printf("\n======================================= DATA INVENTARIS LAB =======================================\n");
    printf("%-10s | %-20s | %-15s | %-5s | %-10s | %-10s | %-12s\n", "ID", "Nama Alat", "Kategori", "Stok", "Lokasi", "Status", "PIC");
    printf("---------------------------------------------------------------------------------------------------\n");

    char* baris = strtok(serialBuffer, "\n");
    while (baris != NULL) {
        if (strlen(baris) > 5) { // Memastikan baris berisi data valid bukan baris kosong
            sscanf(baris, "%[^;];%[^;];%[^;];%d;%[^;];%[^;];%[^;];%[^;\n]", 
                   id, nama, kategori, &stok, lokasi, status, pemilik, pic);
            
            printf("%-10s | %-20s | %-15s | %-5d | %-10s | %-10s | %-12s\n", id, nama, kategori, stok, lokasi, status, pic);
            dataKosong = 0;
        }
        baris = strtok(NULL, "\n");
    }

    if (dataKosong) {
        printf("                                    [ Data Masih Kosong ]                                         \n");
    }
    printf("===================================================================================================\n");
}

void displaySummary() {
    char id[15], nama[30], kategori[20], lokasi[20], status[15], pemilik[20], pic[20];
    int stok;
    
    // Variabel kalkulasi statistik matematika 
    int totalJenisBarang = 0;
    int totalStokTersedia = 0;
    int totalDipinjam = 0;
    int totalRusak = 0;

    kirimDataSerial("GET_ALL\n");
    terimaDataSerial(serialBuffer, sizeof(serialBuffer));

    char* baris = strtok(serialBuffer, "\n");
    while (baris != NULL) {
        if (strlen(baris) > 5) {
            sscanf(baris, "%[^;];%[^;];%[^;];%d;%[^;];%[^;];%[^;];%[^;\n]", 
                   id, nama, kategori, &stok, lokasi, status, pemilik, pic);
            
            totalJenisBarang++;
            
            // Logika kalkulasi ringkasan berdasarkan string status barang
            if (strcasecmp(status, "tersedia") == 0) {
                totalStokTersedia += stok;
            } else if (strcasecmp(status, "dipinjam") == 0) {
                totalDipinjam += stok;
            } else if (strcasecmp(status, "rusak") == 0) {
                totalRusak += stok;
            }
        }
        baris = strtok(NULL, "\n");
    }

    // Tampilkan lembar kalkulasi ringkasan inventaris 
    printf("\n=================================");
    printf("\n   RINGKASAN KONDISI INVENTARIS  ");
    printf("\n=================================");
    printf("\n Total Jenis Item Unik : %d jenis", totalJenisBarang);
    printf("\n Total Unit Tersedia   : %d unit", totalStokTersedia);
    printf("\n Total Unit Dipinjam   : %d unit", totalDipinjam);
    printf("\n Total Unit Rusak      : %d unit", totalRusak);
    printf("\n=================================\n");
}