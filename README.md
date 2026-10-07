# Porównanie struktur danych i algorytmów sortowania

 ## Opis projektu

 Program w języku **C++** służy do porównania czasu wykonywania operacji na różnych strukturach danych.

 Program generuje **100 000 losowych liczb**, a następnie dla poszczególnych struktur wykonuje:

 - wstawianie 100 000 elementów,
- sortowanie elementów,
- dodawanie kolejnych 100 000 elementów do już posortowanej struktury.

 Wyniki pomiarów prezentowane są w nanosekundach, milisekundach lub sekundach.

 Celem programu jest porównanie wydajności różnych sposobów przechowywania i sortowania danych.

---

 ## Wykorzystane struktury danych

 Program porównuje następujące rozwiązania:

 ### 1\. Zwykła tablica

 Wykorzystywana jest tablica:

```
int tablica[2 * N];
```

 Najpierw kopiowane jest do niej 100 000 liczb.

 Do sortowania wykorzystywana jest funkcja:

```
sort(tablica, tablica + N);
```

 Po posortowaniu do tablicy dodawane jest kolejne 100 000 liczb. Nowe elementy są umieszczane w odpowiednich miejscach poprzez przesuwanie istniejących elementów.

---

 ### 2\. `vector<int>`

 Wykorzystywany jest kontener:

```
vector<int> wektor;
```

 Wektor otrzymuje początkowo 100 000 liczb, a następnie jest sortowany za pomocą:

```
sort(wektor.begin(), wektor.end());
```

 Kolejne 100 000 elementów jest dodawane pojedynczo do zachowania kolejności rosnącej.

 Wektor wykorzystuje pamięć ciągłą, dzięki czemu dostęp do elementów jest szybki.

---

 ### 3\. `list<int>` — FIFO

 Do reprezentacji kolejki FIFO wykorzystano:

```
list<int> kolejkaFIFO;
```

 Elementy są dodawane na koniec listy:

```
kolejkaFIFO.push_back(liczby[i]);
```

 Sortowanie wykonywane jest za pomocą:

```
kolejkaFIFO.sort();
```

 Lista dwukierunkowa pozwala na efektywne dodawanie i usuwanie elementów, ale nie zapewnia bezpośredniego dostępu do elementu o określonym indeksie.

---

 ### 4\. `stack<int>` — LIFO

 Do reprezentacji stosu wykorzystano:

```
stack<int> stosLIFO;
```

 Elementy są dodawane za pomocą:

```
stosLIFO.push(liczby[i]);
```

 Ponieważ `stack` nie posiada funkcji sortowania, dane są:

 1. zdejmowane ze stosu,
2. umieszczane w pomocniczym `vector`,
3. sortowane,
4. ponownie umieszczane na stosie.

 Dzięki temu można uzyskać posortowaną zawartość stosu.

---

 ### 5\. Własna kolejka

 Program zawiera również własną implementację kolejki:

```
class MojaKolejka
```

 Kolejka wykorzystuje zwykłą tablicę:

```
int tab[N];
```

 Elementy są dodawane za pomocą metody:

```
dodaj()
```

 Do sortowania zaimplementowano własny **algorytm sortowania bąbelkowego**.

 Algorytm porównuje sąsiednie elementy i zamienia je miejscami, jeżeli znajdują się w niewłaściwej kolejności.

 Sortowanie bąbelkowe ma złożoność:

```
O(n²)
```

 Dlatego dla 100 000 elementów może działać bardzo długo.

---

 ### 6\. Drzewo binarne

 Program wykorzystuje również własne drzewo binarne wyszukiwania:

```
struct Wezel
{
    int wartosc;
    Wezel* lewy;
    Wezel* prawy;
};
```

 Elementy są dodawane za pomocą funkcji:

```
dodajDoDrzewa()
```

 Mniejsza wartość trafia do lewego poddrzewa, a większa lub równa do prawego.

 Po utworzeniu drzewa wartości są zbierane do wektora i sortowane.

---

 ## Generowanie danych

 Na początku programu generowane jest 200 000 losowych liczb:

 - 100 000 liczb przeznaczonych do początkowego wstawiania,
- 100 000 dodatkowych liczb przeznaczonych do późniejszego dodawania.

 Liczby są generowane za pomocą:

```
rand()
```

 Inicjalizacja generatora odbywa się poprzez:

```
srand(static_cast<unsigned int>(time(nullptr)));
```

 Oznacza to, że przy każdym uruchomieniu programu zestaw liczb będzie zazwyczaj inny.

---

 ## Pomiar czasu

 Do pomiaru czasu wykorzystano:

```
chrono::steady_clock
```

 Pomiar wykonywany jest przez funkcję:

```
long long zmierz(void (*funkcja)())
```

 Funkcja zapisuje czas przed i po wykonaniu badanego działania, a następnie zwraca czas wykonania w nanosekundach.

 Wynik jest prezentowany w odpowiedniej jednostce:

 - `ns` — nanosekundy,
- `ms` — milisekundy,
- `s` — sekundy.

 Przykładowy wynik:

