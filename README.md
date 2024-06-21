# MasterMind z różnymi algorytmami metaheurystycznymi

## Przegląd

Projekt ten implementuje grę MasterMind z różnymi podejściami do rozwiązywania przy użyciu algorytmów metaheurystycznych. Celem jest pokazanie, jak różne metaheurystyki mogą być stosowane do rozwiązywania problem optymalizacyjny "NP-complete".

## O grze MasterMind

MasterMind to gra łamania kodu, w której jeden gracz ustawia kod, a drugi gracz próbuje go odgadnąć w określonej liczbie prób. Kod składa się z sekwencji kolorów, a informacja zwrotna jest przekazywana w postaci liczby poprawnych kolorów na poprawnych pozycjach oraz liczby poprawnych kolorów na niepoprawnych pozycjach.

## Struktura Projektu

Projekt składa się z klas implementujących różne algorytmy metaheurystyczne poprzez polimorficzną funkcję `goal`. Główne klasy i ich funkcje to:

- `MasterMind`: Klasa bazowa definiująca interfejs dla gry MasterMind.
- `MasterMind_BF`: Implementacja algorytmu pełnego przeglądu.
- `MasterMind_random`: Implementacja algorytmu losowego rozwiązania.
- `MasterMind_hillClimbing`: Implementacja algorytmu wspinaczkowego.
- `MasterMind_tabu`: Implementacja algorytmu Tabu Search.
