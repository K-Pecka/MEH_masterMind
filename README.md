# MasterMind z różnymi algorytmami metaheurystycznymi

## Przegląd

Projekt ten implementuje grę MasterMind z różnymi podejściami do rozwiązywania przy użyciu algorytmów metaheurystycznych. Celem jest pokazanie, jak różne metaheurystyki mogą być stosowane do rozwiązywania problem optymalizacyjny "NP-complete".

## O grze MasterMind

[Mastermind](https://en.wikipedia.org/wiki/Mastermind_(board_game)) to gra łamania kodu, w której jeden gracz ustawia kod, a drugi gracz próbuje go odgadnąć w określonej liczbie prób. Kod składa się z sekwencji kolorów, a informacja zwrotna jest przekazywana w postaci liczby poprawnych kolorów na poprawnych pozycjach oraz liczby poprawnych kolorów na niepoprawnych pozycjach.

## Struktura Projektu

Projekt składa się z klas implementujących różne algorytmy metaheurystyczne poprzez polimorficzną funkcję `goal`. Główne klasy i ich funkcje to:

- `MasterMind`: Klasa bazowa definiująca interfejs dla gry MasterMind.
- `MasterMind_bruteForce`: Implementacja algorytmu pełnego przeglądu.
- `MasterMind_random`: Implementacja algorytmu losowego rozwiązania.
- `MasterMind_hillClimbing`: Implementacja algorytmu wspinaczkowego.
- `MasterMind_tabu`: Implementacja algorytmu Tabu Search.
- `MasterMind_annealing`: Implementacja algorytmu Wyżarzania.
- `MasterMind_genetic`: Implementacja algorytmu genetycznego.
  
## Parametry

Aplikacja obsługuje następujące parametry, które można określić podczas uruchamiania:

### Dla każdej metody

- **`-method`** lub **`-m`**: Określa metodę rozwiązania problemu.
  Przykład użycia: `-method (string)<metoda>` lub `-m (string)<metoda>`
  
- **`-length`** lub **`-l`**: Ustawia długość kodu, który ma zostać odgadnięty.
  Przykład użycia: `-length (int)<length>` lub `-l (int)<length>`
  
- **`-interaction`** lub **`-i`**: Określa maksymalną liczbę interakcji algorytmu.
  Przykład użycia: `-interaction (int)<ilość interacji>` lub `-i (int)<ilość interacji>`
  
- **`-colorPath`** lub **`-p`**: Ścieżka do pliku zawierającego informacje o kolorach.
  Przykład użycia: `-colorPath (string)<ścieżka do pliku>` lub `-p (string)<ścieżka do pliku>`
  
- **`-solutionPath`** lub **`-sp`**: Ścieżka do pliku zawierającego ustalone rozwiązanie problemu.
  Przykład użycia: `-solutionPath (string)<ścieżka do pliku>` lub `-sp (string)<ścieżka do pliku>`
  
- **`-communication`** lub **`-c`**: Włącza lub wyłącza komunikaty w aplikacji (tryb `dev`).
  Przykład użycia: `-communication (bool || int)<true / false || 0/1>` lub `-c (bool || int)<true / false || 0/1>`
  
- **`-test`** lub **`-t`**: Włącza tryb testowy prezentacji wyników.
  Przykład użycia: `-test (bool || int)<true / false || 0/1>` lub `-t (bool || int)<true / false || 0/1>`
  
### Dla Algorytmu wspinaczkowego

- **`-param deterministic`**: Ustawia typ algorytmu na deterministyczny; domyślnie algorytm jest losowy.

### Dla Algorytmu genetycznego

- **`-param`**: Ustawia parametry dotyczące warunków zakończenia, rodzaju krzyżowania oraz mutacji.
  - "swap" -> rodzaj mutacji
  - "double_point" -> rodzaj krzyżowania
  - "fitness" -> warunek zakończenia

  Przykład użycia: `-param <rodzaj_mutacji> <rodzaj_krzyżowania> <warunek_zakończenia>`.
  Kolejność nie ma znaczenia, nie są wymagane wszystkie parametry.

- **`-GA`**: Ustawia kolejno ilość generacji, wielkość populacji, wielkość elity, prawdopodobieństwo krzyżowania, prawdopodobieństwo mutacji.

  Przykład użycia: `-GA <ilość_generacji> <wielkość_populacji> <wielkość_elity> <prawdopodobieństwo_krzyżowania> <prawdopodobieństwo_mutacji>`.
  Kolejność ma znaczenie.
