#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>
#include <chrono>
#include <random>

using namespace std;
using namespace chrono;

// ============================================================
// Klasa reprezentuj¹ca stos zbudowany na liœcie jednokierunkowej
// ============================================================

class StackList
{
private:
    struct Node
    {
        int value;
        Node* next;

        Node(int value, Node* next = nullptr)
            : value(value), next(next) {}
    };

    Node* topNode;

public:
    StackList() : topNode(nullptr) {}

    ~StackList()
    {
        clear();
    }

    // Dodaje element na szczyt stosu.
    //
    // Parametr:
    // value - liczba, która ma zostaæ dodana na stos.
    void push(int value)
    {
        topNode = new Node(value, topNode);
    }

    // Usuwa element znajduj¹cy siê na szczycie stosu.
    //
    // Brak parametrów - funkcja usuwa aktualnie pierwszy element.
    void pop()
    {
        if (topNode == nullptr)
            return;

        Node* temp = topNode;
        topNode = topNode->next;
        delete temp;
    }

    // Zwraca wartoœæ elementu znajduj¹cego siê na szczycie stosu.
    //
    // Brak parametrów - funkcja odczytuje aktualny szczyt stosu.
    int top() const
    {
        return topNode->value;
    }

    // Sprawdza, czy stos jest pusty.
    //
    // Brak parametrów - funkcja sprawdza aktualny stan stosu.
    bool empty() const
    {
        return topNode == nullptr;
    }

    // Usuwa wszystkie elementy stosu.
    //
    // Brak parametrów - funkcja czyœci ca³y stos.
    void clear()
    {
        while (topNode != nullptr)
        {
            Node* temp = topNode;
            topNode = topNode->next;
            delete temp;
        }
    }

    // Sortuje elementy stosu rosn¹co.
    //
    // Brak parametrów - funkcja sortuje wszystkie elementy
    // znajduj¹ce siê aktualnie na stosie.
    void sortStack()
    {
        vector<int> values;

        // Przeniesienie danych ze stosu do wektora.
        while (!empty())
        {
            values.push_back(top());
            pop();
        }

        // Sortowanie danych.
        sort(values.begin(), values.end());

        // Odtworzenie stosu.
        // Od koñca, aby najmniejsza wartoœæ by³a na szczycie.
        for (auto it = values.rbegin(); it != values.rend(); ++it)
        {
            push(*it);
        }
    }
};


// ============================================================
// Klasa odpowiedzialna za pomiary czasu
// ============================================================

class Timer
{
private:
    steady_clock::time_point startTime;

public:

    // Rozpoczyna pomiar czasu.
    //
    // Brak parametrów - zapisuje aktualny moment rozpoczêcia.
    void start()
    {
        startTime = steady_clock::now();
    }

    // Koñczy pomiar i zwraca czas w mikrosekundach.
    //
    // Brak parametrów - oblicza czas od wywo³ania funkcji start().
    long long stop()
    {
        auto endTime = steady_clock::now();

        return duration_cast<microseconds>(
            endTime - startTime
        ).count();
    }
};


// ============================================================
// Klasa wykonuj¹ca testy
// ============================================================

class SortingTest
{
private:
    static const int ELEMENTS = 100000;

    queue<int> kolejka;
    StackList stos;
    int* tablica;

    // Vector przechowuj¹cy elementy.
    vector<int> wektor;

    // Vector zawieraj¹cy dane wykorzystane do testów.
    vector<int> dane;


    // Czasy dodawania / wpisywania danych.
    long long czasKolejkaDodawanie;
    long long czasStosDodawanie;
    long long czasTablicaDodawanie;
    long long czasWektorDodawanie;


    // Czasy sortowania danych.
    long long czasKolejkaSortowanie;
    long long czasStosSortowanie;
    long long czasTablicaSortowanie;
    long long czasWektorSortowanie;

public:

    SortingTest()
    {
        tablica = new int[ELEMENTS];

        // Rezerwujemy miejsce dla 100 000 elementów w vectorze.
        wektor.reserve(ELEMENTS);

        // Generowanie liczb odbywa sie przed wstawieniem ich do typow danych
        mt19937 generator(12345); // algorytm generatora liczb pseudolosowych.
        uniform_int_distribution<int> distribution(1, 1000000); // tworzy rozkład, który losuje liczby całkowite typu int.

        dane.resize(ELEMENTS); // zmienia rozmiar wektora.

        for (int i = 0; i < ELEMENTS; i++)
        {
            dane[i] = distribution(generator); // nazwa naszego rozkładu
        }

        // Początkowe wartości czasów.
        czasKolejkaDodawanie = 0;
        czasStosDodawanie = 0;
        czasTablicaDodawanie = 0;
        czasWektorDodawanie = 0;

        czasKolejkaSortowanie = 0;
        czasStosSortowanie = 0;
        czasTablicaSortowanie = 0;
        czasWektorSortowanie = 0;
    }

    ~SortingTest()
    {
        delete[] tablica;
    }

    // ========================================================
    // Funkcja Wypisz
    // ========================================================

