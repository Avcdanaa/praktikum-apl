#include <iostream>
using namespace std;

void updateSaldo(int *saldo) {
    cout << "Alamat memori saldo di dalam fungsi: " << saldo << endl;

    *saldo += 50000;
    *saldo -= 2000;
}

int main() {
    int saldo = 100000; 

    cout << "Saldo awal: Rp" << saldo << endl;
    cout << "Alamat memori saldo di main: " << &saldo << endl;

    updateSaldo(&saldo);

    cout << "Saldo setelah update: Rp" << saldo << endl;

    return 0;
}