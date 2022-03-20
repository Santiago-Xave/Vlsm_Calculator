#include <iostream>
#include <string.h>
#include <stdlib.h>
#include <math.h>

using namespace std;
struct Ip {
    char dir[32];
    int mascara, BinMaks[32] = {0};
    int Subredes;
    int DirBin[32] = {0};
};
char Octeto[4][8];
Ip address;

void MakeBin(int DirBin[]) {
    int dir[4];
    for (int i = 0; i < 4; i++) {
        dir[i] = atoi(Octeto[i]);
    }
    int k = 0;
    for (int j = 1; j <= 4; j++) {
        k = (j * 8) - 1;
        for (int i = 0; i < 8; i++) {
            DirBin[k--] = dir[j - 1] % 2;
            dir[j - 1] /= 2;
        }
    }
}

void Order(int Hosts[], int CantH) {
    int aux;
    for (int i = 0; i < CantH; i++) {
        for (int j = i + 1; j < CantH; j++) {
            if (Hosts[i] < Hosts[j]) {
                aux = Hosts[i];
                Hosts[i] = Hosts[j];
                Hosts[j] = aux;
            }
        }
    }
}

int Convert(char *dir) {
    char *tok;
    int i = 0, conta = 0;
    tok = strtok(dir, ".");
    while (tok != NULL) {
        strcpy(Octeto[i++], tok);
        tok = strtok(NULL, ".");
        conta++;
    }
    return conta;
}

void BitsHost(int Hosts[], int Cant, float bits[]) {
    for (int i = 0; i < Cant; i++)
        bits[i] = ceil(log2(Hosts[i]));
}

bool SubnetB(float bits[], int Cant, int bitsRed[]) {
    int Bred = 32 - address.mascara;
    for (int i = 0; i < Cant; i++) {
        bitsRed[i] = Bred - bits[i];
        if (bitsRed[i] <= 0) {
            cout << "La subred " << i + 1
                 << " no es posible de crear, son demasiados hosts para la mascara establecida.";
            return false;
        }
    }
    return true;
}

void Bin_Dec(int Bin[], int Dec[]) {
    int j = 0;
    for (int i = 0, k = 31; i < 32; i++, k--) {
        if (i % 8 == 0 && i != 0)
            j++;
        if (Bin[i] == 1) {
            Dec[j] += pow(2, k % 8);
        }
    }
}

void CalculoSub(int Cant, int MaskSubnet[], int Hosts[]) {
    int Octetos[4] = {0};
    Bin_Dec(address.DirBin, Octetos);
    cout << "\t\tSubred.\t\tHost\t\t\tDireccion de red." << endl;
    for (int i = 0; i < Cant; i++) {
        for (int j = 0; j < Hosts[i]; j++) {
            if (Octetos[3] == 256) {
                Octetos[3] = 0;
                Octetos[2]++;
            }
            if (Octetos[2] == 256) {
                Octetos[2] = 0;
                Octetos[1]++;
            }
            if (Octetos[1] == 256) {
                Octetos[1] = 0;
                Octetos[0]++;
            }
            cout << "\t\t" << i + 1 << "\t\t" << j + 1 << "\t\t\t";
            for (int k = 0; k < 3; k++) {
                cout << Octetos[k] << ".";
            }
            cout <<Octetos[3]++<< "/" << MaskSubnet[i]<< endl;
        }

    }
}

void Intro() {
    cout << "\t\t\t CALCULADORA DE VLSM (SUBNETING)\n";
    cout << "\t\tIngresa la direcion de red que deseas usar:\n";
    cin.getline(address.dir, 32, '\n');
    int Ver = Convert(address.dir);
    if (Ver != 4) {
        cout << "Cantidad de datos invalida.\n";
        return;
    }
    MakeBin(address.DirBin);
    cout << "\t\tIngresa la mascara de la direccion ip que deseas usar(En decimal):\n";
    cin >> address.mascara;
    for (int i = 0; i < address.mascara; i++)
        address.BinMaks[i] = 1;
    for (int i = 0; i < 32; i++) {
        if (address.BinMaks[i] == 0) {
            address.DirBin[i] = 0;
        }
    }
    cout << "\t\tIngresa el Numero de redes:\n";
    cin >> address.Subredes;
    int *hosts = new int[address.Subredes];//numero de host por red
    float *Hbits = new float[address.Subredes];//Cuentos bits nececita cada red
    int *RedBits = new int[address.Subredes];//Bit que queda para cada red
    int *MaskSubnet = new int[address.Subredes];//Nueva mascara por red
    for (int i = 0; i < address.Subredes; i++) {
        cout << "Dijite cuantos hosts tendra la red " << i + 1 << endl;
        cin >> hosts[i];
        hosts[i] += 2;
    }
    Order(hosts, address.Subredes);
    BitsHost(hosts, address.Subredes, Hbits);
    for (int i = 0; i < address.Subredes; i++) {
        hosts[i]=pow(2,Hbits[i]);
    }
    if (!SubnetB(Hbits, address.Subredes, RedBits)) {
        return;
    }
    for (int i = 0; i < address.Subredes; i++) {
        MaskSubnet[i] = address.mascara + RedBits[i];
    }

    CalculoSub(address.Subredes, MaskSubnet, hosts);


    delete[] RedBits;
    delete[] MaskSubnet;
    delete[] Hbits;
    delete[] hosts;
}

int main() {
    Intro();
    return 0;
}
