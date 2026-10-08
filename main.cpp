#include <iostream>
#include <vector>
#include <stack>
#include <queue>
#include <chrono>
#include <cstdlib>
#include <ctime>
#include <algorithm>

using namespace std;


// ==========================================
// KOLEJKA Z TWOJEGO KODU
// ==========================================

// struktura kolejka
struct kolejka
{
    int nr;
    kolejka* nastepny;

    kolejka(int _nr)
    {
        nr=_nr;
        nastepny=NULL;
    }
};

class uczen
{
    kolejka* poczatek;
    kolejka* koniec;

public:

    // konstruktor tworzy pusta kolejke
    uczen()
    {
        poczatek=NULL;
        koniec=NULL;
    }

    // funkcja dodaj, dodaje element na koniec kolejki
    void dodaj(int nr)
    {
        kolejka* nowy=new kolejka(nr);

        if(poczatek==NULL)
        {
            poczatek=nowy;
            koniec=nowy;
        }
        else
        {
            koniec->nastepny=nowy;
            koniec=nowy;
        }
    }

    // funkcja sort_bubble, sortuje kolejke
    void sort_bubble()
    {
        if(poczatek==NULL || poczatek->nastepny==NULL)
        {
            return;
        }

        bool zamiana;
        kolejka* temp;
        kolejka* koniec_sortowania=NULL;

        do
        {
            zamiana=false;
            temp=poczatek;

            while(temp->nastepny!=koniec_sortowania)
            {
                if(temp->nr>temp->nastepny->nr)
                {
                    int t=temp->nr;

                    temp->nr=temp->nastepny->nr;

                    temp->nastepny->nr=t;

                    zamiana=true;
                }

                temp=temp->nastepny;
            }

            koniec_sortowania=temp;

        } while(zamiana);
    }

    // destruktor usuwa kolejke
    ~uczen()
    {
        while(poczatek!=NULL)
        {
            kolejka* temp=poczatek;

            poczatek=poczatek->nastepny;

            delete temp;
        }

        koniec=NULL;
    }
};


// ==========================================
// DRZEWO BINARNE Z TWOJEGO KODU
// ==========================================

// struktura liscia
struct Lisc
{
    int wartosc;

    Lisc* lewy;
    Lisc* prawy;
};

class drzewo
{
public:

    Lisc* korzen;

    // konstruktor tworzy puste drzewo
    drzewo()
    {
        korzen=NULL;
    }

    // funkcja dodaj, dodaje element do drzewa
    Lisc* dodaj(Lisc* korzen, int wartosc)
    {
        // jesli drzewo jest puste
        if(korzen==NULL)
        {
            Lisc* nowy=new Lisc;

            nowy->wartosc=wartosc;
            nowy->lewy=NULL;
            nowy->prawy=NULL;

            return nowy;
        }

        // jesli liczba jest mniejsza to idzie w lewo
        if(wartosc<korzen->wartosc)
        {
            korzen->lewy=dodaj(korzen->lewy,wartosc);
        }

        // jesli liczba jest wieksza to idzie w prawo
        else
        {
            korzen->prawy=dodaj(korzen->prawy,wartosc);
        }

        return korzen;
    }

    void dodaj(int wartosc)
    {
        korzen=dodaj(korzen,wartosc);
    }

    // funkcja przechodzi drzewo i zapisuje liczby
    void przejdz(Lisc* korzen, vector<int>& tab)
    {
        if(korzen==NULL)
        {
            return;
        }

        przejdz(korzen->lewy,tab);

        tab.push_back(korzen->wartosc);

        przejdz(korzen->prawy,tab);
    }

    // funkcja sortuje elementy drzewa
    void sortuj()
    {
        vector<int> tab;

        przejdz(korzen,tab);

        sort(tab.begin(),tab.end());
    }

    // funkcja usun usuwa drzewo
    void usun(Lisc* korzen)
    {
        if(korzen==NULL)
        {
            return;
        }

        usun(korzen->lewy);

        usun(korzen->prawy);

        delete korzen;
    }

    // destruktor usuwa drzewo
    ~drzewo()
    {
        usun(korzen);
    }
};


