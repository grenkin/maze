#ifndef PRINT_MAZE_H_INCLUDED
#define PRINT_MAZE_H_INCLUDED

#include <vector>

// лабиринт со стенками
/*
    данные:
        n - число строк, m - число столбцов
        строки лабиринта: i = 1..n
        столбцы лабиринта: j = 1..m
        дополнительно
            0-я строка сверху, (n+1)-я строка снизу
            0-й столбец слева, (m+1)-й столбец справа
        walls_h - горизонтальные стенки
            walls_h[i][j] = true, если
                между i-й и (i+1)-й строками стенка в j-м столбце,
                i = 0..n, j = 0..m
        walls_v - вертикальные стенки
            walls_v[i][j] = true, если
                между j-м и (j+1)-м столбцами стенка в i-й строке,
                i = 0..n, j = 0..m
    операции:
        конструктор (n - число строк, m - число столбцов)
*/
struct Maze {
    // n - число строк, m - число столбцов
    int n, m;
    std::vector<std::vector<bool> > walls_h, walls_v;
      // walls_h : [0..n, 0..m]Bool
      // walls_v : [0..n, 0..m]Bool

    // конструктор класса Maze
    // создает лабиринт n x m со стенками по краям
    Maze (int n_arg, int m_arg)
        : n(n_arg), m(m_arg)
    {
        walls_h.resize(n + 1);  // walls_h[0..n]
        for (int i = 0; i <= n; ++i)
            walls_h[i].resize(m + 1);  // walls_h[i][0..m]
        walls_v.resize(n + 1);  // walls_v[0..n]
        for (int i = 0; i <= n; ++i)
            walls_v[i].resize(m + 1);  // walls_v[i][0..m]

        /* добавляем стенки по краям лабиринта */
        // добавляем горизонтальные стенки после 0-й и n-й строки
        //   в столбцах j=1..m
        for (int i = 0; i <= n; i += n) {  // for i = {0, n}
            for (int j = 1; j <= m; ++j)
                walls_h[i][j] = true;
        }
        // добавляем вертикальные стенки после 0-го и m-го столбца
        //   в строках i=1..n
        for (int j = 0; j <= m; j += m) {  // for j = {0, m}
            for (int i = 1; i <= n; ++i)
                walls_v[i][j] = true;
        }
    }

    // вывести лабиринт на экран
    void print ();
};

#endif // PRINT_MAZE_H_INCLUDED
