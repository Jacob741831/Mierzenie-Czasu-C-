Jasne — tutaj README trzeba zmienić dość mocno, bo aktualny program porównuje **6 struktur**, wykonuje **3 rodzaje operacji** i ma kilka istotnych różnic względem poprzedniej wersji. Poniżej masz gotowe README do wklejenia do `README.md`.

README.md

# Pomiar czasu operacji na strukturach danych w C++

## Opis projektu

Program służy do porównania czasu wykonywania podstawowych operacji na różnych strukturach danych w języku C++.

Program testuje:

1. **Zwykłą tablicę**
2. **Vector (****`vector`****)**
3. **Kolejkę FIFO (****`queue`****)**
4. **Stos LIFO (****`stack`****)**
5. **Własną kolejkę opartą na liście jednokierunkowej**
6. **Drzewo binarne**

Dla każdej struktury wykonywane są trzy pomiary:

- dodawanie pierwszych **100 000 elementów**,
- sortowanie **100 000 elementów**,
- dodawanie kolejnych **100 000 elementów**.

Wyniki pomiarów są wyświetlane w konsoli w mikrosekundach (`us`).

---

# Liczba elementów

W programie liczba elementów jest określona przez:

```
const int ile=100000;
```

Oznacza to, że podstawowy test wykonywany jest dla **100 000 liczb**.

Liczby są generowane losowo:

```
srand(time(NULL));

for(int i=0;i<ile;i++)
{
    liczby[i]=rand()%1000000;
}
```

Każda liczba znajduje się w zakresie:

```
0 - 999999
```

Ważne jest to, że wszystkie testowane struktury otrzymują **ten sam zestaw 100 000 wylosowanych liczb**.

Dzięki temu wyniki można ze sobą porównywać.

---

# Testowane struktury danych

## 1\. Zwykła tablica

Program wykorzystuje tablicę:

```
int tablica[200000];
```

Pierwsze 100 000 elementów jest zapisywane za pomocą:

```
tablica[i]=liczby[i];
```

Następnie tablica jest sortowana:

```
sort(tablica,tablica+ile);
```

Po sortowaniu program dodaje kolejne 100 000 elementów:

```
tablica[ile+i]=liczby[i];
```

### Mierzone operacje

- dodawanie pierwszych 100 000 elementów,
- sortowanie,
- dodawanie kolejnych 100 000 elementów.

---

# 2\. Vector

Program wykorzystuje standardowy kontener:

```
vector<int> v;
```

Elementy są dodawane za pomocą:

```
v.push_back(liczby[i]);
```

Następnie vector jest sortowany:

```
sort(v.begin(),v.end());
```

Po sortowaniu do vectora ponownie dodawane jest kolejne 100 000 elementów.

### Mierzone operacje

- dodawanie pierwszych 100 000 elementów,
- sortowanie,
- dodawanie kolejnych 100 000 elementów.

---

# 3\. Kolejka FIFO

Program wykorzystuje standardową kolejkę:

```
queue<int> fifo;
```

Elementy są dodawane za pomocą:

```
fifo.push(liczby[i]);
```

Kolejka działa zgodnie z zasadą **FIFO** (_First In, First Out_), czyli pierwszy dodany element jest pierwszym usuwanym elementem.

## Sortowanie kolejki

`queue` nie udostępnia bezpośredniego dostępu do wszystkich swoich elementów.

Dlatego podczas sortowania elementy są przenoszone do pomocniczego vectora:

```
vector<int> fifo_sort;
```

Elementy są pobierane z kolejki:

```
while(!fifo.empty())
{
    fifo_sort.push_back(fifo.front());
    fifo.pop();
}
```

Następnie vector jest sortowany:

```
sort(fifo_sort.begin(),fifo_sort.end());
```

Po sortowaniu elementy są ponownie umieszczane w kolejce:

```
for(int i=0;i<ile;i++)
{
    fifo.push(fifo_sort[i]);
}
```

Dlatego czas sortowania FIFO obejmuje nie tylko samo `sort()`, ale również:

1. przeniesienie elementów z kolejki do vectora,
2. sortowanie vectora,
3. ponowne zapełnienie kolejki.

---

# 4\. Stos LIFO

Program wykorzystuje standardowy stos:

```
stack<int> lifo;
```

Elementy są dodawane za pomocą:

```
lifo.push(liczby[i]);
```

Stos działa zgodnie z zasadą **LIFO** (_Last In, First Out_), czyli ostatni dodany element jest pierwszym usuwanym elementem.

## Sortowanie stosu

Podobnie jak `queue`, standardowy `stack` nie umożliwia bezpośredniego dostępu do wszystkich elementów.

Dlatego podczas sortowania elementy są przenoszone do pomocniczego vectora:

```
vector<int> lifo_sort;
```

Elementy są pobierane ze stosu:

