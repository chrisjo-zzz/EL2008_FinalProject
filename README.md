# HELOOO Kelompok 6

![Hello](https://i.makeagif.com/media/5-08-2019/8RlZpL.gif)

Hallo Kelompok 6. Tolong baca ini ya sebelum mulai NUBBEEEESSSS.

## Extention yang Harus Kalian Download di VSCode

Nanti kalian harus add extention **PlatformIO** (Untuk compile dan upload code ke Arduino) dan **Wokwi** (Untuk simulasikan Arduino) di VSCode

[Tutor Add PlatformIO di VSCode](https://www.youtube.com/watch?v=xrAgUXFdrs8)

[Tutor setup Wokwi di VScode](https://www.youtube.com/watch?v=ECNTyMm_5PE)

[PlatformIO Documentation](https://docs.platformio.org/en/latest/)

[Wokwi Documentation](https://docs.wokwi.com/vscode/getting-started)

![yuh huh](https://media.tenor.com/TL2rTF5jqHoAAAAM/k-on-yui.gif)

## Cara Pake Git

### Cara Setup Git

Jika belum ada Git bisa [download](https://git-scm.com/) dulu ya.

Bisa tonton [tutor ini](https://www.youtube.com/watch?v=wDRoduig_98)

Abis itu kalian bisa clone github reponya di lokasi yang kalian inginin dengan ketik

````bash
git clone https://github.com/AqeelGhani/tugas-besar-pmp-2026-kelompok-6.git
````

Kalau ada pertanyaan  langsung tanya aku ya ;)

![love you](https://giffiles.alphacoders.com/349/34952.gif)

### Cara Pull dan bikin branch baru di git

Nahh kalian saat udah masuk kedalam git bisa bikin branch masing masing nih.

Pertama, kalian bikin branch dengan ketik 

````bash
git branch <nama branch kalian (Nama kalian juga boleh)>
````

Terus kalian bisa masuk ke branch kalian dengan ketik

````bash
git checkout <nama branch kalian>
````

nah abis itu kalian kalau mau pull dari main ke branch kalian bisa ketik

````bash
git pull origin main
````

Gampang KAN!!!!!!

![cute](https://media.tenor.com/B50HsFYHbssAAAAM/anime-eiga-k-on.gif)

### Cara Commit Git

Kalau kalian mau melakukan commit setelah melakukan perubahan ada beberapa hal yang harus kalian lakukan.

Pertama, kalian harus memberi tahu file mana yang mau dilakukan commit. Kalian dapat ketik

````bash
git add <lokasi file>
````

contoh nya:

````bash
git add .\src\testHFile.cpp
````
atau alternatif lain adalah add semua perubahan yang terjadi

````bash
git add .
````

Lalu setelah di git add, kalian dapat langsung melakukan commit

````bash
git commit -m "<pesan commit>"
````

Untuk `<pesan commit>`, akan ada format nya sendiri yaitu

`<jenis commit> : <file yang di commit> : <Penjelasan Commit>`

Contohnya, 

````bash
git commit -m "feat : testHFile.cpp : Pembuatan fungsi sayHello"
````

untuk `<jenis commit>` dapat mengikuti tabel berikut,

| Tipe | Deskripsi |
| :--- | :--- |
| **`feat`** | Commit yang menambah, menyesuaikan, atau menghapus fitur pada API atau UI. |
| **`fix`** | Commit yang memperbaiki bug pada API atau UI dari commit `feat` sebelumnya. |
| **`refactor`** | Commit yang menulis ulang atau merestrukturisasi kode tanpa mengubah perilaku API atau UI. |
| **`perf`** | Tipe khusus dari `refactor` yang bertujuan spesifik untuk meningkatkan performa. |
| **`style`** | Commit yang berkaitan dengan gaya penulisan kode (misal: *white-space*, format, titik koma) dan tidak memengaruhi perilaku aplikasi. |
| **`test`** | Commit yang menambah pengujian (*test*) yang kurang atau memperbaiki pengujian yang sudah ada. |
| **`docs`** | Commit yang hanya memengaruhi dokumentasi. |
| **`build`** | Commit yang memengaruhi komponen terkait proses *build* seperti *tools*, dependensi, versi proyek, dan lain-lain. |
| **`ops`** | Commit yang memengaruhi aspek operasional seperti infrastruktur (IaC), skrip deployment, alur CI/CD, cadangan (*backup*), pemantauan, atau prosedur pemulihan. |
| **`chore`** | Commit untuk tugas-tugas rutin seperti commit awal, memodifikasi `.gitignore`, dan tugas administratif lainnya. |

Untuk penjelasan lebih lanjut dapat lihat di [repo ini](https://gist.github.com/qoomon/5dfcdf8eec66a051ecd85625518cfd13).

![huehuehue](https://i.imgur.com/0jAef66.gif)

### Cara Push ke Github

Setelah kalian udah ngelakuin perubahan, kalian bisa push ke github nihhh

Kalian ketik aja 

````bash
git push origin <nama branch kalian>
````

pastiin ya kalian lagi di branch kalian sebelum push dengan ketik

````bash
git branch
````

dan lihat apakah branch kalian adalah yang di highlight.

Nanti setelah itu kalian bisa lakuin pull request kalau mau merge ke main.

Kalau ini tanya Aku aja ya boss

![Thumbs Up](https://i.pinimg.com/originals/a1/c0/0c/a1c00cb7b524b8dbe0bbb115571e57ca.gif)

## Cara Nulis Program

Nah sebenernya kalau ini mirip mirip ya sama kalau kalian mau nulis program arduino biasa. Tetapi ada beberapa hal yang harus diperhatiin lagi

Pertama, kalian nanti ada dua jenis file yang akan kalian tulia yaitu C++ File `.cpp` dan Header File `.h`.

Cara menulisnya mirip seperti alpro kalau kalian inget, C++ file nya tulis di folder `src` sedangkan Header File ditulis di folder `include`

Note : Jangan lupa ya gunakan `#include <Arduino.h>` untuk menggunakan standard library arduino.

Jika kalian mau melakukan testing, kalian dapat menggunakan file `test.cpp` untuk mencoba fungsi yang telah kalian tulis.

Kalian **JANGAN** mengubah file `main.cpp` untuk melakukan test perfungsi. File ini digunakan untuk melakukan test secara keseluruhan atau mengkompile program akhir.

![stop](https://i2.glitter-graphics.org/pub/2786/2786632gya6yrrqab.gif)

## Cara Compile Program

Setelah kalian menulis program, kalian dapat mengcompile program dengan menggunakan **PlatformIo**.

Pertama, kalian pilih environment yang mau kalian gunakan. 

![Compile 1](image/Compile_1.png)

![Compile 2](image/Compile_2.png)

Lalu kalian tinggal klik compile.

![Compile 3](image/Compile_3.png)

Kalau kalian mau upload ke arduino kalian tinggal klik upload

![Compile 4](image/Compile_4.png)

Gampangkan ya!!!!

![Kawaiiii](https://giffiles.alphacoders.com/352/35262.gif)

## Cara Simulasi

Untuk simulasi akan digunakan **Wokwi**

Pertama, kalian ubah isi `wokwi.toml`.

Untuk environment `uno_main`, ubah menjadi

````
[wokwi]
version = 1
firmware = ".pio/build/uno_main/firmware.hex"
elf = ".pio/build/uno_main/firmware.elf"
````

Untuk environment `uno_test`, ubah menjadi

````
[wokwi]
version = 1
firmware = ".pio/build/uno_test/firmware.hex"
elf = ".pio/build/uno_test/firmware.elf"
````


Lalu setelah itu kalian buka `diagram.json` dan pastikan pada mode Wokwi Diagram Editor

Lalu kalian tinggal klik play

![Simulasi 1](image/Simulasi_1.png)

Simple kan ya.....

![Love](https://i.imgur.com/18yx2pI.gif)

## Notes dari Aqeel si Paling Ganteng

Kalau kalian ada pertanyaan atau merasa butuh tutorial, jangan segan untuk chat digrup ya. Terimakasih Semua.

![Arigato](https://i.pinimg.com/originals/12/99/9e/12999e9ddf2a3b878e9350eca01f816b.gif)