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

void Convert(char *dir) {
    char *tok;
    int i = 0;
    tok = strtok(dir, ".");
    while (tok != NULL) {
        strcpy(Octeto[i++], tok);
        tok = strtok(NULL, ".");
    }
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

int OctetoF(int mascara[]) {
    int OctetoNull;
    int S = 0;
    for (int i = 0; i < 32; i++) {
        if (mascara[i] != 1) {
            OctetoNull = (i / 8);
            break;
        }
    }
    int j = ((OctetoNull + 1) * 8) - 1;
    for (int i = 0; i < 8; i++) {
        if (mascara[j--] == 1) {
            S += pow(2, i);
        }
    }
    return 256 - S;
}

void Bin_Dec(int Bin[]) {
    int octeto[4] = {0};
    int j = 0;
    for (int i = 0, k = 31; i < 32; i++, k--) {
        if (i % 8 == 0 && i != 0)
            j++;
        if (Bin[i] == 1) {
            octeto[j] += pow(2, k % 8);
        }
    }
    for (int i = 0; i < 4; i++) {
        Bin[i] = octeto[i];
    }
}

void CalculoSub(int Cant, int MaskSubnet[], int Hosts[]) {
    int copiaMascara[32];
    for (int i = 0; i < 32; i++)
        copiaMascara[i] = address.DirBin[i];

    Bin_Dec(copiaMascara);
    cout << "\t\tSubred.\t\tHost\t\t\tDireccion de red." << endl;
    for (int i = 0; i < Cant; i++) {
        if (i == 0) {
            for (int j = 0; j < Hosts[i]; j++) {
                cout << "\t\t" << i + 1 << "\t\t" << j + 1 << "\t\t\t";
                for (int k = 0; k < 3; k++) {
                    cout << copiaMascara[k] << ".";
                }
                cout << ++copiaMascara[3] << endl;
            }
        } else {
            cout << "\t\t" << i + 1;
            for (int j = 0; j < Hosts[i]; j++) {
                cout << "\t\t" << j + 1;
                for (int k = 0; k < 32; k++) {

                }
            }
        }
    }
}

void Intro() {
    cout << "\t\t\t CALCULADORA DE VLSM (SUBNETING)\n";
    cout << "\t\tIngresa la direcion de red que deseas usar:\n";
    cin.getline(address.dir, 32, '\n');
    Convert(address.dir);
    MakeBin(address.DirBin);
    cout << "\t\tIngresa la mascara de la direccion ip que deseas usar(En decimal):\n";
    cin >> address.mascara;
    for (int i = 0; i < address.mascara; i++)
        address.BinMaks[i] = 1;
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
    if (!SubnetB(Hbits, address.Subredes, RedBits)) {
        return;
    }
    for (int i = 0; i < address.Subredes; i++)
        MaskSubnet[i] = address.mascara + RedBits[i];
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
