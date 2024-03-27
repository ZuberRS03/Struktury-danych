#ifndef MINIPROJEKT_1_ARRAYLIST_H
#define MINIPROJEKT_1_ARRAYLIST_H

#include <iostream>

template <typename T>
class ArrayList {
private:
    int ileElementow; //licznik elementów w tablicy
    T *przedmioty; //tablica przechowująca elementy
public:
    ArrayList() : ileElementow{ 0 }, przedmioty{ nullptr } {} //konstruktor
    ~ArrayList(); //destruktor
    void dodajElement(T element); //metoda dodająca element do tablicy na końcu
    void dodajElement(T element, int index); //metoda dodająca element na podanym indeksie
    void usunElement(int index); //metoda usuwająca element z tablicy
    int rozmiar(); //metoda zwracająca ilość elementów w tablicy
    void wypisz(); //metoda wypisująca elementy tablicy
    void wyczysc(); //metoda czyszcząca tablicę
    void zmienRozmiar(int nowyRozmiar); //metoda zmieniająca rozmiar tablicy
    void wyszukajElement(T element); //metoda wyszukująca element w tablicy
    T pobierzElement(int index); //metoda zwracająca element z tablicy
};

#endif //MINIPROJEKT_1_ARRAYLIST_H
