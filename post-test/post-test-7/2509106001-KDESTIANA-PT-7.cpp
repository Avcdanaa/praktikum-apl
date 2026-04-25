#include <iostream>
#include <string>
#include <iomanip>
#include <cctype>
#include <stdexcept>  
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

int inputInteger(const string& prompt) {
    int nilai;
    cout << prompt;
    cin >> nilai;
    if (cin.fail()) {
        cin.clear();
        cin.ignore(1000, '\n');
        throw invalid_argument("Input tidak valid! Harus berupa angka bulat.");
    }
    return nilai;
}

float inputFloat(const string& prompt) {
    float nilai;
    cout << prompt;
    cin >> nilai;
    if (cin.fail()) {
        cin.clear();
        cin.ignore(1000, '\n');
        throw invalid_argument("Input tidak valid! Harus berupa angka.");
    }
    return nilai;
}

int binarySearchID(DataWisata *arr, int n, int target) {
    if (n == 0) throw runtime_error("Tidak ada data untuk dicari.");

    int low = 0, high = n - 1;
    while (low <= high) {
        int mid = low + (high - low) / 2;
        if (arr[mid].idWisata == target) return mid;
        else if (arr[mid].idWisata < target) low = mid + 1;
        else high = mid - 1;
    }
    return -1;
}

int linearSearchNama(DataWisata *arr, int n, string target) {
    if (n == 0) throw runtime_error("Tidak ada data untuk dicari.");
    if (target.empty()) throw invalid_argument("Nama yang dicari tidak boleh kosong.");

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
            string a = arr[j].namaTempat, b = arr[j+1].namaTempat;
            for (char &c : a) c = tolower(c);
            for (char &c : b) c = tolower(c);
            if (a > b) { DataWisata tmp = arr[j]; arr[j] = arr[j+1]; arr[j+1] = tmp; swapped = true; }
        }
        if (!swapped) break;
    }
}

void selectionSortHargaDescending(DataWisata *arr, int n) {
    for (int i = 0; i < n - 1; i++) {
        int idxMax = i;
        for (int j = i+1; j < n; j++)
            if (arr[j].hargaTiket > arr[idxMax].hargaTiket) idxMax = j;
        if (idxMax != i) { DataWisata tmp = arr[i]; arr[i] = arr[idxMax]; arr[idxMax] = tmp; }
    }
}

void insertionSortKuotaAscending(DataWisata *arr, int n) {
    for (int i = 1; i < n; i++) {
        DataWisata key = arr[i]; int j = i - 1;
        while (j >= 0 && arr[j].kuotaTersedia > key.kuotaTersedia) { arr[j+1] = arr[j]; j--; }
        arr[j+1] = key;
    }
}

void menuSorting(DataWisata *arr, int count) {
    if (count == 0) throw runtime_error("Tidak ada data untuk diurutkan.");

    DataWisata *salinan = new DataWisata[count];
    for (int i = 0; i < count; i++) salinan[i] = arr[i];

    try {
        int pil = inputInteger("\n--- Pilih Urutan Tampil ---\n1. Nama A-Z (Bubble Sort)\n2. Harga Tertinggi (Selection Sort)\n3. Kuota Terendah (Insertion Sort)\n0. Tanpa pengurutan\nPilihan: ");

        switch (pil) {
            case 1: bubbleSortNamaAscending(salinan, count);    cout << "\n=== Nama A-Z (Bubble Sort) ===" << endl;         break;
            case 2: selectionSortHargaDescending(salinan, count); cout << "\n=== Harga Tertinggi (Selection Sort) ===" << endl; break;
            case 3: insertionSortKuotaAscending(salinan, count);  cout << "\n=== Kuota Terendah (Insertion Sort) ===" << endl;  break;
            default: cout << "\n=== KATALOG WISATA ===" << endl; break;
        }
        cetakTabel(salinan, count);
    } catch (...) {
        delete[] salinan;
        throw;
    }
    delete[] salinan;
}

void fiturPencarian(DataWisata *arr, int count) {
    cout << "\n=== FITUR PENCARIAN ===" << endl;

    int pil = inputInteger("1. Cari berdasarkan ID (Binary Search)\n2. Cari berdasarkan Nama (Linear Search)\nPilihan: ");

    if (pil == 1) {
        int targetID = inputInteger("Masukkan ID Wisata: ");
        if (targetID <= 0) throw out_of_range("ID Wisata harus bernilai positif!");

        int idx = binarySearchID(arr, count, targetID);
        if (idx != -1) { cout << "\nData ditemukan!" << endl; cetakTabel(&arr[idx], 1); }
        else cout << "ID tidak ditemukan." << endl;

    } else if (pil == 2) {
        string targetNama;
        cin.ignore();
        cout << "Masukkan Nama Wisata: "; getline(cin, targetNama);
        if (targetNama.empty()) throw invalid_argument("Nama yang dicari tidak boleh kosong!");

        int idx = linearSearchNama(arr, count, targetNama);
        if (idx != -1) { cout << "\nData ditemukan!" << endl; cetakTabel(&arr[idx], 1); }
        else cout << "Nama tidak ditemukan." << endl;

    } else {
        throw invalid_argument("Pilihan pencarian tidak valid! Pilih 1 atau 2.");
    }
}

