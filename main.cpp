#include <iostream>
#include <vector>
#include <list>
#include <stack>
#include <algorithm>
#include <chrono>
#include <cstdlib>
#include <ctime>
#include <iomanip>

using namespace std;

const int N = 100000;

int liczby[N];
int dodatkowe[N];
int tablica[2 * N];

vector<int> wektor;
list<int> kolejkaFIFO;
stack<int> stosLIFO;

class MojaKolejka
{
private:
    int tab[N];
    int poczatek;
    int koniec;

public:
    MojaKolejka()
    {
        poczatek = 0;
        koniec = 0;
    }

    void reset()
    {
        poczatek = 0;
        koniec = 0;
    }

    void dodaj(int liczba)
    {
        if (koniec < N)
        {
            tab[koniec] = liczba;
            koniec++;
        }
    }

    bool pusta()
    {
        return poczatek == koniec;
    }

    void sortowanieBabelkowe()
    {
        int rozmiar = koniec - poczatek;

        for (int i = 0; i < rozmiar - 1; i++)
        {
            bool zamiana = false;

            for (int j = 0; j < rozmiar - i - 1; j++)
            {
                if (tab[poczatek + j] > tab[poczatek + j + 1])
                {
                    int temp = tab[poczatek + j];
                    tab[poczatek + j] = tab[poczatek + j + 1];
                    tab[poczatek + j + 1] = temp;

                    zamiana = true;
                }
            }

            if (!zamiana)
            {
                break;
            }
        }
    }
};

MojaKolejka mojaKolejka;

struct Wezel
{
    int wartosc;
    Wezel* lewy;
    Wezel* prawy;
};

Wezel* utworzWezel(int wartosc)
{
    Wezel* nowy = new Wezel;

    nowy->wartosc = wartosc;
    nowy->lewy = nullptr;
    nowy->prawy = nullptr;

    return nowy;
}

Wezel* dodajDoDrzewa(Wezel* korzen, int wartosc)
{
    if (korzen == nullptr)
    {
        return utworzWezel(wartosc);
    }

    Wezel* aktualny = korzen;

    while (true)
    {
        if (wartosc < aktualny->wartosc)
        {
            if (aktualny->lewy == nullptr)
            {
                aktualny->lewy = utworzWezel(wartosc);
                break;
            }

            aktualny = aktualny->lewy;
        }
        else
        {
            if (aktualny->prawy == nullptr)
            {
                aktualny->prawy = utworzWezel(wartosc);
                break;
            }

            aktualny = aktualny->prawy;
        }
    }

    return korzen;
}

void usunDrzewo(Wezel* korzen)
{
    if (korzen == nullptr)
    {
        return;
    }

    vector<Wezel*> stos;
    stos.reserve(N);
    stos.push_back(korzen);

    while (!stos.empty())
    {
        Wezel* aktualny = stos.back();
        stos.pop_back();

        if (aktualny->lewy != nullptr)
        {
            stos.push_back(aktualny->lewy);
        }

        if (aktualny->prawy != nullptr)
        {
            stos.push_back(aktualny->prawy);
        }

        delete aktualny;
    }
}

Wezel* korzen = nullptr;

void tablicaWstawianie()
{
    for (int i = 0; i < N; i++)
    {
        tablica[i] = liczby[i];
    }
}

void tablicaSortowanie()
{
    sort(tablica, tablica + N);
}

void tablicaDodawanie()
{
    int rozmiar = N;

    for (int i = 0; i < N; i++)
    {
        int liczba = dodatkowe[i];
        int j = rozmiar - 1;

        while (j >= 0 && tablica[j] > liczba)
        {
            tablica[j + 1] = tablica[j];
            j--;
        }

        tablica[j + 1] = liczba;
        rozmiar++;
    }
}

void wektorWstawianie()
{
    wektor.clear();
    wektor.reserve(2 * N);

    for (int i = 0; i < N; i++)
    {
        wektor.push_back(liczby[i]);
    }
}

void wektorSortowanie()
{
    sort(wektor.begin(), wektor.end());
}

void wektorDodawanie()
{
    for (int i = 0; i < N; i++)
    {
        int liczba = dodatkowe[i];
        int j = static_cast<int>(wektor.size()) - 1;

        wektor.push_back(0);

        while (j >= 0 && wektor[j] > liczba)
        {
            wektor[j + 1] = wektor[j];
            j--;
        }

        wektor[j + 1] = liczba;
    }
}

void fifoWstawianie()
{
    kolejkaFIFO.clear();

    for (int i = 0; i < N; i++)
    {
        kolejkaFIFO.push_back(liczby[i]);
    }
}

void fifoSortowanie()
{
    kolejkaFIFO.sort();
}

