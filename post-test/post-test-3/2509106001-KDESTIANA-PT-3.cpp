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

int cariWisata(DataWisata arr[], int count, int id) {
    for (int i = 0; i < count; i++) {
        if (arr[i].idWisata == id) 
            return i;
    }
    return -1;
}

int cariWisata(DataWisata arr[], int count, string nama) {
    for (int i = 0; i < count; i++) {
        if (arr[i].namaTempat == nama) 
            return i;
    }
    return -1;
}

bool prosesLoginRekursif(AkunUser dbUser[], int &jumlahUser, int sisaPercobaan) {
    if (sisaPercobaan == 0) {
        return false;
    }

    string inputNama, inputNim;
    cout << "\n=== SILAHKAN LOGIN (Percobaan " << (BATAS_LOGIN - sisaPercobaan + 1) << "/" << BATAS_LOGIN << ") ===" << endl;
    cout << "Username (Nama): ";
    cin >> inputNama;
    cout << "Password (NIM): ";
    cin >> inputNim;

    bool ditemukan = false;
    for (int i = 0; i < jumlahUser; i++) {
        if (dbUser[i].namaPengguna == inputNama && dbUser[i].nimPassword == inputNim) {
            ditemukan = true;
            break;
        }
    }

    if (ditemukan) {
        cout << "Login Berhasil! Selamat datang, " << inputNama << endl;
        return true;
    } else {
        cout << "Login Gagal! Sisa kesempatan: " << (sisaPercobaan - 1) << endl;
        return prosesLoginRekursif(dbUser, jumlahUser, sisaPercobaan - 1);
    }
}

void fiturRegister(AkunUser dbUser[], int &jumlahUser) {
    cout << "\n=== REGISTRASI USER BARU ===" << endl;
    
    if (jumlahUser >= MAX_USER) {
        cout << "Kapasitas user penuh!" << endl;
        return;
    }

    string inputNama, inputNIM;
    cout << "Masukkan Nama (Username): ";
    cin >> inputNama;
    
    for(int i = 0; i < jumlahUser; i++) {
        if(dbUser[i].namaPengguna == inputNama) {
            cout << "Username '" << inputNama << "' sudah terdaftar!" << endl;
            cout << "Silakan kembali ke menu utama dan pilih username lain." << endl;
            return;
        }
    }
    
    cout << "Masukkan NIM (Password): ";
    cin >> inputNIM;

    dbUser[jumlahUser].namaPengguna = inputNama;
    dbUser[jumlahUser].nimPassword = inputNIM;
    
    jumlahUser++;
    cout << "Registrasi berhasil!" << endl;
    cout << "Silakan login dengan akun yang sudah dibuat." << endl;
}

void tambahDataWisata(DataWisata arr[], int &count) {
    cout << "\n=== TAMBAH DESTINASI WISATA ===" << endl;
    
    if (count >= MAX_DATA) {
        cout << "Kapasitas data penuh!" << endl;
        return;
    }

    arr[count].idWisata = count + 1;
    cin.ignore();

    cout << "Nama Tempat Wisata: ";
    getline(cin, arr[count].namaTempat);
    
    cout << "Deskripsi Wisata: ";
    getline(cin, arr[count].deskripsi);
    
    cout << "--- Jadwal Operasional ---" << endl;
    cout << "Jam Buka (contoh: 08:00): ";
    getline(cin, arr[count].jadwal.jamBuka);
    
    cout << "Jam Tutup (contoh: 17:00): ";
    getline(cin, arr[count].jadwal.jamTutup);
    
    cout << "Hari Operasional: ";
    getline(cin, arr[count].jadwal.hariOperasional);

    cout << "--- Informasi Pemesanan ---" << endl;
    cout << "Harga Tiket (Rp): ";
    cin >> arr[count].hargaTiket;

    cout << "Kuota Pengunjung Per Hari: ";
    cin >> arr[count].jumlahPengunjung;
    
    arr[count].kuotaTersedia = arr[count].jumlahPengunjung;
    arr[count].statusTersedia = true;
    
    count++;
    cout << "Destinasi berhasil ditambahkan ke sistem!" << endl;
}

void lihatDataWisata(DataWisata arr[], int count) {
    cout << "\n=== KATALOG WISATA TERSEDIA ===" << endl;
    
    if (count == 0) {
        cout << "Belum ada destinasi yang tersedia." << endl;
        return;
    }

    cout << "========================================================================" << endl;
    cout << "| ID | Nama Tempat       | Harga      | Kuota | Status     |" << endl;
    cout << "========================================================================" << endl;

    for (int i = 0; i < count; i++) {
        cout << "| " << setw(2) << arr[i].idWisata << " ";
        cout << "| " << setw(17) << arr[i].namaTempat << " ";
        cout << "| Rp " << setw(6) << arr[i].hargaTiket << " ";
        cout << "| " << setw(5) << arr[i].kuotaTersedia << " ";
        cout << "| " << setw(10) << (arr[i].statusTersedia ? "Aktif" : "Nonaktif") << " |" << endl;
    }
    cout << "========================================================================" << endl;
}

