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

void wypelnijListy(ArrayList<int> listy[], int dane[], int liczbaElementow, int liczbaPomiarow) {
    for(int i = 0; i < liczbaPomiarow; i++) {
        listy[i] = ArrayList<int>();
        for(int j = 0; j < liczbaElementow; j++) {
            listy[i].dodajElementNaKoniec(dane[j]);
        }
    }
}

int main() {

    const int liczbaPomiarow = 2; // Liczba pomiarów

    //Wczytanie danych z pliku do pomocniczej tablicy
    fin.open("wylosowane_dane_500000.txt");
    int liczba;
    int DaneZPliku[500000];
    for(int i = 0; i < 500000; i++) {
        fin >> liczba;
        DaneZPliku[i] = liczba;
    }
    fin.close();

    wyborStruktury: // etykieta na wypadek złego wyboru opcji z menu
    int wybor = menu_Struktury_Danych(); // wybór struktury danych

    // określenie początkowej wielkości struktury danych
//    int ileElementow = 0;
//    cout << "Ile elementow chcesz aby było w strukturze do struktury danych?" << endl;
//    cin >> ileElementow;

    switch(wybor){
        case 1: {
            fout.open("wynikiArrayList.txt"); //Otwarie pliku do zapisu wyników
            fout << "Ilosc elementow startowych; sredni czas dodania elementu na poczatku [ms]; sredni czas dodania elementu na koncu [ms]; sredni czas dodania elementu w losowym miejscu [ms]"<< endl;

            ArrayList<int> listy[liczbaPomiarow]; // Tworzenie tablicy list

            //petla uzupelniajaca tablice listy
            for(int startElementow = 0; startElementow < 500000; startElementow += 10000){

                //Pomiary dodania elementu na poczatku
                wypelnijListy(listy, DaneZPliku, startElementow, liczbaPomiarow);

                double calkowityCzasNaPoczatku = 0.0;
                for(int i = 0; i < liczbaPomiarow; i++) {
                    auto start = high_resolution_clock::now();
                    listy[i].dodajElementNaPoczatek(5);
                    auto stop = high_resolution_clock::now();
                    calkowityCzasNaPoczatku += duration<double, milli>(stop - start).count();
                }

                double sredniCzasNaPoczatku = calkowityCzasNaPoczatku / liczbaPomiarow; // Obliczanie średniego czasu

                //Pomiar czasu dodania elementu na końcu
                wypelnijListy(listy, DaneZPliku, startElementow, liczbaPomiarow);

                double calkowityCzasNaKoncu = 0.0;
                for(int i = 0; i < liczbaPomiarow; i++) {
                    auto start = high_resolution_clock::now();
                    listy[i].dodajElementNaKoniec(5);
                    auto stop = high_resolution_clock::now();
                    calkowityCzasNaKoncu += duration<double, milli>(stop - start).count();
                }

                double sredniCzasNaKoncu = calkowityCzasNaKoncu / liczbaPomiarow; // Obliczanie średniego czasu

                //Pomiar czasu dodania elementu w losowym miejscu
                wypelnijListy(listy, DaneZPliku, startElementow, liczbaPomiarow);

                double calkowityCzasLosoweMiejsce = 0.0;
                for(int i = 0; i < liczbaPomiarow; i++) {
                    int losoweMiejsce = losujLiczbe(0, startElementow);
                    auto start = high_resolution_clock::now();
                    listy[i].dodajElement(5,losoweMiejsce);
                    auto stop = high_resolution_clock::now();
                    calkowityCzasLosoweMiejsce += duration<double, milli>(stop - start).count();
                }

                double sredniCzasLosoweMiejsce = calkowityCzasLosoweMiejsce / liczbaPomiarow; // Obliczanie średniego czasu

                fout << startElementow << ";" << fixed << setprecision(6) << sredniCzasNaPoczatku << ";" << fixed << setprecision(6) << sredniCzasNaKoncu << ";" << fixed << setprecision(6) << sredniCzasLosoweMiejsce << endl;
            }

            fout.close();
            break;
        }
        case 2: {
            fout.open("wynikiLinkedList.txt"); //Otwarie pliku do zapisu wyników
            fout << "Ilosc elementow startowych; sredni czas dodania elementu na poczatku [ms]; sredni czas dodania elementu na koncu [ms]; sredni czas dodania elementu w losowym miejscu [ms]"<< endl;

            LinkedList<int> listy[liczbaPomiarow]; // Tworzenie tablicy list

            //petla uzupelniajaca tablice listy
            for(int startElementow = 0; startElementow < 10; startElementow += 1){


                //Pomiary dodania elementu na poczatku
                cout << "Początkowe listy" << endl;
                for(int i = 0; i < liczbaPomiarow; i++) {
                    listy[i] = LinkedList<int>();
                    for(int j = 0; j < startElementow; j++) {
                        listy[i].addEnd(DaneZPliku[j]);
                    }
                    listy[i].print();
                }

                double calkowityCzasNaPoczatku = 0.0;
                cout << "Listy po dodaniu elementu na poczatku:" << endl;
                for(int i = 0; i < liczbaPomiarow; i++) {
                    auto start = high_resolution_clock::now();
                    listy[i].addFront(5);
                    auto stop = high_resolution_clock::now();
                    calkowityCzasNaPoczatku += duration<double, milli>(stop - start).count();
                    cout << "Czas: " << calkowityCzasNaPoczatku << endl;
                    listy[i].print();
                }

                double sredniCzasNaPoczatku = calkowityCzasNaPoczatku / liczbaPomiarow; // Obliczanie średniego czasu

                cout << "Początkowe listy" << endl;
                for(int i = 0; i < liczbaPomiarow; i++) {
                    listy[i] = LinkedList<int>();
                    for(int j = 0; j < startElementow; j++) {
                        listy[i].addEnd(DaneZPliku[j]);
                    }
                    listy[i].print();
                }

                double calkowityCzasNaKoncu = 0.0;
                cout << "Listy po dodaniu elementu na koncu:" << endl;
                for(int i = 0; i < liczbaPomiarow; i++) {
                    auto start = high_resolution_clock::now();
                    listy[i].addEnd(5);
                    auto stop = high_resolution_clock::now();
                    calkowityCzasNaKoncu += duration<double, milli>(stop - start).count();
                    cout << "Czas: " << calkowityCzasNaKoncu << endl;
                    listy[i].print();
                }

                double sredniCzasNaKoncu = calkowityCzasNaKoncu / liczbaPomiarow; // Obliczanie średniego czasu

                cout << "Początkowe listy" << endl;
                for(int i = 0; i < liczbaPomiarow; i++) {
                    listy[i] = LinkedList<int>();
                    for(int j = 0; j < startElementow; j++) {
                        listy[i].addEnd(DaneZPliku[j]);
                    }
                    listy[i].print();
                }

                double calkowityCzasLosoweMiejsce = 0.0;
                cout << "Listy po dodaniu elementu w losowym miejscu:" << endl;
                for(int i = 0; i < liczbaPomiarow; i++) {
                    int losoweMiejsce = losujLiczbe(0, startElementow);
                    auto start = high_resolution_clock::now();
                    listy[i].addAt(5,losoweMiejsce);
                    auto stop = high_resolution_clock::now();
                    calkowityCzasLosoweMiejsce += duration<double, milli>(stop - start).count();
                    cout << "Czas: " << calkowityCzasLosoweMiejsce << endl;
                    listy[i].print();
                }
                double sredniCzasLosoweMiejsce = calkowityCzasLosoweMiejsce / liczbaPomiarow; // Obliczanie średniego czasu
                cout << startElementow << ";" << fixed << setprecision(6) << sredniCzasNaPoczatku << fixed << setprecision(6) << sredniCzasNaKoncu << fixed << setprecision(6) << sredniCzasLosoweMiejsce <<endl;
            }

            fout.close();

            break;
        }
        case 3: {
            cout << "Wybrano liste jednokierunkowa (head, tail)" << endl;
//            LinkedListWithTail<int> lista;
//            for(int i = 0; i < ileElementow; i++){
//                lista.addBack(losujLiczbe(min, max));
//            }
//            lista.print();
            break;
        }
        case 4: {
            cout << "Wybrano liste dwukierunkowa" << endl;
//            DoubleLinkedList<int> lista;
//            for(int i = 0; i < ileElementow; i++){
//                lista.addBack(losujLiczbe(min, max)); // Dodajemy elementy na końcu listy
//            }
//            cout << "Lista dwukierunkowa (przód): ";
//            lista.printForward();
//            cout << "Lista dwukierunkowa (tył): ";
//            lista.printBackward();
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

