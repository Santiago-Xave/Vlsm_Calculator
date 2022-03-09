#include <iostream>
#include <string.h>
#include <string>

using namespace std;
char Octeto[4][8];

void MakeBin() {
    int dir[4],DirBin[4][8];
    for (int i = 0; i < 4; i++) {
    dir[i]= stoi(Octeto[i]);
    }
    for(int i=0;i<8;i++){
        DirBin[i][];
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

bool Verify(char *dir) {

    return true;
}

void Intro() {
    char Dir[32];
    int Host, Redes;
    cout << "\t\t\t CALCULADORA DE VLSM (SUBNETING)\n";
    cout << "\t\tIngresa la direcion de red que deseas usar:\n";
    cin.getline(Dir, '\n');
    Convert(Dir);
    cout << "\t\tIngresa el Numero de redes:\n";
    cin >> Redes;
    cout << "\t\tIngresa el numero de host:\n";
    cin >> Host;


}

int main() {
    Intro();
    return 0;

}
