#include <iostream> //podstawowa biblioteka wejścia/wyjścia
#include <fstream> //do wczytywania i zapisywania plików
#include <chrono> //do pomiaru czasu
#include <cstdlib> //do losowania liczb
#include <iomanip> //do std::fixed i std::setprecision

#include "OpenAddressingHashTable.h"
#include "ChainedHashTable.h"
#include "CuckooHashTable.h"

using namespace std;
using namespace std::chrono;

ifstream fin;
ofstream fout;

// Funkcja losująca liczbę z przedziału <min, max>
int losujLiczbe(int min, int max) {
    return rand() % (max - min + 1) + min;
}

// Funkcja wyboru struktury danych
int menu_wyboru() {
    cout << "Wybierz strukture danych:" << endl;
    cout << "1. Tablica mieszajaca z adresowaniem otwartym" << endl;
    cout << "2. Tablica mieszajaca z adresowaniem zamknietym" << endl;
    cout << "3. Tablica mieszajaca z haszowaniem kukułczym" << endl;
    cout << "4. Wyjscie" << endl;

    int wybor = 0;
    cout << "Twoj wybor: ";
    cin >> wybor;

    return wybor;
}

void zapelnijDanymiCuckooHash(CuckooHashTable* hashTables[], int dane[][2], int liczbaTablic, int iloscDanych){

    for (int i = 0; i < liczbaTablic; ++i) {
        hashTables[i]->clear();
        for (int j = 0; j < iloscDanych; ++j) {
            hashTables[i]->insert(dane[j][0], dane[j][1]);
        }
    }
}
void pomiar_OpenAddressingHashTable(int dane[10000][2], int iloscDanych, int skokIlosciDanych, int liczbaPomiarow, int cyfrPoPrzecinku){

}

void pomiar_ChainedHashTable(int dane[10000][2], int iloscDanych, int skokIlosciDanych, int liczbaPomiarow, int cyfrPoPrzecinku){

}

void pomiar_CockoHashTable(int dane[10000][2], int iloscDanych, int skokIlosciDanych, int liczbaPomiarow, int cyfrPoPrzecinku) {
    fout.open("CockoHash_Wyniki.txt");

    fout << "Ilosc elementow; czas insert(); czas remove()" << endl;

    // Tworzenie 30 tablic mieszających z haszowaniem kukułczym
    CuckooHashTable* hashTables[liczbaPomiarow];

    // Inicjalizacja każdej tablicy
    for(int i = 0; i < liczbaPomiarow; ++i) {
        hashTables[i] = new CuckooHashTable(10);
    }

    for(int startElementow = 1; startElementow <= iloscDanych; startElementow += skokIlosciDanych) {
        cout << "-------------------------------------------------- " << endl;
        cout << "Ilosc elementow: " << startElementow << endl;

        int randomKey = losujLiczbe(0, iloscDanych + 1);
        int randomValue = losujLiczbe(0, 10000);

        //Tu powinno być doprowadzenie tablicy do stany początkowego
        zapelnijDanymiCuckooHash(hashTables, dane, liczbaPomiarow, startElementow);

        cout << endl;
        cout << "dodawanie elementow do tablicy: " << endl;

        // Pomiar czasu insert()
        double czasInsert = 0.0;
        for(int j = 0; j < liczbaPomiarow; ++j) {

            cout << endl;
            cout << "pomiar: " << j << endl;

            hashTables[j]->print();

            auto start = high_resolution_clock::now(); //początek pomiaru czasu
            hashTables[j]->insert(randomKey, randomValue);
            auto stop = high_resolution_clock::now(); //koniec pomiaru czasu
            czasInsert += duration<double, milli>(stop - start).count(); //dodanie czasu do sumy

            cout << "po dodaniu "<< endl;

            hashTables[j]->print();
        }
        czasInsert /= liczbaPomiarow; //średni czas Insert

        cout << endl;
        cout << "usuwanie elementow do tablicy: " << endl;

        // Pomiar czasu remove()
        double czasRemove = 0.0;
        for(int j = 0; j < liczbaPomiarow; ++j) {

            cout << "pomiar: " << j << endl;

            auto start = high_resolution_clock::now(); //początek pomiaru czasu
            hashTables[j]->remove(randomKey);
            auto stop = high_resolution_clock::now(); //koniec pomiaru czasu
            czasRemove += duration<double, milli>(stop - start).count(); //dodanie czasu do sumy

            cout << "po odjeciu "<< endl;

            hashTables[j]->print();
        }
        czasRemove /= liczbaPomiarow; //średni czas Remove

        fout << startElementow << "; " << fixed << setprecision(cyfrPoPrzecinku) << czasInsert <<
        "; " << fixed << setprecision(cyfrPoPrzecinku) << czasRemove << endl;
    }
    // Sprzątanie pamięci
    for (int i = 0; i < liczbaPomiarow; ++i) {
        delete hashTables[i];
    }

    fout.close();
}

int main() {

    const int iloscDanych = 15; // ilość danych do przetworzenia 10000
    const int skokIlosciDanych = 5; // Skok ilości danych 500
    const int liczbaPomiarow = 2; // ilość pomiarów 30
    const int cyfrPoPrzecinku = 6; // ilość cyfr po przecinku 6

    int dane[iloscDanych][2]; // tablica przechowująca dane
    for(int i = 0; i < iloscDanych; i++) {
        dane[i][0] = i; // klucz
        dane[i][1] = losujLiczbe(0, 10000); // wartość
    }

    int wybor = menu_wyboru(); // wybór struktury danych

    switch (wybor) {
        case 1: {
            pomiar_OpenAddressingHashTable(dane, iloscDanych, skokIlosciDanych, liczbaPomiarow, cyfrPoPrzecinku);
            break;
        }

        case 2: {
            pomiar_ChainedHashTable(dane, iloscDanych, skokIlosciDanych, liczbaPomiarow, cyfrPoPrzecinku);
            break;
        }

        case 3: {
            pomiar_CockoHashTable(dane, iloscDanych, skokIlosciDanych, liczbaPomiarow, cyfrPoPrzecinku);
            break;
        }

        case 4: {
            cout << "Koniec programu!" << endl;
            return 0;
        }

        default: {
            cout << "Niepoprawny wybor!" << endl;
            break;
        }

    }
    return 0;
}