```
while(!lifo.empty())
{
    lifo_sort.push_back(lifo.top());
    lifo.pop();
}
```

Następnie vector jest sortowany:

```
sort(lifo_sort.begin(),lifo_sort.end());
```

Po sortowaniu elementy są ponownie umieszczane na stosie.

Czas sortowania obejmuje więc:

1. zdejmowanie elementów ze stosu,
2. zapisanie ich do vectora,
3. sortowanie vectora,
4. ponowne dodanie elementów do stosu.

---

# 5\. Własna kolejka oparta na liście jednokierunkowej

Program posiada również własną implementację kolejki.

Element kolejki jest reprezentowany przez strukturę:

```
struct kolejka
{
    int nr;
    kolejka* nastepny;
};
```

Każdy element przechowuje:

- `nr` – wartość elementu,
- `nastepny` – wskaźnik na kolejny element.

Za obsługę kolejki odpowiada klasa:

```
class uczen
```

Klasa posiada dwa wskaźniki:

```
kolejka* poczatek;
kolejka* koniec;
```

`poczatek` wskazuje pierwszy element kolejki, a `koniec` wskazuje jej ostatni element.

---

## Funkcja `dodaj()`

Funkcja:

```
void dodaj(int nr)
```

dodaje nowy element na koniec kolejki.

Parametr:

- `nr` – wartość, która ma zostać dodana do kolejki.

Nowy element jest tworzony dynamicznie:

```
kolejka* nowy=new kolejka(nr);
```

Jeżeli kolejka jest pusta, nowy element staje się jednocześnie początkiem i końcem kolejki.

W przeciwnym przypadku zostaje dopięty na końcu:

```
koniec->nastepny=nowy;
koniec=nowy;
```

---

## Funkcja `sort_bubble()`

Funkcja:

```
void sort_bubble()
```

sortuje elementy własnej kolejki za pomocą **sortowania bąbelkowego (Bubble Sort)**.

Algorytm porównuje sąsiednie elementy:

```
if(temp->nr>temp->nastepny->nr)
```

Jeżeli elementy są w złej kolejności, ich wartości zostają zamienione.

W odróżnieniu od `queue`, sortowanie tej kolejki odbywa się bez przenoszenia elementów do vectora.

### Złożoność

Bubble Sort ma średnią i pesymistyczną złożoność:

```
O(n²)
```

Przy 100 000 elementów może to powodować bardzo długi czas działania programu.

---

## Destruktor `uczen`

Destruktor:

```
~uczen()
```

usuwa wszystkie elementy kolejki utworzone za pomocą `new`.

Dzięki temu pamięć zajmowana przez elementy listy zostaje zwolniona.

---

# 6\. Drzewo binarne

Program posiada również własną implementację drzewa binarnego.

Pojedynczy element drzewa reprezentuje struktura:

```
struct Lisc
{
    int wartosc;

    Lisc* lewy;
    Lisc* prawy;
};
```

Każdy element przechowuje:

- `wartosc` – wartość liczbową,
- `lewy` – wskaźnik na lewe poddrzewo,
- `prawy` – wskaźnik na prawe poddrzewo.

Za obsługę drzewa odpowiada klasa:

```
class drzewo
```

Korzeń drzewa jest przechowywany w:

```
Lisc* korzen;
```

---

## Funkcja `dodaj()`

Drzewo posiada dwie wersje funkcji `dodaj()`.

### Wersja rekurencyjna

```
Lisc* dodaj(Lisc* korzen, int wartosc)
```

Parametry:

- `korzen` – korzeń aktualnie sprawdzanego poddrzewa,
- `wartosc` – wartość, która ma zostać dodana.

Jeżeli drzewo jest puste, tworzony jest nowy element.

Jeżeli dodawana wartość jest mniejsza od wartości w aktualnym węźle, przechodzi do lewego poddrzewa:

```
if(wartosc<korzen->wartosc)
{
    korzen->lewy=dodaj(korzen->lewy,wartosc);
}
```

W przeciwnym przypadku przechodzi do prawego poddrzewa:

```
else
{
    korzen->prawy=dodaj(korzen->prawy,wartosc);
}
```

### Wersja publiczna

```
void dodaj(int wartosc)
```

Dodaje wartość do całego drzewa:

```
korzen=dodaj(korzen,wartosc);
```

---

# Sortowanie drzewa

Funkcja:

```
void sortuj()
```

wykorzystuje funkcję:

```
void przejdz(Lisc* korzen, vector<int>& tab)
```

Funkcja `przejdz()` wykonuje przejście drzewa **in-order**:

1. lewe poddrzewo,
2. aktualny węzeł,
3. prawe poddrzewo.

Wartości są zapisywane do vectora:

```
tab.push_back(korzen->wartosc);
```

Następnie vector jest sortowany:

