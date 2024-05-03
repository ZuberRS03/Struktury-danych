#include <iostream> //do obsługi strumieni wejścia/wyjścia
#include <fstream> //do obsługi plików
#include <chrono> //do mierzenia czasu
#include <cstdlib> //do losowania liczb

#include "MaxHeap.h"
#include "AVLTree.h"

using namespace std;

ifstream fin;
ofstream fout;

//funkcja do wyboru kolejki
int menuKolejki() {
    int wybor;
    cout << "----------Wybor kolejki priorytetowej----------\n";
    cout << "1. Max Heap\n";
    cout << "2. AVL Tree\n";
    cout << "3. Exit\n";
    cout << "-----------------------------------------------\n";
    cout << "Wybor ";
    cin >> wybor;
    return wybor;
}

//funkcja losująca liczbę z przedziału <min, max>
int losujLiczbe(int min, int max){
    return rand() % (max - min + 1) + min;
}

int main() {
    //podatawowe dane do badan
    const int liczbaPomiarow = 30; // Liczba pomiarów 30
    const int liczbaElementow = 100000; // Max liczba elementów w stróktórze danych 100000
    const int skokIlosciDanych = 5000; // Skok ilości danych 5000

    //wybor kolejki
    int wybranaKolejka = menuKolejki();

    //Ewentualne wczytanie danych z pliku

    switch (wybranaKolejka) {
        case 1:{
            //otwarcie pliku do zapisu wynikow
            fout.open("wynikiMaxHeap.txt");
            fout << "Liczba elementow;Czas insert(e,p);Czas extract-max();Czas find-max();Czas modify-key(e,p);Czas return-size()" << endl;

            //badania dla MaxHeap
            for(int startElementow = 0; startElementow < liczbaElementow; startElementow += skokIlosciDanych) {
                //pomiar insert(e,p)

                //pomiar extract-max()

                //pomiar find-max()

                //pomiar modify-key(e,p)

                //pomiar return-size()

            }

            fout.close();
            break;
        }
        case 2:{

            fout.open("wynikiAVLTree.txt");
            fout << "Liczba elementow;Czas insert(e,p);Czas extract-max();Czas find-max();Czas modify-key(e,p);Czas return-size()" << endl;

            //badania dla AVLTree
            for(int startElementow = 0; startElementow < liczbaElementow; startElementow += skokIlosciDanych) {
                //pomiar insert(e,p)

                //pomiar extract-max()

                //pomiar find-max()

                //pomiar modify-key(e,p)

                //pomiar return-size()

            }

            fout.close();
            break;
        }
        case 3:{
            cout << "Koniec programu\n";
            break;
        }
        defoult:{
            cout << "Niepoprawny wybor\n";
            break;
        }
    }
    return 0;
}