void lihatDataWisata(DataWisata *arr, int count) {
    cout << "\n=== LIHAT & KELOLA DATA ===" << endl;
    if (count == 0) throw runtime_error("Belum ada data wisata yang tersedia.");

    int pilMenu = inputInteger("1. Urutkan & Tampilkan (Sorting)\n2. Cari Data (Searching)\nPilihan: ");

    if      (pilMenu == 1) menuSorting(arr, count);
    else if (pilMenu == 2) fiturPencarian(arr, count);
    else throw invalid_argument("Pilihan tidak valid! Pilih 1 atau 2.");
}

bool prosesLoginRekursif(AkunUser *dbUser, int *jumlahUser, int sisaPercobaan) {
    if (sisaPercobaan == 0) return false;
    string inputNama, inputNim;
    cout << "\n=== LOGIN (Percobaan " << (BATAS_LOGIN - sisaPercobaan + 1) << "/" << BATAS_LOGIN << ") ===" << endl;
    cout << "Username: "; cin >> inputNama;
    cout << "Password: "; cin >> inputNim;

    if (inputNama.empty() || inputNim.empty())
        throw invalid_argument("Username dan password tidak boleh kosong!");

    for (int i = 0; i < *jumlahUser; i++) {
        if (dbUser[i].namaPengguna == inputNama && dbUser[i].nimPassword == inputNim) {
            cout << "Login Berhasil! Selamat datang, " << inputNama << "!" << endl;
            return true;
        }
    }
    cout << "Login Gagal! Sisa kesempatan: " << (sisaPercobaan - 1) << endl;
    return prosesLoginRekursif(dbUser, jumlahUser, sisaPercobaan - 1);
}

void fiturRegister(AkunUser *dbUser, int *jumlahUser) {
    cout << "\n=== REGISTRASI USER BARU ===" << endl;

    // Validasi kapasitas penuh
    if (*jumlahUser >= MAX_USER)
        throw length_error("Kapasitas user penuh! Tidak dapat menambah user baru.");

    string inputNama, inputNIM;
    cout << "Masukkan Nama (Username): "; cin >> inputNama;

    if (inputNama.empty())
        throw invalid_argument("Username tidak boleh kosong!");

    for (int i = 0; i < *jumlahUser; i++)
        if (dbUser[i].namaPengguna == inputNama)
            throw runtime_error("Username '" + inputNama + "' sudah terdaftar!");

    cout << "Masukkan NIM (Password): "; cin >> inputNIM;
    if (inputNIM.empty())
        throw invalid_argument("Password tidak boleh kosong!");

    dbUser[*jumlahUser].namaPengguna = inputNama;
    dbUser[*jumlahUser].nimPassword  = inputNIM;
    (*jumlahUser)++;
    cout << "Registrasi berhasil!" << endl;
}


void tambahDataWisata(DataWisata *arr, int *count) {
    cout << "\n=== TAMBAH DESTINASI WISATA ===" << endl;

    if (*count >= MAX_DATA)
        throw length_error("Kapasitas data penuh! Tidak dapat menambah destinasi baru.");

    DataWisata *dataBaru = &arr[*count];
    dataBaru->idWisata = *count + 1;
    cin.ignore();

    cout << "Nama Tempat Wisata   : "; getline(cin, dataBaru->namaTempat);
    if (dataBaru->namaTempat.empty())
        throw invalid_argument("Nama tempat wisata tidak boleh kosong!");

    cout << "Deskripsi            : "; getline(cin, dataBaru->deskripsi);
    cout << "Jam Buka             : "; getline(cin, dataBaru->jadwal.jamBuka);
    cout << "Jam Tutup            : "; getline(cin, dataBaru->jadwal.jamTutup);
    cout << "Hari Operasional     : "; getline(cin, dataBaru->jadwal.hariOperasional);

    dataBaru->hargaTiket = inputFloat("Harga Tiket (Rp)     : ");
    if (dataBaru->hargaTiket < 0)
        throw invalid_argument("Harga tiket tidak boleh negatif!");

    dataBaru->jumlahPengunjung = inputInteger("Kuota Pengunjung     : ");
    if (dataBaru->jumlahPengunjung <= 0)
        throw invalid_argument("Kuota pengunjung harus lebih dari 0!");

    dataBaru->kuotaTersedia  = dataBaru->jumlahPengunjung;
    dataBaru->statusTersedia = true;
    (*count)++;
    cout << "Data berhasil ditambahkan!" << endl;
}

