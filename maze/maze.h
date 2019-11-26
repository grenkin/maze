#ifndef PRINT_MAZE_H_INCLUDED
#define PRINT_MAZE_H_INCLUDED

#include <vector>

// лабиринт со стенками
/*
    данные:
        n - число строк, m - число столбцов
        дополнительно
            0-я строка сверху, (n+1)-я строка снизу
            0-й столбец слева, (m+1)-й столбец справа
        walls_h - горизонтальные стенки
            walls_h[i][j] = true, если
                между i-й и (i+1)-й строками стенка в j-м столбце,
                i = 1..n-1, j = 1..m
            walls_v[i][j] = true, если
                между j-м и (j+1)-м столбцами стенка в i-й строке,
                i = 1..n, j = 1..m-1
        walls_v - вертикальные стенки
            walls_h[i][j] = true, если
                между i-й и (i+1)-й строками стенка в j-м столбце,
                i = 1..n-1, j = 1..m
            walls_v[i][j] = true, если
                между j-м и (j+1)-м столбцами стенка в i-й строке,
                i = 1..n, j = 1..m-1
    операции:
        конструктор (n - число строк, m - число столбцов)
*/
struct Maze {
    // n - число строк, m - число столбцов
    int n, m;
    std::vector<std::vector<bool> > walls_h, walls_v;
      // walls_h : [1..n-1, 1..m]Bool
      // walls_v : [1..n, 1..m-1]Bool

    // конструктор класса Maze
    // создает лабиринт n x m без стенок
    Maze (int n_arg, int m_arg)
        : n(n_arg), m(m_arg)
    {
        walls_h.resize(n);
        for (int i = 1; i <= n - 1; ++i)
            walls_h[i].resize(m + 1);
        walls_v.resize(n + 1);
        for (int i = 1; i <= n; ++i)
            walls_v[i].resize(m);
    }

    // вывести лабиринт на экран
    void print ();
};

#endif // PRINT_MAZE_H_INCLUDED