    // Wpisuje 100 000 elementów do kolejki, stosu z listy,
    // zwyk³ej tablicy oraz vectora i mierzy czas ka¿dej operacji.
    //
    // Parametry:
    // brak - liczba elementów jest okreœlona przez sta³¹ ELEMENTS.
    void Wypisz()
    {
        Timer timer;

        // ----------------------------------------------------
        // KOLEJKA
        // ----------------------------------------------------

        timer.start();

        for (int i = 0; i < ELEMENTS; i++)
        {
            kolejka.push(dane[i]);
        }

        czasKolejkaDodawanie = timer.stop();


        // ----------------------------------------------------
        // STOS Z LISTY
        // ----------------------------------------------------

        timer.start();

        for (int i = 0; i < ELEMENTS; i++)
        {
            stos.push(dane[i]);
        }

        czasStosDodawanie = timer.stop();


        // ----------------------------------------------------
        // ZWYK£A TABLICA
        // ----------------------------------------------------

        timer.start();

        for (int i = 0; i < ELEMENTS; i++)
        {
            tablica[i] = dane[i];
        }

        czasTablicaDodawanie = timer.stop();


        // ----------------------------------------------------
        // VECTOR
        // ----------------------------------------------------

        timer.start();

        for (int i = 0; i < ELEMENTS; i++)
        {
            wektor.push_back(dane[i]);
        }

        czasWektorDodawanie = timer.stop();


        // ----------------------------------------------------
        // WYNIKI
        // ----------------------------------------------------

        cout << "Wypisywanie:\n";
        cout << "kolejka: " << czasKolejkaDodawanie << " us\n";
        cout << "stos:    " << czasStosDodawanie << " us\n";
        cout << "tablica: " << czasTablicaDodawanie << " us\n";
        cout << "vector:  " << czasWektorDodawanie << " us\n";
        cout << endl;
    }


    // ========================================================
    // Funkcja Sortuj
    // ========================================================

    // Sortuje wczeœniej zapisane 100 000 elementów w kolejce,
    // stosie z listy, zwyk³ej tablicy oraz vectorze
    // i mierzy czas sortowania.
    //
    // Parametry:
    // brak - funkcja korzysta z danych zapisanych wczeœniej
    // przez funkcjê Wypisz().
    void Sortuj()
    {
        Timer timer;


        // ----------------------------------------------------
        // SORTOWANIE KOLEJKI
        // ----------------------------------------------------

        timer.start();

        vector<int> kolejkaDane;

        // Wyci¹gniêcie elementów z kolejki.
        while (!kolejka.empty())
        {
            kolejkaDane.push_back(kolejka.front());
            kolejka.pop();
        }

        // Sortowanie elementów.
        sort(kolejkaDane.begin(), kolejkaDane.end());

        // Ponowne utworzenie kolejki.
        for (int value : kolejkaDane)
        {
            kolejka.push(value);
        }

        czasKolejkaSortowanie = timer.stop();


        // ----------------------------------------------------
        // SORTOWANIE STOSU
        // ----------------------------------------------------

        timer.start();

        stos.sortStack();

        czasStosSortowanie = timer.stop();


        // ----------------------------------------------------
        // SORTOWANIE TABLICY
        // ----------------------------------------------------

        timer.start();

        sort(tablica, tablica + ELEMENTS);

        czasTablicaSortowanie = timer.stop();


        // ----------------------------------------------------
        // SORTOWANIE VECTOR
        // ----------------------------------------------------

        timer.start();

        sort(wektor.begin(), wektor.end());

        czasWektorSortowanie = timer.stop();


        // ----------------------------------------------------
        // WYNIKI
        // ----------------------------------------------------

        cout << "Sortowanie:\n";
        cout << "kolejka: " << czasKolejkaSortowanie << " us\n";
        cout << "stos:    " << czasStosSortowanie << " us\n";
        cout << "tablica: " << czasTablicaSortowanie << " us\n";
        cout << "vector:  " << czasWektorSortowanie << " us\n";
        cout << endl;
    }


    // ========================================================
    // Funkcja czas_dodawanie
    // ========================================================

    // Dodaje czas wpisywania elementów oraz czas sortowania
    // dla kolejki, stosu, tablicy oraz vectora.
    //
    // Parametry:
    // brak - funkcja korzysta z czasów zapisanych wcześniej
    // przez funkcje Wypisz() oraz Sortuj().
    void czas_dodawanie()
    {
        long long czasKolejka =
            czasKolejkaDodawanie + czasKolejkaSortowanie;

        long long czasStos =
            czasStosDodawanie + czasStosSortowanie;

        long long czasTablica =
            czasTablicaDodawanie + czasTablicaSortowanie;

        long long czasWektor =
            czasWektorDodawanie + czasWektorSortowanie;


        // ----------------------------------------------------
        // WYNIKI
        // ----------------------------------------------------

        cout << "Dodawanie:\n";
        cout << "kolejka: " << czasKolejka << " us\n";
        cout << "stos:    " << czasStos << " us\n";
        cout << "tablica: " << czasTablica << " us\n";
        cout << "vector:  " << czasWektor << " us\n";
        cout << endl;
    }
};


// ============================================================
// MAIN
// ============================================================

int main()
{
    SortingTest test;

    // Najpierw wpisujemy 100 000 elementów.
    test.Wypisz();

    // Następnie sortujemy wcześniej wpisane elementy.
    test.Sortuj();

    // Na koniec dodajemy czas wpisywania
    // oraz czas sortowania.
    test.czas_dodawanie();

    return 0;
}