void lifoWstawianie()
{
    while (!stosLIFO.empty())
    {
        stosLIFO.pop();
    }

    for (int i = 0; i < N; i++)
    {
        stosLIFO.push(liczby[i]);
    }
}

void lifoSortowanie()
{
    vector<int> temp;

    while (!stosLIFO.empty())
    {
        temp.push_back(stosLIFO.top());
        stosLIFO.pop();
    }

    sort(temp.begin(), temp.end());

    for (int i = static_cast<int>(temp.size()) - 1; i >= 0; i--)
    {
        stosLIFO.push(temp[i]);
    }
}

void mojaKolejkaWstawianie()
{
    mojaKolejka.reset();

    for (int i = 0; i < N; i++)
    {
        mojaKolejka.dodaj(liczby[i]);
    }
}

void mojaKolejkaSortowanie()
{
    mojaKolejka.sortowanieBabelkowe();
}

void drzewoWstawianie()
{
    korzen = nullptr;

    for (int i = 0; i < N; i++)
    {
        korzen = dodajDoDrzewa(korzen, liczby[i]);
    }
}

void drzewoSortowanie()
{
    vector<int> wartosci;
    wartosci.reserve(N);

    vector<Wezel*> stos;
    stos.push_back(korzen);

    while (!stos.empty())
    {
        Wezel* aktualny = stos.back();
        stos.pop_back();

        if (aktualny == nullptr)
        {
            continue;
        }

        wartosci.push_back(aktualny->wartosc);

        stos.push_back(aktualny->lewy);
        stos.push_back(aktualny->prawy);
    }

    sort(wartosci.begin(), wartosci.end());
}

long long zmierz(void (*funkcja)())
{
    auto start = chrono::steady_clock::now();

    funkcja();

    auto koniec = chrono::steady_clock::now();

    return chrono::duration_cast<chrono::nanoseconds>(koniec - start).count();
}

void pokazCzas(long long czas)
{
    if (czas < 1000000)
    {
        cout << "Czas: " << czas << " ns\n";
    }
    else if (czas < 1000000000)
    {
        cout << fixed << setprecision(3);
        cout << "Czas: " << czas / 1000000.0 << " ms\n";
    }
    else
    {
        cout << fixed << setprecision(3);
        cout << "Czas: " << czas / 1000000000.0 << " s\n";
    }
}

int main()
{
    srand(static_cast<unsigned int>(time(nullptr)));

    for (int i = 0; i < N; i++)
    {
        liczby[i] = rand();
    }

    for (int i = 0; i < N; i++)
    {
        dodatkowe[i] = rand();
    }

    cout << "ZWYKLA TABLICA\n";

    cout << "Wstawianie 100000 liczb:\n";
    pokazCzas(zmierz(tablicaWstawianie));

    tablicaWstawianie();

    cout << "Sortowanie:\n";
    pokazCzas(zmierz(tablicaSortowanie));

    tablicaSortowanie();

    cout << "Dodawanie kolejnych 100000:\n";
    pokazCzas(zmierz(tablicaDodawanie));

    cout << "\nVECTOR\n";

    cout << "Wstawianie 100000 liczb:\n";
    pokazCzas(zmierz(wektorWstawianie));

    wektorWstawianie();

    cout << "Sortowanie:\n";
    pokazCzas(zmierz(wektorSortowanie));

    wektorSortowanie();

    cout << "Dodawanie kolejnych 100000:\n";
    pokazCzas(zmierz(wektorDodawanie));

    cout << "\nFIFO - LIST\n";

    cout << "Wstawianie 100000 liczb:\n";
    pokazCzas(zmierz(fifoWstawianie));

    fifoWstawianie();

    cout << "Sortowanie:\n";
    pokazCzas(zmierz(fifoSortowanie));

    cout << "\nLIFO - STACK\n";

    cout << "Wstawianie 100000 liczb:\n";
    pokazCzas(zmierz(lifoWstawianie));

    lifoWstawianie();

    cout << "Sortowanie:\n";
    pokazCzas(zmierz(lifoSortowanie));

    cout << "\nWLASNA KOLEJKA\n";

    cout << "Wstawianie 100000 liczb:\n";
    pokazCzas(zmierz(mojaKolejkaWstawianie));

    mojaKolejkaWstawianie();

    cout << "Sortowanie babelkowe:\n";
    pokazCzas(zmierz(mojaKolejkaSortowanie));

    cout << "\nDRZEWO BINARNE\n";

    cout << "Wstawianie 100000 liczb:\n";
    pokazCzas(zmierz(drzewoWstawianie));

    cout << "Sortowanie:\n";
    pokazCzas(zmierz(drzewoSortowanie));

    usunDrzewo(korzen);

    return 0;
}