void ubahDataWisata(DataWisata arr[], int &count) {
    cout << "\n=== UBAH INFORMASI DESTINASI ===" << endl;
    
    if (count == 0) {
        cout << "Belum ada data untuk diubah." << endl;
        return;
    }

    for (int i = 0; i < count; i++) {
        cout << "ID: " << arr[i].idWisata << " | Nama: " << arr[i].namaTempat << endl;
    }

    int idUbah;
    cout << "Masukkan ID Wisata yang akan diubah: ";
    cin >> idUbah;

    int index = cariWisata(arr, count, idUbah);

    if (index != -1) {
        cout << "\n--- Ubah Informasi: " << arr[index].namaTempat << " ---" << endl;
        cout << "1. Update Kuota (Musim Liburan)" << endl;
        cout << "2. Update Harga Tiket" << endl;
        cout << "3. Update Status Ketersediaan" << endl;
        cout << "Pilihan Update: ";
        int pilihanUpdate;
        cin >> pilihanUpdate;

        if (pilihanUpdate == 1) {
            cout << "Masukkan Kuota Pengunjung Baru: ";
            cin >> arr[index].jumlahPengunjung;
            arr[index].kuotaTersedia = arr[index].jumlahPengunjung;
            cout << "Kuota berhasil diperbarui!" << endl;
        } else if (pilihanUpdate == 2) {
            cout << "Masukkan Harga Tiket Baru (Rp): ";
            cin >> arr[index].hargaTiket;
            cout << "Harga berhasil diperbarui!" << endl;
        } else if (pilihanUpdate == 3) {
            cout << "Apakah destinasi aktif untuk pemesanan? (1=Ya, 0=Tidak): ";
            int status;
            cin >> status;
            arr[index].statusTersedia = (status == 1);
            cout << "Status berhasil diperbarui!" << endl;
        } else {
            cout << "Pilihan update tidak valid." << endl;
        }
    } else {
        cout << "ID Wisata tidak ditemukan!" << endl;
    }
}

void hapusDataWisata(DataWisata arr[], int &count) {
    cout << "\n=== HAPUS DESTINASI WISATA ===" << endl;

    if (count == 0) {
        cout << "Belum ada data untuk dihapus." << endl;
        return;
    }

    for (int i = 0; i < count; i++) {
        cout << "ID: " << arr[i].idWisata << " | Nama: " << arr[i].namaTempat << endl;
    }

    int idHapus;
    cout << "Masukkan ID Wisata yang akan dihapus: ";
    cin >> idHapus;

    int index = cariWisata(arr, count, idHapus);

    if (index != -1) {
        for (int j = index; j < count - 1; j++) {
            arr[j] = arr[j + 1];
        }
        count--;
        cout << "Destinasi berhasil dihapus dari sistem!" << endl;
    } else {
        cout << "ID Wisata tidak ditemukan!" << endl;
    }
}

void menuUtamaCRUD(DataWisata daftarWisata[], int &jumlahData) {
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
            case 1: tambahDataWisata(daftarWisata, jumlahData); break;
            case 2: lihatDataWisata(daftarWisata, jumlahData); break;
            case 3: ubahDataWisata(daftarWisata, jumlahData); break;
            case 4: hapusDataWisata(daftarWisata, jumlahData); break;
            case 5: cout << "Terima kasih telah menggunakan layanan kami." << endl; break;
            default: cout << "Pilihan tidak valid!" << endl;
        }
    } while (pilihan != 5);
}

int main() {
    AkunUser databaseUser[MAX_USER];
    DataWisata daftarWisata[MAX_DATA];
    int jumlahUser = 0;
    int jumlahData = 0;

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
            if (prosesLoginRekursif(databaseUser, jumlahUser, BATAS_LOGIN)) {
                menuUtamaCRUD(daftarWisata, jumlahData);
                break;
            } else {
                cout << "Anda gagal login 3 kali. Program berhenti." << endl;
                return 0;
            }
        } else if (pilihanAwal == 2) {
            fiturRegister(databaseUser, jumlahUser);
        } else if (pilihanAwal == 3) {
            cout << "Program selesai." << endl;
            return 0;
        } else {
            cout << "Pilihan tidak valid!" << endl;
        }
    } while (true);

    return 0;
}