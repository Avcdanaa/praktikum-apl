#include <iostream>
#include <string>
using namespace std;

const int BATAS_LOGIN = 3;
const string USER_DEFAULT = "desti";
const string PASS_DEFAULT = "001";

bool prosesLogin() {
    string namaInput, passwordInput;
    int percobaan = 0;
    bool loginBerhasil = false;

    while (percobaan < BATAS_LOGIN) {
        cout << "\n--- LOGIN ---" << endl;
        cout << "Masukkan Username : ";
        cin >> namaInput;
        cout << "Masukkan Password : ";
        cin >> passwordInput;

        if (namaInput == USER_DEFAULT && passwordInput == PASS_DEFAULT) {
            loginBerhasil = true;
            break;
        } else {
            percobaan++;
            if (percobaan < BATAS_LOGIN) {
                cout << "Username atau Password salah!" << endl;
                cout << "Sisa percobaan: " << (BATAS_LOGIN - percobaan) << endl;
            }
        }
    }

    if (!loginBerhasil) {
        cout << "\n Akses Ditolak! Percobaan login habis." << endl;
    }

    return loginBerhasil;
}

void konversiJamKeMenitDetik() {
    int inputJam, outputMenit, outputDetik;

    cout << "\n--- Konversi: Jam -> Menit & Detik ---" << endl;
    cout << "Masukkan jumlah Jam : ";
    cin >> inputJam;

    outputMenit = inputJam * 60;
    outputDetik = inputJam * 3600;

    cout << "\n>>> HASIL KONVERSI <<<" << endl;
    cout << inputJam << " Jam = " << outputMenit << " Menit" << endl;
    cout << inputJam << " Jam = " << outputDetik << " Detik" << endl;
}

void konversiMenitKeJamDetik() {
    int inputMenit, outputJam, sisaMenit, outputDetik;

    cout << "\n--- Konversi: Menit -> Jam & Detik ---" << endl;
    cout << "Masukkan jumlah Menit : ";
    cin >> inputMenit;

    outputJam = inputMenit / 60;
    sisaMenit = inputMenit % 60;
    outputDetik = inputMenit * 60;

    cout << "\n>>> HASIL KONVERSI <<<" << endl;
    cout << inputMenit << " Menit = " << outputJam << " Jam " << sisaMenit << " Menit" << endl;
    cout << inputMenit << " Menit = " << outputDetik << " Detik" << endl;
}

void konversiDetikKeJamMenit() {
    int inputDetik, outputJam, outputMenit, sisaDetik;

    cout << "\n--- Konversi: Detik -> Jam & Menit ---" << endl;
    cout << "Masukkan jumlah Detik : ";
    cin >> inputDetik;

    outputJam = inputDetik / 3600;
    sisaDetik = inputDetik % 3600;
    outputMenit = sisaDetik / 60;
    sisaDetik = sisaDetik % 60;

    cout << "\n>>> HASIL KONVERSI <<<" << endl;
    cout << inputDetik << " Detik = " << outputJam << " Jam " << outputMenit << " Menit " << sisaDetik << " Detik" << endl;
}

void tampilkanMenu() {
    cout << "\n============================================" << endl;
    cout << "                MENU UTAMA                  " << endl;
    cout << "============================================" << endl;
    cout << "  1. Konversi Jam -> Menit dan Detik         " << endl;
    cout << "  2. Konversi Menit -> Jam dan Detik         " << endl;
    cout << "  3. Konversi Detik -> Jam dan Menit         " << endl;
    cout << "  4. Keluar                                 " << endl;
    cout << "============================================" << endl;
}

int main() {
    int pilihanMenu;
    bool programBerjalan = true;

    cout << "============================================" << endl;
    cout << "     PROGRAM KONVERSI WAKTU SEDERHANA       " << endl;
    cout << "============================================" << endl;

    if (prosesLogin() == false) {
        cout << "Program akan berhenti..." << endl;
        return 0;
    }

    cout << "\n Login Berhasil! Selamat datang, " << USER_DEFAULT << "!" << endl;

    while (programBerjalan == true) {
        tampilkanMenu();
        cout << "Masukkan pilihan menu (1-4): ";
        cin >> pilihanMenu;

        if (pilihanMenu == 1) {
            konversiJamKeMenitDetik();
        }
        else if (pilihanMenu == 2) {
            konversiMenitKeJamDetik();
        }
        else if (pilihanMenu == 3) {
            konversiDetikKeJamMenit();
        }
        else if (pilihanMenu == 4) {
            cout << "\n============================================" << endl;
            cout << "  Terima kasih telah menggunakan program!   " << endl;
            cout << "  Program akan keluar...                    " << endl;
            cout << "============================================" << endl;
            programBerjalan = false;
        }
        else {
            cout << "\n plihan tidak valid! Masukkan 1-4." << endl;
        }
    }

    return 0;
}