#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>
#include <chrono>
#include <random>

using namespace std;
using namespace chrono;

// ============================================================
// Klasa reprezentująca stos zbudowany na liście jednokierunkowej
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
    // value - liczba, która ma zostać dodana na stos.
    void push(int value)
    {
        topNode = new Node(value, topNode);
    }

    // Usuwa element znajdujący się na szczycie stosu.
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

    // Zwraca wartość elementu znajdującego się na szczycie stosu.
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
    // Brak parametrów - funkcja czyści cały stos.
    void clear()
    {
        while (topNode != nullptr)
        {
            Node* temp = topNode;
            topNode = topNode->next;
            delete temp;
        }
    }

    // Sortuje elementy stosu rosnąco.
    //
    // Brak parametrów - funkcja sortuje wszystkie elementy
    // znajdujące się aktualnie na stosie.
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
        // Od końca, aby najmniejsza wartość była na szczycie.
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
    // Brak parametrów - zapisuje aktualny moment rozpoczęcia.
    void start()
    {
        startTime = steady_clock::now();
    }

    // Kończy pomiar i zwraca czas w mikrosekundach.
    //
    // Brak parametrów - oblicza czas od wywołania funkcji start().
    long long stop()
    {
        auto endTime = steady_clock::now();

        return duration_cast<microseconds>(
            endTime - startTime
        ).count();
    }
};


// ============================================================
// Klasa wykonująca testy
// ============================================================

class SortingTest
{
private:
    static const int ELEMENTS = 100000;

    queue<int> kolejka;
    StackList stos;
    int* tablica;

    vector<int> dane;

public:

    SortingTest()
    {
        tablica = new int[ELEMENTS];

        // Generowanie liczb odbywa się przed pomiarem,
        // aby czas generowania nie wpływał na wynik.
        mt19937 generator(12345);
        uniform_int_distribution<int> distribution(1, 1000000);

        dane.resize(ELEMENTS);

        for (int i = 0; i < ELEMENTS; i++)
        {
            dane[i] = distribution(generator);
        }
    }

    ~SortingTest()
    {
        delete[] tablica;
    }

    // ========================================================
    // Funkcja Wypisz
    // ========================================================

    // Wpisuje 100 000 elementów do kolejki, stosu z listy
    // oraz zwykłej tablicy i mierzy czas każdej operacji.
    //
    // Parametry:
    // brak - liczba elementów jest określona przez stałą ELEMENTS.
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

        long long czasKolejka = timer.stop();


        // ----------------------------------------------------
        // STOS Z LISTY
        // ----------------------------------------------------

        timer.start();

        for (int i = 0; i < ELEMENTS; i++)
        {
            stos.push(dane[i]);
        }

        long long czasStos = timer.stop();


        // ----------------------------------------------------
        // ZWYKŁA TABLICA
        // ----------------------------------------------------

        timer.start();

        for (int i = 0; i < ELEMENTS; i++)
        {
            tablica[i] = dane[i];
        }

        long long czasTablica = timer.stop();


        // ----------------------------------------------------
        // WYNIKI
        // ----------------------------------------------------

        cout << "Wypisywanie:\n";
        cout << "kolejka: " << czasKolejka << " us\n";
        cout << "stos:    " << czasStos << " us\n";
        cout << "tablica: " << czasTablica << " us\n";
        cout << endl;
    }


    // ========================================================
    // Funkcja Sortuj
    // ========================================================

    // Sortuje wcześniej zapisane 100 000 elementów w kolejce,
    // stosie z listy oraz zwykłej tablicy i mierzy czas sortowania.
    //
    // Parametry:
    // brak - funkcja korzysta z danych zapisanych wcześniej
    // przez funkcję Wypisz().
    void Sortuj()
    {
        Timer timer;


        // ----------------------------------------------------
        // SORTOWANIE KOLEJKI
        // ----------------------------------------------------

        timer.start();

        vector<int> kolejkaDane;

        // Wyciągnięcie elementów z kolejki.
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

        long long czasKolejka = timer.stop();


        // ----------------------------------------------------
        // SORTOWANIE STOSU
        // ----------------------------------------------------

        timer.start();

        stos.sortStack();

        long long czasStos = timer.stop();


        // ----------------------------------------------------
        // SORTOWANIE TABLICY
        // ----------------------------------------------------

        timer.start();

        sort(tablica, tablica + ELEMENTS);

        long long czasTablica = timer.stop();


        // ----------------------------------------------------
        // WYNIKI
        // ----------------------------------------------------

        cout << "Sortowanie:\n";
        cout << "kolejka: " << czasKolejka << " us\n";
        cout << "stos:    " << czasStos << " us\n";
        cout << "tablica: " << czasTablica << " us\n";
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

    return 0;
}