```
Czas: 2.315 ms
```

---

 ## Kolejność wykonywanych testów

 Program wykonuje testy w następującej kolejności:

```
ZWYKLA TABLICA
    ├── Wstawianie 100000 liczb
    ├── Sortowanie
    └── Dodawanie kolejnych 100000

VECTOR
    ├── Wstawianie 100000 liczb
    ├── Sortowanie
    └── Dodawanie kolejnych 100000

FIFO - LIST
    ├── Wstawianie 100000 liczb
    └── Sortowanie

LIFO - STACK
    ├── Wstawianie 100000 liczb
    └── Sortowanie

WLASNA KOLEJKA
    ├── Wstawianie 100000 liczb
    └── Sortowanie babelkowe

DRZEWO BINARNE
    ├── Wstawianie 100000 liczb
    └── Sortowanie
```

---

 ## Złożoność obliczeniowa

 Orientacyjna złożoność poszczególnych operacji:

 | Struktura | Wstawianie | Sortowanie | Dodawanie elementów |
| --- | --- | --- | --- |
| Tablica | O(n) | O(n log n) | O(n²) |
| `vector` | O(n) | O(n log n) | O(n²) |
| `list` | O(n) | O(n log n) | — |
| `stack` | O(n) | O(n log n) | — |
| Własna kolejka | O(n) | O(n²) | — |
| Drzewo BST | średnio O(n log n) | O(n log n) | — |

### Uwaga dotycząca drzewa

 W przypadku zwykłego drzewa BST złożoność wstawiania jednego elementu wynosi średnio:

```
O(log n)
```

 ale w najgorszym przypadku:

```
O(n)
```

 Jeżeli dane będą ułożone w niekorzystnej kolejności, drzewo może stać się praktycznie listą.

---

 ## Wymagania

 Do skompilowania programu potrzebny jest kompilator obsługujący standard C++11 lub nowszy.

 Program korzysta ze standardowych bibliotek:

```
<iostream>
<vector>
<list>
<stack>
<algorithm>
<chrono>
<cstdlib>
<ctime>
<iomanip>
```

 Nie są wymagane żadne dodatkowe biblioteki zewnętrzne.

---

 ## Kompilacja

 ### Linux / macOS

 Przykładowo przy użyciu `g++`:

```
g++ -std=c++11 -O2 main.cpp -o program
```

 Następnie:

```
./program
```

 ### Windows

 Przy użyciu MinGW:

```
g++ -std=c++11 -O2 main.cpp -o program.exe
```

 Uruchomienie:

```
program.exe
```

---

 ## Przykładowy wynik

 Wyniki będą zależne od komputera, kompilatora oraz aktualnie wygenerowanych danych.

 Przykładowa struktura wyniku:

```
ZWYKLA TABLICA
Wstawianie 100000 liczb:
Czas: ...

Sortowanie:
Czas: ...

Dodawanie kolejnych 100000:
Czas: ...

VECTOR
Wstawianie 100000 liczb:
Czas: ...

Sortowanie:
Czas: ...

Dodawanie kolejnych 100000:
Czas: ...

FIFO - LIST
Wstawianie 100000 liczb:
Czas: ...

Sortowanie:
Czas: ...

LIFO - STACK
Wstawianie 100000 liczb:
Czas: ...

Sortowanie:
Czas: ...

WLASNA KOLEJKA
Wstawianie 100000 liczb:
Czas: ...

Sortowanie babelkowe:
Czas: ...

DRZEWO BINARNE
Wstawianie 100000 liczb:
Czas: ...

Sortowanie:
Czas: ...
```

---

 ## Cel eksperymentu

 Program pozwala praktycznie porównać wydajność różnych struktur danych.

 Szczególnie widoczna powinna być różnica pomiędzy efektywnymi algorytmami sortowania o złożoności około `O(n log n)` a sortowaniem bąbelkowym `O(n²)`.

 Program pokazuje również, że wybór struktury danych ma duże znaczenie dla czasu wykonywania operacji. Ta sama operacja może być bardzo szybka dla jednej struktury i bardzo wolna dla innej.

---

 ## Ważne uwagi dotyczące implementacji

 Program został przygotowany przede wszystkim jako eksperyment porównawczy. Niektóre rozwiązania celowo są implementowane w prosty sposób, aby umożliwić obserwację różnic wydajności.

 W szczególności:

 - własna kolejka wykorzystuje sortowanie bąbelkowe,
- `stack` wymaga przeniesienia danych do pomocniczego wektora podczas sortowania,
- tablica i `vector` przesuwają elementy podczas dodawania do posortowanej struktury,
- drzewo jest zwykłym BST i nie jest samobalansujące,
- czasy mogą się różnić pomiędzy kolejnymi uruchomieniami.

 ### Uwaga dotycząca drzewa

 Przy `N = 100000` zwykłe BST może w pewnych przypadkach uzyskać bardzo niekorzystny kształt. Dla losowych danych powinno jednak działać znacznie lepiej niż całkowicie niezbalansowane drzewo.

