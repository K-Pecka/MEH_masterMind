# MasterMind z różnymi algorytmami metaheurystycznymi

## Przegląd

Projekt ten implementuje grę MasterMind z różnymi podejściami do rozwiązywania przy użyciu algorytmów metaheurystycznych. Celem jest pokazanie, jak różne metaheurystyki mogą być stosowane do rozwiązywania problem optymalizacyjny "NP-complete".

## O grze MasterMind

[Mastermind](https://en.wikipedia.org/wiki/Mastermind_(board_game)) to gra łamania kodu, w której jeden gracz ustawia kod, a drugi gracz próbuje go odgadnąć w określonej liczbie prób. Kod składa się z sekwencji kolorów, a informacja zwrotna jest przekazywana w postaci liczby poprawnych kolorów na poprawnych pozycjach oraz liczby poprawnych kolorów na niepoprawnych pozycjach.

## Struktura Projektu

Projekt składa się z klas implementujących różne algorytmy metaheurystyczne poprzez polimorficzną funkcję `goal`. Główne klasy i ich funkcje to:

- `MasterMind`: Klasa bazowa definiująca interfejs dla gry MasterMind.
- `MasterMind_BF`: Implementacja algorytmu pełnego przeglądu.
- `MasterMind_random`: Implementacja algorytmu losowego rozwiązania.
- `MasterMind_hillClimbing`: Implementacja algorytmu wspinaczkowego.
- `MasterMind_tabu`: Implementacja algorytmu Tabu Search.

## Parametry

Aplikacja obsługuje następujące parametry, które można określić podczas uruchamiania:

- **`-method`** lub **`-m`**: Określa metodę rozwiązania problemu.
- **`-param`**: Określa dodatkowe parametry używane w algorytmach metaheurystycznych, takie jak w np. wspinaczkowym `random` lub `deterministic` określające typ podejścia do algorytmu.
- **`-length`** lub **`-l`**: Ustawia długość kodu, który ma zostać odgadnięty.
- **`-interaction` lub **`-i`**: Określa maksymalną liczbę interakcji algorytmu.
- **`-path`** lub **`-p`**: Ścieżka do pliku zawierającego informacje o kolorach.
- **`-communication`** lub **`-c`**: Włącza lub wyłącza komunikaty w aplikacji <tryb dev>.

Domyślne wartości parametrów: `length=10`, `interaction=100`, `path=../data/color.txt`, `communication=false`.
