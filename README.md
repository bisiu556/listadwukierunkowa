# Test Wydajności: Sortowanie Listy Dwukierunkowej vs Tablica w C++

Projekt w języku C++ demonstrujący i porównujący wydajność algorytmu sortowania przez wybór (znajdowanie elementu maksymalnego) na dwóch różnych strukturach danych: **tablicy dynamicznej** oraz **dwukierunkowej liście powiązanej**.

---

## 📋 Spis Treści
* [Opis Projektu](#-opis-projektu)
* [Struktura Kodu](#-struktura-kodu)
* [Wymagania systemowe](#-wymagania-systemowe)
* [Kompilacja i Uruchomienie](#-kompilacja-i-uruchomienie)
* [Analiza Złożoności i Wydajności](#-analiza-złożoności-i-wydajności)
* [Autor](#-autor)

---

## 🚀 Opis Projektu

Program wykonuje następujące operacje dla $N = 50\,000$ losowych liczb całkowitych:
1. Alokuje pamięć dla tablicy dynamicznej oraz buduje dwukierunkową listę powiązaną (dodając elementy na początek).
2. Mierzy czas sortowania **tablicy** algorytmem Selection Sort (porządek malejący).
3. Mierzy czas sortowania **listy dwukierunkowej** poprzez bezpośrednią manipulację wskaźnikami (`next` i `prev`), co pozwala uniknąć kosztownego kopiowania danych.
4. Wyświetla wyniki czasowe oraz największą wylosowaną liczbę.
5. Poprawnie zwalnia całą zaalokowaną pamięć dynamiczną (`delete[]` oraz usuwanie węzłów listy).

---

## 🛠️ Struktura Kodu

* `struct lista2` – Definicja węzła listy dwukierunkowej (`liczba`, wskaźnik `next`, wskaźnik `prev`).
* `void dodajNaPoczatek(...)` – Dodaje nowy element na początek listy dwukierunkowej.
* `void sortujListe2(...)` – Sortuje listę dwukierunkową przez przestawianie wskaźników węzłów (obsługuje m.in. przypadki sąsiadujących elementów oraz ogólne zamiany).
* `void sortujTablice(...)` – Klasyczne sortowanie tablicy przez wybór (Selection Sort).
* `void zwolnijPamiec(...)` – Zapobiega wyciekom pamięci usuwając elementy listy.
* `int main()` – Inicjalizuje generator liczb pseudolosowych, wypełnia struktury, mierzy czasy wykonania przy użyciu `<ctime>` i wypisuje raport.

---

## 💻 Wymagania systemowe

Do skompilowania i uruchomienia projektu potrzebujesz:
* Kompilatora C++ obsługującego standard **C++11** lub nowszy (np. `g++`, `clang++`, MSVC).
* Systemu operacyjnego Windows, Linux lub macOS.

---

## ⚙️ Kompilacja i Uruchomienie

### Za pomocą g++ (Linux / MinGW na Windows):
Otwórz terminal w folderze z plikiem źródłowym (np. `main.cpp`) i wykonaj polecenia:

```bash
# Kompilacja
g++ main.cpp -O3 -o test_wydajnosci

# Uruchomienie
./test_wydajnosci
