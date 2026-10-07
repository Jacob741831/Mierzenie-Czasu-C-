# Pomiar czasu sortowania struktur danych w C++

 ## Opis projektu

 Program służy do porównania czasu wykonywania operacji na trzech różnych strukturach danych:

 1. **Kolejka (`queue`)**
2. **Stos zbudowany na liście jednokierunkowej**
3. **Zwykła tablica dynamiczna**

 Program pracuje na **100 000 elementach**.

 Po uruchomieniu wykonywane są automatycznie dwa testy:

 - pomiar czasu wpisywania elementów,
- pomiar czasu sortowania elementów.

 Wyniki są wyświetlane w konsoli.

---

 ## Struktura programu

 Program został napisany obiektowo i wykorzystuje kilka klas.

 ### Klasa `StackList`

 Klasa implementuje stos przy użyciu listy jednokierunkowej.

 Podstawowe operacje:

 - `push()` – dodaje element na szczyt stosu,
- `pop()` – usuwa element ze szczytu stosu,
- `top()` – zwraca element znajdujący się na szczycie,
- `empty()` – sprawdza, czy stos jest pusty,
- `clear()` – usuwa wszystkie elementy,
- `sortStack()` – sortuje elementy stosu.

 Stos wykorzystuje własną strukturę:

```
struct Node
{
    int value;
    Node* next;
};
```

 Każdy element listy przechowuje wartość oraz wskaźnik na następny element.

---

 ## Klasa `Timer`

 Klasa `Timer` odpowiada za mierzenie czasu wykonywania operacji.

 Posiada dwie funkcje:

 ### `start()`

 Rozpoczyna pomiar czasu.

 ### `stop()`

 Kończy pomiar i zwraca czas wykonania operacji w mikrosekundach (`us`).

 Do pomiaru wykorzystano:

```
std::chrono::steady_clock
```

---

 ## Klasa `SortingTest`

 Klasa `SortingTest` wykonuje właściwe testy.

 Przechowuje:

```
queue<int> kolejka;
StackList stos;
int* tablica;
```

 Dodatkowo przygotowuje 100 000 liczb, które są następnie używane we wszystkich trzech strukturach.

 Dzięki temu każda struktura otrzymuje taki sam zestaw danych.

---

 # Funkcja `Wypisz()`

 Funkcja `Wypisz()` odpowiada za wpisanie 100 000 elementów do każdej struktury.

 Mierzone są osobno:

 - czas dodawania elementów do kolejki,
- czas dodawania elementów do stosu,
- czas zapisywania elementów do tablicy.

 Wynik jest wyświetlany w postaci:

```
Wypisywanie:
kolejka: <czas> us
stos:    <czas> us
tablica: <czas> us
```

 ### Kolejka

 Elementy są dodawane za pomocą:

```
kolejka.push(dane[i]);
```

 ### Stos

 Elementy są dodawane za pomocą:

```
stos.push(dane[i]);
```

 ### Tablica

 Elementy są zapisywane bezpośrednio pod kolejnymi indeksami:

```
tablica[i] = dane[i];
```

---

 # Funkcja `Sortuj()`

 Funkcja `Sortuj()` sortuje wcześniej zapisane elementy.

 Mierzone są osobno:

 - czas sortowania kolejki,
- czas sortowania stosu,
- czas sortowania tablicy.

 Wynik:

```
Sortowanie:
kolejka: <czas> us
stos:    <czas> us
tablica: <czas> us
```

---

 ## Sortowanie kolejki

 Kolejka nie pozwala na bezpośredni dostęp do wszystkich elementów.

 Dlatego elementy są najpierw przenoszone do pomocniczego `vector<int>`:

```
vector<int> kolejkaDane;
```

 Następnie dane są sortowane:

```
sort(kolejkaDane.begin(), kolejkaDane.end());
```

 Na końcu elementy są ponownie dodawane do kolejki.

---

 ## Sortowanie stosu

 Elementy stosu są przenoszone do pomocniczego wektora.

 Następnie wektor jest sortowany za pomocą:

```
sort(values.begin(), values.end());
```

 Po sortowaniu stos jest ponownie budowany.

 Najmniejsza wartość znajduje się na szczycie stosu.

---

 ## Sortowanie tablicy

 Tablica jest sortowana bezpośrednio za pomocą:

```
sort(tablica, tablica + ELEMENTS);
```

---

 # Kolejność wykonywania programu

 Po uruchomieniu programu wykonywane są kolejno:

```
1. Utworzenie obiektu SortingTest
2. Wygenerowanie 100 000 liczb
3. Wpisanie liczb do kolejki
4. Wpisanie liczb do stosu
5. Wpisanie liczb do tablicy
6. Wyświetlenie czasów wpisywania
7. Sortowanie kolejki
8. Sortowanie stosu
9. Sortowanie tablicy
10. Wyświetlenie czasów sortowania
```

---

 # Przykładowy wynik

 Wartości będą różne w zależności od komputera, kompilatora i aktualnego obciążenia systemu.

 Przykładowo:

```
Wypisywanie:
kolejka: 1250 us
stos:    4200 us
tablica: 180 us

Sortowanie:
kolejka: 8200 us
stos:    10500 us
tablica: 6900 us
```

 Powyższe liczby są tylko przykładem.

---

 # Jednostka czasu

 Wyniki są podawane w:

```
us
```

 czyli mikrosekundach.

 Przeliczenie:

```
1 sekunda = 1 000 000 mikrosekund
1 milisekunda = 1 000 mikrosekund
```

---

 # Kompilacja

 Program wymaga kompilatora obsługującego standard C++11 lub nowszy.

 Przykład dla `g++`:

```
g++ -std=c++11 -O2 main.cpp -o program
```

 Uruchomienie:

```
./program
```

 W systemie Windows:

```
program.exe
```

---

 # Ważna uwaga dotycząca pomiarów

 Czas wykonywania programu może być różny przy każdym uruchomieniu.

 Na wynik wpływają między innymi:

 - procesor,
- pamięć RAM,
- optymalizacje kompilatora,
- obciążenie systemu,
- inne uruchomione programy.

 Dlatego jeden pomiar nie powinien być traktowany jako absolutny wynik.

 Dla dokładniejszego porównania warto wykonać program kilka razy i obliczyć średnią.

---

 # Cel projektu

 Celem projektu jest praktyczne porównanie sposobu działania:

 - kolejki,
- stosu opartego na liście,
- tablicy,

 pod względem:

 1. czasu dodawania 100 000 elementów,
2. czasu sortowania 100 000 elementów.

 Program pokazuje również różnice wynikające z organizacji danych w pamięci oraz sposobu dostępu do elementów.

```
:::

W komentarzach przy funkcjach i ich parametrach jest opisane **co dany parametr oznacza i do czego służy**. W tym konkretnym programie większość funkcji nie przyjmuje parametrów, ponieważ liczba elementów jest ustalona przez `ELEMENTS = 100000`.
```
