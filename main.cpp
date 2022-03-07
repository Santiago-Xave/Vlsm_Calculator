#include <iostream>
#include <string.h>
#include <string>

using namespace std;
char Octeto[10][10];
void Convert(char* dir){
    char *tok;
    int i=0;
    tok = strtok(dir, ".");
    while (tok != NULL) {
        strcpy(Octeto[i++],tok);
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
