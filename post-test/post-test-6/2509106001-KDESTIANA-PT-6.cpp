#include <iostream>
#include <string>
#include <iomanip>
#include <cctype>
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

int binarySearchID(DataWisata *arr, int n, int target) {
    int low = 0;
    int high = n - 1;
    while (low <= high) {
        int mid = low + (high - low) / 2;
        if (arr[mid].idWisata == target) return mid;
        else if (arr[mid].idWisata < target) low = mid + 1;
        else high = mid - 1;
    }
    return -1;
}

int linearSearchNama(DataWisata *arr, int n, string target) {
    for (int i = 0; i < n; i++) {
        string dataNama = arr[i].namaTempat;
        string inputNama = target;
        for (char &c : dataNama) c = tolower(c);
        for (char &c : inputNama) c = tolower(c);
        if (dataNama == inputNama) return i;
    }
    return -1;
}

void cetakTabel(DataWisata *arr, int count) {
    if (count == 0) { cout << "Belum ada data." << endl; return; }
    cout << "=============================================================================" << endl;
    cout << "| ID | Nama Tempat          | Harga Tiket  | Kuota | Status   |" << endl;
    cout << "=============================================================================" << endl;
    for (int i = 0; i < count; i++) {
        cout << "| " << setw(2)  << arr[i].idWisata << " ";
        cout << "| " << setw(20) << left << arr[i].namaTempat << right << " ";
        cout << "| Rp " << setw(9) << fixed << setprecision(0) << arr[i].hargaTiket << " ";
        cout << "| " << setw(5)  << arr[i].kuotaTersedia << " ";
        cout << "| " << setw(8)  << (arr[i].statusTersedia ? "Aktif" : "Nonaktif") << " |" << endl;
    }
    cout << "=============================================================================" << endl;
}

void bubbleSortNamaAscending(DataWisata *arr, int n) {
    bool swapped;
    for (int i = 0; i < n - 1; i++) {
        swapped = false;
        for (int j = 0; j < n - i - 1; j++) {
            string a = arr[j].namaTempat;
            string b = arr[j + 1].namaTempat;
            for (char &c : a) c = tolower(c);
            for (char &c : b) c = tolower(c);
            if (a > b) {
                DataWisata temp = arr[j];
                arr[j]         = arr[j + 1];
                arr[j + 1]     = temp;
                swapped = true;
            }
        }
        if (!swapped) break;
    }
}

void selectionSortHargaDescending(DataWisata *arr, int n) {
    for (int i = 0; i < n - 1; i++) {
        int indeksMax = i;
        for (int j = i + 1; j < n; j++) {
            if (arr[j].hargaTiket > arr[indeksMax].hargaTiket) indeksMax = j;
        }
        if (indeksMax != i) {
            DataWisata temp = arr[i];
            arr[i]          = arr[indeksMax];
            arr[indeksMax]  = temp;
        }
    }
}

void insertionSortKuotaAscending(DataWisata *arr, int n) {
    for (int i = 1; i < n; i++) {
        DataWisata key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j].kuotaTersedia > key.kuotaTersedia) {
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1] = key;
    }
}

void menuSorting(DataWisata *arr, int count) {
    DataWisata *salinan = new DataWisata[count];
    for (int i = 0; i < count; i++) salinan[i] = arr[i];
    int pil;
    cout << "\n--- Pilih Urutan Tampil ---" << endl;
    cout << "1. Nama A-Z          (Bubble Sort)"  << endl;
    cout << "2. Harga Tertinggi   (Selection Sort)"  << endl;
    cout << "3. Kuota Terendah    (Insertion Sort)" << endl;
    cout << "0. Tanpa pengurutan" << endl;
    cout << "Pilihan: "; cin >> pil;
    switch (pil) {
        case 1: bubbleSortNamaAscending(salinan, count); cout << "\n=== KATALOG WISATA - Nama A-Z (Bubble Sort) ===" << endl; break;
        case 2: selectionSortHargaDescending(salinan, count); cout << "\n=== KATALOG WISATA - Harga Tertinggi (Selection Sort) ===" << endl; break;
        case 3: insertionSortKuotaAscending(salinan, count); cout << "\n=== KATALOG WISATA - Kuota Terendah (Insertion Sort) ===" << endl; break;
        default: cout << "\n=== KATALOG WISATA ===" << endl; break;
    }
    cetakTabel(salinan, count);
    delete[] salinan;
}

