#include <iostream>
#include <cstdlib>
#include <ctime>
#include <random>

using namespace std;

// Definicja struktury dla listy dwukierunkowej
struct lista2
{
    int liczba;
    struct lista2 *next; // wskaŸnik na nastêpny element
    struct lista2 *prev; // wskaŸnik na poprzedni element
};

// Funkcja dodaj¹ca nowy element na sam pocz¹tek listy
void dodajNaPoczatek(struct lista2 *&start, int wartosc)
{
    struct lista2 *nowy = new struct lista2;
    nowy->liczba = wartosc;
    nowy->prev = NULL;
    nowy->next = start;

    if (start != NULL)
    {
        start->prev = nowy;
    }
    start = nowy;
}

// Funkcja usuwaj¹ca ca³¹ listê z pamiêci (zapobiega wyciekom RAM-u)
void zwolnijPamiec(struct lista2 *&start)
{
    while (start != NULL)
    {
        struct lista2 *temp = start;
        start = start->next;
        delete temp;
    }
}

// Sortowanie listy dwukierunkowej (szukanie MAX i przepinanie wskaŸników)
void sortujListe2(struct lista2 *&start)
{
    if (start == NULL) return;

    struct lista2 *pierwszy = start;

    while (pierwszy != NULL && pierwszy->next != NULL)
    {
        struct lista2 *maxWsk = pierwszy;
        struct lista2 *a = pierwszy->next;

        // Szukamy najwiêkszej liczby w pozosta³ej czêœci listy
        while (a != NULL)
        {
            if (a->liczba > maxWsk->liczba)
            {
                maxWsk = a;
            }
            a = a->next;
        }

        // Jeœli znaleŸliœmy wiêkszy element, przestawiamy wskaŸniki
        if (maxWsk != pierwszy)
        {
            struct lista2 *pPrev = pierwszy->prev;
            struct lista2 *pNext = pierwszy->next;
            struct lista2 *mPrev = maxWsk->prev;
            struct lista2 *mNext = maxWsk->next;

            if (pierwszy->next == maxWsk) // Przypadek: elementy s¹ obok siebie
            {
                if (pPrev != NULL) pPrev->next = maxWsk;
                else start = maxWsk;

                maxWsk->prev = pPrev;
                maxWsk->next = pierwszy;
                pierwszy->prev = maxWsk;
                pierwszy->next = mNext;

                if (mNext != NULL) mNext->prev = pierwszy;
            }
            else // Przypadek: elementy s¹ oddalone od siebie
            {
                if (pPrev != NULL) pPrev->next = maxWsk;
                else start = maxWsk;

                maxWsk->prev = pPrev;
                maxWsk->next = pNext;
                pNext->prev = maxWsk;

                mPrev->next = pierwszy;
                pierwszy->prev = mPrev;
                pierwszy->next = mNext;

                if (mNext != NULL) mNext->prev = pierwszy;
            }

            pierwszy = maxWsk->next;
        }
        else
        {
            pierwszy = pierwszy->next;
        }
    }
}

// Sortowanie tradycyjnej tablicy (wybór elementu MAX)
void sortujTablice(int tab[], int n)
{
    for (int i = 0; i < n - 1; i++)
    {
        int maxIdx = i;
        for (int j = i + 1; j < n; j++)
        {
            if (tab[j] > tab[maxIdx])
            {
                maxIdx = j;
            }
        }
        if (maxIdx != i)
        {
            int temp = tab[i];
            tab[i] = tab[maxIdx];
            tab[maxIdx] = temp;
        }
    }
}

int main()
{
    // Inicjalizator generatora liczb losowych
    random_device rd;
    srand(rd());

    const int N = 50000; // Liczba elementów do przetestowania

    struct lista2 *start = NULL;
    int *tab = new int[N];

    // Wype³nienie obu struktur identycznymi danymi losowymi
    for (int i = 0; i < N; i++)
    {
        int losowa = rand() % 100000;
        tab[i] = losowa;
        dodajNaPoczatek(start, losowa);
    }

    cout << "Test wydajnosci dla " << N << " liczb (insert sort / szukanie MAX):\n" << endl;

    // 1. Pomiar czasu dla tradycyjnej tablicy
    clock_t startTab = clock();
    sortujTablice(tab, N);
    clock_t stopTab = clock();
    double czasTab = (double)(stopTab - startTab) / CLOCKS_PER_SEC;
    cout << "Insert Sort (tablica): " << czasTab << " s" << endl;

    // 2. Pomiar czasu dla listy dwukierunkowej
    clock_t startLista = clock();
    sortujListe2(start);
    clock_t stopLista = clock();
    double czasLista = (double)(stopLista - startLista) / CLOCKS_PER_SEC;
    cout << "Szukanie MAX (lista dwukierunkowa): " << czasLista << " s" << endl;

    // Podsumowanie wyników i najwiêksza liczba
    cout << "\nNajwieksza liczba ogolnie w strukturach: " << tab[0] << endl;
    cout << "Czas znalezienia i posortowania: "
         << (double)((stopTab - startTab) + (stopLista - startLista)) / CLOCKS_PER_SEC << " s" << endl;

    // Czyszczenie pamiêci dynamicznej
    delete[] tab;
    zwolnijPamiec(start);

    return 0;
}
