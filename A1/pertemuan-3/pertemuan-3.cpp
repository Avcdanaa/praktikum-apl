// #include <iostream>
// using namespace std;

// int kuadrat(int x) {
//     return x * x;
// }

// void sapa(string nama) {
//     cout << "Halo, " << nama << "!" << endl;
// }

// int main() {
//     sapa("Budi");
//     cout << "Hasil 5 kuadrat: " << kuadrat(5) << endl;
//     return 0;
// }

// #include <iostream>
// using namespace std;

// int kuadrat(int x);
// void sapa(string nama);

// int main() {
// sapa("Andi");
// cout << "Hasil 3 kuadrat: " << kuadrat(3) << endl;
// return 0;
// }

// int kuadrat(int x) {
// return x * x;
// }

// void sapa(string nama) {
// cout << "Halo, " << nama << "!" << endl;
// }

// #include <iostream>
// using namespace std;

// // Bagian Definisi Prosedur
// // Di sini 'namaHero', 'level', dan 'hp' adalah PARAMETER.
// // Mereka hanyalah "variabel kosong" yang menunggu nilai.
// void tampilkanStatus(string namaHero, int level, double hp) {
//     cout << " = STATUS HERO =" << endl;
//     cout << "Nama : " << namaHero << endl;
//     cout << "Level : " << level << endl;
//     cout << "Darah : " << hp << "%" << endl;
//     cout << "===================" << endl;

//     cout << endl;
// }

// int main() {
//     // Bagian pengambilan argumen
//     // Kasus 1: Mengirim nilai secara langsung
//     // "Alucard", 15, dan 90.5 adalah argumen.
//     tampilkanStatus("Alucard", 15, 90.5);

//     // Kasus 2: Mengirim menggunakan variabel lain
//     string hero2 = "Miya";
//     int lvl2 = 12;
//     double hp2 = 45.0;

//     // Variabel 'hero2', 'lvl2', dan 'hp2' dikirim sebagai argumen
//     tampilkanStatus(hero2, lvl2, hp2);

//     return 0;
// }

// #include <iostream>
// using namespace std;

// // Prosedur ini menerima nilai dari variable gajiSaya
// void cobaUbahGaji(int gajiSaya) {
//     gajiSaya = 1000000000; // Gaji di dalam prosedur
//     cout << "Gaji pas di dalam fungsi: " << gajiSaya << endl;
// }

// int main() {
//     int gajiSaya = 5000000; // Gaji di dalam main

//     cout << "Gaji awal: " << gajiSaya << endl;

//     cobaUbahGaji(gajiSaya); // Kirim ke fungsi

//     cout << "Gaji setelah fungsi dipanggil: " << gajiSaya << endl;

//     return 0;
// }

// #include <iostream>
// using namespace std;

// // Perhatikan tanda '&' di sebelah parameter
// void tukarsenjata(string &senjata) {
//     senjata = "Sarung Wadimor"; // Langsung ganti isi variabel aslinya
// }

// int main() {
//     string senjatahero = "Kayu Busuk";

//     cout << "Senjata awal: " << senjatahero << endl;

//     tukarsenjata(senjatahero); // Panggil prosedur

//     // Variable dalam main akan ikut terubah
//     cout << "Senjata sekarang: " << senjatahero << endl;

//     return 0;
// }

// #include <iostream>
// using namespace std;

// // 'kadarGula' punya nilai default "Normal"
// // Parameter default wajib ditaruh paling kanan!
// void pesankopi(string menu, string kadargula = "Normal") {
//     cout << "Pesanan: " << menu << " | Gula: " << kadargula << endl;
// }

// int main() {
//     // Kasus 1: pengguna mengirim 1 parameter
//     pesankopi("Kopi Susu");

//     // Kasus 2: pengguna mengirim 2 parameter dan menggantikan
//     // parameter default dari prosedur
//     pesankopi("Americano", "Less Sugar");

//     return 0;
// }

// #include <iostream>
// using namespace std;

// // Variabel global
// int skorTertinggi = 100;

// void cetakSkor() {
//     // Fungsi ini akan membaca variabel global skorTertinggi
//     cout << "Skor Fungsi: " << skorTertinggi << endl;
// }

// int main() {
//     cout << "Skor: " << skorTertinggi << endl;
//     cetakSkor();
//     return 0;
// }

// #include <iostream>
// using namespace std;

// void calonJuara() {
//     // Variabel lokal, cuma bisa dipakai di dalam fungsi ini
//     string Team = "RRQ";
//     cout << "Tim: " << Team << endl;
// }

// int main() {
//     calonJuara(); // Fungsi berjalan normal
//     # cout << "Tim: " << Team << endl;
//     // Variabel Team tidak bisa diakses di sini
//     return 0;
// }

// #include <iostream>
// using namespace std;

// // Variabel global bernilai 10
// int angka = 10;

// void cobaShadow() {
//     // Variabel lokal akan menimpa variabel global 'angka'
//     int angka = 500;
//     cout << "Nilai angka dalam fungsi: " << angka << " (Ini yang lokal)" << endl;
// }

// int main() {
//     cout << "Nilai angka di global: " << angka << " (Ini yang global)" << endl;
//     cobaShadow();
//     cout << "Nilai angka akhir: " << angka << " (Balik ke global)" << endl;
//     return 0;
// }

// #include <iostream>
// using namespace std;

// // Fungsi menjumlahkan bilangan bulat
// int tambah(int a, int b) {
//     return a + b;
// }

// // Fungsi 2 menjumlahkan bilangan desimal
// double tambah(double a, double b) {
//     return a + b;
// }

// int main() {
//     cout << "Hasil Int: " << tambah(5, 6) << endl;
//     cout << "Hasil Double: " << tambah(5.5, 6.6) << endl;
//     return 0;
// }

// #include <iostream>
// using namespace std;

// int hitungLuas(int panjang, int lebar) {
//     int hasil = panjang * lebar;
//     return hasil; // Return mengembalikan nilai hasil
// }

// int main() {
//     int p = 10;
//     int l = 5;

//     // Pemanggilan fungsi
//     int luasTanah = hitungLuas(p, l);

//     cout << "Panjang: " << p << "m, Lebar: " << l << "m" << endl;
//     cout << "Total Luas Tanah: " << luasTanah << " meter persegi." << endl;

//     return 0;
// }

// #include <iostream>
// using namespace std;

// void cekGenap(int angka) {
//     if (angka % 2 == 0) {
//         cout << angka << " adalah Genap." << endl;
//         return; // Stop di sini, kode di bawah tidak dijalankan
//     }
//     // Kode ini hanya jalan kalau angka ganjil
//     cout << angka << " adalah Ganjil." << endl;
// }

// int main() {
//     cekGenap(4);
//     cekGenap(7);
//     return 0;
// }

// #include <iostream>
// using namespace std;

// int faktorialIteratif(int n) {
//     int hasil = 1;
//     for (int i = 1; i <= n; i++) {
//         hasil *= i;
//     }
//     return hasil;
// }

// int main() {
//     cout << "5! = " << faktorialIteratif(5) << endl;
//     return 0;
// }

// #include <iostream>
// using namespace std;

// int faktorialRekursif(int n) {
//     if (n <= 1) return 1; // Base case
//     return n * faktorialRekursif(n - 1); // Rekursi
// }

// int main() {
//     cout << "5! = " << faktorialRekursif(5) << endl;
//     return 0;
// // }