void ubahDataWisata(DataWisata *arr, int *count) {
    cout << "\n=== UBAH INFORMASI DESTINASI ===" << endl;
    if (*count == 0) throw runtime_error("Belum ada data wisata untuk diubah.");

    int idUbah = inputInteger("Masukkan ID Wisata: ");
    if (idUbah <= 0) throw out_of_range("ID Wisata harus bernilai positif!");

    int index = -1;
    for (int i = 0; i < *count; i++) if (arr[i].idWisata == idUbah) { index = i; break; }
    if (index == -1) throw runtime_error("ID Wisata " + to_string(idUbah) + " tidak ditemukan!");

    DataWisata *dataUbah = &arr[index];
    int pil = inputInteger("1. Update Kuota\n2. Update Harga\n3. Update Status\nPilihan: ");

    if (pil == 1) {
        int kuotaBaru = inputInteger("Kuota Baru: ");
        if (kuotaBaru <= 0) throw invalid_argument("Kuota baru harus lebih dari 0!");
        dataUbah->jumlahPengunjung = kuotaBaru;
        dataUbah->kuotaTersedia    = kuotaBaru;
    } else if (pil == 2) {
        float hargaBaru = inputFloat("Harga Baru: ");
        if (hargaBaru < 0) throw invalid_argument("Harga tidak boleh negatif!");
        dataUbah->hargaTiket = hargaBaru;
    } else if (pil == 3) {
        int s = inputInteger("Status (1=Aktif / 0=Nonaktif): ");
        if (s != 0 && s != 1) throw invalid_argument("Status hanya boleh 0 atau 1!");
        dataUbah->statusTersedia = (s == 1);
    } else {
        throw invalid_argument("Pilihan update tidak valid!");
    }
    cout << "Data berhasil diperbarui!" << endl;
}

void hapusDataWisata(DataWisata *arr, int *count) {
    cout << "\n=== HAPUS DESTINASI WISATA ===" << endl;
    if (*count == 0) throw runtime_error("Belum ada data wisata untuk dihapus.");

    int idHapus = inputInteger("Masukkan ID Wisata: ");
    if (idHapus <= 0) throw out_of_range("ID Wisata harus bernilai positif!");

    int index = -1;
    for (int i = 0; i < *count; i++) if (arr[i].idWisata == idHapus) { index = i; break; }
    if (index == -1) throw runtime_error("ID Wisata " + to_string(idHapus) + " tidak ditemukan!");

    for (int j = index; j < *count - 1; j++) arr[j] = arr[j+1];
    (*count)--;
    cout << "Data berhasil dihapus!" << endl;
}

void menuUtamaCRUD(DataWisata *daftarWisata, int *jumlahData) {
    int pilihan;
    do {
        cout << "\n=== MENU ADMIN ===" << endl;
        cout << "1. Tambah Destinasi" << endl;
        cout << "2. Lihat Destinasi (Sort/Search)" << endl;
        cout << "3. Ubah Informasi" << endl;
        cout << "4. Hapus Destinasi" << endl;
        cout << "5. Keluar" << endl;

        try {
            pilihan = inputInteger("Pilihan: ");
            switch (pilihan) {
                case 1: tambahDataWisata(daftarWisata, jumlahData); break;
                case 2: lihatDataWisata (daftarWisata, *jumlahData); break;
                case 3: ubahDataWisata  (daftarWisata, jumlahData);  break;
                case 4: hapusDataWisata (daftarWisata, jumlahData);  break;
                case 5: cout << "Keluar dari menu admin." << endl;   break;
                default: cout << "[!] Pilihan tidak valid!" << endl;
            }
        }
        catch (const invalid_argument& e) {
            cout << "[ERROR - invalid_argument] " << e.what() << endl;
        }
        catch (const out_of_range& e) {
            cout << "[ERROR - out_of_range] " << e.what() << endl;
        }
        catch (const length_error& e) {
            cout << "[ERROR - length_error] " << e.what() << endl;
        }
        catch (const runtime_error& e) {
            cout << "[ERROR - runtime_error] " << e.what() << endl;
        }
        catch (const exception& e) {
            cout << "[ERROR] " << e.what() << endl;
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
        cout << "1. Login" << endl;
        cout << "2. Register" << endl;
        cout << "3. Keluar" << endl;

        try {
            pilihanAwal = inputInteger("Pilihan: ");

            if (pilihanAwal == 1) {
                if (jumlahUser == 0)
                    throw runtime_error("Belum ada akun terdaftar. Silakan Register terlebih dahulu.");

                if (prosesLoginRekursif(databaseUser, &jumlahUser, BATAS_LOGIN))
                    menuUtamaCRUD(daftarWisata, &jumlahData);
                else {
                    cout << "Gagal login 3 kali. Program berhenti." << endl;
                    return 0;
                }

            } else if (pilihanAwal == 2) {
                fiturRegister(databaseUser, &jumlahUser);

            } else if (pilihanAwal == 3) {
                cout << "Program selesai. Terima kasih!" << endl;
                return 0;

            } else {
                cout << "[!] Pilihan tidak valid! Masukkan 1, 2, atau 3." << endl;
            }
        }
        catch (const invalid_argument& e) {
            cout << "[ERROR - invalid_argument] " << e.what() << endl;
        }
        catch (const length_error& e) {
            cout << "[ERROR - length_error] " << e.what() << endl;
        }
        catch (const runtime_error& e) {
            cout << "[ERROR - runtime_error] " << e.what() << endl;
        }
        catch (const exception& e) {
            cout << "[ERROR] " << e.what() << endl;
        }

    } while (true);

    return 0;
}