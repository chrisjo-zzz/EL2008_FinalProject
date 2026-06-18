@echo off
echo =========================================================
echo Memulai Kompilasi PC Client untuk Windows (MSVC)
echo =========================================================

:: Bersihkan file eksekutabel lama jika ada
if exist inventory.exe del inventory.exe
if exist *.obj del *.obj

:: Kompilasi menggunakan cl.exe
cl /I.\include src\main.c src\app_logic.c src\user_interface.c src\serial_comm_windows.c /Fe:inventory.exe

:: Cek status kompilasi
if %ERRORLEVEL% EQU 0 (
    echo.
    echo =========================================================
    echo Kompilasi Berhasil!
    echo Bersihkan sisa file objek...
    del *.obj
    echo Jalankan program dengan: .\inventory.exe
    echo Atau langsung pakai port: .\inventory.exe COM3
    echo =========================================================
) else (
    echo.
    echo [ERROR] Kompilasi gagal. Periksa pesan error di atas.
)