void fiturPencarian(DataWisata *arr, int count) {
    int pil;
    cout << "\n=== FITUR PENCARIAN  ===" << endl;
    cout << "1. Cari berdasarkan ID (Binary Search)" << endl;
    cout << "2. Cari berdasarkan Nama (Linear Search)" << endl;
    cout << "Pilihan: "; cin >> pil;
    if (pil == 1) {
        int targetID;
        cout << "Masukkan ID Wisata: "; cin >> targetID;
        int idx = binarySearchID(arr, count, targetID);
        if (idx != -1) { cout << "\nData ditemukan menggunakan Binary Search!" << endl; cetakTabel(&arr[idx], 1); }
        else cout << "ID tidak ditemukan dalam data." << endl;
    } else if (pil == 2) {
        string targetNama;
        cin.ignore();
        cout << "Masukkan Nama Wisata: "; getline(cin, targetNama);
        int idx = linearSearchNama(arr, count, targetNama);
        if (idx != -1) { cout << "\nData ditemukan menggunakan Linear Search!" << endl; cetakTabel(&arr[idx], 1); }
        else cout << "Nama tidak ditemukan dalam data." << endl;
    } else cout << "Pilihan tidak valid!" << endl;
}

void lihatDataWisata(DataWisata *arr, int count) {
    cout << "\n=== LIHAT & KELOLA DATA ===" << endl;
    if (count == 0) { cout << "Belum ada data." << endl; return; }
    int pilMenu;
    cout << "1. Urutkan & Tampilkan Data (Sorting)" << endl;
    cout << "2. Cari Data (Searching)" << endl;
    cout << "Pilihan: "; cin >> pilMenu;
    if (pilMenu == 1) menuSorting(arr, count);
    else if (pilMenu == 2) fiturPencarian(arr, count);
    else cout << "Pilihan tidak valid!" << endl;
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
    if (*jumlahUser >= MAX_USER) { cout << "Kapasitas user penuh!" << endl; return; }
    string inputNama, inputNIM;
    cout << "Masukkan Nama (Username): "; cin >> inputNama;
    for (int i = 0; i < *jumlahUser; i++) {
        if (dbUser[i].namaPengguna == inputNama) { cout << "Username sudah terdaftar!" << endl; return; }
    }
    cout << "Masukkan NIM (Password): "; cin >> inputNIM;
    dbUser[*jumlahUser].namaPengguna = inputNama;
    dbUser[*jumlahUser].nimPassword  = inputNIM;
    (*jumlahUser)++;
    cout << "Registrasi berhasil!" << endl;
}

void tambahDataWisata(DataWisata *arr, int *count) {
    cout << "\n=== TAMBAH DESTINASI WISATA ===" << endl;
    if (*count >= MAX_DATA) { cout << "Kapasitas data penuh!" << endl; return; }
    DataWisata *dataBaru = &arr[*count];
    dataBaru->idWisata = *count + 1;
    cin.ignore();
    cout << "Nama Tempat Wisata   : "; getline(cin, dataBaru->namaTempat);
    cout << "Deskripsi            : "; getline(cin, dataBaru->deskripsi);
    cout << "Jam Buka             : "; getline(cin, dataBaru->jadwal.jamBuka);
    cout << "Jam Tutup            : "; getline(cin, dataBaru->jadwal.jamTutup);
    cout << "Hari Operasional     : "; getline(cin, dataBaru->jadwal.hariOperasional);
    cout << "Harga Tiket (Rp)     : "; cin >> dataBaru->hargaTiket;
    cout << "Kuota Pengunjung     : "; cin >> dataBaru->jumlahPengunjung;
    dataBaru->kuotaTersedia  = dataBaru->jumlahPengunjung;
    dataBaru->statusTersedia = true;
    (*count)++;
    cout << "Data berhasil ditambahkan!" << endl;
}

