#ifndef MINIPROJEKT_1_ARRAYLIST_H
#define MINIPROJEKT_1_ARRAYLIST_H

#include <iostream>

template <typename T>
class ArrayList {
private:
    int ileElementow; //licznik elementów w tablicy
    int pojemnosc; //pojemność tablicy
    T *przedmioty; //tablica przechowująca elementy
public:
    ArrayList() : ileElementow{ 0 }, pojemnosc{ 0 }, przedmioty{ nullptr } {} //konstruktor
    ~ArrayList(); //destruktor

    void dodajElementNaKoniec(T element); //metoda dodająca element do tablicy na końcu
    void dodajElement(T element, int index); //metoda dodająca element na podanym indeksie
    void dodajElementNaPoczatek(T element); //metoda dodająca element na początku tablicy
    void usunElement(int index); //metoda usuwająca element z tablicy
    int rozmiar(); //metoda zwracająca ilość elementów w tablicy
    void wypisz(); //metoda wypisująca elementy tablicy
    void wyczysc(); //metoda czyszcząca tablicę
    void zmienRozmiar(int nowyRozmiar); //metoda zmieniająca rozmiar tablicy
    void wyszukajElement(T element); //metoda wyszukująca element w tablicy
    T pobierzElement(int index); //metoda zwracająca element z tablicy
    int getIleElementow(); //metoda zwracająca ilość elementów w tablicy
    int getPojemnosc(); //metoda zwracająca pojemność tablicy
};

template<typename T>
ArrayList<T>::~ArrayList() {
    delete[] przedmioty;
}

template<typename T>
void ArrayList<T>::dodajElementNaKoniec(T element) {
    if (ileElementow == pojemnosc) { //jeżeli liczba elementów jest równa pojemności tablicy
        if(pojemnosc == 0)
            pojemnosc = 1; //jeżeli pojemność tablicy jest równa 0 to ustawiamy ją na 1 (pierwszy element w tablicy)
        pojemnosc *= 2; //podwajamy pojemność tablicy
        T *nowaTablica = new T[pojemnosc]; //tworzymy nową tablicę o 1 większą
        for (int i = 0; i < ileElementow; i++) {  //przepisujemy elementy z tablicy przedmioty do nowej tablicy
            nowaTablica[i] = przedmioty[i];
        }
        nowaTablica[ileElementow] = element; //dodajemy nowy element na końcu tablicy
        delete[] przedmioty; //zwalniamy pamięć zajmowaną przez starą tablicę
        przedmioty = nowaTablica; //przypisujemy nową tablicę do wskaźnika przedmioty
    } else {
        przedmioty[ileElementow] = element; //dodajemy nowy element na końcu tablicy
    }
    ileElementow++; //zwiększamy licznik elementów
}

template<typename T>
void ArrayList<T>::dodajElement(T element, int index) {
    //zapezpieczenie przed wyjściem poza zakres tablicy
    if (index < 0 || index > ileElementow) {
        throw std::out_of_range("Niepoprawny indeks");
    }
    if (ileElementow == pojemnosc) {
        if(pojemnosc == 0)
            pojemnosc = 1;
        pojemnosc *= 2;
        T *nowaTablica = new T[pojemnosc];
        for (int i = 0; i < index; i++) {
            nowaTablica[i] = przedmioty[i];
        }
        nowaTablica[index] = element;
        for (int i = index; i < ileElementow; i++) {
            nowaTablica[i + 1] = przedmioty[i];
        }
        delete[] przedmioty;
        przedmioty = nowaTablica;
    } else {
        for (int i = ileElementow; i > index; i--) {
            przedmioty[i] = przedmioty[i - 1];
        }
        przedmioty[index] = element;
    }
    ileElementow++;
}

template<typename T>
void ArrayList<T>::dodajElementNaPoczatek(T element) {
    if (ileElementow == pojemnosc) {
        if(pojemnosc == 0)
            pojemnosc = 1;
        pojemnosc *= 2;
        T *nowaTablica = new T[pojemnosc];
        nowaTablica[0] = element;
        for (int i = 0; i < ileElementow; i++) {
            nowaTablica[i + 1] = przedmioty[i];
        }
        delete[] przedmioty;
        przedmioty = nowaTablica;
    } else {
        for (int i = ileElementow; i > 0; i--) {
            przedmioty[i] = przedmioty[i - 1];
        }
        przedmioty[0] = element;
    }
    ileElementow++;
}

template<typename T>
void ArrayList<T>::usunElement(int index) {
    //zapezpieczenie przed wyjściem poza zakres tablicy
    if (index < 0 || index >= ileElementow) {
        throw std::out_of_range("Niepoprawny indeks");
    }
    T *nowaTablica = new T[ileElementow - 1];
    for (int i = 0; i < index; i++) {
        nowaTablica[i] = przedmioty[i];
    }
    for (int i = index + 1; i < ileElementow; i++) {
        nowaTablica[i - 1] = przedmioty[i];
    }
    delete[] przedmioty;
    przedmioty = nowaTablica;
    ileElementow--;
}

template<typename T>
int ArrayList<T>::rozmiar() {
    return ileElementow;
}

template<typename T>
void ArrayList<T>::wypisz() {
    for (int i = 0; i < ileElementow; i++) {
        std::cout << przedmioty[i] << " ";
    }
    std::cout << std::endl;
}

template<typename T>
void ArrayList<T>::wyczysc() {
    delete[] przedmioty;
    przedmioty = nullptr;
    ileElementow = 0;
}

template<typename T>
void ArrayList<T>::zmienRozmiar(int nowyRozmiar) {
    T *nowaTablica = new T[nowyRozmiar];
    for (int i = 0; i < ileElementow; i++) {
        nowaTablica[i] = przedmioty[i];
    }
    delete[] przedmioty;
    przedmioty = nowaTablica;
}

template<typename T>
void ArrayList<T>::wyszukajElement(T element) {
    for (int i = 0; i < ileElementow; i++) {
        if (przedmioty[i] == element) {
            std::cout << "Element: " << element << " znajduje sie na pozycji " << i << std::endl;
            return;
        }
    }
    std::cout << "Element: " << element << " nie znajduje sie w tablicy" << std::endl;
}

template<typename T>
T ArrayList<T>::pobierzElement(int index) {
    //zapezpieczenie przed wyjściem poza zakres tablicy
    if (index < 0 || index >= ileElementow) {
        throw std::out_of_range("Niepoprawny indeks");
    }
    return przedmioty[index];
}

template<typename T>
int ArrayList<T>::getIleElementow() {
    return ileElementow;
}

template<typename T>
int ArrayList<T>::getPojemnosc() {
    return pojemnosc;
}
#endif //MINIPROJEKT_1_ARRAYLIST_H
