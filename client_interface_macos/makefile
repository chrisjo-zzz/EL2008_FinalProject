# KONFIGURASI COMPILER 
CC = gcc
# -I./include memberitahu compiler untuk mencari file .h di folder include/
CFLAGS = -Wall -Wextra -I./include

# NAMA EKSEKUTABEL
TARGET = inventory

# FILE SUMBER (Hanya gunakan driver macOS) 
SRCS = src/main.c \
       src/app_logic.c \
       src/user_interface.c \
       src/serial_comm_macos.c

# FILE OBJEK (Dihasilkan otomatis dari SRCS) 
OBJS = $(SRCS:.c=.o)

# ATURAN DEFAULT 
all: $(TARGET)

# TAHAP LINKING (Menggabungkan .o menjadi eksekutabel) 
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)
	@echo "========================================================="
	@echo "Kompilasi PC Client Berhasil!"
	@echo "Jalankan dengan         : ./$(TARGET)"
	@echo "Atau langsung pakai port: ./$(TARGET) /dev/cu.usbmodem11301"
	@echo "========================================================="

# TAHAP KOMPILASI (Mengubah .c menjadi .o) 
src/%.o: src/%.c
	$(CC) $(CFLAGS) -c $< -o $@

# PEMBERSIHAN 
clean:
	rm -f src/*.o $(TARGET)
	@echo "Membersihkan file objek dan eksekutabel PC Client."