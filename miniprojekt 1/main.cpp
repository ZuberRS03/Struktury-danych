#include <iostream>
#include <cstdlib>
#include <random>
#include <fstream>
#include <vector>
#include <chrono>
#include <iomanip> // Dla std::fixed i std::setprecision

#include "ArrayList.h"
#include "LinkedLists.h"
#include "LinkedListWithTail.h"
#include "DoubleLinkedList.h"

using namespace std;
using namespace std::chrono;

ifstream fin;
ofstream fout;

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

template<typename ListType, typename DataType>
void wypelnijListe(ListType& lista, const DataType dane[], int liczbaElementow) {
    lista.clear(); // Najpierw czyścimy listę, aby zacząć od czystego stanu
    for(int i = 0; i < liczbaElementow; ++i) {
        lista.addEnd(dane[i]);
    }
}

int main() {

    const int liczbaPomiarow = 30; // Liczba pomiarów
    const int liczbaElementow = 100000;
    const int skokIlosciDanych = 10000;

    int wyborStruktury = menu_Struktury_Danych(); // wybór struktury danych

    //Wczytanie danych z pliku do pomocniczej tablicy dla dodawania elementów
    //fin.open("wylosowane_dane_500000.txt");
    fin.open("dane_do_find_500000.txt");
    int liczba;
    int DaneZPliku[liczbaElementow];
    for(int i = 0; i < liczbaElementow; i++) {
        fin >> liczba;
        DaneZPliku[i] = liczba;
    }
    fin.close();

    switch(wyborStruktury){
        case 1: {
            fout.open("wynikiArrayList.txt"); //Otwarie pliku do zapisu wyników
            fout << "Ilosc elementow startowych; sredni czas dodania elementu na poczatku [ms]; sredni czas dodania elementu na koncu [ms]; sredni czas dodania elementu w losowym miejscu [ms]; sredni czas wyszukiwania losowej liczby [ms]"<< endl;

            ArrayList<int> listy[liczbaPomiarow]; // Tworzenie tablicy list

            //petla uzupelniajaca tablice listy
            for(int startElementow = 0; startElementow < liczbaElementow; startElementow += skokIlosciDanych){

                //Pomiary dodania elementu na poczatku

                double calkowityCzasNaPoczatku = 0.0;
                for(int i = 0; i < liczbaPomiarow; i++) {
                    wypelnijListe(listy[i], DaneZPliku, startElementow);
                    auto start = high_resolution_clock::now();
                    listy[i].addFront(5);
                    auto stop = high_resolution_clock::now();
                    calkowityCzasNaPoczatku += duration<double, milli>(stop - start).count();
                }

                double sredniCzasNaPoczatku = calkowityCzasNaPoczatku / liczbaPomiarow; // Obliczanie średniego czasu

                //Pomiar czasu dodania elementu na końcu

                double calkowityCzasNaKoncu = 0.0;
                for(int i = 0; i < liczbaPomiarow; i++) {
                    wypelnijListe(listy[i], DaneZPliku, startElementow);
                    auto start = high_resolution_clock::now();
                    listy[i].addEnd(5);
                    auto stop = high_resolution_clock::now();
                    calkowityCzasNaKoncu += duration<double, milli>(stop - start).count();
                }

                double sredniCzasNaKoncu = calkowityCzasNaKoncu / liczbaPomiarow; // Obliczanie średniego czasu

                //Pomiar czasu dodania elementu w losowym miejscu

                double calkowityCzasLosoweMiejsce = 0.0;
                for(int i = 0; i < liczbaPomiarow; i++) {
                    wypelnijListe(listy[i], DaneZPliku, startElementow);
                    int losoweMiejsce = losujLiczbe(0, startElementow);
                    auto start = high_resolution_clock::now();
                    listy[i].addAt(5,losoweMiejsce);
                    auto stop = high_resolution_clock::now();
                    calkowityCzasLosoweMiejsce += duration<double, milli>(stop - start).count();
                }

                double sredniCzasLosoweMiejsce = calkowityCzasLosoweMiejsce / liczbaPomiarow; // Obliczanie średniego czasu

                //Pomiar czasu wyszukania elementu

                double calkowityCzasWyszukiwania = 0.0;
                for(int i = 0; i < liczbaPomiarow; i++) {
                    wypelnijListe(listy[i], DaneZPliku, startElementow);
                    int liczbaDoSzukania = losujLiczbe(0, 1000);
                    int czyZnaleziono = 0;
                    auto start = high_resolution_clock::now();
                    czyZnaleziono = listy[i].find(liczbaDoSzukania);
                    auto stop = high_resolution_clock::now();
                    if (czyZnaleziono != -1){
                        calkowityCzasWyszukiwania += duration<double, milli>(stop - start).count();
                    } else if(czyZnaleziono == -1){
                        calkowityCzasWyszukiwania = -1 * liczbaPomiarow;
                    }
                }

                double sredniCzasWyszukiwania = calkowityCzasWyszukiwania / liczbaPomiarow; // Obliczanie średniego czasu

                fout << startElementow << ";" << fixed << setprecision(6) << sredniCzasNaPoczatku << ";" << fixed << setprecision(6) << sredniCzasNaKoncu << ";" << fixed << setprecision(6) << sredniCzasLosoweMiejsce << ";" << fixed << setprecision(6) << sredniCzasWyszukiwania << endl;
            }

            fout.close();
            break;
        }
        case 2: {
            fout.open("wynikiLinkedList.txt"); //Otwarie pliku do zapisu wyników
            fout << "Ilosc elementow startowych; sredni czas dodania elementu na poczatku [ms]; sredni czas dodania elementu na koncu [ms]; sredni czas dodania elementu w losowym miejscu [ms]"<< endl;

            LinkedList<int> listy[liczbaPomiarow]; // Tworzenie tablicy list

            //petla uzupelniajaca tablice listy
            for(int startElementow = 0; startElementow < liczbaElementow; startElementow += skokIlosciDanych){


                //Pomiary dodania elementu na poczatku

                double calkowityCzasNaPoczatku = 0.0;
                for(int i = 0; i < liczbaPomiarow; i++) {
                    wypelnijListe(listy[i], DaneZPliku, startElementow);
                    auto start = high_resolution_clock::now();
                    listy[i].addFront(5);
                    auto stop = high_resolution_clock::now();
                    calkowityCzasNaPoczatku += duration<double, milli>(stop - start).count();
                }

                double sredniCzasNaPoczatku = calkowityCzasNaPoczatku / liczbaPomiarow; // Obliczanie średniego czasu

                //Pomiar czasu dodania elementu na końcu

                double calkowityCzasNaKoncu = 0.0;
                for(int i = 0; i < liczbaPomiarow; i++) {
                    wypelnijListe(listy[i], DaneZPliku, startElementow);
                    auto start = high_resolution_clock::now();
                    listy[i].addEnd(5);
                    auto stop = high_resolution_clock::now();
                    calkowityCzasNaKoncu += duration<double, milli>(stop - start).count();
                }

                double sredniCzasNaKoncu = calkowityCzasNaKoncu / liczbaPomiarow; // Obliczanie średniego czasu

                //Pomiar czasu dodania elementu w losowym miejscu

                double calkowityCzasLosoweMiejsce = 0.0;
                for(int i = 0; i < liczbaPomiarow; i++) {
                    wypelnijListe(listy[i], DaneZPliku, startElementow);
                    int losoweMiejsce = losujLiczbe(0, startElementow);
                    auto start = high_resolution_clock::now();
                    listy[i].addAt(5,losoweMiejsce);
                    auto stop = high_resolution_clock::now();
                    calkowityCzasLosoweMiejsce += duration<double, milli>(stop - start).count();
                }
                double sredniCzasLosoweMiejsce = calkowityCzasLosoweMiejsce / liczbaPomiarow; // Obliczanie średniego czasu

                //Pomiar czasu wyszukania elementu

                double calkowityCzasWyszukiwania = 0.0;
                for(int i = 0; i < liczbaPomiarow; i++) {
                    wypelnijListe(listy[i], DaneZPliku, startElementow);
                    int liczbaDoSzukania = losujLiczbe(0, 1000);
                    int czyZnaleziono = 0;
                    auto start = high_resolution_clock::now();
                    czyZnaleziono = listy[i].find(liczbaDoSzukania);
                    auto stop = high_resolution_clock::now();
                    if (czyZnaleziono != -1){
                        calkowityCzasWyszukiwania += duration<double, milli>(stop - start).count();
                    } else if(czyZnaleziono == -1){
                        calkowityCzasWyszukiwania = -1 * liczbaPomiarow;
                    }
                }

                double sredniCzasWyszukiwania = calkowityCzasWyszukiwania / liczbaPomiarow; // Obliczanie średniego czasu

                fout << startElementow << ";" << fixed << setprecision(6) << sredniCzasNaPoczatku << ";" << fixed << setprecision(6) << sredniCzasNaKoncu << ";" << fixed << setprecision(6) << sredniCzasLosoweMiejsce << ";" << fixed << setprecision(6) << sredniCzasWyszukiwania << endl;
            }

            fout.close();
            break;
        }
        case 3: {
            fout.open("wynikiLinkedListWithTail.txt"); //Otwarie pliku do zapisu wyników
            fout << "Ilosc elementow startowych; sredni czas dodania elementu na poczatku [ms]; sredni czas dodania elementu na koncu [ms]; sredni czas dodania elementu w losowym miejscu [ms]"<< endl;

            LinkedListWithTail<int> listy[liczbaPomiarow]; // Tworzenie tablicy list

            //petla uzupelniajaca tablice listy
            for(int startElementow = 0; startElementow < liczbaElementow; startElementow += skokIlosciDanych){


                //Pomiary dodania elementu na poczatku

                double calkowityCzasNaPoczatku = 0.0;
                for(int i = 0; i < liczbaPomiarow; i++) {
                    wypelnijListe(listy[i], DaneZPliku, startElementow);
                    auto start = high_resolution_clock::now();
                    listy[i].addFront(5);
                    auto stop = high_resolution_clock::now();
                    calkowityCzasNaPoczatku += duration<double, milli>(stop - start).count();
                }

                double sredniCzasNaPoczatku = calkowityCzasNaPoczatku / liczbaPomiarow; // Obliczanie średniego czasu

                //Pomiar czasu dodania elementu na końcu

                double calkowityCzasNaKoncu = 0.0;
                for(int i = 0; i < liczbaPomiarow; i++) {
                    wypelnijListe(listy[i], DaneZPliku, startElementow);
                    auto start = high_resolution_clock::now();
                    listy[i].addEnd(5);
                    auto stop = high_resolution_clock::now();
                    calkowityCzasNaKoncu += duration<double, milli>(stop - start).count();
                }

                double sredniCzasNaKoncu = calkowityCzasNaKoncu / liczbaPomiarow; // Obliczanie średniego czasu

                //Pomiar czasu dodania elementu w losowym miejscu

                double calkowityCzasLosoweMiejsce = 0.0;
                for(int i = 0; i < liczbaPomiarow; i++) {
                    wypelnijListe(listy[i], DaneZPliku, startElementow);
                    int losoweMiejsce = losujLiczbe(0, startElementow);
                    auto start = high_resolution_clock::now();
                    listy[i].addAt(5,losoweMiejsce);
                    auto stop = high_resolution_clock::now();
                    calkowityCzasLosoweMiejsce += duration<double, milli>(stop - start).count();
                }
                double sredniCzasLosoweMiejsce = calkowityCzasLosoweMiejsce / liczbaPomiarow; // Obliczanie średniego czasu

                //Pomiar czasu wyszukania elementu

                double calkowityCzasWyszukiwania = 0.0;
                for(int i = 0; i < liczbaPomiarow; i++) {
                    wypelnijListe(listy[i], DaneZPliku, startElementow);
                    int liczbaDoSzukania = losujLiczbe(0, 1000);
                    int czyZnaleziono = 0;
                    auto start = high_resolution_clock::now();
                    czyZnaleziono = listy[i].find(liczbaDoSzukania);
                    auto stop = high_resolution_clock::now();
                    if (czyZnaleziono != -1){
                        calkowityCzasWyszukiwania += duration<double, milli>(stop - start).count();
                    } else if(czyZnaleziono == -1){
                        calkowityCzasWyszukiwania = -1 * liczbaPomiarow;
                    }
                }

                double sredniCzasWyszukiwania = calkowityCzasWyszukiwania / liczbaPomiarow; // Obliczanie średniego czasu

                fout << startElementow << ";" << fixed << setprecision(6) << sredniCzasNaPoczatku << ";" << fixed << setprecision(6) << sredniCzasNaKoncu << ";" << fixed << setprecision(6) << sredniCzasLosoweMiejsce << ";" << fixed << setprecision(6) << sredniCzasWyszukiwania << endl;

            }

            fout.close();
            break;
        }
        case 4: {
            fout.open("wynikiDoubleLinkedList.txt"); //Otwarie pliku do zapisu wyników
            fout << "Ilosc elementow startowych; sredni czas dodania elementu na poczatku [ms]; sredni czas dodania elementu na koncu [ms]; sredni czas dodania elementu w losowym miejscu [ms]"<< endl;

            DoubleLinkedList<int> listy[liczbaPomiarow]; // Tworzenie tablicy list

            //petla uzupelniajaca tablice listy
            for(int startElementow = 0; startElementow < liczbaElementow; startElementow += skokIlosciDanych){

                //Pomiary dodania elementu na poczatku
                double calkowityCzasNaPoczatku = 0.0;
                for(int i = 0; i < liczbaPomiarow; i++) {
                    wypelnijListe(listy[i], DaneZPliku, startElementow);
                    auto start = high_resolution_clock::now();
                    listy[i].addFront(5);
                    auto stop = high_resolution_clock::now();
                    calkowityCzasNaPoczatku += duration<double, milli>(stop - start).count();
                }

                double sredniCzasNaPoczatku = calkowityCzasNaPoczatku / liczbaPomiarow; // Obliczanie średniego czasu

                //Pomiar czasu dodania elementu na końcu
                double calkowityCzasNaKoncu = 0.0;
                for(int i = 0; i < liczbaPomiarow; i++) {
                    wypelnijListe(listy[i], DaneZPliku, startElementow);
                    auto start = high_resolution_clock::now();
                    listy[i].addEnd(5);
                    auto stop = high_resolution_clock::now();
                    calkowityCzasNaKoncu += duration<double, milli>(stop - start).count();
                }

                double sredniCzasNaKoncu = calkowityCzasNaKoncu / liczbaPomiarow; // Obliczanie średniego czasu

                //Pomiar czasu dodania elementu w losowym miejscu
                double calkowityCzasLosoweMiejsce = 0.0;
                for(int i = 0; i < liczbaPomiarow; i++) {
                    wypelnijListe(listy[i], DaneZPliku, startElementow);
                    int losoweMiejsce = losujLiczbe(0, startElementow);
                    auto start = high_resolution_clock::now();
                    listy[i].addAt(5,losoweMiejsce);
                    auto stop = high_resolution_clock::now();
                    calkowityCzasLosoweMiejsce += duration<double, milli>(stop - start).count();
                }
                double sredniCzasLosoweMiejsce = calkowityCzasLosoweMiejsce / liczbaPomiarow; // Obliczanie średniego czasu

                //Pomiar czasu wyszukania elementu
                  double calkowityCzasWyszukiwania = 0.0;
                for(int i = 0; i < liczbaPomiarow; i++) {
                    wypelnijListe(listy[i], DaneZPliku, startElementow);
                    int liczbaDoSzukania = losujLiczbe(0, 1000);
                    int czyZnaleziono = 0;
                    auto start = high_resolution_clock::now();
                    czyZnaleziono = listy[i].find(liczbaDoSzukania);
                    auto stop = high_resolution_clock::now();
                    if (czyZnaleziono != -1){
                        calkowityCzasWyszukiwania += duration<double, milli>(stop - start).count();
                    } else if(czyZnaleziono == -1){
                        calkowityCzasWyszukiwania = -1 * liczbaPomiarow;
                    }
                }

                double sredniCzasWyszukiwania = calkowityCzasWyszukiwania / liczbaPomiarow; // Obliczanie średniego czasu
                fout << startElementow << ";" << fixed << setprecision(6) << sredniCzasNaPoczatku << ";" << fixed << setprecision(6) << sredniCzasNaKoncu << ";" << fixed << setprecision(6) << sredniCzasLosoweMiejsce << ";" << fixed << setprecision(6) << sredniCzasWyszukiwania << endl;
            }

            fout.close();
            break;
        }
        default: {
            cout << "Niepoprawny wybor, wybierz ocpcje od 1 do 4:" << endl;
            break;
        }
    }


    return 0;
}

