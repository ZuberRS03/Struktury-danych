#include <iostream>
#include <time.h>
#include <cstdlib>

#include "ArrayList.h"

using namespace std;
clock_t start, stop;

int menu_Struktury_Danych(){
    int wybor;
    cout << "-----------------Menu-----------------" << endl;
    cout << "Wybierz strukture danych:" << endl;
    cout << "1. Tablicza dynamiczna (ArrayList):" << endl;
    cout << "2. Lista jednokierunkowa (head):" << endl;
    cout << "3. Lista jednokierunkowa (head, tail):" << endl;
    cout << "4. Lista dwukierunkowa:" << endl;
    cout << "--------------------------------------" << endl;
    cout << endl;

    cout << "Wybor: ";
    cin >> wybor;
    return wybor;
}
int main() {

    wyborStruktury:
    int wybor = menu_Struktury_Danych();
    switch(wybor){
        case 1: {
            cout << "Wybrano tablice dynamiczna (ArrayList)" << endl;
            ArrayList<int> lista;
            lista.dodajElement(5);
            lista.dodajElement(10);
            lista.dodajElement(15);
            lista.dodajElement(20);
            lista.wypisz();
            lista.dodajElement(25, 2);
            lista.wypisz();
            lista.usunElement(1);
            lista.wypisz();
            cout << "Rozmiar tablicy: " << lista.rozmiar() << endl;
            cout << "Element na indeksie 1: " << lista.pobierzElement(1) << endl;
            lista.wyszukajElement(15);
            lista.wyszukajElement(100);
            lista.wyczysc();
            cout << "Rozmiar tablicy: " << lista.rozmiar() << endl;
            break;
        }
        case 2: {
            cout << "Wybrano liste jednokierunkowa (head)" << endl;
            break;
        }
        case 3: {
            cout << "Wybrano liste jednokierunkowa (head, tail)" << endl;
            break;
        }
        case 4: {
            cout << "Wybrano liste dwukierunkowa" << endl;
            break;
        }
        default: {
            cout << "Niepoprawny wybor, wybierz ocpcje od 1 do 4:" << endl;
            goto wyborStruktury;
            break;
        }
    }
    return 0;
}

