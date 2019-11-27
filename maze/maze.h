#ifndef PRINT_MAZE_H_INCLUDED
#define PRINT_MAZE_H_INCLUDED

#include <vector>
#include "console.h"

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
                i = 0..n+1, j = 0..m+1
        walls_v - вертикальные стенки
            walls_v[i][j] = true, если
                между j-м и (j+1)-м столбцами стенка в i-й строке,
                i = 0..n+1, j = 0..m+1
    операции:
        конструктор (n - число строк, m - число столбцов)
        случайная генерация лабиринта (стенки ставятся с вероятностью prob%)
        поиск случайного пути из пункта a в пункт b
        поиск кратчайшего пути из пункта a в пункт b
        вывод лабиринта на экран
        вывод пути в лабиринте на экран
*/
struct Maze {
    // n - число строк, m - число столбцов
    int n, m;
    std::vector<std::vector<bool> > walls_h, walls_v;
      // walls_h : [0..n+1, 0..m+1]Bool
      // walls_v : [0..n+1, 0..m+1]Bool

    // клеточка лабиринта
    struct Point {
        int i, j;
        bool operator== (Point q) { return this->i == q.i && this->j == q.j; }
        bool operator!= (Point q) { return !(*this == q); }
    };
    // путь в лабиринте
    typedef std::vector<Point> Path;

    // направления движения
    enum Dir {
        DIR_LEFT, DIR_RIGHT, DIR_UP, DIR_DOWN
    };
    static const int num_dir = 4;  // количество направлений
    const Dir dir_values[num_dir] = {DIR_LEFT, DIR_RIGHT, DIR_UP, DIR_DOWN};
    const int di[num_dir] = {0, 0, -1, 1};
    const int dj[num_dir] = {-1, 1, 0, 0};

    // конструктор класса Maze
    // создает лабиринт n x m со стенками по краям
    Maze (int n_arg, int m_arg)
        : n(n_arg), m(m_arg)
    {
        walls_h.resize(n + 2);  // walls_h[0..n+1]
        for (int i = 0; i <= n + 1; ++i)
            walls_h[i].resize(m + 2);  // walls_h[i][0..m+1]
        walls_v.resize(n + 2);  // walls_v[0..n+1]
        for (int i = 0; i <= n + 1; ++i)
            walls_v[i].resize(m + 2);  // walls_v[i][0..m+1]

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

    // случайная генерация лабиринта
    //   каждая стенка ставится с вероятностью prob процентов
    //   srand() не вызывается
    void generate_random (int prob);

    // принадлежит ли пункт лабиринту
    bool in_maze (Point p);

    // можно ли пройти из пункта p в направлении dir
    bool can_go (Point p, Dir dir);

    // пройти из пункта p в направлении dir
    Point move_dir (Point p, Dir dir);

    // найти случайный путь в лабиринте из пункта a в пункт b
    //   path[0..n]:  path[0] = a, path[n] = b
    Path find_random_path (Point a, Point b);

    // найти кратчайший путь в лабиринте из пункта a в пункт b
    //   path[0..n]:  path[0] = a, path[n] = b
    Path find_shortest_path (Point a, Point b);

    // вывести лабиринт на экран
    // c - текущее местоположение
    void print (Point c = {0, 0});

    // вывести путь в лабиринте на экран с паузами delay_ms мс
    void animate_path (Path path, int delay_ms);
};

#endif // PRINT_MAZE_H_INCLUDED
