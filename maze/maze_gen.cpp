/*
    Модуль генерации лабиринта

    Реализации методов
        Maze
            generate_random

    Вспомогательные функции
        random_binary(p) - бинарная случайная величина, вероятность p%
*/

#include <cstdlib>
#include "maze.h"

// бинарная случайная величина
//   1 - с вероятностью p%, 0 - с вероятностью (1-p)%
bool random_binary (int p)
{
    int random_value = rand();  // 0..RAND_MAX
    return (random_value < (double)RAND_MAX * p / 100);
}

// случайная генерация лабиринта
//   каждая стенка ставится с вероятностью prob процентов
//   srand() не вызывается
void Maze::generate_random (int prob)
{
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            // перечисляем все внутренние стенки:
            //   справа и снизу от клеточек (i, j), i=1..n-1, j=1..m-1
            //   справа от клеточек (i, j), i=n, j=1..m-1
            //   снизу от клеточек (i, j), i=1..n-1, j=m

            // с вероятностью prob% ставим стенку справа от клеточки (i, j)
            if (j < m && random_binary(prob))
                walls_v[i][j] = true;
            // с вероятностью prob% ставим стенку под клеточкой (i, j)
            if (i < n && random_binary(prob))
                walls_h[i][j] = true;
        }
    }
}
