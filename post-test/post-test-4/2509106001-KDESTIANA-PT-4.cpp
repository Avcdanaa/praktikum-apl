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

int cariWisata(DataWisata *arr, int count, int id) {
    for (int i = 0; i < count; i++) {
        if (arr[i].idWisata == id) return i;
    }
    return -1;
}

bool prosesLoginRekursif(AkunUser *dbUser, int *jumlahUser, int sisaPercobaan) {
    if (sisaPercobaan == 0) return false;

    string inputNama, inputNim;
    cout << "\n=== SILAHKAN LOGIN (Percobaan " << (BATAS_LOGIN - sisaPercobaan + 1) << "/" << BATAS_LOGIN << ") ===" << endl;
    cout << "Username: "; cin >> inputNama;
    cout << "Password: "; cin >> inputNim;

    for (int i = 0; i < *jumlahUser; i++) {
        if (dbUser[i].namaPengguna == inputNama && dbUser[i].nimPassword == inputNim) {
            cout << "Login Berhasil! Selamat datang, " << inputNama << endl;
            return true;
        }
    }

    cout << "Login Gagal! Sisa kesempatan: " << (sisaPercobaan - 1) << endl;
    return prosesLoginRekursif(dbUser, jumlahUser, sisaPercobaan - 1);
}

void fiturRegister(AkunUser *dbUser, int *jumlahUser) {
    cout << "\n=== REGISTRASI USER BARU ===" << endl;
    if (*jumlahUser >= MAX_USER) {
        cout << "Kapasitas user penuh!" << endl; return;
    }

    string inputNama, inputNIM;
    cout << "Masukkan Nama (Username): "; cin >> inputNama;

    for(int i = 0; i < *jumlahUser; i++) {
        if(dbUser[i].namaPengguna == inputNama) {
            cout << "Username sudah terdaftar!" << endl; return;
        }
    }

    cout << "Masukkan NIM (Password): "; cin >> inputNIM;
    dbUser[*jumlahUser].namaPengguna = inputNama;
    dbUser[*jumlahUser].nimPassword = inputNIM;
    (*jumlahUser)++;
    cout << "Registrasi berhasil!" << endl;
}

void tambahDataWisata(DataWisata *arr, int *count) {
    cout << "\n=== TAMBAH DESTINASI WISATA ===" << endl;
    if (*count >= MAX_DATA) { cout << "Kapasitas data penuh!" << endl; return; }

    DataWisata *dataBaru = &arr[*count]; 
    dataBaru->idWisata = *count + 1;
    cin.ignore();

    cout << "Nama Tempat Wisata: "; getline(cin, dataBaru->namaTempat);
    cout << "Deskripsi: "; getline(cin, dataBaru->deskripsi);
    cout << "Jam Buka: "; getline(cin, dataBaru->jadwal.jamBuka);
    cout << "Jam Tutup: "; getline(cin, dataBaru->jadwal.jamTutup);
    cout << "Hari Operasional: "; getline(cin, dataBaru->jadwal.hariOperasional);
    cout << "Harga Tiket (Rp): "; cin >> dataBaru->hargaTiket;
    cout << "Kuota Pengunjung: "; cin >> dataBaru->jumlahPengunjung;

    dataBaru->kuotaTersedia = dataBaru->jumlahPengunjung;
    dataBaru->statusTersedia = true;
    (*count)++;
    cout << "Data berhasil ditambahkan!" << endl;
}

void lihatDataWisata(DataWisata *arr, int count) {
    cout << "\n=== KATALOG WISATA ===" << endl;
    if (count == 0) { cout << "Belum ada data." << endl; return; }

    cout << "========================================================================" << endl;
    cout << "| ID | Nama Tempat       | Harga    | Kuota | Status  |" << endl;
    cout << "========================================================================" << endl;
    for (int i = 0; i < count; i++) {
        DataWisata *ptr = &arr[i];
        cout << "| " << setw(2) << ptr->idWisata << " ";
        cout << "| " << setw(17) << ptr->namaTempat << " ";
        cout << "| Rp " << setw(6) << ptr->hargaTiket << " ";
        cout << "| " << setw(5) << ptr->kuotaTersedia << " ";
        cout << "| " << setw(7) << (ptr->statusTersedia ? "Aktif" : "Nonaktif") << " |" << endl;
    }
    cout << "========================================================================" << endl;
}

void ubahDataWisata(DataWisata *arr, int *count) {
    cout << "\n=== UBAH INFORMASI DESTINASI ===" << endl;
    if (*count == 0) { cout << "Belum ada data." << endl; return; }

    int idUbah;
    cout << "Masukkan ID Wisata: "; cin >> idUbah;
    int index = cariWisata(arr, *count, idUbah);

    if (index != -1) {

        DataWisata *dataUbah = &arr[index];
        cout << "1. Update Kuota\n2. Update Harga\n3. Update Status\nPilihan: ";
        int pil; cin >> pil;
        if (pil == 1) { cout << "Kuota Baru: "; cin >> dataUbah->jumlahPengunjung; dataUbah->kuotaTersedia = dataUbah->jumlahPengunjung; }
        else if (pil == 2) { cout << "Harga Baru: "; cin >> dataUbah->hargaTiket; }
        else if (pil == 3) { cout << "Status (1=Aktif/0=Tidak): "; int s; cin >> s; dataUbah->statusTersedia = (s == 1); }
        cout << "Data berhasil diperbarui!" << endl;
    } else {
        cout << "ID tidak ditemukan!" << endl;
    }
}

void hapusDataWisata(DataWisata *arr, int *count) {
    cout << "\n=== HAPUS DESTINASI WISATA ===" << endl;
    if (*count == 0) { cout << "Belum ada data." << endl; return; }

    int idHapus;
    cout << "Masukkan ID Wisata: "; cin >> idHapus;
    int index = cariWisata(arr, *count, idHapus);

    if (index != -1) {
        for (int j = index; j < *count - 1; j++) arr[j] = arr[j + 1];
        (*count)--;
        cout << "Data berhasil dihapus!" << endl;
    } else {
        cout << "ID tidak ditemukan!" << endl;
    }
}

void menuUtamaCRUD(DataWisata *daftarWisata, int *jumlahData) {
    int pilihan;
    do {
        cout << "\n=== MENU ADMIN ===" << endl;
        cout << "1. Tambah Destinasi\n2. Lihat Destinasi\n3. Ubah Informasi\n4. Hapus Destinasi\n5. Keluar\nPilihan: ";
        cin >> pilihan;
        switch (pilihan) {
            case 1: tambahDataWisata(daftarWisata, jumlahData); break;
            case 2: lihatDataWisata(daftarWisata, *jumlahData); break;
            case 3: ubahDataWisata(daftarWisata, jumlahData); break;
            case 4: hapusDataWisata(daftarWisata, jumlahData); break;
            case 5: cout << "Keluar dari menu admin." << endl; break;
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
        cout << "1. Login\n2. Register\n3. Keluar\nPilihan: ";
        cin >> pilihanAwal;

        if (pilihanAwal == 1) {

            if (prosesLoginRekursif(databaseUser, &jumlahUser, BATAS_LOGIN)) 
            {
                menuUtamaCRUD(daftarWisata, &jumlahData);
            } else {
                cout << "Gagal login 3 kali. Program berhenti." << endl;
                return 0;
            }
        } else if (pilihanAwal == 2) {
            fiturRegister(databaseUser, &jumlahUser);
        } else if (pilihanAwal == 3) {
            cout << "Program selesai." << endl;
            return 0;
        } else {
            cout << "Pilihan tidak valid!" << endl;
        }
    } while (true);

    return 0;
}