void ubahDataWisata(DataWisata *arr, int *count) {
    cout << "\n=== UBAH INFORMASI DESTINASI ===" << endl;
    if (*count == 0) { cout << "Belum ada data." << endl; return; }
    int idUbah;
    cout << "Masukkan ID Wisata: "; cin >> idUbah;
    int index = -1;
    for(int i=0; i<*count; i++) if(arr[i].idWisata == idUbah) { index = i; break; }
    if (index != -1) {
        DataWisata *dataUbah = &arr[index];
        cout << "1. Update Kuota\n2. Update Harga\n3. Update Status\nPilihan: ";
        int pil; cin >> pil;
        if      (pil == 1) { cout << "Kuota Baru: "; cin >> dataUbah->jumlahPengunjung; dataUbah->kuotaTersedia = dataUbah->jumlahPengunjung; }
        else if (pil == 2) { cout << "Harga Baru: "; cin >> dataUbah->hargaTiket; }
        else if (pil == 3) { cout << "Status (1=Aktif/0=Tidak): "; int s; cin >> s; dataUbah->statusTersedia = (s == 1); }
        cout << "Data berhasil diperbarui!" << endl;
    } else cout << "ID tidak ditemukan!" << endl;
}

void hapusDataWisata(DataWisata *arr, int *count) {
    cout << "\n=== HAPUS DESTINASI WISATA ===" << endl;
    if (*count == 0) { cout << "Belum ada data." << endl; return; }
    int idHapus;
    cout << "Masukkan ID Wisata: "; cin >> idHapus;
    int index = -1;
    for(int i=0; i<*count; i++) if(arr[i].idWisata == idHapus) { index = i; break; }
    if (index != -1) {
        for (int j = index; j < *count - 1; j++) arr[j] = arr[j + 1];
        (*count)--;
        cout << "Data berhasil dihapus!" << endl;
    } else cout << "ID tidak ditemukan!" << endl;
}

void menuUtamaCRUD(DataWisata *daftarWisata, int *jumlahData) {
    int pilihan;
    do {
        cout << "\n=== MENU ADMIN ===" << endl;
        cout << "1. Tambah Destinasi"          << endl;
        cout << "2. Lihat Destinasi (Sort/Search)"  << endl;
        cout << "3. Ubah Informasi"             << endl;
        cout << "4. Hapus Destinasi"            << endl;
        cout << "5. Keluar"                     << endl;
        cout << "Pilihan: "; cin >> pilihan;
        switch (pilihan) {
            case 1: tambahDataWisata(daftarWisata, jumlahData);  break;
            case 2: lihatDataWisata (daftarWisata, *jumlahData); break;
            case 3: ubahDataWisata  (daftarWisata, jumlahData);  break;
            case 4: hapusDataWisata (daftarWisata, jumlahData);  break;
            case 5: cout << "Keluar dari menu admin." << endl;   break;
            default: cout << "Pilihan tidak valid!" << endl;
        }
    } while (pilihan != 5);
}

int main() {
    AkunUser   databaseUser[MAX_USER];
    DataWisata daftarWisata[MAX_DATA];
    int jumlahUser = 0;
    int jumlahData = 0;
    int pilihanAwal;
    do {
        cout << "\n==========================================" << endl;
        cout << "   SISTEM PEMESANAN TIKET WISATA ALAM    " << endl;
        cout << "==========================================" << endl;
        cout << "1. Login"    << endl;
        cout << "2. Register" << endl;
        cout << "3. Keluar"   << endl;
        cout << "Pilihan: "; cin >> pilihanAwal;
        if (pilihanAwal == 1) {
            if (prosesLoginRekursif(databaseUser, &jumlahUser, BATAS_LOGIN)) menuUtamaCRUD(daftarWisata, &jumlahData);
            else { cout << "Gagal login 3 kali. Program berhenti." << endl; return 0; }
        } else if (pilihanAwal == 2) fiturRegister(databaseUser, &jumlahUser);
        else if (pilihanAwal == 3) { cout << "Program selesai." << endl; return 0; }
        else cout << "Pilihan tidak valid!" << endl;
    } while (true);
    return 0;
}