```
sort(tab.begin(),tab.end());
```

### Ważna uwaga

W obecnej wersji programu wynik posortowany w vectorze nie jest zapisywany z powrotem do drzewa.

Oznacza to, że funkcja `sortuj()` wykonuje przejście drzewa i sortowanie pomocniczego vectora, ale nie zmienia fizycznej struktury drzewa.

---

# Usuwanie drzewa

Funkcja:

```
void usun(Lisc* korzen)
```

rekurencyjnie usuwa wszystkie elementy drzewa.

Najpierw usuwane są:

1. lewe poddrzewo,
2. prawe poddrzewo,
3. aktualny element.

Destruktor:

```
~drzewo()
```

wywołuje funkcję `usun()`, dzięki czemu pamięć zajmowana przez drzewo zostaje zwolniona po zakończeniu programu.

---

# Pomiar czasu

Do pomiaru czasu wykorzystano:

```
chrono::high_resolution_clock
```

Pomiar rozpoczyna się za pomocą:

```
start=chrono::high_resolution_clock::now();
```

Po zakończeniu operacji pobierany jest czas końcowy:

```
stop=chrono::high_resolution_clock::now();
```

Następnie różnica jest zamieniana na mikrosekundy:

```
chrono::duration_cast<chrono::microseconds>
(stop-start);
```

Wyniki są więc przedstawiane w jednostce:

```
us
```

czyli mikrosekundach.

---

# Wykonywane pomiary

Dla każdej struktury wykonywane są trzy pomiary.

## 1\. Dodawanie pierwszych 100 000 elementów

Program mierzy czas potrzebny na zapisanie 100 000 wylosowanych liczb w danej strukturze.

Przykładowo dla vectora:

```
for(int i=0;i<ile;i++)
{
    v.push_back(liczby[i]);
}
```

---

## 2\. Sortowanie

Po dodaniu pierwszych 100 000 elementów struktura jest sortowana.

W zależności od struktury stosowana jest inna metoda:

| Struktura | Sposób sortowania |
| --- | --- |
| Zwykła tablica | `std::sort()` |
| Vector | `std::sort()` |
| FIFO | Vector pomocniczy + `std::sort()` |
| LIFO | Vector pomocniczy + `std::sort()` |
| Własna kolejka | Bubble Sort |
| Drzewo binarne | Przejście in-order + `std::sort()` vectora |

---

## 3\. Dodawanie kolejnych 100 000 elementów

Po wykonaniu sortowania program dodaje do każdej struktury kolejne 100 000 elementów.

Dzięki temu można sprawdzić, jak struktura zachowuje się po wcześniejszym wypełnieniu i wykonaniu sortowania.

---

# Przebieg programu

Po uruchomieniu programu wykonywane są kolejno następujące czynności:

```
1. Ustalenie liczby elementów na 100 000
2. Wylosowanie 100 000 liczb
3. Pomiar dodawania do zwykłej tablicy
4. Pomiar sortowania tablicy
5. Pomiar dodawania kolejnych elementów do tablicy

6. Pomiar dodawania do vectora
7. Pomiar sortowania vectora
8. Pomiar dodawania kolejnych elementów do vectora

9. Pomiar dodawania do FIFO
10. Pomiar sortowania FIFO
11. Pomiar dodawania kolejnych elementów do FIFO

12. Pomiar dodawania do LIFO
13. Pomiar sortowania LIFO
14. Pomiar dodawania kolejnych elementów do LIFO

15. Pomiar dodawania do własnej kolejki
16. Pomiar sortowania własnej kolejki
17. Pomiar dodawania kolejnych elementów do własnej kolejki

18. Pomiar dodawania do drzewa binarnego
19. Pomiar sortowania drzewa
20. Pomiar dodawania kolejnych elementów do drzewa

21. Wyświetlenie wszystkich wyników
```

---

# Przykładowy wynik

Przykładowy wynik programu może wyglądać następująco:

```
========================================
              CZASY OPERACJI
========================================

Zwykla tablica:
Dodawanie 100000: 150 us
Sortowanie: 6500 us
Dodawanie kolejnych 100000: 140 us

Vector:
Dodawanie 100000: 900 us
Sortowanie: 6200 us
Dodawanie kolejnych 100000: 700 us

FIFO:
Dodawanie 100000: 1200 us
Sortowanie: 8500 us
Dodawanie kolejnych 100000: 1100 us

LIFO:
Dodawanie 100000: 800 us
Sortowanie: 8200 us
Dodawanie kolejnych 100000: 750 us

Kolejka z kodu:
Dodawanie 100000: 4500 us
Sortowanie: ...
Dodawanie kolejnych 100000: 4000 us

Drzewo binarne:
Dodawanie 100000: 12000 us
Sortowanie: 7000 us
Dodawanie kolejnych 100000: 11000 us
```

