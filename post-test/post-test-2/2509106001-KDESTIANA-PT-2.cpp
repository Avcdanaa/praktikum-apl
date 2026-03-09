#include <iostream>
#include <string>
#include <iomanip>

using namespace std;

const int MAX_DATA = 100;
const int MAX_USER = 100;
const int BATAS_LOGIN = 3;

struct JadwalOperasional {
    string jamBuka;
    string jamTutup;
    string hariOperasional;
};

struct DataWisata {
    int idWisata;
    string namaTempat;
    string deskripsi;
    JadwalOperasional jadwal;
    int jumlahPengunjung;
    int kuotaTersedia;
    float hargaTiket;
    bool statusTersedia;
};

struct AkunUser {
    string namaPengguna;
    string nimPassword;
};

AkunUser databaseUser[MAX_USER];
DataWisata daftarWisata[MAX_DATA];

int jumlahUser = 0;
int jumlahData = 0;

void fiturRegister() {
    cout << "\n=== REGISTRASI USER BARU ===" << endl;
    
    if (jumlahUser >= MAX_USER) {
        cout << "Kapasitas user penuh!" << endl;
        return;
    }

    string inputNama, inputNIM;
    
    cout << "Masukkan Nama (Username): ";
    cin >> inputNama;
    
    for (int i = 0; i < jumlahUser; i++) {
        if (databaseUser[i].namaPengguna == inputNama) {
            cout << "Username '" << inputNama << "' sudah terdaftar!" << endl;
            cout << "Silakan kembali ke menu utama dan pilih username lain." << endl;
            return;
        }
    }
    
    cout << "Masukkan NIM (Password): ";
    cin >> inputNIM;

    databaseUser[jumlahUser].namaPengguna = inputNama;
    databaseUser[jumlahUser].nimPassword = inputNIM;
    
    jumlahUser++;
    cout << "Registrasi berhasil!" << endl;
    cout << "Silakan login dengan akun yang sudah dibuat." << endl;
}

bool fiturLogin() {
    int percobaan = 0;
    string inputNama, inputNim;
    bool ditemukan = false;

    while (percobaan < BATAS_LOGIN && !ditemukan) {
        cout << "\n=== SILAHKAN LOGIN ===" << endl;
        cout << "Username (Nama): ";
        cin >> inputNama;
        cout << "Password (NIM): ";
        cin >> inputNim;

        for (int i = 0; i < jumlahUser; i++) {
            if (databaseUser[i].namaPengguna == inputNama && 
                databaseUser[i].nimPassword == inputNim) {
                ditemukan = true;
                break;
            }
        }

        if (!ditemukan) {
            percobaan++;
            cout << "Login Gagal! Sisa kesempatan: " << (BATAS_LOGIN - percobaan) << endl;
        }
    }

    if (ditemukan) {
        cout << "Login Berhasil! Selamat datang, " << inputNama << endl;
        return true;
    } else {
        cout << "Anda gagal login 3 kali. Program berhenti." << endl;
        return false;
    }
}

void tambahDataWisata() {
    cout << "\n=== TAMBAH DESTINASI WISATA ===" << endl;
    
    if (jumlahData >= MAX_DATA) {
        cout << "Kapasitas data penuh!" << endl;
        return;
    }

    daftarWisata[jumlahData].idWisata = jumlahData + 1;

    cout << "Nama Tempat Wisata: ";
    cin.ignore();
    getline(cin, daftarWisata[jumlahData].namaTempat);

    cout << "Deskripsi Wisata: ";
    getline(cin, daftarWisata[jumlahData].deskripsi);

    cout << "--- Jadwal Operasional ---" << endl;
    cout << "Jam Buka (contoh: 08:00): ";
    getline(cin, daftarWisata[jumlahData].jadwal.jamBuka);
    
    cout << "Jam Tutup (contoh: 17:00): ";
    getline(cin, daftarWisata[jumlahData].jadwal.jamTutup);
    
    cout << "Hari Operasional: ";
    getline(cin, daftarWisata[jumlahData].jadwal.hariOperasional);

    cout << "--- Informasi Pemesanan ---" << endl;
    cout << "Harga Tiket (Rp): ";
    cin >> daftarWisata[jumlahData].hargaTiket;

    cout << "Kuota Pengunjung Per Hari: ";
    cin >> daftarWisata[jumlahData].jumlahPengunjung;
    
    daftarWisata[jumlahData].kuotaTersedia = daftarWisata[jumlahData].jumlahPengunjung;
    daftarWisata[jumlahData].statusTersedia = true;

    jumlahData++;
    cout << "Destinasi berhasil ditambahkan ke sistem pemesanan!" << endl;
}

void lihatDataWisata() {
    cout << "\n=== KATALOG WISATA TERSEDIA ===" << endl;

    if (jumlahData == 0) {
        cout << "Belum ada destinasi yang tersedia." << endl;
        return;
    }

    cout << "====================================================================================================" << endl;
    cout << "| ID | Nama Tempat       | Harga Tiket  | Kuota/Hari | Tersedia | Jam Buka  | Status     |" << endl;
    cout << "====================================================================================================" << endl;

    for (int i = 0; i < jumlahData; i++) {
        cout << "| " << setw(2) << daftarWisata[i].idWisata << " ";
        cout << "| " << setw(17) << daftarWisata[i].namaTempat << " ";
        cout << "| Rp " << setw(8) << daftarWisata[i].hargaTiket << " ";
        cout << "| " << setw(10) << daftarWisata[i].jumlahPengunjung << " ";
        cout << "| " << setw(8) << daftarWisata[i].kuotaTersedia << " ";
        cout << "| " << setw(9) << daftarWisata[i].jadwal.jamBuka << " ";
        
        if (daftarWisata[i].statusTersedia) {
            cout << "| " << setw(10) << "Aktif" << " |" << endl;
        } else {
            cout << "| " << setw(10) << "Nonaktif" << " |" << endl;
        }
    }
    cout << "====================================================================================================" << endl;
}

