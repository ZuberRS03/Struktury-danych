#include <iostream>
#include <time.h>
#include <cstdlib>
#include <random>

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
int losujLiczbe(int min, int max){
    return rand() % (max - min + 1) + min;
}

int main() {

    wyborStruktury: // etykieta na wypadek złego wyboru opcji z menu
    int wybor = menu_Struktury_Danych(); // wybór struktury danych

    // określenie początkowej wielkości struktury danych
    int ileElementow = 0;
    cout << "Ile elementow chcesz wylosowac do struktury danych?" << endl;
    cin >> ileElementow;

    // określenie zakresu losowanych liczb
    int min, max;
    cout << "Podaj zakres liczb do losowania:" << endl;
    cout << "Min: ";
    cin >> min;
    cout << "Max: ";
    cin >> max;

    switch(wybor){
        case 1: {
            cout << "Wybrano tablice dynamiczna (ArrayList)" << endl;
            ArrayList<int> lista;
            for(int i = 0; i < ileElementow; i++){
                lista.dodajElement(losujLiczbe(min, max));
            }
            lista.wypisz();
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