Powyższe wartości są **wyłącznie przykładowe**. Rzeczywiste wyniki zależą od komputera, kompilatora, optymalizacji i obciążenia systemu.

---

# Jednostka czasu

Program wyświetla wyniki w:

```
us
```

czyli mikrosekundach.

Przeliczenie jednostek:

```
1 sekunda = 1 000 000 us
1 milisekunda = 1 000 us
```

---

# Ważna uwaga dotycząca własnej kolejki

Własna kolejka wykorzystuje sortowanie bąbelkowe:

```
void sort_bubble()
```

Bubble Sort posiada złożoność:

```
O(n²)
```

Dla:

```
n = 100 000
```

oznacza to bardzo dużą liczbę porównań.

W praktyce sortowanie 100 000 losowych elementów za pomocą Bubble Sort może trwać **bardzo długo** w porównaniu z `std::sort()`.

Jest to celowe w tym projekcie, ponieważ pozwala pokazać różnicę pomiędzy prostym algorytmem sortowania a wydajniejszym `std::sort()`.

---

# Ważna uwaga dotycząca drzewa binarnego

Drzewo jest budowane poprzez kolejne wywołania:

```
d.dodaj(liczby[i]);
```

Elementy mniejsze od aktualnego węzła trafiają do lewego poddrzewa, a większe lub równe do prawego.

W przypadku niekorzystnego układu danych drzewo może stać się bardzo podobne do listy jednokierunkowej.

Wtedy operacje na drzewie mogą być znacznie wolniejsze.

Ponieważ liczby są losowe, kształt drzewa może być różny przy każdym uruchomieniu programu.

---

# Ważna uwaga dotycząca pomiarów

Czas działania programu może być różny przy każdym uruchomieniu.

Na wyniki wpływają między innymi:

- procesor,
- pamięć RAM,
- kompilator,
- poziom optymalizacji,
- obciążenie systemu,
- inne uruchomione programy,
- sposób generowania liczb losowych,
- aktualny stan pamięci.

Dlatego pojedynczy pomiar nie powinien być traktowany jako absolutny wynik.

Dla dokładniejszego porównania warto uruchomić program kilka razy i porównać otrzymane wyniki.

---

# Kompilacja

Program wymaga kompilatora obsługującego standard C++11 lub nowszy.

Przykład kompilacji przy użyciu `g++`:

```
g++ -std=c++11 -O2 main.cpp -o program
```

Uruchomienie w systemie Linux:

```
./program
```

W systemie Windows:

```
program.exe
```

---

# Wykorzystane biblioteki

Program wykorzystuje następujące biblioteki:

```
#include <iostream>
#include <vector>
#include <stack>
#include <queue>
#include <chrono>
#include <cstdlib>
#include <ctime>
#include <algorithm>
```

Ich zastosowanie:

| Biblioteka | Zastosowanie |
| --- | --- |
| `<iostream>` | Wyświetlanie wyników w konsoli |
| `<vector>` | Kontener dynamiczny oraz pomocnicze tablice |
| `<stack>` | Standardowy stos LIFO |
| `<queue>` | Standardowa kolejka FIFO |
| `<chrono>` | Pomiar czasu |
| `<cstdlib>` | `rand()` i `srand()` |
| `<ctime>` | Pobranie aktualnego czasu dla generatora liczb |
| `<algorithm>` | Funkcja `sort()` |

---

# Podsumowanie

Celem projektu jest praktyczne porównanie wydajności różnych struktur danych oraz sposobów sortowania.

Program pozwala porównać:

- zwykłą tablicę,
- `vector`,
- kolejkę FIFO,
- stos LIFO,
- własną kolejkę opartą na liście jednokierunkowej,
- drzewo binarne.

Dla każdej struktury mierzone są:

1. czas dodania pierwszych 100 000 elementów,
2. czas sortowania,
3. czas dodania kolejnych 100 000 elementów.

Projekt pokazuje, że wybór struktury danych oraz algorytmu ma duży wpływ na czas wykonywania programu.

Szczególnie widoczna jest różnica pomiędzy:

```
std::sort()
```

a:

```
Bubble Sort
```

przy dużej liczbie elementów.

W komentarzach przy funkcjach i ich parametrach opisane jest, **co dany parametr oznacza i do czego służy**. W tym programie liczba testowanych elementów jest ustalona przez:

```
const int ile=100000;
```

dlatego większość funkcji nie wymaga przekazywania liczby elementów jako parametru.

Jedna ważna rzecz: w Twoim kodzie `drzewo::sortuj()` **nie sortuje faktycznie drzewa** — tylko tworzy vector, przechodzi po drzewie i sortuje ten vector, a wynik jest potem wyrzucany. README powyżej opisuje to zgodnie z rzeczywistym działaniem kodu, żeby nie było rozbieżności między dokumentacją a programem.