void ubahDataWisata() {
    cout << "\n=== UBAH INFORMASI DESTINASI ===" << endl;
    
    if (jumlahData == 0) {
        cout << "Belum ada data untuk diubah." << endl;
        return;
    }

    for (int i = 0; i < jumlahData; i++) {
        cout << "ID: " << daftarWisata[i].idWisata << " | Nama: " << daftarWisata[i].namaTempat << endl;
    }

    int idUbah;
    cout << "Masukkan ID Wisata yang akan diubah: ";
    cin >> idUbah;

    bool ditemukan = false;
    for (int i = 0; i < jumlahData; i++) {
        if (daftarWisata[i].idWisata == idUbah) {
            ditemukan = true;
            
            cout << "\n--- Ubah Informasi ---" << endl;
            cout << "1. Update Kuota (Musim Liburan)" << endl;
            cout << "2. Update Harga Tiket" << endl;
            cout << "3. Update Status Ketersediaan" << endl;
            cout << "Pilihan Update: ";
            int pilihanUpdate;
            cin >> pilihanUpdate;

            if (pilihanUpdate == 1) {
                cout << "Masukkan Kuota Pengunjung Baru: ";
                cin >> daftarWisata[i].jumlahPengunjung;
                daftarWisata[i].kuotaTersedia = daftarWisata[i].jumlahPengunjung;
                cout << "Kuota berhasil diperbarui!" << endl;
            } else if (pilihanUpdate == 2) {
                cout << "Masukkan Harga Tiket Baru (Rp): ";
                cin >> daftarWisata[i].hargaTiket;
                cout << "Harga berhasil diperbarui!" << endl;
            } else if (pilihanUpdate == 3) {
                cout << "Apakah destinasi aktif untuk pemesanan? (1=Ya, 0=Tidak): ";
                int status;
                cin >> status;
                daftarWisata[i].statusTersedia = (status == 1);
                cout << "Status berhasil diperbarui!" << endl;
            } else {
                cout << "Pilihan update tidak valid." << endl;
            }
            break;
        }
    }

    if (!ditemukan) {
        cout << "ID Wisata tidak ditemukan!" << endl;
    }
}

void hapusDataWisata() {
    cout << "\n=== HAPUS DESTINASI WISATA ===" << endl;

    if (jumlahData == 0) {
        cout << "Belum ada data untuk dihapus." << endl;
        return;
    }

    for (int i = 0; i < jumlahData; i++) {
        cout << "ID: " << daftarWisata[i].idWisata << " | Nama: " << daftarWisata[i].namaTempat << endl;
    }

    int idHapus;
    cout << "Masukkan ID Wisata yang akan dihapus (Jadwal Batal/Promo Kadaluarsa): ";
    cin >> idHapus;

    bool ditemukan = false;
    for (int i = 0; i < jumlahData; i++) {
        if (daftarWisata[i].idWisata == idHapus) {
            ditemukan = true;
            
            for (int j = i; j < jumlahData - 1; j++) {
                daftarWisata[j] = daftarWisata[j + 1];
            }
            
            jumlahData--;
            cout << "Destinasi berhasil dihapus dari sistem!" << endl;
            break;
        }
    }

    if (!ditemukan) {
        cout << "ID Wisata tidak ditemukan!" << endl;
    }
}

void menuUtamaCRUD() {
    int pilihan;
    do {
        cout << "\n=== SISTEM PEMESANAN TIKET WISATA ALAM ===" << endl;
        cout << "1. Tambah Destinasi (Create)" << endl;
        cout << "2. Lihat Destinasi (Read)" << endl;
        cout << "3. Ubah Informasi (Update)" << endl;
        cout << "4. Hapus Destinasi (Delete)" << endl;
        cout << "5. Keluar" << endl;
        cout << "Pilihan: ";
        cin >> pilihan;

        switch (pilihan) {
            case 1: tambahDataWisata(); break;
            case 2: lihatDataWisata(); break;
            case 3: ubahDataWisata(); break;
            case 4: hapusDataWisata(); break;
            case 5: cout << "Terima kasih telah menggunakan layanan kami." << endl; break;
            default: cout << "Pilihan tidak valid!" << endl;
        }
    } while (pilihan != 5);
}

int main() {
    jumlahUser = 0;

    int pilihanAwal;

    do {
        cout << "\n========================================" << endl;
        cout << "   SISTEM PEMESANAN TIKET WISATA ALAM   " << endl;
        cout << "========================================" << endl;
        cout << "1. Login" << endl;
        cout << "2. Register" << endl;
        cout << "3. Keluar" << endl;
        cout << "========================================" << endl;
        cout << "Pilihan: ";
        cin >> pilihanAwal;

        if (pilihanAwal == 1) {
            if (fiturLogin()) {
                menuUtamaCRUD();
                break;
            } else {
                return 0;
            }
        } else if (pilihanAwal == 2) {
            fiturRegister();
        } else if (pilihanAwal == 3) {
            cout << "Program selesai." << endl;
            return 0;
        } else {
            cout << "Pilihan tidak valid!" << endl;
        }
    } while (true);

    return 0;
}