int main()
{
    const int ile=100000;

    // tablica do przechowania jednego losowania
    int liczby[ile];

    // jedno losowanie 100000 liczb
    srand(time(NULL));

    for(int i=0;i<ile;i++)
    {
        liczby[i]=rand()%1000000;
    }


    // zmienne do mierzenia czasu
    chrono::high_resolution_clock::time_point start;
    chrono::high_resolution_clock::time_point stop;


    // ==========================================
    // ZWYKLA TABLICA
    // ==========================================

    int tablica[200000];

    // dodawanie pierwszych 100000
    start=chrono::high_resolution_clock::now();

    for(int i=0;i<ile;i++)
    {
        tablica[i]=liczby[i];
    }

    stop=chrono::high_resolution_clock::now();

    auto czas_tablica_dodawanie=
        chrono::duration_cast<chrono::microseconds>
        (stop-start);


    // sortowanie
    start=chrono::high_resolution_clock::now();

    sort(tablica,tablica+ile);

    stop=chrono::high_resolution_clock::now();

    auto czas_tablica_sortowanie=
        chrono::duration_cast<chrono::microseconds>
        (stop-start);


    // dodawanie kolejnych 100000
    start=chrono::high_resolution_clock::now();

    for(int i=0;i<ile;i++)
    {
        tablica[ile+i]=liczby[i];
    }

    stop=chrono::high_resolution_clock::now();

    auto czas_tablica_kolejne=
        chrono::duration_cast<chrono::microseconds>
        (stop-start);


    // ==========================================
    // VECTOR
    // ==========================================

    vector<int> v;

    // dodawanie pierwszych 100000
    start=chrono::high_resolution_clock::now();

    for(int i=0;i<ile;i++)
    {
        v.push_back(liczby[i]);
    }

    stop=chrono::high_resolution_clock::now();

    auto czas_vector_dodawanie=
        chrono::duration_cast<chrono::microseconds>
        (stop-start);


    // sortowanie
    start=chrono::high_resolution_clock::now();

    sort(v.begin(),v.end());

    stop=chrono::high_resolution_clock::now();

    auto czas_vector_sortowanie=
        chrono::duration_cast<chrono::microseconds>
        (stop-start);


    // dodawanie kolejnych 100000
    start=chrono::high_resolution_clock::now();

    for(int i=0;i<ile;i++)
    {
        v.push_back(liczby[i]);
    }

    stop=chrono::high_resolution_clock::now();

    auto czas_vector_kolejne=
        chrono::duration_cast<chrono::microseconds>
        (stop-start);


    // ==========================================
    // FIFO
    // ==========================================

    queue<int> fifo;

    // dodawanie pierwszych 100000
    start=chrono::high_resolution_clock::now();

    for(int i=0;i<ile;i++)
    {
        fifo.push(liczby[i]);
    }

    stop=chrono::high_resolution_clock::now();

    auto czas_fifo_dodawanie=
        chrono::duration_cast<chrono::microseconds>
        (stop-start);


    // sortowanie FIFO
    start=chrono::high_resolution_clock::now();

    vector<int> fifo_sort;

    while(!fifo.empty())
    {
        fifo_sort.push_back(fifo.front());

        fifo.pop();
    }

    sort(fifo_sort.begin(),fifo_sort.end());

    for(int i=0;i<ile;i++)
    {
        fifo.push(fifo_sort[i]);
    }

    stop=chrono::high_resolution_clock::now();

    auto czas_fifo_sortowanie=
        chrono::duration_cast<chrono::microseconds>
        (stop-start);


    // dodawanie kolejnych 100000
    start=chrono::high_resolution_clock::now();

    for(int i=0;i<ile;i++)
    {
        fifo.push(liczby[i]);
    }

    stop=chrono::high_resolution_clock::now();

    auto czas_fifo_kolejne=
        chrono::duration_cast<chrono::microseconds>
        (stop-start);


    // ==========================================
    // LIFO
    // ==========================================

    stack<int> lifo;

    // dodawanie pierwszych 100000
    start=chrono::high_resolution_clock::now();

    for(int i=0;i<ile;i++)
    {
        lifo.push(liczby[i]);
    }

    stop=chrono::high_resolution_clock::now();

    auto czas_lifo_dodawanie=
        chrono::duration_cast<chrono::microseconds>
        (stop-start);


    // sortowanie LIFO
    start=chrono::high_resolution_clock::now();

    vector<int> lifo_sort;

    while(!lifo.empty())
    {
        lifo_sort.push_back(lifo.top());

        lifo.pop();
    }

    sort(lifo_sort.begin(),lifo_sort.end());

    for(int i=0;i<ile;i++)
    {
        lifo.push(lifo_sort[i]);
    }

    stop=chrono::high_resolution_clock::now();

    auto czas_lifo_sortowanie=
        chrono::duration_cast<chrono::microseconds>
        (stop-start);


    // dodawanie kolejnych 100000
    start=chrono::high_resolution_clock::now();

    for(int i=0;i<ile;i++)
    {
        lifo.push(liczby[i]);
    }

    stop=chrono::high_resolution_clock::now();

    auto czas_lifo_kolejne=
        chrono::duration_cast<chrono::microseconds>
        (stop-start);


    // ==========================================
    // KOLEJKA Z TWOJEGO KODU
    // ==========================================

    uczen u;

    // dodawanie pierwszych 100000
    start=chrono::high_resolution_clock::now();

    for(int i=0;i<ile;i++)
    {
        u.dodaj(liczby[i]);
    }

    stop=chrono::high_resolution_clock::now();

    auto czas_kolejka_dodawanie=
        chrono::duration_cast<chrono::microseconds>
        (stop-start);


    // sortowanie kolejki
    start=chrono::high_resolution_clock::now();

    u.sort_bubble();

    stop=chrono::high_resolution_clock::now();

    auto czas_kolejka_sortowanie=
        chrono::duration_cast<chrono::microseconds>
        (stop-start);


    // dodawanie kolejnych 100000
    start=chrono::high_resolution_clock::now();

    for(int i=0;i<ile;i++)
    {
        u.dodaj(liczby[i]);
    }

    stop=chrono::high_resolution_clock::now();

    auto czas_kolejka_kolejne=
        chrono::duration_cast<chrono::microseconds>
        (stop-start);


    // ==========================================
    // DRZEWO BINARNE
    // ==========================================

    drzewo d;

    // dodawanie pierwszych 100000
    start=chrono::high_resolution_clock::now();

    for(int i=0;i<ile;i++)
    {
        d.dodaj(liczby[i]);
    }

    stop=chrono::high_resolution_clock::now();

    auto czas_drzewo_dodawanie=
        chrono::duration_cast<chrono::microseconds>
        (stop-start);


    // sortowanie drzewa
    start=chrono::high_resolution_clock::now();

    d.sortuj();

    stop=chrono::high_resolution_clock::now();

    auto czas_drzewo_sortowanie=
        chrono::duration_cast<chrono::microseconds>
        (stop-start);


    // dodawanie kolejnych 100000
    start=chrono::high_resolution_clock::now();

    for(int i=0;i<ile;i++)
    {
        d.dodaj(liczby[i]);
    }

    stop=chrono::high_resolution_clock::now();

    auto czas_drzewo_kolejne=
        chrono::duration_cast<chrono::microseconds>
        (stop-start);


    // ==========================================
    // WYSWIETLANIE CZASOW
    // ==========================================

    cout<<endl;
    cout<<"========================================"<<endl;
    cout<<"              CZASY OPERACJI"<<endl;
    cout<<"========================================"<<endl;


    cout<<endl;
    cout<<"Zwykla tablica:"<<endl;

    cout<<"Dodawanie 100000: "
        <<czas_tablica_dodawanie.count()
        <<" us"<<endl;

    cout<<"Sortowanie: "
        <<czas_tablica_sortowanie.count()
        <<" us"<<endl;

    cout<<"Dodawanie kolejnych 100000: "
        <<czas_tablica_kolejne.count()
        <<" us"<<endl;


    cout<<endl;
    cout<<"Vector:"<<endl;

    cout<<"Dodawanie 100000: "
        <<czas_vector_dodawanie.count()
        <<" us"<<endl;

    cout<<"Sortowanie: "
        <<czas_vector_sortowanie.count()
        <<" us"<<endl;

    cout<<"Dodawanie kolejnych 100000: "
        <<czas_vector_kolejne.count()
        <<" us"<<endl;


    cout<<endl;
    cout<<"FIFO:"<<endl;

    cout<<"Dodawanie 100000: "
        <<czas_fifo_dodawanie.count()
        <<" us"<<endl;

    cout<<"Sortowanie: "
        <<czas_fifo_sortowanie.count()
        <<" us"<<endl;

    cout<<"Dodawanie kolejnych 100000: "
        <<czas_fifo_kolejne.count()
        <<" us"<<endl;


    cout<<endl;
    cout<<"LIFO:"<<endl;

    cout<<"Dodawanie 100000: "
        <<czas_lifo_dodawanie.count()
        <<" us"<<endl;

    cout<<"Sortowanie: "
        <<czas_lifo_sortowanie.count()
        <<" us"<<endl;

    cout<<"Dodawanie kolejnych 100000: "
        <<czas_lifo_kolejne.count()
        <<" us"<<endl;


    cout<<endl;
    cout<<"Kolejka z kodu:"<<endl;

    cout<<"Dodawanie 100000: "
        <<czas_kolejka_dodawanie.count()
        <<" us"<<endl;

    cout<<"Sortowanie: "
        <<czas_kolejka_sortowanie.count()
        <<" us"<<endl;

    cout<<"Dodawanie kolejnych 100000: "
        <<czas_kolejka_kolejne.count()
        <<" us"<<endl;


    cout<<endl;
    cout<<"Drzewo binarne:"<<endl;

    cout<<"Dodawanie 100000: "
        <<czas_drzewo_dodawanie.count()
        <<" us"<<endl;

    cout<<"Sortowanie: "
        <<czas_drzewo_sortowanie.count()
        <<" us"<<endl;

    cout<<"Dodawanie kolejnych 100000: "
        <<czas_drzewo_kolejne.count()
        <<" us"<<endl;


    return 0;
}
